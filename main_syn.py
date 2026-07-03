from neuron import h
import matplotlib.pyplot as plt
import math
import random

h.load_file('stdrun.hoc')

# ==========================================================
# 1. MORPHOLOGY
# ==========================================================
s_diam, s_l, s_nseg = 16, 16, 1
pdend_nseg, pdend_diam, pdend_l = 1, 2.25, 20.0     # F = 0
sdend_nseg, sdend_diam, sdend_l = 1, 1.1, 24.23     # F = 1.33, adjusted for spines
tdend_nseg, tdend_diam, tdend_l = 11, 0.72, 395.2   # F = 3.0, adjusted for spines

# ==========================================================
# 2. MECHANISMS (Table 2 )
# ==========================================================
soma_mechanisms = {
    'pas': {'g_pas': 11.5e-6}, 'naf': {'gbar_naf': 1.5}, 'nap': {'gbar_nap': 4.0e-5},
    'kaf': {'gbar_kaf': 0.225}, 'kas': {'gbar_kas': 0.0104}, 'kir': {'gbar_kir': 1.4e-4},
    'krp': {'gbar_krp': 0.001}, 'cal12': {'pbar_cal12': 6.7e-6}, 'cal13': {'pbar_cal13': 4.25e-7},
    'can': {'pbar_can': 1.0e-5}, 'car': {'pbar_car': 2.6e-5}, 'caq': {'pbar_caq': 6.0e-6},
    'cat': {'pbar_cat': 4.0e-7}, 'bkkca': {'gkbar_bkkca': 0.001}, 'skkca': {'gkbar_skkca': 0.145}
}

dend_mechanisms = {
    'pas': {'g_pas': 11.5e-6}, 'naf': {'gbar_naf': 0.0195}, 'nap': {'gbar_nap': 1.38e-7},
    'kaf': {'gbar_kaf': 0.021}, 'kas': {'gbar_kas': 9.51e-4}, 'kir': {'gbar_kir': 1.4e-4},
    'bkkca': {'gkbar_bkkca': 0.001}, 'skkca': {'gkbar_skkca': 0.145},
    'cal12': {'pbar_cal12': 6.7e-6}, 'cal13': {'pbar_cal13': 4.25e-7},
    'can': {'pbar_can': 1.0e-5}, 'car': {'pbar_car': 2.6e-5},
    'caq': {'pbar_caq': 6.0e-6}, 'cat': {'pbar_cat': 4.0e-7},
    'cadyn': {'pump_cadyn': 0.02, 'taur_cadyn': 43.0, 'drive_cadyn': 1000.0} # Original Paper cadyn
}

def insert_mechanisms(sec, mech_dict):
    sec.Ra = 100        
    sec.cm = 1.0  # Constant standard capacitance across stretched geometry
    for mechanism, parameters in mech_dict.items():
        sec.insert(mechanism)
        for param_name, param_value in parameters.items():
            setattr(sec, param_name, param_value)
    sec.e_pas = -70.0
    sec.ena = 50.0
    sec.ek = -90
    return sec

# Sections
soma = h.Section(name='soma')
soma.nseg, soma.diam, soma.L = s_nseg, s_diam, s_l
insert_mechanisms(soma, soma_mechanisms)

prim_dend, sec_dend, tert_dend = [], [], []
for i in range(4):
    prim_dend.append(insert_mechanisms(h.Section(name=f'prim_{i}'), dend_mechanisms))
    prim_dend[i].nseg, prim_dend[i].diam, prim_dend[i].L = pdend_nseg, pdend_diam, pdend_l
    prim_dend[i].connect(soma(0.5), 0)

