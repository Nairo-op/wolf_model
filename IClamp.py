import numpy as np
import matplotlib.pyplot as plt
from neuron import h
import os
import sys
from imp_files.msn_class import MSNNeuron    
from imp_files.utilities import run_parallel_sweeps, load_mechanisms

"""
IClamp.py
=========

This script executes somatic current clamp (I-Clamp) protocols on the Striatal 
Medium Spiny Neuron (MSN) multicompartmental model. It performs parallel parameter 
sweeps for different current injection amplitudes to study the membrane response, 
action potential generation, and hyperpolarization-activated rectifying properties.

Physiological Rationale:
- MSN Resting Potential: MSNs are characterized by a highly hyperpolarized resting membrane 
  potential (around -85 mV to -90 mV), maintained by strong inwardly rectifying potassium 
  currents (Kir). The model is initialized at -87.75 mV to reflect this biological "down-state".
- Depolarizing Current Sweeps (+0.248 nA and +0.271 nA): These amplitudes are selected to 
  test the threshold of action potential generation. MSNs typically exhibit a late-firing 
  pattern (delayed excitation) due to the presence of slowly activating A-type K+ currents (KAs).
- Hyperpolarizing Current Sweep (-0.225 nA): Test current to observe the inwardly rectifying 
  potassium current (Kir) properties and membrane resistance.
- Injection Window: A 500 ms current pulse is injected starting at t = 200 ms. This allows 
  the model to equilibrate for 200 ms before stimulation, and then observe post-stimulus 
  decay/afterhyperpolarization up to t = 900 ms.

"""

def run_single_sweep(amp):
    """
    Executes a single current clamp simulation sweep for a given injection amplitude.
    This function is run inside separate CPU processes to prevent cross-talk in NEURON's global state.
    
    Parameters:
    - amp (float): Current injection amplitude in nanoamps (nA).
    
    Returns:
    - t_vec (ndarray): Vector of simulation time points (ms).
    - v_vec (ndarray): Vector of recorded somatic membrane potentials (mV).
    """
    # 1. Enforce headless mode before any NEURON imports inside the worker
    # This prevents NEURON from trying to open interactive X11 windows in subprocesses, 
    # ensuring stable parallel execution in non-interactive environments.
    os.environ["NEURON_MODULE_OPTIONS"] = "-nogui"
    
    h.load_file('stdrun.hoc')
    h.celsius = 35.0
    
    # Tighten time-step for clean action-potential upstrokes
    h.dt = 0.01
    h.steps_per_ms = 100
    
    # 2. Safely check and load compiled mechanisms if they aren't already auto-loaded
    load_mechanisms()
            
    # 3. Securely import your model and execute the current clamp protocol
    cell = MSNNeuron()
    soma = cell.soma
    
    stim = h.IClamp(soma(0.5))
    stim.delay = 200.0
    stim.dur = 500.0
    stim.amp = amp
    
    v_vec = h.Vector().record(soma(0.5)._ref_v)
    t_vec = h.Vector().record(h._ref_t)
    
    h.cai0_ca_ion = 0.001
    h.cao0_ca_ion = 5.0
    h.cali0_cal_ion = 0.001
    h.calo0_cal_ion = 5.0
    
    h.finitialize(-87.75)
    h.continuerun(900.0)
    
    return np.array(t_vec), np.array(v_vec)

def main():
    """
    Main execution loop. Sets up the parameter sweep amplitudes, triggers 
    the parallel runner, and plots the somatic voltage responses.
    """
    
    amps = [0.248, 0.271, -0.227]
    
    # Reusable parallel runner handles execution and terminal progress bar automatically
    results = run_parallel_sweeps(run_single_sweep, amps, label="Running IClamp Sweeps")

    plt.figure(figsize=(10, 5))
    color_map = {0.248: 'red', 0.271: 'blue', -0.225: 'green'}
    
    for amp in amps:
        t_vec, v_vec = results[amp]
        color = color_map.get(amp, 'black')
        plt.plot(t_vec, v_vec, color=color, linewidth=1.5, label=f'{amp} nA')
        
    plt.xlabel('Time (ms)')
    plt.ylabel('Voltage (mV)')
    plt.title('Nucleus Accumbens MSN - soma current clamp for 500 ms')
    plt.axvspan(200, 200 + 500, color='red', alpha=0.05, label='Injection Window')
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend()
    plt.savefig('./plots/fig_1_nucleus_accumbens_msn_current_clamp.png', dpi=300)
    plt.show()



if __name__ == '__main__':
    main()