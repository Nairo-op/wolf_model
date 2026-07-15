import numpy as np
import os
import sys
import matplotlib.pyplot as plt
from imp_files.utilities import run_parallel_sweeps, load_mechanisms
from imp_files.msn_class import MSNNeuron    

# Enforce headless mode before any NEURON imports, only run if there are any errors
"""os.environ["NEURON_MODULE_OPTIONS"] = "-nogui"    
"""

from neuron import h

h.celsius = 35.0
h.load_file('stdrun.hoc')


def run_single_simulation(amp):
    
    # checking if mechanisms are already auto-loaded
    load_mechanisms()
            
    # creating cell object and running
    cell = MSNNeuron()
    soma = cell.soma
    
    # current injection
    iclamp = h.IClamp(soma(0.5))
    iclamp.delay = 100.0
    iclamp.dur = 500.0
    iclamp.amp = amp
    
    # recording refernce vectors for plotting
    t_vec = h.Vector().record(h._ref_t)
    v_vec = h.Vector().record(soma(0.5)._ref_v)
    
    # NetCon to detect spikes
    nc = h.NetCon(soma(0.5)._ref_v, None, sec=soma)
    nc.threshold = 0.0
    spikes = h.Vector()
    nc.record(spikes)
    
    # initialize and run
    h.finitialize(-87.75)
    h.continuerun(650.0)
    
    t_arr = np.array(t_vec)
    v_arr = np.array(v_vec)
    
    idx = np.argmin(np.abs(t_arr - 550.0))
    v_at_450ms = v_arr[idx]
    
    spike_count = len([s for s in spikes if 100.0 <= s <= 600.0])
    freq = spike_count / 0.5
    
    # return frequency and v @ 450 ms
    return v_at_450ms, freq


def main():
    iv_amps = np.linspace(-0.2, 0.2, 20)
    fi_amps = np.linspace(0.15, 0.45, 15)
    all_amps = np.unique(np.concatenate([iv_amps, fi_amps]))
    
    results = run_parallel_sweeps(
        target_function=run_single_simulation, 
        parameter_list=all_amps, 
        label="Simulating I-V sweeps (Parallel)"
    )

    iv_x = []
    iv_y = []
    for amp in iv_amps:
        iv_x.append(amp * 1000)
        iv_y.append(results[amp][0])
        
    fi_x = []
    fi_y = []
    for amp in fi_amps:
        fi_x.append(amp)
        fi_y.append(results[amp][1])
        
    # --- Plotting I-V Curve ---
    plt.figure(figsize=(6, 5))
    plt.plot(iv_x, iv_y, 'ks-', label='Model')
    plt.xlabel('I (pA)')
    plt.ylabel('V (mV)')
    plt.axhline(-87.75, color='gray', linestyle='--', linewidth=0.5)
    plt.axvline(0, color='gray', linestyle='--', linewidth=0.5)
    plt.gca().spines['top'].set_visible(False)
    plt.gca().spines['right'].set_visible(False)
    plt.title('Current-Voltage (I-V) Relationship')
    plt.tight_layout()
    plt.savefig('./plots/figure_1e_iv_curve.png', dpi=300)
    
    # --- Plotting F-I Curve ---
    plt.figure(figsize=(5, 4))
    plt.plot(fi_x, fi_y, 'k-', linewidth=2)
    plt.xlabel('I (nA)')
    plt.ylabel('F (Hz)')
    plt.gca().spines['top'].set_visible(False)
    plt.gca().spines['right'].set_visible(False)
    plt.title('Frequency-Current (F-I) Relationship')
    plt.tight_layout()
    plt.savefig('./plots/figure_1e_fi_curve.png', dpi=300)
    
    plt.show()

if __name__ == '__main__':
    main()