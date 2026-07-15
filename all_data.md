# Striatal MSN Multicompartmental Model Parameters

This document catalogs the biophysical, morphological, and kinetic parameters of the reconstructed striatal Medium Spiny Neuron (MSN) model, based on the classic publication:
> **Wolf et al. (2005)** - *Computational Model of the Striatal Medium Spiny Neuron: Biophysical Properties and State Transitions* (J. Neurosci 25:9080–9095).

---

## 1. Calcium Channel Biophysics & Kinetics

All voltage-gated calcium channels (VGCCs) use the **Goldman-Hodgkin-Katz (GHK)** current equation to calculate the calcium flux, which is driven by concentration gradients.

### CaQ Channel (Q-type)
* **Permeability (Somatic):** $\bar{p} = 6.0 \times 10^{-6}$ cm/s
* **State Variables:** $m$ (activation, squared)
* **Inactivation:** None modeled
* **Current Formula:**
  $$i_{\text{Ca}} = \bar{p} \cdot m^2 \cdot \text{ghk}(v, [\text{Ca}]_i, [\text{Ca}]_o)$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 9.0}{6.6}}}$$
* **Time Constant:** $\tau_m = 0.377$ ms (constant)

### CaN Channel (N-type)
* **Permeability (Somatic):** $\bar{p} = 1.0 \times 10^{-5}$ cm/s
* **State Variables:** $m$ (activation, squared), $h$ (inactivation)
* **Inactivation Fraction ($a$):** 0.21 (fraction of current that inactivates; $1-a = 0.79$ is persistent)
* **Current Formula:**
  $$i_{\text{Ca}} = \bar{p} \cdot m^2 \cdot (a \cdot h + 1 - a) \cdot \text{ghk}(v, [\text{Ca}]_i, [\text{Ca}]_o)$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 8.7}{7.4}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 74.8}{6.5}}}$$
* **Gating Kinetics:**
  $$\alpha_m = \frac{0.1157 \cdot (V + 17.19)}{e^{\frac{V + 17.19}{15.22}} - 1}$$
  $$\beta_m = 1.15 \cdot e^{\frac{V}{23.82}}$$
  $$\tau_m = \frac{1}{\alpha_m + \beta_m}$$
  $$\tau_h = 23.33 \text{ ms (constant)}$$

### CaR Channel (R-type)
* **Permeability (Somatic):** $\bar{p} = 2.6 \times 10^{-5}$ cm/s
* **State Variables:** $m$ (activation, cubed), $h$ (inactivation)
* **Current Formula:**
  $$i_{\text{Ca}} = \bar{p} \cdot m^3 \cdot h \cdot \text{ghk}(v, [\text{Ca}]_i, [\text{Ca}]_o)$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 10.3}{6.6}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 33.3}{17.0}}}$$
* **Gating Kinetics:**
  $$\tau_m = 1.7 \text{ ms (constant)}$$
  $$\tau_h = \text{Lookup Table (linear interpolation between } -30 \text{ mV and } 10 \text{ mV)}$$

#### CaR Inactivation Gating Time Constant ($\tau_h$) Lookup Table
| Membrane Potential $V$ (mV) | $\tau_h$ (ms) |
| :-------------------------- | :------------ |
| $V \le -30.0$               | 33.33         |
| $-20.0$                     | 21.67         |
| $-10.0$                     | 11.67         |
| $0.0$                       | 10.00         |
| $V \ge 10.0$                | 6.67          |

---

### CaT Channel (T-type)
* **Permeability (Somatic):** $\bar{p} = 4.0 \times 10^{-7}$ cm/s
* **State Variables:** $m$ (activation, cubed), $h$ (inactivation)
* **Current Formula:**
  $$i_{\text{Ca}} = \bar{p} \cdot m^3 \cdot h \cdot \text{ghk}(v, [\text{cal}]_i, [\text{cal}]_o)$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 51.73}{6.53}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 80.0}{6.7}}}$$
* **Gating Kinetics:** $\tau_m$ and $\tau_h$ are determined by linear interpolation of a lookup table between $-65$ mV and $10$ mV (step size $5$ mV).

