# 🧠 Detailed Model Comparison Report: `nacb_msp` vs `wolf_model`

This report provides a comprehensive comparison of the Nucleus Accumbens (NAc) Medium Spiny Neuron (MSN) simulation models in `nacb_msp` (original ModelDB reference) and `wolf_model` (your current model).

By running identical current clamp simulations and performing static code analysis, we identified several critical discrepancies. The most prominent issues are a **60 mV gating shift** and a **2x kinetics scaling error** in the inward rectifying potassium channel (`Kir.mod`), as well as a global **calcium/chloride ion type mismatch** in the L-type and T-type channel mechanisms.

---

## 📊 Simulation Validation & Impact

Below is the somatic membrane potential response under current clamp stimulation (**100 ms to 600 ms, 0.2481 nA**):

| Metric | Original Reference (`nacb_msp`) | Your Model (`wolf_model`) — **Before Fix** | Your Model (`wolf_model`) — **After Kir Fix** |
| :--- | :--- | :--- | :--- |
| **Spike Count** | **1** | **2** (Hyper-excitable) | **1** (Correct) |
| **Spike Time(s)** | **436.4 ms** | **362.6 ms, 510.5 ms** | **443.1 ms** |
| **Peak Voltage** | **+20.82 mV** | **+21.08 mV** | **+20.86 mV** |
| **Resting Potential**| **-87.76 mV** | **-87.74 mV** | **-87.76 mV** |
| **Mean Abs. Diff** | **0.00 mV** (Base) | **2.30 mV** | **0.32 mV** (Extremely close) |

> [!NOTE]
> Fixing the gating and scaling parameters of the inward rectifier channel (`kir`) restores the correct **single-spike** behavior, reducing the trace discrepancy to a negligible mean absolute difference of **0.32 mV**. The remaining minor difference (6.7 ms spike time shift) is due to small conductance rounding in the dendritic compartments of `main.hoc` and the chloride/calcium pool mismatch.

---

## 🔍 Critical Differences & Bugs

### 1. Inward Rectifier Potassium Channel (`Kir.mod`) — **Critical**
*   **Gating Equation Shift (60 mV error)**:
    In the original `kir.mod`, the half-activation voltage is shifted by `mshift = 30 mV` in the depolarizing direction:
    $$V_{\text{half, eff}} = V_{\text{half}} + V_{\text{shift}} = -52\text{ mV} + 30\text{ mV} = -22\text{ mV}$$
    In your `Kir.mod` (`rates` procedure), the equation was incorrectly written as:
    `minf = 1 / (1 + exp((v - (-82.0)) / 13.0))`
    This represents a $V_{\text{half, eff}}$ of **$-82$ mV**, shifting activation by **60 mV** in the hyperpolarized direction. Because of this, `kir` was almost fully closed at rest, reducing the cell's leak current and making it hyper-excitable (spiking twice instead of once).
*   **Time Constant Scaling (2x kinetics error)**:
    In the original `kir.mod`, the time constant is scaled by `qfact = 0.5` (equivalent to dividing by 0.5, i.e., multiplying by 2).
    In your `Kir.mod`, the hardcoded lookup table values were scaled by **4** (equivalent to `qfact = 0.25`), making the channel's activation kinetics twice as slow as they should be.

### 2. Chloride vs. Calcium-L/T Ion Mismatch (`CaL12.mod`, `CaL13.mod`, `CaT.mod`, `cadyn_lt.mod`) — **Critical**
*   In your model, L-type channels (`CaL12`, `CaL13`), T-type channels (`CaT`), and their submembrane diffusion shell (`cadyn_lt`) were incorrectly set to use the chloride ion (`cl`) instead of the custom calcium-L/T ion (`cal`).
*   This means they write to chloride current (`icl`) and update intracellular chloride concentration (`cli`) instead of calcium (`ical` and `cali`).
*   To compensate, your simulation scripts contain hacks that initialize chloride concentrations (`h.cli0_cl_ion = 0.001`, `h.clo0_cl_ion = 5.0`) to match calcium levels, and manually set `ecl` to `GLOBAL_E_CA` (120 mV) to force the chloride reversal potential to match calcium.

### 3. Synaptic Calcium Current Deficit (`AMPA.mod`, `NMDA.mod`) — **Major**
*   In the original model, synaptic receptors (`AMPA.mod`, `NMDA.mod`) write a fraction of their current to the L/T-type calcium pool (`cal` ion) via `ical` (based on `ca_ratio = 0.005` for AMPA and `ca_ratio = 0.1` for NMDA).
*   In your `wolf_model`, `AMPA.mod` and `NMDA.mod` are basic double-exponential synapses that only generate nonspecific current `i`, completely omitting the calcium current component.

---

## 🛠️ Step-by-Step Replacement Instructions

Here is exactly what needs to be changed in each file of your `wolf_model` directory.

### 1. File: `Kir.mod`
Locate the `rates()` procedure in `Kir.mod` and replace the `minf` calculation and the entire interpolation table block to fix both the gating shift and the 2x scaling error.

