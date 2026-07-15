import numpy as np
import os
import sys
from imp_files.utilities import run_parallel_sweeps
import matplotlib.pyplot as plt
from neuron import h
from imp_files.msn_class import MSNNeuron




def run_synaptic_simulation(condition):
    os.environ["NEURON_MODULE_OPTIONS"] = "-nogui"
    
    h.load_file('stdrun.hoc')
    h.celsius = 35.0
    h.dt = 0.025
    
    if not hasattr(h, 'cai0_ca_ion'):
        target_binary = 'libnrnmech.so' if sys.platform != 'win32' else 'nrnmech.dll'
        for root, dirs, files in os.walk(os.getcwd()):
            if target_binary in files:
                try: h.nrn_load_dll(os.path.join(root, target_binary))
                except RuntimeError: pass
                break

    cell = MSNNeuron()
    
    h.cai0_ca_ion = 0.001
    h.cao0_ca_ion = 5.0
    h.cali0_cal_ion = 0.001
    h.calo0_cal_ion = 5.0

    # Calibrated maximum conductances (uS)
    w_ampa = 0.000593  
    w_nmda = 0.00032 if condition != "No_NMDA" else 0.0
    
    if condition == "gGABA_0":
        w_gaba = 0.0
    elif condition == "gGABA_5":
        w_gaba = 0.000435 * 5.0
    else:
        w_gaba = 0.000435  

    for gaba_syn in cell.gaba_synapses:
        if hasattr(gaba_syn, 'e'):
            gaba_syn.e = -60.0  

    intervals = [400.0, 900.0, 1400.0, 1900.0, 2000.0]
    freq_steps = [3.0, 7.5, 3.0, 7.5, 3.0]
    
    stimulators = []
    connections = []
    
    ampa_vectors = []
    nmda_vectors = []
    gaba_vectors = []
    
    def attach_poisson_gated_trains(synapse_list, weight, vec_list):
        base_seed = 12345 + int(np.sum([ord(c) for c in condition]))
        
        for idx, syn in enumerate(synapse_list):
            # FIXED: Record currents regardless of the condition string
            if hasattr(syn, '_ref_i'):
                v_rec = h.Vector().record(syn._ref_i)
                vec_list.append(v_rec)
                
            t_start = 0.0
            for dur, freq in zip(intervals, freq_steps):
                ns = h.NetStim()
                ns.interval = 1000.0 / freq
                ns.noise = 0.5
                ns.start = t_start
                
                # FIXED: Dynamically calculate allowed spikes inside the window duration
                window_duration = dur - t_start
                ns.number = int(window_duration * (freq / 1000.0))

                ns.seed(base_seed + idx)
                
                nc = h.NetCon(ns, syn)
                nc.weight[0] = weight
                nc.delay = 1.0
                
                stimulators.append(ns)
                connections.append(nc)
                t_start = dur

    attach_poisson_gated_trains(cell.ampa_synapses, w_ampa, ampa_vectors)
    attach_poisson_gated_trains(cell.nmda_synapses, w_nmda, nmda_vectors)
    attach_poisson_gated_trains(cell.gaba_synapses, w_gaba, gaba_vectors)

    t_vec = h.Vector().record(h._ref_t)
    v_vec = h.Vector().record(cell.soma(0.5)._ref_v)

    h.finitialize(-87.75)
    h.continuerun(2000.0)
    
    t_arr = np.array(t_vec)
    total_steps = len(t_arr)
    
    i_ampa_sum = np.zeros(total_steps)
    i_nmda_sum = np.zeros(total_steps)
    i_gaba_sum = np.zeros(total_steps)
    
    # FIXED: Compute summations unconditionally so that all metrics return accurately
    for v_rec in ampa_vectors: i_ampa_sum += np.array(v_rec)
    for v_rec in nmda_vectors: i_nmda_sum += np.array(v_rec)
    for v_rec in gaba_vectors: i_gaba_sum += np.array(v_rec)

    return {
        "t": t_arr / 1000.0,
        "v": np.array(v_vec),
        "i_ampa": i_ampa_sum,
        "i_nmda": i_nmda_sum,
        "i_gaba": i_gaba_sum,
    }
def main():
    conditions = ["Control", "No_NMDA", "gGABA_0", "gGABA_5"]
    results = run_parallel_sweeps(run_synaptic_simulation, conditions, label="Simulating Synaptic Framework")
    
    t = results["Control"]["t"]
    fig, axes = plt.subplots(4, 1, figsize=(10, 11), sharex=True)
    
    # Panel A: Control vs No NMDA
    axes[0].plot(t, results["Control"]["v"], color='black', label='Control', linewidth=1)
    axes[0].plot(t, results["No_NMDA"]["v"], color='red', label='No NMDA', linewidth=1)
    axes[0].set_ylabel('Vm (mV)')
    axes[0].set_ylim(-90, 30)
    axes[0].legend(frameon=False, loc='upper right')
    axes[0].set_title("Panel A: State Transitions & NMDA Dependence")

    # Panel B: Currents
    axes[1].plot(t, results["Control"]["i_ampa"], color='blue', label='AMPA', linewidth=1)
    axes[1].plot(t, results["Control"]["i_nmda"], color='red', label='NMDA', linewidth=1)
    axes[1].plot(t, results["Control"]["i_gaba"], color='green', label='GABA', linewidth=1)
    axes[1].set_ylabel('Current')
    axes[1].legend(frameon=False, loc='lower right')
    axes[1].set_title("Panel B: Underlying Synaptic Profiles")

    # Panel C: Frequency Step Commands
    t_step = [0.0, 0.4, 0.4, 0.9, 0.9, 1.4, 1.4, 1.9, 1.9, 2.0]
    # f_step = [3.0, 3.0, 7.5, 7.5, 3.0, 3.0, 7.5, 7.5, 3.0, 3.0]
    f_step = [3.0, 3.0, 7.5, 7.5, 3.0, 3.0, 7.5, 7.5, 3.0, 3.0]

    axes[2].plot(t_step, f_step, color='red', linewidth=2.5, label='Command Input')
    axes[2].set_ylabel('Inst Freq/Syn (Hz)')
    axes[2].set_ylim(0, 10)
    axes[2].set_title("Panel C: Afferent Firing Pattern Dynamics")

    # Panel D: GABA Variations
    axes[3].plot(t, results["gGABA_0"]["v"], color='orange', label='gGABA*0', linewidth=1)
    axes[3].plot(t, results["gGABA_5"]["v"], color='black', label='gGABA*5', linewidth=1)
    axes[3].set_ylabel('Vm (mV)')
    axes[3].set_xlabel('Time (sec)')
    axes[3].set_ylim(-90, 30)
    axes[3].legend(frameon=False, loc='upper right')
    axes[3].set_title("Panel D: Influence of Shunting GABA Inhibition")

    for ax in axes:
        ax.spines['top'].set_visible(False)
        ax.spines['right'].set_visible(False)
        ax.grid(axis='x', linestyle=':', alpha=0.5)

    plt.tight_layout()
    plt.savefig('figure_3_replicated_output.png', dpi=300)
    plt.show()

if __name__ == '__main__':
    main()