#### CaT Gating Time Constants ($\tau_m, \tau_h$) Lookup Table
| Membrane Potential $V$ (mV) | $\tau_m$ (ms) | $\tau_h$ (ms) |
| :-------------------------- | :------------ | :------------ |
| $V \le -65.0$               | 6.73          | 127.33        |
| $-60.0$                     | 6.73          | 69.33         |
| $-55.0$                     | 4.37          | 54.00         |
| $-50.0$                     | 2.90          | 43.00         |
| $-45.0$                     | 2.27          | 39.67         |
| $-40.0$                     | 1.87          | 35.67         |
| $-35.0$                     | 1.47          | 35.67         |
| $-30.0$                     | 1.27          | 35.67         |
| $-25.0$                     | 1.20          | 36.00         |
| $-20.0$                     | 1.10          | 36.33         |
| $-15.0$                     | 1.20          | 36.33         |
| $-10.0$                     | 1.20          | 36.67         |
| $-5.0$                      | 1.10          | 36.67         |
| $0.0$                       | 1.10          | 36.67         |
| $5.0$                       | 1.10          | 36.67         |
| $V \ge 10.0$                | 1.10          | 36.67         |

---

### CaL12 Channel (CaV1.2 L-type)
* **Permeability (Somatic):** $\bar{p} = 6.7 \times 10^{-6}$ cm/s
* **State Variables:** $m$ (activation, squared), $h$ (inactivation)
* **Inactivation Fraction ($a$):** 0.17
* **Current Formula:**
  $$i_{\text{Ca}} = \bar{p} \cdot m^2 \cdot (a \cdot h + 1 - a) \cdot \text{ghk}(v, [\text{cal}]_i, [\text{cal}]_o)$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 8.9}{6.7}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 13.4}{11.9}}}$$
* **Gating Kinetics:**
  $$\alpha_m = \frac{0.1194 \cdot V}{e^{\frac{V}{9.005}} - 1}$$
  $$\beta_m = 2.97 \cdot e^{\frac{V}{31.4}}$$
  $$\tau_m = \frac{1}{\alpha_m + \beta_m}$$
  $$\tau_h = 14.77 \text{ ms (constant)}$$

---

### CaL13 Channel (CaV1.3 L-type)
* **Permeability (Somatic):** $\bar{p} = 4.25 \times 10^{-7}$ cm/s
* **State Variables:** $m$ (activation, squared), $h$ (inactivation)
* **Inactivation Fraction ($a$):** 0.17
* **Current Formula:**
  $$i_{\text{Ca}} = \bar{p} \cdot m^2 \cdot (a \cdot h + 1 - a) \cdot \text{ghk}(v, [\text{cal}]_i, [\text{cal}]_o)$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 33.0}{6.7}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 13.4}{11.9}}}$$
* **Gating Kinetics:**
  $$\alpha_m = \frac{0.1194 \cdot V}{e^{\frac{V}{9.005}} - 1}$$
  $$\beta_m = 2.97 \cdot e^{\frac{V}{31.4}}$$
  $$\tau_m = \frac{1}{\alpha_m + \beta_m}$$
  $$\tau_h = 14.77 \text{ ms (constant)}$$

---

## 2. Sodium & Potassium Channels

### NaF Channel (Fast Transient Sodium)
* **Maximum Conductance (Somatic):** $\bar{g} = 1.5$ S/cm²
* **State Variables:** $m$ (activation, cubed), $h$ (inactivation)
* **Current Formula:**
  $$i_{\text{Na}} = \bar{g} \cdot m^3 \cdot h \cdot (V - E_{\text{Na}})$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 23.9}{11.8}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 62.9}{10.7}}}$$
* **Gating Kinetics:** $\tau_m$ and $\tau_h$ are determined by linear interpolation of a lookup table between $-80$ mV and $30$ mV (step size $10$ mV).

#### NaF Gating Time Constants ($\tau_m, \tau_h$) Lookup Table
| Membrane Potential $V$ (mV) | $\tau_m$ (ms) | $\tau_h$ (ms) |
| :-------------------------- | :------------ | :------------ |
| $V \le -80.0$               | 0.023         | 0.433         |
| $-70.0$                     | 0.030         | 0.433         |
| $-60.0$                     | 0.037         | 0.433         |
| $-50.0$                     | 0.043         | 0.433         |
| $-40.0$                     | 0.067         | 0.433         |
| $-30.0$                     | 0.107         | 0.433         |
| $-20.0$                     | 0.053         | 0.283         |
| $-10.0$                     | 0.050         | 0.167         |
| $0.0$                       | 0.040         | 0.150         |
| $10.0$                      | 0.027         | 0.107         |
| $20.0$                      | 0.020         | 0.100         |
| $V \ge 30.0$                | 0.020         | 0.093         |

---

### NaP Channel (Persistent Sodium)
* **Maximum Conductance (Somatic):** $\bar{g} = 4.0 \times 10^{-5}$ S/cm²
* **State Variables:** $m$ (activation), $h$ (slow inactivation)
* **Current Formula:**
  $$i_{\text{Na}} = \bar{g} \cdot m \cdot h \cdot (V - E_{\text{Na}})$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 52.6}{4.6}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 48.8}{10}}}$$
