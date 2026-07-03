# Validity Analysis of SK and BK Channels (skkca.mod and bkkca.mod)

This document provides a detailed validity check of the small-conductance calcium-activated potassium channel ([skkca.mod](file:///home/amajnas/wolf_model/skkca.mod)) and the large-conductance calcium-activated potassium channel ([bkkca.mod](file:///home/amajnas/wolf_model/bkkca.mod)) in the current workspace, comparing them to:
1. The published paper: *NMDA/AMPA Ratio Impacts State Transitions and Entrainment...* ([Wolf et al., 2005](file:///home/amajnas/wolf_model/NMDAAMPA%20Ratio%20Impacts%20State%20Transitions%20and%20Entrainment.pdf)).
2. The original ModelDB code submission for the Wolf et al. (2005) model (Model ID 112834).

---

## 1. Maximum Conductance ($g_{\text{bar}}$) Validity

In Table 2 of the published paper (p. 9082), the maximum conductances for active properties are specified as:
*   **BK $\text{K}_{\text{Ca}}$**: $0.001 \text{ S/cm}^2$
*   **SK $\text{K}_{\text{Ca}}$**: $0.145 \text{ S/cm}^2$

### Comparison table:
| Parameter | Published Paper (2005) | Original ModelDB (112834) | Workspace Code ([main_syn.py](file:///home/amajnas/wolf_model/main_syn.py#L24)) | Status |
| :--- | :--- | :--- | :--- | :--- |
| **BK $g_{\text{bar}}$** | $0.001 \text{ S/cm}^2$ | $0.001 \text{ S/cm}^2$ | $0.001 \text{ S/cm}^2$ (`gkbar_bkkca`) | **Correct** |
| **SK $g_{\text{bar}}$** | $0.145 \text{ S/cm}^2$ | $0.175 \text{ S/cm}^2$ | $0.145 \text{ S/cm}^2$ (`gkbar_skkca`) | **Correct** (Rectified to match paper) |

> [!NOTE]
> The maximum conductances configured in the workspace's active simulation scripts (such as [main_syn.py](file:///home/amajnas/wolf_model/main_syn.py#L24) and [vClamp.py](file:///home/amajnas/wolf_model/vClamp.py#L30)) match the **published paper's Table 2 exactly**. This fixes a slight discrepancy in the original ModelDB code where SK's $g_{\text{bar}}$ was set to $0.175 \text{ S/cm}^2$.

---

## 2. Kinetic Models & Parameters Validity

The paper states on page 9083:
> *"Both channels were taken from previous modeling studies (Moczydlowski and Latorre, 1983; Shao et al., 1999). The total conductance of the BK current was adjusted to shape spike width, and the SK channel was necessary to shape the spike afterhyperpolarization (AHP)."*

In the **original ModelDB code**:
*   **BK channel (`bkkca.mod`)** was modeled using the **Shao et al. (1999)** equations (a 3-state Markov kinetic scheme: `cst <-> ost <-> ist`).
*   **SK channel (`skkca.mod`)** was modeled using the **Moczydlowski and Latorre (1983)** equations (Scheme R1), but used **BK-like micromolar parameters** (`k1 = 0.18 mM` [180 µM], `k2 = 0.011 mM` [11 µM]). This is a known copy-paste simplification/error in the original code, as SK channels are voltage-independent and active in the sub-micromolar/nanomolar range.

In the **current workspace**:
*   **`bkkca.mod`** has been changed to use the **Moczydlowski and Latorre (1983)** equations (Scheme R1) instead of Shao et al. (1999). It uses BK-like parameters representing Channel A from the 1983 paper:
    *   `k1 = 0.18 mM` (180 µM)
    *   `k2 = 0.011 mM` (11 µM)
    *   `abar = 0.48 /ms`
    *   `bbar = 0.28 /ms`
*   **`skkca.mod`** also uses the **Moczydlowski and Latorre (1983)** equations (Scheme R1), but its kinetic parameters have been **scaled down by a factor of 1000** to shift the calcium sensitivity from BK's micromolar range to SK's nanomolar range (representing Channel B):
    *   `k1 = 0.48e-3 mM` (480 nM, compared to Channel B's `0.48 mM` in Moczydlowski & Latorre)
    *   `k2 = 0.13e-6 mM` (0.13 nM, compared to Channel B's `0.13e-3 mM` in Moczydlowski & Latorre)
    *   `abar = 0.28 /ms`
    *   `bbar = 0.48 /ms`

### Parameter Summary:
```
skkca.mod (Workspace):
  k1   = 0.48e-3 mM  (480 nM calcium dissociation constant - high affinity)
  k2   = 0.13e-6 mM  (0.13 nM calcium dissociation constant)
  abar = 0.28 /ms
  bbar = 0.48 /ms

bkkca.mod (Workspace):
  k1   = 0.18 mM     (180 µM calcium dissociation constant - low affinity)
  k2   = 0.011 mM    (11 µM calcium dissociation constant)
  abar = 0.48 /ms
  bbar = 0.28 /ms
```

> [!TIP]
> The current workspace's implementation of `skkca` rectifies the biophysical limitation of the original ModelDB code. By scaling down the dissociation constants $K_1$ and $K_4$ by 1000, it models a channel with **sub-micromolar (nanomolar) calcium sensitivity**, which is physiologically correct for SK channels, whereas the original ModelDB code mistakenly modeled the SK channel with micromolar BK kinetics.
>
> However, `bkkca.mod` in the workspace has been switched from the original **Shao et al. (1999)** Markov model to the **Moczydlowski and Latorre (1983)** model. Both are valid representations of BK channels, but they are mathematically distinct.

---

## 3. Recommendations & Next Steps

1. **Verify if BK model swap was intentional:** Since the paper references both Shao et al. (1999) and Moczydlowski & Latorre (1983), the swap of BK to Moczydlowski & Latorre is valid, but mathematically different from the ModelDB baseline. If you want to replicate the original paper's exact voltage traces, we may want to restore the Shao et al. (1999) kinetic scheme for `bkkca.mod`.
2. **Kinetics Validation:** The model compiles and runs successfully. We can run simulations with both active and inactive channels to verify their contribution to the afterhyperpolarization (AHP) and spike widths.
