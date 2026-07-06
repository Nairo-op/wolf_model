from neuron import h
import matplotlib.pyplot as plt
import math

h.load_file('stdrun.hoc')
h.celsius = 35.0

# Set SK affinity to corrected micromolar parameters globally
h.k1_skkca = 0.48e-3  # 0.48 uM
h.k2_skkca = 0.13e-3  # 0.13 uM

# Morphological & Passive Constants
s_diam, s_l, s_nseg = 16, 16, 1
pdend_nseg, pdend_diam, pdend_l = 1, 2.25, 20
sdend_nseg, sdend_diam, sdend_l = 1, 1.1, 24.23
tdend_nseg, tdend_diam, tdend_l = 11, 0.72, 395.2

e_pas = -70.0  
e_na = 50.0    
e_k = -90      
e_ca = 120     

# 1. Fixed Parameter Dictionaries (Added the correct paper parameters for the pools)
soma_mechanisms = {
    'pas': {'g_pas': 11.5e-6}, 'naf': {'gbar_naf': 1.5}, 'nap': {'gbar_nap': 4.0e-5},
    'kaf': {'gbar_kaf': 0.225}, 'kas': {'gbar_kas': 0.0104},
    'kir': {'gbar_kir': 1.4e-4}, 'krp': {'gbar_krp': 0.001},
    'cal12': {'pbar_cal12': 6.7e-6}, 'cal13': {'pbar_cal13': 4.25e-7},
    'can': {'pbar_can': 1.0e-5}, 'car': {'pbar_car': 2.6e-5}, 'caq': {'pbar_caq': 6.0e-6},
    'cat': {'pbar_cat': 4.0e-7},
    'bkkca': {'gkbar_bkkca': 0.001},
    'skkca': {'gkbar_skkca': 0.145},
    'cadyn_lt': {'drive_cadyn_lt': 10000, 'pump_cadyn_lt': 0.02, 'F_cadyn_lt': 1.0}, 
    'cadyn_nqr': {'drive_cadyn_nqr': 10000, 'pump_cadyn_nqr': 0.02, 'F_cadyn_nqr': 1.0},
}

pdend_mechanisms = {
    'pas': {'g_pas': 11.5e-6}, 'naf': {'gbar_naf': 0.0195}, 'nap': {'gbar_nap': 1.38e-7},
    'kaf': {'gbar_kaf': 0.225}, 'kas': {'gbar_kas': 0.0104}, 'kir': {'gbar_kir': 1.4e-4},
    'bkkca': {'gkbar_bkkca': 0.001}, 'skkca': {'gkbar_skkca': 0.145},
    'cal12': {'pbar_cal12': 6.7e-6}, 'cal13': {'pbar_cal13': 4.25e-7},
    'can': {'pbar_can': 1.0e-5}, 'car': {'pbar_car': 2.6e-5},
    'caq': {'pbar_caq': 6.0e-6}, 'cat': {'pbar_cat': 4.0e-7},
    'cadyn_lt': {'drive_cadyn_lt': 10000, 'pump_cadyn_lt': 0.02, 'F_cadyn_lt': 1.0},
    'cadyn_nqr': {'drive_cadyn_nqr': 10000, 'pump_cadyn_nqr': 0.02, 'F_cadyn_nqr': 1.0}
}

sdend_mechanisms = {
    'pas': {'g_pas': 11.5e-6}, 'naf': {'gbar_naf': 0.0195}, 'nap': {'gbar_nap': 1.38e-7},
    'kir': {'gbar_kir': 1.4e-4}, 'kaf': {'gbar_kaf': 0.021}, 'kas': {'gbar_kas': 9.51e-4}, 
    'bkkca': {'gkbar_bkkca': 0.001}, 'skkca': {'gkbar_skkca': 0.145},
    'cal12': {'pbar_cal12': 6.7e-6}, 'cal13': {'pbar_cal13': 4.25e-7},
    'can': {'pbar_can': 1.0e-5}, 'car': {'pbar_car': 2.6e-5},
    'caq': {'pbar_caq': 6.0e-6}, 'cat': {'pbar_cat': 4.0e-7},
    'cadyn_nqr': {'drive_cadyn_nqr': 10000, 'pump_cadyn_nqr': 0.02, 'F_cadyn_nqr': 1.33},
    'cadyn_lt': {'drive_cadyn_lt': 10000, 'pump_cadyn_lt': 0.02, 'F_cadyn_lt': 1.33}  
}

tdend_mechanisms = {
    'pas': {'g_pas': 11.5e-6}, 'naf': {'gbar_naf': 0.0195}, 'nap': {'gbar_nap': 1.38e-7},
    'kir': {'gbar_kir': 1.4e-4}, 'kaf': {'gbar_kaf': 0.021}, 'kas': {'gbar_kas': 9.51e-4}, 
    'bkkca': {'gkbar_bkkca': 0.001}, 'skkca': {'gkbar_skkca': 0.145},
    'cal12': {'pbar_cal12': 6.7e-6}, 'cal13': {'pbar_cal13': 4.25e-7},
    'can': {'pbar_can': 1.0e-5}, 'car': {'pbar_car': 2.6e-5},
    'caq': {'pbar_caq': 6.0e-6}, 'cat': {'pbar_cat': 4.0e-7},
    'cadyn_nqr': {'drive_cadyn_nqr': 10000, 'pump_cadyn_nqr': 0.02, 'F_cadyn_nqr': 3.0},
    'cadyn_lt': {'drive_cadyn_lt': 10000, 'pump_cadyn_lt': 0.02, 'F_cadyn_lt': 3.0}
}