* **Gating Kinetics:**
  $$\tau_m = \begin{cases} 
  0.025 + 0.14 \cdot e^{\frac{V + 40.0}{10.0}} & \text{if } V < -40.0\text{ mV} \\ 
  0.020 + 0.145 \cdot e^{-\frac{V + 40.0}{10.0}} & \text{if } V \ge -40.0\text{ mV} 
  \end{cases}$$
  $$\tau_h = \text{Lookup Table (linear interpolation between } -100 \text{ mV and } 10 \text{ mV)}$$

#### NaP Inactivation Gating Time Constant ($\tau_h$) Lookup Table
| Membrane Potential $V$ (mV) | $\tau_h$ (ms) |
| :-------------------------- | :------------ |
| $V \le -100.0$              | 1500.00       |
| $-90.0$                     | 1583.33       |
| $-80.0$                     | 1733.33       |
| $-70.0$                     | 2033.33       |
| $-60.0$                     | 2100.00       |
| $-50.0$                     | 1666.67       |
| $-40.0$                     | 1416.67       |
| $-30.0$                     | 1166.67       |
| $-20.0$                     | 1000.00       |
| $-10.0$                     | 900.00        |
| $0.0$                       | 833.33        |
| $V \ge 10.0$                | 700.00        |

---

### KAf Channel (Fast A-type Potassium)
* **Maximum Conductance (Somatic):** $\bar{g} = 0.225$ S/cm²
* **State Variables:** $m$ (activation, squared), $h$ (inactivation)
* **Current Formula:**
  $$i_{\text{K}} = \bar{g} \cdot m^2 \cdot h \cdot (V - E_{\text{K}})$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 10.0}{17.7}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 75.6}{10.0}}}$$
* **Gating Kinetics:**
  $$\tau_h = 4.67 \text{ ms (constant)}$$
  $$\tau_m = \text{Lookup Table (linear interpolation between } -40 \text{ mV and } 50 \text{ mV)}$$

#### KAf Activation Gating Time Constant ($\tau_m$) Lookup Table
| Membrane Potential $V$ (mV) | $\tau_m$ (ms) |
| :-------------------------- | :------------ |
| $V \le -40.0$               | 0.600         |
| $-30.0$                     | 0.367         |
| $-20.0$                     | 0.333         |
| $-10.0$                     | 0.333         |
| $0.0$                       | 0.300         |
| $10.0$                      | 0.267         |
| $20.0$                      | 0.300         |
| $30.0$                      | 0.300         |
| $40.0$                      | 0.300         |
| $V \ge 50.0$                | 0.267         |

---

### KAs Channel (Slow A-type Potassium)
* **Maximum Conductance (Somatic):** $\bar{g} = 0.0104$ S/cm²
* **State Variables:** $m$ (activation, squared), $h$ (inactivation)
* **Inactivation Fraction ($a$):** 0.996 (fraction of current that inactivates; $1-a = 0.004$ is persistent)
* **Current Formula:**
  $$i_{\text{K}} = \bar{g} \cdot m^2 \cdot (a \cdot h + 1 - a) \cdot (V - E_{\text{K}})$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 27.0}{16.0}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 33.5}{21.5}}}$$
* **Gating Kinetics:**
  $$\tau_m = 0.378 + 9.91 \cdot e^{-\left(\frac{V + 34.3}{30.1}\right)^2}$$
  $$\alpha_h = e^{-\frac{V + 90.96}{29.01}}$$
  $$\beta_h = e^{\frac{V + 90.96}{100.0}}$$
  $$\tau_h = \frac{1097.4}{\alpha_h + \beta_h}$$

---

### Kir Channel (Inwardly Rectifying Potassium)
* **Maximum Conductance (Somatic):** $\bar{g} = 1.4 \times 10^{-4}$ S/cm²
* **State Variables:** $m$ (activation)
* **Current Formula:**
  $$i_{\text{K}} = \bar{g} \cdot m \cdot (V - E_{\text{K}})$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{\frac{V + 82.0}{13.0}}}$$
* **Gating Kinetics:**
  $$\tau_m = \text{Lookup Table (linear interpolation between } -100 \text{ mV and } 0 \text{ mV)}$$

