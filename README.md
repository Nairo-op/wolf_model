# Multicompartmental Model of Nucleus Accumbens Medium Spiny Neurons (MSNs)

This repository contains a Python-NEURON reconstruction of the striatal Medium Spiny Neuron (MSN) model originally characterized by **Wolf et al. (2005)**: *"Computational Model of the Striatal Medium Spiny Neuron: Biophysical Properties and State Transitions"* (Journal of Neuroscience, 25(39):9080-9095).

Medium Spiny Neurons (MSNs), which make up over 95% of the striatal population, are characterized by a highly hyperpolarized "down-state" maintained by strong inwardly rectifying potassium currents ($I_{\text{Kir}}$), delayed excitation (late-spiking) mediated by slow A-type potassium currents ($I_{\text{KAs}}$), and bistable state transitions driven by glutamatergic afferents and shunting GABAergic inhibition. This model provides a biophysical framework for exploring these physiological phenomena in a multicompartmental reconstructed morphology.

---

##  Scientific & Biophysical Features

* **Multicompartmental Morphology:** Standardized reconstruction consisting of a soma and 28 dendritic branches (4 primary, 8 secondary, 16 tertiary branches).
* **Dendritic Spine Compensation:** Incorporates dendritic spines without explicit compartmentalization by scaling the passive membrane capacitance ($C_m$) and leak conductance ($g_{\text{pas}}$) by a localized spine factor ($F_{\text{spine}}$). Dendritic diameters ($d$) and lengths ($L$) are adjusted according to cable theory ($d_{\text{adj}} = d \cdot F_{\text{spine}}^{1.5}$, $L_{\text{adj}} = L \cdot F_{\text{spine}}^{0.5}$) to preserve the correct axial resistance and electrotonic properties of the branches.
* **14 Active Ion Channels:** 
  * *Sodium:* Fast transient ($I_{\text{NaF}}$) and persistent ($I_{\text{NaP}}$) currents.
  * *Potassium:* Fast A-type ($I_{\text{KAf}}$), slow A-type ($I_{\text{KAs}}$), inward rectifier ($I_{\text{Kir}}$), and slowly inactivating delayed rectifier ($I_{\text{Krp}}$) currents.
  * *Calcium:* L-type ($\text{Ca}_V1.2$, $\text{Ca}_V1.3$), N-type, R-type, Q-type, and T-type calcium currents.
  * *Calcium-Activated Potassium:* Large-conductance BK (`bkkca`) and small-conductance SK (`skkca`) currents.
* **Dual-Pool Calcium Dynamics:** Intracellular space is split into two independent submembrane shells to prevent artificial feedback:
  * **Standard Pool (`cai`):** Coupled to high-threshold N-, P/Q-, and R-type currents.
  * **L/T-type Pool (`cali`):** Coupled to L-type and T-type currents.
  Both pools implement Michaelis-Menten extrusion pumps and first-order decay.
* **Synaptic Integration:** Colocalized glutamatergic **AMPA** and **NMDA** (with voltage-dependent $\text{Mg}^{2+}$ block) receptors on spines, and GABAergic **GABA** receptors along the dendritic shafts and soma.

---

##  Repository Structure

