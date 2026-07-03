import math
import numpy as np
import matplotlib.pyplot as plt
from concurrent.futures import ProcessPoolExecutor
from neuron import h

# --- Worker Function for Parallelization ---
def run_vclamp_sweep(v_step):
    """
    Runs a single voltage clamp step simulation and returns the max/min 
    current values for all calcium channels.
    """
    # Load core NEURON libraries inside the worker process
    h.load_file('stdrun.hoc')
    
    # 1. Recreate the cell geometry and mechanisms 
    s_diam, s_l, s_nseg = 16, 16, 1
    pdend_nseg, pdend_diam, pdend_l = 1, 2.25, 20
    sdend_nseg, sdend_diam, sdend_l = 1, 1.1, 24.23
    tdend_nseg, tdend_diam, tdend_l = 11, 0.72, 395.2
    
    e_pas, e_na, e_k = -70.0, 50.0, -90

    soma_mechanisms = {
        'pas': {'g_pas': 11.5e-6}, 'naf': {'gbar_naf': 1.5}, 'nap': {'gbar_nap': 4.0e-5},
        'kaf': {'gbar_kaf': 0.225}, 'kas': {'gbar_kas': 0.0104},
        'kir': {'gbar_kir': 1.4e-4}, 'krp': {'gbar_krp': 0.001},
        'cal12': {'pbar_cal12': 6.7e-6}, 'cal13': {'pbar_cal13': 4.25e-7},
        'can': {'pbar_can': 1.0e-5}, 'car': {'pbar_car': 2.6e-5}, 'caq': {'pbar_caq': 6.0e-6},
        'cat': {'pbar_cat': 4.0e-7}, 'bkkca': {'gkbar_bkkca': 0.001}, 'skkca': {'gkbar_skkca': 0.145}
    }
    
    def insert_mechanisms(sec, mech_dict):
        sec.Ra = 100       
        sec.cm = 1.0   
        for mechanism, parameters in mech_dict.items():
            sec.insert(mechanism)
            for param_name, param_value in parameters.items():
                setattr(sec, param_name, param_value)
        sec.e_pas = e_pas
        sec.ena = e_na
        sec.ek = e_k
        return sec

    soma = h.Section(name='soma')
    soma.nseg = int(s_nseg)
    soma.diam = s_diam
    soma.L = s_l
    insert_mechanisms(soma, soma_mechanisms)

    # 2. Setup Voltage Clamp at the Soma
    vclamp = h.VClamp(soma(0.5))
    vclamp.dur[0] = 50.0   # Holding period (ms)
    vclamp.amp[0] = -87.75 # Holding potential (mV)
    vclamp.dur[1] = 200.0  # Step period (ms)
    vclamp.amp[1] = v_step # Step potential (mV)
    vclamp.dur[2] = 50.0   # Return period (ms)
    vclamp.amp[2] = -87.75 # Return potential (mV)

    # 3. Setup Recording vector for Total Calcium Current
    # Since individual channels are hidden but write to ca_ion, we track total ica
    ca_vector = h.Vector().record(soma(0.5)._ref_ica)
    t_vec = h.Vector().record(h._ref_t)

    # 4. Run Simulation
    h.finitialize(-87.75)   
    h.tstop = 300
    h.run()

    # 5. Extract peak total calcium current during the step window
    t_arr = np.array(t_vec)
    step_indices = np.where((t_arr >= 55.0) & (t_arr <= 245.0))[0]
    
    result = {'v': v_step}
    current_data = np.array(ca_vector)
    step_currents = current_data[step_indices]
    
    if len(step_currents) > 0:
        # Inward calcium current is negative; find max absolute deviation
        if np.abs(np.min(step_currents)) > np.abs(np.max(step_currents)):
            peak_current = np.min(step_currents)
        else:
            peak_current = np.max(step_currents)
    else:
        peak_current = 0.0
        
    result['total_ca'] = peak_current
    return result


# --- Main Block ---
if __name__ == '__main__':
    # Define voltage command steps (from -90mV to +60mV in 5mV increments)
    voltages = np.arange(-90, 61, 5)
    
    print(f"Starting parallel VClamp simulation across {len(voltages)} steps...")
    
    # ProcessPoolExecutor manages independent Python instances to bypass GIL
    results = []
    with ProcessPoolExecutor() as executor:
        results = list(executor.map(run_vclamp_sweep, voltages))
        
    # Sort results back by voltage order
    results = sorted(results, key=lambda x: x['v'])
    
    # Organize data for plotting
    v_axis = [r['v'] for r in results]
    total_ca_current = [r['total_ca'] for r in results]

    # Plotting the Total Calcium IV curve
    plt.figure(figsize=(10, 6))
    plt.plot(v_axis, total_ca_current, marker='o', color='crimson', label='Total $I_{Ca}$')
        
    plt.xlabel('Command Potential (mV)')
    plt.ylabel('Peak Current ($mA/cm^2$)')
    plt.title('Total Calcium Current I-V Curve (Soma Voltage Clamp)')
    plt.axhline(0, color='gray', linestyle='--', alpha=0.5)
    plt.axvline(-70, color='gray', linestyle=':', alpha=0.5, label='Resting Vm')
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend()
    plt.show()