#### Kir Activation Gating Time Constant ($\tau_m$) Lookup Table
| Membrane Potential $V$ (mV) | $\tau_m$ (ms) |
| :-------------------------- | :------------ |
| $V \le -100.0$              | 7.465         |
| $-90.0$                     | 8.000         |
| $-80.0$                     | 9.435         |
| $-70.0$                     | 10.755        |
| $-60.0$                     | 12.120        |
| $-50.0$                     | 13.795        |
| $-40.0$                     | 15.385        |
| $-30.0$                     | 14.285        |
| $-20.0$                     | 11.765        |
| $-10.0$                     | 8.890         |
| $V \ge 0.0$                 | 8.000         |

---

### Krp Channel (Slowly Inactivating Delayed Rectifier Potassium)
* **Maximum Conductance (Somatic):** $\bar{g} = 0.001$ S/cm²
* **State Variables:** $m$ (activation), $h$ (inactivation)
* **Inactivation Fraction ($a$):** 0.70
* **Current Formula:**
  $$i_{\text{K}} = \bar{g} \cdot m \cdot (a \cdot h + 1 - a) \cdot (V - E_{\text{K}})$$
* **Steady-State Gating:**
  $$m_{\infty} = \frac{1}{1 + e^{-\frac{V + 13.5}{11.8}}}$$
  $$h_{\infty} = \frac{1}{1 + e^{\frac{V + 54.7}{18.6}}}$$
* **Gating Kinetics:** $\tau_m$ and $\tau_h$ are determined by linear interpolation of a lookup table between $-100$ mV and $50$ mV (step size $5$ mV).

#### Krp Gating Time Constants ($\tau_m, \tau_h$) Lookup Table
| Membrane Potential $V$ (mV) | $\tau_m$ (ms) | $\tau_h$ (ms) |
| :-------------------------- | :------------ | :------------ |
| $V \le -100.0$              | 13.33         | 2333.33       |
| $-95.0$                     | 15.00         | 2333.33       |
| $-90.0$                     | 16.27         | 2333.33       |
| $-85.0$                     | 18.33         | 2333.33       |
| $-80.0$                     | 21.47         | 2333.33       |
| $-75.0$                     | 25.00         | 2333.33       |
| $-70.0$                     | 27.97         | 2333.33       |
| $-65.0$                     | 30.00         | 2333.33       |
| $-60.0$                     | 31.17         | 2333.33       |
| $-55.0$                     | 31.67         | 2333.33       |
| $-50.0$                     | 31.80         | 2333.33       |
| $-45.0$                     | 32.33         | 2333.33       |
| $-40.0$                     | 33.07         | 2333.33       |
| $-35.0$                     | 31.67         | 2333.33       |
| $-30.0$                     | 26.57         | 2333.33       |
| $-25.0$                     | 20.00         | 2333.33       |
| $-20.0$                     | 14.83         | 2333.33       |
| $-15.0$                     | 11.67         | 2333.33       |
| $-10.0$                     | 9.77          | 2333.33       |
| $-5.0$                      | 8.33          | 2333.33       |
| $0.0$                       | 6.67          | 2247.50       |
| $5.0$                       | 5.00          | 2000.00       |
| $10.0$                      | 3.87          | 1580.07       |
| $15.0$                      | 3.33          | 1166.67       |
| $20.0$                      | 3.20          | 927.77        |
| $25.0$                      | 3.33          | 833.33        |
| $30.0$                      | 3.50          | 778.77        |
| $35.0$                      | 3.33          | 733.33        |
| $40.0$                      | 2.67          | 694.50        |
| $45.0$                      | 1.67          | 666.67        |
| $V \ge 50.0$                | 1.67          | 666.67        |

---

## 3. Calcium-Activated Potassium Channels

In medium spiny neurons, calcium-activated potassium channels are selectively activated by calcium influx from specific high-voltage-gated calcium channels. Thus, both SK and BK channels read calcium levels from the submembrane N/Q/R-type pool (`cai`) rather than the L/T-type pool (`cali`).

### SK Channel (`skkca` - Small-Conductance)
* **Maximum Conductance (Somatic):** $\bar{g} = 0.145$ S/cm²
* **State Variables:** $o$ (open fraction gating variable, two-state Markov scheme: Closed $\leftrightarrow$ Open)
* **Current Formula:**
  $$i_{\text{K}} = \bar{g} \cdot o \cdot (V - E_{\text{K}})$$
* **Gating Differential Equation:**
  $$\frac{do}{dt} = \frac{o_{\infty} - o}{\tau_o}$$
* **Transition Rates & Kinetic Equations:**
  $$\alpha = \frac{[\text{Ca}]_i \cdot a_{\text{bar}}}{[\text{Ca}]_i + K_1(V)}$$
  $$\beta = \frac{b_{\text{bar}}}{1 + \frac{[\text{Ca}]_i}{K_2(V)}}$$
  $$\tau_o = \frac{s_{\text{tau}}}{\alpha + \beta}$$
  $$o_{\infty} = \frac{\alpha}{\alpha + \beta}$$
  where $K_i(V) = k_i \cdot e^{-\frac{2 \cdot d_i \cdot F \cdot V}{R \cdot T}}$ are voltage-dependent dissociation constants.