```diff
-    minf = 1 / (1 + exp((v - (-82.0)) / 13.0))
+    minf = 1 / (1 + exp((v + 22.0) / 13.0))

     : --- HARDCODED LINEAR INTERPOLATION FOR KIR (mtau) ---
     : Range bounds: -100.0 mV to 0.0 mV, Step size: 10.0 mV
     
     if (v <= -100.0) {
         : mtau = 14.93
         mtau = 7.465
     } else if (v >= 0.0) {
         : mtau = 16.0
         mtau = 8.0
     } else {
         : Map voltage to table index (step size is 10 mV, starting at -100 mV)
         v_idx = floor((v - (-100.0)) / 10.0)
         fraction = ((v - (-100.0)) / 10.0) - v_idx
         
         : Perform linear interpolation based on index
         if (v_idx == 0) { 
-            mtau = 14.93 + fraction * (16.0 - 14.93)
+            mtau = 7.465 + fraction * (8.0 - 7.465)
         }
         else if (v_idx == 1) { 
-            mtau = 16.0 + fraction * (18.87 - 16.0)
+            mtau = 8.0 + fraction * (9.435 - 8.0)
         }
         else if (v_idx == 2) { 
-            mtau = 18.87 + fraction * (21.51 - 18.87)
+            mtau = 9.435 + fraction * (10.755 - 9.435)
         }
         else if (v_idx == 3) { 
-            mtau = 21.51 + fraction * (24.24 - 21.51)
+            mtau = 10.755 + fraction * (12.12 - 10.755)
         }
         else if (v_idx == 4) { 
-            mtau = 24.24 + fraction * (27.59 - 24.24)
+            mtau = 12.12 + fraction * (13.795 - 12.12)
         }
         else if (v_idx == 5) { 
-            mtau = 27.59 + fraction * (30.77 - 27.59)
+            mtau = 13.795 + fraction * (15.385 - 13.795)
         }
         else if (v_idx == 6) { 
-            mtau = 30.77 + fraction * (28.57 - 30.77)
+            mtau = 15.385 + fraction * (14.285 - 15.385)
         }
         else if (v_idx == 7) { 
-            mtau = 28.57 + fraction * (23.53 - 28.57)
+            mtau = 14.285 + fraction * (11.765 - 14.285)
         }
         else if (v_idx == 8) { 
-            mtau = 23.53 + fraction * (17.78 - 23.53)
+            mtau = 11.765 + fraction * (8.89 - 11.765)
         }
         else if (v_idx == 9) { 
-            mtau = 17.78 + fraction * (16.0 - 17.78)
+            mtau = 8.89 + fraction * (8.0 - 8.89)
         }
     }
```

### 2. Files: `CaL12.mod`, `CaL13.mod`, `CaT.mod`, and `cadyn_lt.mod`
Replace all occurrences of chloride (`cl`, `icl`, `cli`, `clo`, `ecl`, `clinf`) with the L/T-type calcium ion (`cal`, `ical`, `cali`, `calo`, `ecal`, `calinf`).

*   **`CaL12.mod` (Line 3-7 & 24-29)**:
    ```diff
    NEURON {
        SUFFIX cal12
-       USEION cl READ ecl, cli, clo WRITE icl VALENCE 2
-       RANGE pbar, icl, a
+       USEION cal READ cali, calo WRITE ical VALENCE 2
+       RANGE pbar, ical, a
    }
    ...
    ASSIGNED {
        v (mV)
-       ecl (mV)
-       icl (mA/cm2)
-       cli (mM)
-       clo (mM)
+       ical (mA/cm2)
+       cali (mM)
+       calo (mM)
    }
    ```
    *(Remember to also rename references inside the `BREAKPOINT` and `ghk` function from `icl/cli/clo` to `ical/cali/calo`)*.

*   **`cadyn_lt.mod` (Line 6-10, 28, 37-42 & 45-56)**:
    ```diff
    NEURON {
        SUFFIX cadyn_lt
-       USEION cl READ icl, cli WRITE cli
-       RANGE pump, clinf, taur, drive, F
+       USEION cal READ ical, cali WRITE cali VALENCE 2
+       RANGE pump, calinf, taur, drive, F
    }
    ...
    PARAMETER {
-       clinf = 1e-5 (mM)
+       calinf = 1e-5 (mM)
    }
    STATE {
-       cli (mM)
+       cali (mM)
    }
    ...
    ASSIGNED {
-       icl (mA/cm2)
+       ical (mA/cm2)
    }
    ```

### 3. File: `main.py`
Correct the initialization parameters for the ions:
```diff
 h.cai0_ca_ion = 0.001
 h.cao0_ca_ion = 5.0
-h.cli0_cl_ion = 0.001
-h.clo0_cl_ion = 5.0
+h.cali0_cal_ion = 0.001
+h.calo0_cal_ion = 5.0
```

### 4. File: `main.hoc`
Update the chloride initialization hack to use the correct `ecal` variable:
```diff
-        if (name_declared("ecl")) {
-            ecl = GLOBAL_E_CA
-        }
+        if (name_declared("ecal")) {
+            ecal = GLOBAL_E_CA
+        }
```
*(Also change dendritic conductances in `main.hoc` to match `main.py` exactly if you want perfect trace alignment: `gbar_kaf = 0.020584` instead of `0.021`, and `gbar_kas = 0.00095142` instead of `9.51e-4`)*.