for i in range(8):
    sec_dend.append(insert_mechanisms(h.Section(name=f'sec_{i}'), dend_mechanisms))
    sec_dend[i].nseg, sec_dend[i].diam, sec_dend[i].L = sdend_nseg, sdend_diam, sdend_l
    sec_dend[i].connect(prim_dend[math.floor(i // 2)](1), 0)

for i in range(16):
    tert_dend.append(insert_mechanisms(h.Section(name=f'tert_{i}'), dend_mechanisms))
    tert_dend[i].nseg, tert_dend[i].diam, tert_dend[i].L = tdend_nseg, tdend_diam, tdend_l
    tert_dend[i].connect(sec_dend[math.floor(i // 2)](1), 0)

# ==========================================================
# 3. SYNAPTIC DISTRIBUTION 
# ==========================================================
syn_objects = []
netstims = []
netcons = []

def attach_synapse(seg, syn_type, start_time, duration, initial_rate, up_state_rate):
    
    # 1. Instantiate your custom point processes
    if syn_type == 'AMPA':
        syn = h.AMPA(seg)
    elif syn_type == 'NMDA':
        syn = h.NMDA(seg)
    elif syn_type == 'GABA':
        syn = h.GABA(seg)

    syn_objects.append(syn)
    
    stim_base = h.NetStim()
    stim_base.interval = 1000.0 / initial_rate  # 3.0 Hz 
    stim_base.number = int(duration * initial_rate / 1000.0)
    stim_base.start = start_time
    stim_base.noise = 1.0 
    netstims.append(stim_base)
    
    nc_base = h.NetCon(stim_base, syn)
    nc_base.weight[0] = 1.0  
    nc_base.delay = 0.1
    netcons.append(nc_base)
    
    stim_up = h.NetStim()
    stim_up.interval = 1000.0 / (up_state_rate - initial_rate)  # Step up to 7.5 Hz 
    stim_up.number = int(500 * (up_state_rate - initial_rate) / 1000.0)
    stim_up.start = 100.0  
    stim_up.noise = 1.0 
    netstims.append(stim_up)
    
    nc_up = h.NetCon(stim_up, syn)
    nc_up.weight[0] = 1.0
    nc_up.delay = 0.1
    netcons.append(nc_up)

# Revert frequencies back to the exact paper baseline values
base_rate = 3.0  # Hz 
up_rate = 7.5    # Hz 

# Populate synapses across the morphology exactly as defined by paper text splits
for i in range(16): 
    attach_synapse(soma((i+0.5)/16), 'GABA', 0, 700, base_rate, up_rate)

for branch in prim_dend:
    attach_synapse(branch(0.5), 'AMPA', 0, 700, base_rate, up_rate)
    attach_synapse(branch(0.5), 'NMDA', 0, 700, base_rate, up_rate)
    for loc in [0.25, 0.5, 0.75]: attach_synapse(branch(loc), 'GABA', 0, 700, base_rate, up_rate)

for branch in sec_dend:
    for loc in [0.33, 0.66]:
        attach_synapse(branch(loc), 'AMPA', 0, 700, base_rate, up_rate)
        attach_synapse(branch(loc), 'NMDA', 0, 700, base_rate, up_rate)
    for loc in [0.25, 0.5, 0.75]: attach_synapse(branch(loc), 'GABA', 0, 700, base_rate, up_rate)

for branch in tert_dend:
    for loc in [0.2, 0.4, 0.6, 0.8]:
        attach_synapse(branch(loc), 'AMPA', 0, 700, base_rate, up_rate)
        attach_synapse(branch(loc), 'NMDA', 0, 700, base_rate, up_rate)
    for loc in [0.33, 0.66]: attach_synapse(branch(loc), 'GABA', 0, 700, base_rate, up_rate)


v_vec = h.Vector().record(soma(0.5)._ref_v)
t_vec = h.Vector().record(h._ref_t)

h.finitialize(-87.75)  # Rest at paper standard baseline 
h.tstop = 700
h.continuerun(700)

# Plotting state transitions
plt.figure(figsize=(10, 5))
plt.plot(t_vec, v_vec, color='black', linewidth=1.2, label='Somatic Membrane Potential')
plt.axvspan(100, 600, color='red', alpha=0.05, label='High Frequency Coordinated Volley')
plt.xlabel('Time (ms)')
plt.ylabel('Voltage (mV)')
plt.title('Nucleus Accumbens MSN Synaptically Driven Up-State Firing')
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend()
plt.show()