* **Thermodynamic Constants:**
  * $F$ (Faraday constant) = $96.4853$ kC/eq
  * $R$ (Gas constant) = $8.3144$ J/(mol·K)
  * $T$ (Absolute temperature) = $273.15 + \text{celsius}$ (NEURON default $35^\circ\text{C}$ $\rightarrow 308.15$ K)
* **Channel Parameters:**
  * $d_1 = 0.84$ (activation gating valence)
  * $d_2 = 1.0$ (deactivation gating valence)
  * $k_1 = 0.18$ mM (dissociation constant at 0 mV)
  * $k_2 = 0.011$ mM (dissociation constant at 0 mV)
  * $a_{\text{bar}} = 0.48$ ms⁻¹ (maximum forward rate)
  * $b_{\text{bar}} = 0.28$ ms⁻¹ (maximum backward rate)
  * $s_{\text{tau}} = 1.0$ (time constant scale factor)
  * $Q_{10} = 1.0$ (temperature scaling sensitivity)

---

### BK Channel (`bkkca` - Large-Conductance)
* **Maximum Conductance (Somatic):** $\bar{g} = 1.0 \times 10^{-3}$ S/cm²
* **State Variables:** Three-state cyclic Markov kinetic model with fractions of Closed ($C_{\text{st}}$), Open ($O_{\text{st}}$), and Inactivated ($I_{\text{st}}$) states:
  $$\begin{array}{ccc}
  & k_3([\text{Ca}], V) & \\
  C_{\text{st}} & \rightleftharpoons & O_{\text{st}} \\
  \nwarrow k_2(V) & & \swarrow k_1(V) \\
  & I_{\text{st}} &
  \end{array}$$
  Subject to conservation: $C_{\text{st}} + O_{\text{st}} + I_{\text{st}} = 1.0$.
* **Current Formula:**
  $$i_{\text{K}} = \bar{g} \cdot O_{\text{st}} \cdot (V - E_{\text{K}})$$
* **Transition Rate Constants:**
  * **$k_1$ (Open $\rightarrow$ Inactivated):** Rapid inactivation upon depolarization.
    $$k_1 = \text{alp}(0.1, V, -10.0, 1.0) = \frac{1}{0.1 + e^{\frac{V + 10.0}{1.0}} \cdot 1.0}$$
  * **$k_2$ (Inactivated $\rightarrow$ Closed):** Recovery from inactivation (favored at hyperpolarized potentials).
    $$k_2 = \text{alp}(0.1, V, -120.0, -10.0) = \frac{1}{0.1 + e^{\frac{V + 120.0}{-10.0}} \cdot 1.0}$$
  * **$k_3$ (Closed $\rightarrow$ Open):** Dual voltage and cooperative calcium gating (third-order calcium dependence).
    $$k_3 = \text{alpha}(0.001, 1.0, V, -20.0, 7.0) \cdot 1.0 \times 10^8 \cdot [\text{Ca}]_i^3$$
    where:
    $$\text{alpha}(t_{\text{min}}, t_{\text{max}}, V, V_{\text{half}}, k) = \frac{1}{t_{\text{min}} + \frac{1}{\frac{1}{t_{\text{max}} - t_{\text{min}}} + e^{\frac{V - V_{\text{half}}}{k}}}}$$
  * **$k_4$ (Open $\rightarrow$ Closed):** Deactivation closing rate.
    $$k_4 = \text{alp}(0.01, V, -44.0, -5.0) = \frac{1}{0.01 + e^{\frac{V + 44.0}{-5.0}} \cdot 1.0}$$

---

## 4. Submembrane Calcium Dynamics

The intracellular space contains two distinct, independent submembrane shell pools to prevent artificial crosstalk between channel classes:
1. **Standard Calcium Pool (`cai` / `cadyn_nqr`):** Coupled to high-threshold N-, P/Q-, and R-type calcium currents ($i_{\text{Ca}}$).
2. **L/T-type Calcium Pool (`cali` / `cadyn_lt`):** Coupled to L-type (CaV1.2, CaV1.3) and T-type calcium currents ($i_{\text{CaL}}$).

Each submembrane shell uses a Michaelis-Menten active extrusion pump and a passive decay process.

