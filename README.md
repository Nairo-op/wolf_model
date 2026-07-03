# Nucleus Accumbens MSN Simulation Model

This repository implements the multi-compartment Nucleus Accumbens (NAc) Medium Spiny Neuron (MSN) simulation model described in **Wolf et al. (2005)**: *"NMDA/AMPA Ratio Impacts State Transitions and Entrainment"* ([PDF](file:///home/amajnas/wolf_model/NMDAAMPA%20Ratio%20Impacts%20State%20Transitions%20and%20Entrainment.pdf)).

The model is built in Python using the NEURON simulator to study somatic excitability, stochastic synaptic integration, and state transitions (up/down states).

---

## Repository Structure

*   **Simulation Scripts:**
    *   [main.py](file:///home/amajnas/wolf_model/main.py): Somatic current clamp simulation.
    *   [main_syn.py](file:///home/amajnas/wolf_model/main_syn.py): Stochastic synaptic input simulation (AMPA, NMDA, GABA).
    *   [vClamp.py](file:///home/amajnas/wolf_model/vClamp.py): Parallelized voltage-clamp simulation to map calcium currents.
*   **Mechanisms (`.mod`):**
    *   Sodium & Potassium channels (`NaF`, `NaP`, `KAf`, `KAs`, `Kir`, `Krp`).
    *   Calcium & Calcium-activated channels (`CaL12`, `CaL13`, `CaN`, `CaQ`, `CaR`, `CaT`, `bkkca`, `skkca`, `cadyn`).
    *   Synaptic mechanisms (`AMPA`, `NMDA`, `GABA`).
*   **Data & Documentation:**
    *   [Data/](file:///home/amajnas/wolf_model/Data): Lookup tables and fitting code used to configure channel kinetics.
    *   [channel_validity_analysis.md](file:///home/amajnas/wolf_model/channel_validity_analysis.md): Detailed comparison against ModelDB (ID 112834) and the original publication.

---

## Biophysical Adjustments

This implementation resolves known discrepancies in the original ModelDB code release:
1.  **SK Channel Ca2+ Sensitivity:** Modified [skkca.mod](file:///home/amajnas/wolf_model/skkca.mod) dissociation constants ($K_1, K_4$) by a factor of 1000 to restore physiological sub-micromolar (nanomolar) sensitivity.
2.  **SK Conductance:** Restored somatic/dendritic $g_{\text{bar}}$ to $0.145 \text{ S/cm}^2$ to match the published paper exactly.
3.  **BK Kinetics:** Updated [bkkca.mod](file:///home/amajnas/wolf_model/bkkca.mod) to utilize the Moczydlowski & Latorre (1983) kinetic scheme.

---

## Getting Started

### 1. Installation
Install the required dependencies:
```bash
pip install neuron numpy matplotlib
```

### 2. Compilation
Compile the NMODL files from the repository root:
```bash
nrnivmodl
```

### 3. Execution
Run any of the following commands:
```bash
python main.py       # Excitability check (current clamp)
python main_syn.py   # Up/down state transition simulation
python vClamp.py     # Calcium current-voltage sweep
```
