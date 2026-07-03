# Nucleus Accumbens MSN Simulation (Wolf et al. 2005)

Hey! Welcome. This repository contains a NEURON simulation model for a Nucleus Accumbens (NAc) Medium Spiny Neuron (MSN). It's based on the paper **"NMDA/AMPA Ratio Impacts State Transitions and Entrainment"** by Wolf et al. (2005). You can check out the full paper PDF directly in this repo: [Wolf_2005_Paper.pdf](file:///home/amajnas/wolf_model/NMDAAMPA%20Ratio%20Impacts%20State%20Transitions%20and%20Entrainment.pdf).

If you are trying to understand MSN excitability, up/down state transitions, or how synaptic balance shapes firing behavior, you've come to the right place.

---

## What's in the Box?

Here is a quick tour of what's inside this repository:

*   **Python Scripts to Run Simulations:**
    *   [main.py](file:///home/amajnas/wolf_model/main.py): A straightforward somatic current clamp simulation on the multi-compartment MSN model. It injects a step current to the soma and plots the membrane potential. Good for checking basic excitability.
    *   [main_syn.py](file:///home/amajnas/wolf_model/main_syn.py): A more complex simulation incorporating synaptic inputs (stochastic AMPA, NMDA, and GABA receptors). This is where you can play with synaptic ratios and observe up/down state transitions.
    *   [vClamp.py](file:///home/amajnas/wolf_model/vClamp.py): A multi-process script that runs a voltage clamp sweep across the cell soma to map the peak Calcium Current I-V curve.

*   **NMODL Channel Mechanisms (`.mod` files):**
    *   Active currents: Fast Sodium ([NaF](file:///home/amajnas/wolf_model/NaF.mod)), Persistent Sodium ([NaP](file:///home/amajnas/wolf_model/NaP.mod)), Fast A-type Potassium ([KAf](file:///home/amajnas/wolf_model/KAf.mod)), Slow A-type Potassium ([KAs](file:///home/amajnas/wolf_model/KAs.mod)), Inward Rectifying Potassium ([Kir](file:///home/amajnas/wolf_model/Kir.mod)), and Anomalous Rectifier ([Krp](file:///home/amajnas/wolf_model/Krp.mod)).
    *   Calcium currents: L-type ([CaL12](file:///home/amajnas/wolf_model/CaL12.mod), [CaL13](file:///home/amajnas/wolf_model/CaL13.mod)), N-type ([CaN](file:///home/amajnas/wolf_model/CaN.mod)), Q-type ([CaQ](file:///home/amajnas/wolf_model/CaQ.mod)), R-type ([CaR](file:///home/amajnas/wolf_model/CaR.mod)), and T-type ([CaT](file:///home/amajnas/wolf_model/CaT.mod)).
    *   Calcium-activated Potassium currents: Large conductance BK ([bkkca.mod](file:///home/amajnas/wolf_model/bkkca.mod)) and Small conductance SK ([skkca.mod](file:///home/amajnas/wolf_model/skkca.mod)).
    *   Synapses: [AMPA.mod](file:///home/amajnas/wolf_model/AMPA.mod), [NMDA.mod](file:///home/amajnas/wolf_model/NMDA.mod), and [GABA.mod](file:///home/amajnas/wolf_model/GABA.mod).
    *   Calcium dynamics: [cadyn.mod](file:///home/amajnas/wolf_model/cadyn.mod).

*   **Data & Fitting Resources:**
    *   [channel_kinetics_lookups.csv](file:///home/amajnas/wolf_model/Data/channel_kinetics_lookups.csv): Gating time constants and activation/inactivation data at various membrane potentials.
    *   [code_for_alpha_beta.py](file:///home/amajnas/wolf_model/Data/code_for_alpha_beta.py): Helper python script to fit Boltzmann equations and extract rate functions ($\alpha$ and $\beta$) from lookup tables.
    *   [fitted_channel_equations.txt](file:///home/amajnas/wolf_model/Data/fitted_channel_equations.txt): Compiled equations and parameters resulting from the channel fittings.

*   **Documentation:**
    *   [channel_validity_analysis.md](file:///home/amajnas/wolf_model/channel_validity_analysis.md): A detailed report examining the channel conductances and kinetics (particularly SK and BK channels) compared to both the published paper and the original ModelDB package.
    *   [wolf.ses](file:///home/amajnas/wolf_model/wolf.ses): A NEURON session file if you want to load the model's GUI layout.

---

## A Quick Word on Channel Fixes in this Repo

If you compare this model to the original ModelDB code submission (Model ID 112834), you'll notice a couple of important biophysical fixes:
1.  **SK Channel Ca2+ Sensitivity:** The original ModelDB code mistakenly modeled the SK channel (`skkca`) with micromolar-range BK kinetics (copy-paste artifact). We've scaled the calcium dissociation constants ($K_1$, $K_4$) down by a factor of 1000 in [skkca.mod](file:///home/amajnas/wolf_model/skkca.mod) to shift its sensitivity into the physiological **sub-micromolar (nanomolar)** range.
2.  **SK Conductance:** We restored SK $g_{\text{bar}}$ to $0.145\text{ S/cm}^2$ to match Table 2 of the published paper exactly (fixing the $0.175\text{ S/cm}^2$ discrepancy in the ModelDB release).
3.  **BK kinetics:** The [bkkca.mod](file:///home/amajnas/wolf_model/bkkca.mod) uses the classic Moczydlowski & Latorre (1983) scheme.

For more details on this, take a look at the [channel_validity_analysis.md](file:///home/amajnas/wolf_model/channel_validity_analysis.md) file.

---

## Getting Started

### 1. Prerequisites
You'll need a standard Python environment with NEURON, NumPy, and Matplotlib. 

You can install them via pip:
```bash
pip install neuron numpy matplotlib
```

### 2. Compile the Mechanisms
Before running any simulations, you have to compile the NMODL (`.mod`) files so NEURON can read them. Run this in your terminal from the repository root:

```bash
nrnivmodl
```

*(On Windows, you might need to use `mknrndll` instead.)*

### 3. Run the Simulations

*   **To check somatic excitability (current injection):**
    ```bash
    python main.py
    ```
*   **To check synaptic responses (up/down state transitions):**
    ```bash
    python main_syn.py
    ```
*   **To run the voltage clamp sweep (parallelized over your CPU cores):**
    ```bash
    python vClamp.py
    ```

---

## Model Morphology & Setup
The model represents a simplified multicompartment MSN consisting of:
*   A **Soma** (1 compartment)
*   **Primary Dendrites** (4 branches, spine factor $F=1.0$)
*   **Secondary Dendrites** (8 branches, spine factor $F=1.33$)
*   **Tertiary Dendrites** (16 branches, spine factor $F=3.0$, where most of the synaptic inputs land)

Spines are modeled implicitly by stretching the compartment lengths and diameters according to their spine factors ($F$) to preserve membrane surface area and input resistance.

---

Feel free to poke around, tweak the conductances, change synaptic rates in `main_syn.py`, or open up a pull request if you find any other discrepancies!