### Dynamical Differential Equations
For the standard pool ($cai$):
$$\frac{d[\text{Ca}]_i}{dt} = \text{drive}_{\text{channel}} + \text{pump} \cdot \text{drive}_{\text{pump}} + \frac{C_{\infty} - [\text{Ca}]_i}{\tau_r}$$

For the L/T-type pool ($cali$):
$$\frac{d[\text{Ca}]_{\text{L},i}}{dt} = \text{drive}_{\text{channel}} + \text{pump} \cdot \text{drive}_{\text{pump}} + \frac{C_{\infty} - [\text{Ca}]_{\text{L},i}}{\tau_r}$$

### Drive Variables & Pump Equations
* **Channel Influx:**
  $$\text{drive}_{\text{channel}} = \begin{cases} 
  \frac{-\text{drive} \cdot I_{\text{Ca}}}{2 \cdot F \cdot \text{depth} \cdot F_{\text{spine}}} & \text{if } I_{\text{Ca}} < 0 \\
  0 & \text{if } I_{\text{Ca}} \ge 0 
  \end{cases}$$
* **Michaelis-Menten Extrusion Pump:**
  $$\text{drive}_{\text{pump}} = \frac{-k_t \cdot [\text{Ca}]_i}{[\text{Ca}]_i + k_d}$$
* **Dynamics Parameters:**
  * $C_{\infty}$ (equilibrium baseline concentration) = $1.0 \times 10^{-5}$ mM ($10$ nM)
  * $\tau_r$ (exponential decay removal time constant) = $43$ ms
  * $\text{drive}$ (influx scaling coefficient) = $10000$
  * $F$ (Faraday constant) = $96489$ C/mol
  * $\text{depth}$ (submembrane shell depth) = $0.1$ $\mu$m
  * $F_{\text{spine}}$ (spine factor) = $1.0$
  * $k_t$ (maximum pump transport rate) = $1.0 \times 10^{-4}$ mM/ms
  * $k_d$ (pump dissociation constant) = $1.0 \times 10^{-4}$ mM
  * $\text{pump}$ (extrusion multiplier scaling factor) = $0.02$

---

## 5. Synaptic Receptors

Excitatory (glutamatergic AMPA and NMDA) and inhibitory (GABAergic) inputs are modeled using dual-exponential conductances.

### AMPA Synapses (Excitatory)
* **Model Type:** Dual-exponential conductance ($g = h - m$)
* **Rise Time Constant ($\tau_1$):** 1.1 ms
* **Decay Time Constant ($\tau_2$):** 5.75 ms
* **Reversal Potential ($e$):** 0 mV
* **State Equations:**
  $$m' = -\frac{m}{\tau_1}, \quad h' = -\frac{h}{\tau_2}$$
  $$\text{NetReceive: } m = m + w \cdot f_{\text{factor}}, \quad h = h + w \cdot f_{\text{factor}}$$
  where:
  $$t_p = \frac{\tau_1 \cdot \tau_2}{\tau_2 - \tau_1} \cdot \ln\left(\frac{\tau_2}{\tau_1}\right)$$
  $$f_{\text{factor}} = \frac{-1}{e^{-t_p/\tau_1} - e^{-t_p/\tau_2}}$$

### NMDA Synapses (Excitatory with Magnesium Block)
* **Model Type:** Dual-exponential conductance with voltage-dependent magnesium blocking factor $B(V)$ ($g = (h - m) \cdot B(V)$)
* **Rise Time Constant ($\tau_1$):** 2.82 ms
* **Decay Time Constant ($\tau_2$):** 160 ms
* **Reversal Potential ($e$):** 0 mV
* **External Magnesium Concentration ($[Mg^{2+}]_o$):** 1.0 mM
* **Magnesium Block Function:**
  $$B(V) = \frac{1}{1 + \frac{[\text{Mg}^{2+}]_o}{3.57} \cdot e^{-V \cdot 0.062}}$$

### GABA Synapses (Inhibitory)
* **Model Type:** Dual-exponential conductance ($g = h - m$)
* **Rise Time Constant ($\tau_1$):** 0.25 ms
* **Decay Time Constant ($\tau_2$):** 3.75 ms
* **Reversal Potential ($e$):** -60 mV

---

## 6. Morphology & Compartmental Properties

To incorporate dendritic spines without explicitly modeling them as separate compartments, the passive membrane area (capacitance $C_m$ and leak conductance $g_{\text{pas}}$) is scaled up by a **Spine Factor ($F_{\text{spine}}$)**. To preserve the original input resistance and axial electrotonic cable properties, dendritic dimensions are scaled by:
* $d_{\text{adjusted}} = d_{\text{true}} \cdot F_{\text{spine}}^{3/2}$
* $L_{\text{adjusted}} = L_{\text{true}} \cdot F_{\text{spine}}^{1/2}$

