from neuron import h
import matplotlib.pyplot as plt
import math


h.load_file('stdrun.hoc')
h.load_file('nrngui.hoc')
h.celsius = 35.0


# Soma
s_diam = 16 
s_l = 16 
s_nseg = 1
s_cm = 1 
s_ra = 100 

# Primary dendrite (Spine Factor F = 1.0)
pdend_n = 1
pdend_d = 2.25
pdend_l = 20 
pdend_F = 1.0

# Secondary Dendrite (Spine Factor F = 1.33)
sdend_F = 1.33

sdend_n = 1
true_sdend_d = 1.0   # True diameter
true_sdend_l = 20.0     # True length

sdend_d = 1.1        # adjusted diameter
sdend_l = 24.23         # adjusted length

# Tertiary dendrite (Spine Factor F = 3.0)
tdend_F = 3.0

tdend_n = 11
true_tdend_d = 0.5   # True diameter
true_tdend_l = 190.0    # True length

tdend_d = 0.72       # adjusted diameter
tdend_l = 395.2         # adjusted length

e_pas = -70.0           # passive reversal potential (mV)
e_na = 50.0             # sodium reversal potential (mV)
e_k = -90               # potassium reversal potential (mV)
e_ca = 120              # calcium reversal potential (mV)



soma_mechanisms = {
    'pas': {'g_pas': 11.5e-6},
    'naf': {'gbar_naf': 1.5},
    'nap': {'gbar_nap': 4.0e-5},
    'kaf': {'gbar_kaf': 0.225},
    'kas': {'gbar_kas': 0.0104},
    'kir': {'gbar_kir': 1.4e-4},
    'krp': {'gbar_krp': 0.001},
    'cal12': {'pbar_cal12': 6.7e-6},
    'cal13': {'pbar_cal13': 4.25e-7},
    'can': {'pbar_can': 1.0e-5},
    'car': {'pbar_car': 2.6e-5},
    'caq': {'pbar_caq': 6.0e-6},
    'cat': {'pbar_cat': 4.0e-7},
    'bkkca': {'gkbar_bkkca': 0.001},
    'skkca': {'gkbar_skkca': 0.145},
    'cadyn_lt': {}, 
    'cadyn_nqr': {}
    }


pdend_mech = {
    'pas': {'g_pas': 11.5e-6}, 
    'naf': {'gbar_naf': 0.0195}, 
    'nap': {'gbar_nap': 1.3802e-7 },
    'kaf': {'gbar_kaf': .225 },
    'kas': {'gbar_kas': 0.0104 }, 
    'kir': {'gbar_kir': 1.4e-4},
    'bkkca': {'gkbar_bkkca': 0.001}, 
    'skkca': {'gkbar_skkca': 0.145},
    'cal12': {'pbar_cal12': 6.7e-6}, 
    'cal13': {'pbar_cal13': 4.25e-7},
    'can': {'pbar_can': 1.0e-5}, 
    'car': {'pbar_car': 2.6e-5},
    'caq': {'pbar_caq': 6.0e-6}, 
    'cat': {'pbar_cat': 4.0e-7},
    'cadyn_lt': {},
    'cadyn_nqr': {}

}


sdend_mech = {
    'pas': {'g_pas': 11.5e-6 }, 
    'naf': {'gbar_naf': 0.0195 }, 
    'nap': {'gbar_nap': 1.3802e-7 },
    'kaf': {'gbar_kaf': 0.020584 },
    'kas': {'gbar_kas': 0.00095142 },
    'kir': {'gbar_kir': 1.4e-4 }, 
    'bkkca': {'gkbar_bkkca': 0.001},
    'skkca': {'gkbar_skkca': 0.145},
    'cal12': {'pbar_cal12': 6.7e-6 }, 
    'cal13': {'pbar_cal13': 4.25e-7 },
    'can': {'pbar_can': 1.0e-5 }, 
    'car': {'pbar_car': 2.6e-5 },
    'caq': {'pbar_caq': 6.0e-6 },
    'cat': {'pbar_cat': 4.0e-7 },
    'cadyn_nqr': {},
    'cadyn_lt': {}  
}

tdend_mecha = {
    'pas': {'g_pas': 11.5e-6 }, 
    'naf': {'gbar_naf': 0.0195 }, 
    'nap': {'gbar_nap': 1.3802e-7 },
    'kaf': {'gbar_kaf': 0.020584 },
    'kas': {'gbar_kas': 0.00095142 },  
    'kir': {'gbar_kir': 1.4e-4 }, 
    'bkkca': {'gkbar_bkkca': 0.001}, 
    'skkca': {'gkbar_skkca': 0.145},
    'cal12': {'pbar_cal12': 6.7e-6 }, 
    'cal13': {'pbar_cal13': 4.25e-7 },
    'can': {'pbar_can': 1.0e-5 }, 
    'car': {'pbar_car': 2.6e-5 },
    'caq': {'pbar_caq': 6.0e-6 }, 
    'cat': {'pbar_cat': 4.0e-7 },
    'cadyn_nqr': {},
    'cadyn_lt': {}
}

"""for mech in [soma_mechanisms, pdend_mech]:
    mech['kaf']['gbar_kaf'] = 0.225/2
    mech['kas']['gbar_kas'] = 0.0104/2"""

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
    # no need to set e_ca here, as it is handled by NEURON
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
        pdend.append(create_dendrite(f'prim_{i}', pdend_n, pdend_d, pdend_l, pdend_mech ))        
        if i < 2:
            pdend[i].connect(soma_ref(1), 0)  
        else:
            pdend[i].connect(soma_ref(0), 0)  

    # Secondary
    for i in range(8):
        sdend.append(create_dendrite(f'sec_{i}', sdend_n, sdend_d, sdend_l, sdend_mech,))
        pdend_index = math.floor(i // 2) 
        sdend[i].connect(pdend[pdend_index](1), 0)
    
    # Tertiary
    for i in range(16):
        tdend.append(create_dendrite(f'tert_{i}', tdend_n, tdend_d, tdend_l, tdend_mecha))
        sdend_index = math.floor(i // 2)
        tdend[i].connect(sdend[sdend_index](1), 0)

    return pdend, sdend, tdend

# Initialize cell
soma = create_soma()
prim_dend, sec_dend, tert_dend = create_all_dendrite_br2(soma)

stim = h.IClamp(soma(0))
stim.delay = 200   # ms
stim.dur = 500     # ms
stim.amp = 0.248 # nA

# Setup Recording
v_vec = h.Vector().record(soma(0.5)._ref_v)
t_vec = h.Vector().record(h._ref_t)


h.cai0_ca_ion = 0.001
h.cao0_ca_ion = 5.0
h.cali0_cal_ion = 0.001
h.calo0_cal_ion = 5.0

# State Initialization 

h.finitialize(-87.75)   

h.tstop = 900

h.continuerun(900)

# Plotting
plt.figure(figsize=(10, 5))
plt.plot(t_vec, v_vec, color='black', linewidth=1.5, label='Full Cell Membrane Potential')
plt.xlabel('Time (ms)')
plt.ylabel('Voltage (mV)')
plt.title(f'Nucleus Accumbens MSN - soma current clamp amp: {stim.amp} nA for {stim.dur} ms')
plt.axvspan(stim.delay, stim.delay + stim.dur, color='red', alpha=0.05, label='Injection Window')
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.show()