###  Simulation Workflows
* **[main.py](https://github.com/Nairo-op/MSN2005_wolf_et_al-replicated-/tree/main/main.py)** — Somatic current clamp simulation using NEURON's interactive Graphical User Interface (GUI) layout configured via `main.ses`.
* **[IClamp.py](https://github.com/Nairo-op/MSN2005_wolf_et_al-replicated-/tree/main/IClamp.py)** — Executes somatic current clamp steps to measure responses to depolarizing step currents (+0.271 nA, +0.248 nA) and hyperpolarizing step currents (-0.227 nA).
* **[chan_currents.py](https://github.com/Nairo-op/MSN2005_wolf_et_al-replicated-/tree/main/chan_currents.py)** — Investigates the impact of slow A-type potassium current ($I_{\text{KAs}}$) inactivation kinetics on the characteristic late-firing (delayed excitation) behavior of MSNs.
* **[current_volt_freq.py](https://github.com/Nairo-op/MSN2005_wolf_et_al-replicated-/tree/main/current_volt_freq.py)** — Sweeps current steps to map out the steady-state Current-Voltage ($I\text{-}V$) relationship and the Frequency-Current ($F\text{-}I$) excitability curve.
* **[syn.py](https://github.com/Nairo-op/MSN2005_wolf_et_al-replicated-/tree/main/syn.py)** — Replicates the stochastic synaptic input protocols from Figure 3 of the paper, demonstrating up-state transitions driven by Poisson afferent inputs, and exploring the impact of NMDA block and shunting GABAergic inhibition.

###  Mechanisms & Helper Modules (`imp_files/`)
* **`*.mod`** — NMODL files containing the biophysical implementations of all channels, calcium dynamics, and synaptic receptors.
* **[msn_class.py](https://github.com/Nairo-op/MSN2005_wolf_et_al-replicated-/tree/main/imp_files/msn_class.py)** — Python class template defining the morphology, compartment connectivity, channel insertion, and synaptic placements of the MSN.
* **[utilities.py](https://github.com/Nairo-op/MSN2005_wolf_et_al-replicated-/tree/main/imp_files/utilities.py)** — Parallel sweep manager and auto-loader helper scripts.

###  Documentation
* **[all_data.md](https://github.com/Nairo-op/MSN2005_wolf_et_al-replicated-/tree/main/all_data.md)** — A complete, mathematically rigorous reference document cataloging all gating variables, kinetics lookup tables, membrane properties, and channel densities across the compartmental tree.

---

##  Getting Started

### 1. Requirements
Ensure you have the NEURON simulator, NumPy, and Matplotlib installed in your environment:
```bash
pip install neuron numpy matplotlib
```

### 2. Compiling the NMODL Mechanisms
Before running any script, you must compile the NMODL (`.mod`) files located in `imp_files/`. In the root directory of the repository, execute:

```bash
nrnivmodl imp_files/
```
*Note: On Windows, use the `mknrndll` GUI application to select the `imp_files` folder and compile.*

### 3. Running Simulations

#### Excitability GUI Walkthrough
To run the interactive NEURON GUI and manually test somatic current injection:
```bash
python main.py
```
This loads RunControl, IClamp control panels, and somatic membrane potential plots. Click **Init & Run** in the GUI to start.

#### Sommer Characterization Sweeps (Batch/Parallel)
The characterization sweeps run in headless mode and utilize parallel CPU execution to perform sweeps quickly:

* **Somatic Current Steps (I-Clamp):**
  ```bash
  python IClamp.py
  ```
  *Generates somatic voltage responses to multiple step amplitudes, saved to `plots/fig_1_nucleus_accumbens_msn_current_clamp.png`.*

* **I-V & F-I Curves Mapping:**
  ```bash
  python current_volt_freq.py
  ```
  *Generates the steady-state current-voltage relationship and spike frequency curves, saved to `plots/figure_1e_iv_curve.png` and `plots/figure_1e_fi_curve.png`.*

* **Role of $I_{\text{KAs}}$ on Delayed Spiking:**
  ```bash
  python chan_currents.py
  ```
  *Sweeps the scale of the KAs inactivation variable to analyze spike delay. Generates somatic voltage traces, inactivation state variables, and major somatic current profiles, saved to the `plots/` directory.*

* **Stochastic Synaptic Input & State Transitions:**
  ```bash
  python syn.py
  ```
  *Drives the cell with stochastic Poisson inputs (GABA, AMPA, and NMDA) to induce bistable down-to-up state transitions. Generates a multi-panel figure replicating the effects of NMDA block and shunting GABA changes, saved as `figure_3_replicated_output.png`.*

---

##  Key Physiological Findings & Replications

### Excitability & Inward Rectification (Figure 1)
MSNs rest at approximately $-88$ mV in their "down-state," stabilized by inwardly rectifying Kir channels. Injecting hyperpolarizing current (-0.227 nA) reveals this rectifying property—the membrane voltage does not drop linearly but deflects into a steady hyperpolarized plateau. Under depolarizing current steps (+0.271 nA), the cell slowly depolarizes, showing a delay before firing its first action potential.

### Delayed Excitation & $I_{\text{KAs}}$ Kinetics (Figure 2)
The delay in action potential generation during depolarizing steps is governed by the slow inactivation of the A-type potassium current ($I_{\text{KAs}}$). At rest, these channels are closed but de-inactivated (ready to open). Depolarization causes them to open rapidly, shunting the incoming current and delaying spike generation. The delay persists until the channels slowly inactivate ($\tau_h \approx 200\text{–}300$ ms). Modulating this inactivation rate dramatically changes the spike latency.

### Bistability and Up-State Transitions (Figure 3)
Under low-frequency synaptic inputs, the membrane potential fluctuates within the hyperpolarized down-state. When inputs increase (e.g., simulating cortical burst firing), the depolarizing AMPA currents drive the membrane potential to near $-55$ mV. At this level, the voltage-dependent Magnesium block of NMDA channels is relieved. The resulting massive influx of NMDA current drives the membrane potential into a sustained, depolarized "up-state" (around $-50$ mV to $-60$ mV), where the neuron is primed to fire. Local shunting GABAergic inhibition acts as a crucial gatekeeper, regulating the likelihood and duration of these transitions.

---

##  References
* **Wolf JA, Moyer JT, Lazarewicz MT, Contreras D, Benoit-Marand M, O'Donnell P, Finkel LH (2005).** *Computational Model of the Striatal Medium Spiny Neuron: Biophysical Properties and State Transitions.* Journal of Neuroscience 25(39):9080-9095. [Link to paper](https://github.com/Nairo-op/MSN2005_wolf_et_al-replicated-/tree/main/paper/NMDAAMPA%20Ratio%20Impacts%20State%20Transitions%20and%20Entrainment.pdf).