### Morphological Cable Dimensions
| Compartment Class       | Branches | Segments / Branch | True Length ($\mu$m) | True Diam ($\mu$m) | Spine Factor $F_{\text{spine}}$ | Adjusted Length ($\mu$m) | Adjusted Diam ($\mu$m) |
| :---------------------- | :------: | :---------------: | :------------------: | :----------------: | :-----------------------------: | :----------------------: | :--------------------: |
| **Soma**                |    1     |         1         |         16.0         |        16.0        |              1.00               |          16.00           |         16.00          |
| **Primary Dendrites**   |    4     |         1         |         20.0         |        2.25        |              1.00               |          20.00           |          2.25          |
| **Secondary Dendrites** |    8     |         1         |         20.0         |        1.00        |              1.33               |          24.23           |          1.10          |
| **Tertiary Dendrites**  |    16    |        11         |        190.0         |        0.50        |              3.00               |          395.20          |          0.72          |

### Specific Membrane Properties
* **Axial Resistivity ($R_a$):** 100 $\Omega\cdot\text{cm}$
* **Specific Capacitance ($C_m$):** 1.0 $\mu\text{F/cm}^2$ (scaled dynamically by $F_{\text{spine}}$ in dendrites)
* **Passive Leak Reversal ($E_{\text{pas}}$):** $-70.0$ mV
* **Passive Leak Conductance ($g_{\text{pas}}$):** $11.5 \times 10^{-6}$ S/cm² (scaled dynamically by $F_{\text{spine}}$ in dendrites)

---

### Compartmental Conductance Densities
Channel conductances are distributed differentially across the compartmental tree:

* Active conductances ($\bar{g}$) are in units of **S/cm²**.
* Calcium permeabilities ($\bar{p}$) are in units of **cm/s**.

| Mechanism                            |    Somatic Density    |    Primary Dendrites    |   Secondary Dendrites   |   Tertiary Dendrites    |
| :----------------------------------- | :-------------------: | :---------------------: | :---------------------: | :---------------------: |
| **Leak ($g_{\text{pas}}$)**          | $11.5 \times 10^{-6}$ |  $11.5 \times 10^{-6}$  |  $11.5 \times 10^{-6}$  |  $11.5 \times 10^{-6}$  |
| **NaF ($\bar{g}_{\text{naf}}$)**     |         1.50          |         0.0195          |         0.0195          |         0.0195          |
| **NaP ($\bar{g}_{\text{nap}}$)**     | $4.0 \times 10^{-5}$  | $1.3802 \times 10^{-7}$ | $1.3802 \times 10^{-7}$ | $1.3802 \times 10^{-7}$ |
| **KAf ($\bar{g}_{\text{kaf}}$)**     |         0.225         |          0.225          |        0.020584         |        0.020584         |
| **KAs ($\bar{g}_{\text{kas}}$)**     |        0.0104         |         0.0104          | $9.5142 \times 10^{-4}$ | $9.5142 \times 10^{-4}$ |
| **Kir ($\bar{g}_{\text{kir}}$)**     | $1.4 \times 10^{-4}$  |  $1.4 \times 10^{-4}$   |  $1.4 \times 10^{-4}$   |  $1.4 \times 10^{-4}$   |
| **Krp ($\bar{g}_{\text{krp}}$)**     |         0.001         |           0.0           |           0.0           |           0.0           |
| **CaL12 ($\bar{p}_{\text{cal12}}$)** | $6.7 \times 10^{-6}$  |  $6.7 \times 10^{-6}$   |  $6.7 \times 10^{-6}$   |  $6.7 \times 10^{-6}$   |
| **CaL13 ($\bar{p}_{\text{cal13}}$)** | $4.25 \times 10^{-7}$ |  $4.25 \times 10^{-7}$  |  $4.25 \times 10^{-7}$  |  $4.25 \times 10^{-7}$  |
| **CaN ($\bar{p}_{\text{can}}$)**     | $1.0 \times 10^{-5}$  |  $1.0 \times 10^{-5}$   |  $1.0 \times 10^{-5}$   |  $1.0 \times 10^{-5}$   |
| **CaR ($\bar{p}_{\text{car}}$)**     | $2.6 \times 10^{-5}$  |  $2.6 \times 10^{-5}$   |  $2.6 \times 10^{-5}$   |  $2.6 \times 10^{-5}$   |
| **CaQ ($\bar{p}_{\text{caq}}$)**     | $6.0 \times 10^{-6}$  |  $6.0 \times 10^{-6}$   |  $6.0 \times 10^{-6}$   |  $6.0 \times 10^{-6}$   |
| **CaT ($\bar{p}_{\text{cat}}$)**     | $4.0 \times 10^{-7}$  |  $4.0 \times 10^{-7}$   |  $4.0 \times 10^{-7}$   |  $4.0 \times 10^{-7}$   |
| **BK ($\bar{g}_{\text{bkkca}}$)**    |         0.001         |          0.001          |          0.001          |          0.001          |
| **SK ($\bar{g}_{\text{skkca}}$)**    |         0.145         |          0.145          |          0.145          |          0.145          |