for mech_dict in [soma_mechanisms, pdend_mechanisms, sdend_mechanisms, tdend_mechanisms]:
    mech_dict['skkca']['gkbar_skkca'] = 0.0145

# 2. Fixed Function: Safely inserts and handles range variables per segment
def insert_mechanisms(sec, mech_dict):
    sec.Ra = 100       
    sec.cm = 1.0   
    for mechanism, parameters in mech_dict.items():
        sec.insert(mechanism)
        for param_name, param_value in parameters.items():
            for seg in sec:
                setattr(seg, param_name, param_value)
    
    sec.e_pas = e_pas
    sec.ena = e_na
    sec.ek = e_k
    sec.eca = e_ca
    if hasattr(sec(0.5), 'ecl'):
        sec.ecl = e_ca
    return sec

def create_soma():
    soma = h.Section(name='soma')
    soma.nseg = int(s_nseg)
    soma.diam = s_diam
    soma.L = s_l
    return insert_mechanisms(soma, soma_mechanisms)

def create_dendrite(name_str, nseg, diam, l, mech_dict):
    dend = h.Section(name=name_str)
    dend.nseg = int(nseg)
    dend.diam = diam
    dend.L = l
    return insert_mechanisms(dend, mech_dict)

def create_all_dendrite_br2(soma_ref):
    pdend, sdend, tdend = [], [], []
    # Primary
    for i in range(4):
        pdend.append(create_dendrite(f'prim_{i}', pdend_nseg, pdend_diam, pdend_l, pdend_mechanisms ))        
        if i < 3:
            pdend[i].connect(soma_ref(1), 0)  
        else:
            pdend[i].connect(soma_ref(0), 0)  
    # Secondary
    for i in range(8):
        sdend.append(create_dendrite(f'sec_{i}', sdend_nseg, sdend_diam, sdend_l, sdend_mechanisms,))
        pdend_index = math.floor(i // 2) 
        sdend[i].connect(pdend[pdend_index](1), 0)
    # Tertiary
    for i in range(16):
        tdend.append(create_dendrite(f'tert_{i}', tdend_nseg, tdend_diam, tdend_l, tdend_mechanisms))
        sdend_index = math.floor(i // 2)
        tdend[i].connect(sdend[sdend_index](1), 0)
    return pdend, sdend, tdend

# Initialize cell
soma = create_soma()
prim_dend, sec_dend, tert_dend = create_all_dendrite_br2(soma)

stim = h.IClamp(soma(0.5))
stim.delay = 100   # ms
stim.dur = 500     # ms
stim.amp = 0.260   # nA

# Setup Recording Vectors
v_vec = h.Vector().record(soma(0.5)._ref_v)
t_vec = h.Vector().record(h._ref_t)
cai_vec = h.Vector().record(soma(0.5)._ref_cai)
cli_vec = h.Vector().record(soma(0.5)._ref_cli)

# State Initialization 
h.finitialize(-87.75)   
h.celsius = 35.0 
h.tstop = 700

# 3. Fixed Mechanism Introspection Layout
print("--- Checking Segment Attributes ---")
print("Has cadyn_lt:", hasattr(soma(0.5), 'cadyn_lt'))   # Returns True
print("Has cadyn_nqr:", hasattr(soma(0.5), 'cadyn_nqr')) # Returns True

print("\n--- Listing Mechanisms in Segment ---")
for mech in soma(0.5):
    print(mech.name())

h.continuerun(700)

print("\n--- Final States ---")
print("Initial/Final cai:", soma(0.5).cai)  
print("Initial/Final cli:", soma(0.5).cli)  

# Plotting
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

ax1.plot(t_vec, v_vec, color='black', linewidth=1.5, label='Soma Voltage')
ax1.set_ylabel('Voltage (mV)')
ax1.set_title(f'Nucleus Accumbens MSN current clamp {stim.amp} nA')
ax1.axvspan(stim.delay, stim.delay + stim.dur, color='red', alpha=0.05, label='Injection Window')
ax1.grid(True, linestyle='--', alpha=0.6)
ax1.legend()

ax2.plot(t_vec, cai_vec, color='blue', linewidth=1.5, label='Internal Ca (cai - NQR Pool)')
ax2.plot(t_vec, cli_vec, color='darkorange', linewidth=1.5, label='Internal Cl (cli - LT Pool)')
ax2.set_xlabel('Time (ms)')
ax2.set_ylabel('Concentration (mM)')
ax2.grid(True, linestyle='--', alpha=0.6)
ax2.legend()

plt.tight_layout()
plt.show()