# 🧠 Nucleus Accumbens MSN Simulation Model

An implementation of the multi-compartment Nucleus Accumbens (NAc) Medium Spiny Neuron (MSN) simulation model described in **Wolf et al. (2005)**: *"NMDA/AMPA Ratio Impacts State Transitions and Entrainment"* ([PDF Link](file:///home/amajnas/wolf_model/NMDAAMPA%20Ratio%20Impacts%20State%20Transitions%20and%20Entrainment.pdf)).

This model is built in Python using the **NEURON simulator** to study somatic excitability, stochastic synaptic integration, and state transitions (up/down states).

---

## 📂 Repository Structure

### 💻 Simulation Scripts
*   **[main.py](file:///home/amajnas/wolf_model/main.py)** — Somatic current clamp simulation.
*   **[main_syn.py](file:///home/amajnas/wolf_model/main_syn.py)** — Stochastic synaptic input simulation (AMPA, NMDA, GABA).
*   **[vClamp.py](file:///home/amajnas/wolf_model/vClamp.py)** — Parallelized voltage-clamp simulation to map calcium currents.

### ⚡ Mechanisms (`.mod` files)
*   **Sodium & Potassium:** `NaF`, `NaP`, `KAf`, `KAs`, `Kir`, `Krp`
*   **Calcium & Calcium-Activated:** `CaL12`, `CaL13`, `CaN`, `CaQ`, `CaR`, `CaT`, `bkkca`, `skkca`, `cadyn`
*   **Synaptic Receptors:** `AMPA`, `NMDA`, `GABA`

### 📊 Data & Documentation
*   **[Data/](file:///home/amajnas/wolf_model/Data)** — Lookup tables and fitting code used to configure channel kinetics.
*   **[channel_validity_analysis.md](file:///home/amajnas/wolf_model/channel_validity_analysis.md)** — Detailed comparison against ModelDB (ID 112834) and the original publication.

---

> [!IMPORTANT]
> ### 🔧 Biophysical Adjustments
>
> This implementation resolves critical discrepancies present in the original ModelDB code release:
> 
> 1. **SK Channel Ca²⁺ Sensitivity:** Modified [skkca.mod](file:///home/amajnas/wolf_model/skkca.mod) dissociation constants ($K_1, K_4$) by a factor of 1000 to restore physiological sub-micromolar (nanomolar) sensitivity.
> 2. **SK Conductance:** Restored somatic/dendritic $g_{\text{bar}}$ to $0.145 \text{ S/cm}^2$ to match the published paper's Table 2 exactly.
> 3. **BK Kinetics:** Updated [bkkca.mod](file:///home/amajnas/wolf_model/bkkca.mod) to utilize the Moczydlowski & Latorre (1983) kinetic scheme.

---

## 🚀 Getting Started

### 📦 1. Installation
Install the required dependencies via pip:
```bash
pip install neuron numpy matplotlib
```

### ⚙️ 2. Compilation
Compile the NMODL files from the repository root:
```bash
nrnivmodl
```

### 🏃 3. Execution
Run any of the simulation workflows:
```bash
python main.py       # Somatic excitability check (current clamp)
python main_syn.py   # Up/down state transition simulation
python vClamp.py     # Calcium current-voltage sweep
```