---

### Synapse Spatial Distribution
Colocalized AMPA/NMDA (excitatory glutamatergic) synapses are targeted at spines, while GABA (inhibitory GABAergic) synapses are targeted at the somatic and dendritic shafts.

* **Glutamatergic Synapses (AMPA/NMDA):** 84 total locations
  * **Primary Dendrites:** 1 location per branch at $0.5$ (4 locations total)
  * **Secondary Dendrites:** 2 locations per branch at $0.33, 0.66$ (16 locations total)
  * **Tertiary Dendrites:** 4 locations per branch at $0.2, 0.4, 0.6, 0.8$ (64 locations total)
* **GABAergic Synapses (GABA):** 80 total locations
  * **Soma:** 16 locations at $0.5$ (16 locations total)
  * **Primary Dendrites:** 3 locations per branch at $0.25, 0.5, 0.75$ (12 locations total)
  * **Secondary Dendrites:** 3 locations per branch at $0.25, 0.5, 0.75$ (24 locations total)
  * **Tertiary Dendrites:** 2 locations per branch at $0.33, 0.66$ (32 locations total)

---

## 7. Experimental & Simulation Setups

### Standard Simulation Parameters
* **Initial Voltage ($V_{\text{init}}$):** $-87.75$ mV (reflecting hyperpolarized biological "down-state" resting potential)
* **Temperature:** $35^\circ\text{C}$ (`h.celsius`)
* **Standard Time Step ($dt$):** $0.01$ ms
* **Standard Resolution:** $100$ points/ms (`steps_per_ms`)
* **Ion Initial & Boundary Concentrations:**
  * $[\text{Ca}]_i^0$ (initial internal standard calcium) = $0.001$ mM ($1$ $\mu$M)
  * $[\text{Ca}]_o^0$ (external standard calcium) = $5.0$ mM
  * $[\text{Ca}]_{\text{L},i}^0$ (initial internal L/T-type calcium) = $0.001$ mM ($1$ $\mu$M)
  * $[\text{Ca}]_{\text{L},o}^0$ (external L/T-type calcium) = $5.0$ mM

### Current Clamp Protocols
* **Somatic Injection Sweeps (`IClamp.py`):**
  * Stimulus duration = $500.0$ ms
  * Stimulus onset delay = $200.0$ ms
  * Total simulation time = $900.0$ ms
  * Injection amplitudes tested:
    * $+0.271$ nA: Triggers action potential spike trains.
    * $+0.248$ nA: Triggers near-threshold subthreshold depolarizations.
    * $-0.227$ nA: Triggers hyperpolarization to characterize strong inward rectification (Kir).
* **Delayed Excitation & KAs Modulation Sweep (`chan_currents.py`):**
  * Stimulus amplitude = $+0.232$ nA
  * Stimulus duration = $600.0$ ms
  * Stimulus onset delay = $100.0$ ms
  * Total simulation time = $800.0$ ms
  * Condition sweeps scale the slow KAs inactivation variable `a_kas` by factors of $1.0$ (Control), $0.6$ (decreased delay), and $1.4$ (increased delay) to study its role in late-firing action potentials.
* **I-V Relationship Sweep (`current_volt_freq.py`):**
  * Stimulus amplitude sweeps: 20 linear increments between $-0.2$ nA ($-200$ pA) and $+0.2$ nA ($+200$ pA).
  * Stimulus duration = $500.0$ ms
  * Stimulus onset delay = $100.0$ ms
  * Somatic potential measured at $t = 550.0$ ms (450 ms after stimulus onset, to capture steady-state rectifying behavior).
* **F-I Firing Frequency Sweep (`current_volt_freq.py`):**
  * Stimulus amplitude sweeps: 15 linear increments between $+0.15$ nA and $+0.45$ nA.
  * Stimulus duration = $500.0$ ms
  * Stimulus onset delay = $100.0$ ms
  * Spike frequency calculated as $F = \frac{\text{spike\_count}}{0.5 \text{ s}}$ for spikes occurring during the injection window ($100.0$ to $600.0$ ms).