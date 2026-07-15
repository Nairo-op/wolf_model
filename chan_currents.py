import numpy as np
import matplotlib.pyplot as plt
import os
from imp_files.utilities import run_parallel_sweeps, load_mechanisms
# Enforce headless mode inside the worker process
os.environ["NEURON_MODULE_OPTIONS"] = "-nogui"


from neuron import h
h.load_file('stdrun.hoc')
h.celsius = 35.0


def run_figure2_sweep(setup_tuple):

    scale, condition_name = setup_tuple
    
    # Safely handle dynamic mechanism auto-loading
    load_mechanisms()

    from imp_files.msn_class import MSNNeuron    
    cell = MSNNeuron()
    soma = cell.soma
    
    # Scale the KAs inactivation parameter if a custom scale is provided
    for seg in soma:
        if hasattr(seg, 'a_kas'):  # Replace 'a_kas' with the exact name in your .mod file if different
            seg.a_kas *= scale

    # Replicate current injection settings from the paper (0.232 nA)
    stim = h.IClamp(soma(0.5))
    stim.delay = 100.0
    stim.dur = 600.0
    stim.amp = 0.232
    
    # Vectors to record data
    t_vec = h.Vector().record(h._ref_t)
    v_vec = h.Vector().record(soma(0.5)._ref_v)
    
    # Setup state variable and current recording (Only needed for Control run)
    records = {}
    if condition_name == "Control":
        # Adjust strings to match your actual NMODL suffix/variable declarations
        records['KAs_h'] = h.Vector().record(soma(0.5)._ref_h_kas)
        records['KAf_h'] = h.Vector().record(soma(0.5)._ref_h_kaf)
        records['NaF'] = h.Vector().record(soma(0.5)._ref_ina_naf)
        records['KAs'] = h.Vector().record(soma(0.5)._ref_ik_kas)
        records['KAf'] = h.Vector().record(soma(0.5)._ref_ik_kaf)
        records['Kir'] = h.Vector().record(soma(0.5)._ref_ik_kir)
        records['Krp'] = h.Vector().record(soma(0.5)._ref_ik_krp)

    h.finitialize(-87.75)
    h.continuerun(800.0)
    
    # Format return dictionary safely converting vectors to numpy arrays
    out = {
        "t": np.array(t_vec),
        "v": np.array(v_vec)
    }
    for k, vec in records.items():
        out[k] = np.array(vec)
        
    return out

def main():
    # Define sweep protocols: (Scale Factor, Condition Name)
    protocols = [
        (1.0, "Control"),
        (0.6, "Inact *0.6"),
        (1.4, "Inact *1.4")
    ]
    
    # Run parallel framework
    results = run_parallel_sweeps(
        target_function=run_figure2_sweep,
        parameter_list=protocols,
        label="Simulating Figure 2 Framework"
    )
    
    # --- PLOT 1: Figure 2A (Somatic Voltage Profiles) ---
    plt.figure(figsize=(7, 5))
    plt.plot(results[(1.0, "Control")]['t'], results[(1.0, "Control")]['v'], color='black', label='Control', linewidth=2)
    plt.plot(results[(0.6, "Inact *0.6")]['t'], results[(0.6, "Inact *0.6")]['v'], color='#1f77b4', label='Inact *0.6', linewidth=2)
    plt.plot(results[(1.4, "Inact *1.4")]['t'], results[(1.4, "Inact *1.4")]['v'], color='#d62728', label='Inact *1.4', linewidth=2)
    
    plt.title('Figure 2A: Somatic Voltage Traces', fontsize=12, fontweight='bold')
    plt.xlabel('Time (ms)')
    plt.ylabel('Voltage (mV)')
    plt.legend(frameon=False)
    plt.gca().spines['top'].set_visible(False)
    plt.gca().spines['right'].set_visible(False)
    plt.tight_layout()
    plt.savefig('./plots/figure_2a_voltage.png', dpi=300)
    
    # Extract baseline datasets for Panel B variants from the control profile
    control_data = results[(1.0, "Control")]
    t_arr = control_data['t']
    
    # --- PLOT 2: Figure 2B Inset (Inactivation States) ---
    plt.figure(figsize=(5, 3.5))
    plt.plot(t_arr, control_data['KAs_h'], color='#d62728', label='KAs_h', linewidth=2)
    plt.plot(t_arr, control_data['KAf_h'], color='#8c564b', label='KAf_h', linewidth=2)
    
    plt.title('Figure 2B Inset: Inactivation States', fontsize=11, fontweight='bold')
    plt.xlabel('Time (ms)')
    plt.ylabel('Inact. State')
    plt.ylim(0, 1.1)
    plt.legend(frameon=False)
    plt.gca().spines['top'].set_visible(False)
    plt.gca().spines['right'].set_visible(False)
    plt.tight_layout()
    plt.savefig('./plots/figure_2b_inset_states.png', dpi=300)
    
    # --- PLOT 3: Figure 2B Main (Major Somatic Currents) ---
    plt.figure(figsize=(7, 5))
    plt.plot(t_arr, control_data['NaF'], color='black', label='NaF', linewidth=2)
    plt.plot(t_arr, control_data['KAs'], color='#d62728', label='KAs', linewidth=2)
    plt.plot(t_arr, control_data['KAf'], color='#8c564b', label='KAf', linewidth=2)
    plt.plot(t_arr, control_data['Kir'], color='#1f77b4', label='Kir', linewidth=2)
    plt.plot(t_arr, control_data['Krp'], color='#2ca02c', label='Krp', linewidth=2)
    
    plt.title('Figure 2B: Major Somatic Currents', fontsize=12, fontweight='bold')
    plt.xlabel('Time (ms)')
    plt.ylabel(f'Current (mA/cm^2)')
    plt.legend(frameon=False)
    plt.gca().spines['top'].set_visible(False)
    plt.gca().spines['right'].set_visible(False)
    plt.tight_layout()
    plt.savefig('./plots/figure_2b_currents.png', dpi=300)
    

if __name__ == '__main__':
    main()