# Data used in mod files

## Calcium  (L & T )

### CaQ Channel

Q-type calcium channel (CaQ) uses the GHK current equation.
    - Permeability: pbar = 6e-6 cm/s (somatic default).
    - State variables: m (activation, squared). 
    - No inactivation is modeled.
    - Gating formula: ica = pbar * m^2 * ghk(v, cai, cao)
    - Kinetics: Steady-state activation minf is voltage-dependent
    - minf = 1 / (1 + exp( - (v + 9.0) / 6.6))
    - time constant mtau is fixed at 0.377 ms.

### CaN

 N-type Calcium Channel Current (CaN)

N-type calcium channel (CaN) uses the GHK current equation.
- Permeability: pbar = 1e-5 cm/s (somatic default).
- State variables: m (activation, squared) and h (inactivation).
- Gating formula: ica = pbar * m^2 * (a * h + (1 - a)) * ghk(v, cai, cao)
  where 'a' is the inactivation contribution fraction (default: 0.21).
- Kinetics: Gating rate time constants (mtau, htau) are calculated analytically.
- m_alpha = 0.1157 * (v + 17.19)/ (exp((v + 17.19)/15.22) - 1)
- m_beta = 1.15 * exp(v / 23.82)
- minf = 1 / ( 1 + exp(-(v + 8.7) / 7.4))
- mtau = 1 / (m_alpha + m_beta)
- htau = 23.33
- hinf = 1 / (1 + exp((v + 74.8) / 6.5))

### CaR

R-type Calcium Channel Current (CaR)


- R-type calcium channel (CaR) uses the GHK current equation.
- Permeability: pbar = 2.6e-5 cm/s (somatic default).
- State variables: m (activation, cubed) and h (inactivation).
- Gating formula: ica = pbar * m^3 * h * ghk(v, cai, cao)
- Kinetics: Activation time-constant mtau is fixed at 1.7 ms. 
- Inactivation time-constant htau is derived via linear interpolation of a hardcoded lookup table in the range of -30 mV to 10 mV.

 if (v <= -30.0) {
        htau = 33.33
    } else if (v >= 10.0) {
        htau = 6.67
    } else {
        : Map voltage to table index (step size is 10 mV, starting at -30 mV)
        v_idx = floor((v - (-30.0)) / 10.0)
        fraction = ((v - (-30.0)) / 10.0) - v_idx
        
        : Perform linear interpolation based on index
        if (v_idx == 0) { 
            htau = 33.33 + fraction * (21.67 - 33.33)
        }
        else if (v_idx == 1) { 
            htau = 21.67 + fraction * (11.67 - 21.67)
        }
        else if (v_idx == 2) { 
            htau = 11.67 + fraction * (10.0 - 11.67)
        }
        else if (v_idx == 3) { 
            htau = 10.0 + fraction * (6.67 - 10.0)
        }


### CaT
T-type Calcium Channel Current (CaT)

Low-threshold T-type calcium channel (CaT), uses the GHK current equation.
- Permeability: pbar = 4e-7 cm/s (somatic default).
- State variables: m (activation, cubed) and h (inactivation).
- Gating formula: ical = pbar * m^3 * h * ghk(v, cali, calo)
- Kinetics: Gating rate time constants (mtau, htau) are calculated using hardcoded linear interpolation lookup tables over the range of -65 mV to 10 mV with a step size of 5 mV. 
- minf and hinf are calculated using analytical equations.
- minf = 1 / (1 + exp(- (v + (51.73)) / 6.53))
- hinf = 1 / (1 + exp((v + (80.0)) / 6.7))


    if (v <= -65.0) {
        mtau = 6.73
        htau = 127.33
    } else if (v >= 10.0) {
        mtau = 1.1
        htau = 36.67
    } else {
        : Map voltage to table index (step size is 5 mV, starting at -65 mV)
        v_idx = floor((v - (-65.0)) / 5.0)
        fraction = ((v - (-65.0)) / 5.0) - v_idx
        
        : Perform linear interpolation based on index
        if (v_idx == 0) { 
            mtau = 6.73 + fraction * (6.73 - 6.73) 
            htau = 127.33 + fraction * (69.33 - 127.33)
        }
        else if (v_idx == 1) { 
            mtau = 6.73 + fraction * (4.37 - 6.73) 
            htau = 69.33 + fraction * (54.0 - 69.33)
        }
        else if (v_idx == 2) { 
            mtau = 4.37 + fraction * (2.9 - 4.37) 
            htau = 54.0 + fraction * (43.0 - 54.0)
        }
        else if (v_idx == 3) { 
            mtau = 2.9 + fraction * (2.27 - 2.9) 
            htau = 43.0 + fraction * (39.67 - 43.0)
        }
        else if (v_idx == 4) { 
            mtau = 2.27 + fraction * (1.87 - 2.27) 
            htau = 39.67 + fraction * (35.67 - 39.67)
        }
        else if (v_idx == 5) { 
            mtau = 1.87 + fraction * (1.47 - 1.87) 
            htau = 35.67 + fraction * (35.67 - 35.67)
        }
        else if (v_idx == 6) { 
            mtau = 1.47 + fraction * (1.27 - 1.47) 
            htau = 35.67 + fraction * (35.67 - 35.67)
        }
        else if (v_idx == 7) { 
            mtau = 1.27 + fraction * (1.2 - 1.27) 
            htau = 35.67 + fraction * (36.0 - 35.67)
        }
        else if (v_idx == 8) { 
            mtau = 1.2 + fraction * (1.1 - 1.2) 
            htau = 36.0 + fraction * (36.33 - 36.0)
        }
        else if (v_idx == 9) { 
            mtau = 1.1 + fraction * (1.2 - 1.1) 
            htau = 36.33 + fraction * (36.33 - 36.33)
        }
        else if (v_idx == 10) { 
            mtau = 1.2 + fraction * (1.2 - 1.2) 
            htau = 36.33 + fraction * (36.67 - 36.33)
        }
        else if (v_idx == 11) { 
            mtau = 1.2 + fraction * (1.1 - 1.2) 
            htau = 36.67 + fraction * (36.67 - 36.67)
        }
        else if (v_idx == 12) { 
            mtau = 1.1 + fraction * (1.1 - 1.1) 
            htau = 36.67 + fraction * (36.67 - 36.67)
        }
        else if (v_idx == 13) { 
            mtau = 1.1 + fraction * (1.1 - 1.1) 
            htau = 36.67 + fraction * (36.67 - 36.67)
        }
        else if (v_idx == 14) { 
            mtau = 1.1 + fraction * (1.1 - 1.1) 
            htau = 36.67 + fraction * (36.67 - 36.67)
        }
    }


### CaL12
CaL 1.2 L-type Calcium Channel (Moczydlowski & Latorre 1983)


High-threshold CaL 1.2 L-type calcium channel.
- Flux calculation: Uses the Goldman-Hodgkin-Katz (GHK) current equation.
- Permeability: pbar = 6.7e-6 cm/s (somatic default).
- State variables: m (activation, squared) and h (inactivation).
- Gating formula: ical = pbar * m^2 * (a * h + (1 - a)) * ghk(v, cali, calo)
  where 'a' is the inactivation contribution fraction (default: 0.17).
- Kinetics: Activation/inactivation rates (minf, mtau, hinf, htau) are calculated analytically.
- m_alpha = 0.1194 * v / (exp(v / 9.005) - 1)
- m_beta = 2.97 * exp(v / 31.4)
- minf = 1 / (1 + exp(- (v + 8.9) / 6.7)) 
- mtau = 1 / (m_alpha + m_beta)
- htau = 14.77
- hinf = 1 / (1 + exp((v + 13.4) / 11.9))


References:
- Moczydlowski E, Latorre R (1983) J Gen Physiol 82:511-542.
- Wolf JA et al. (2005) J Neurosci 25:9080-9095.

### CaL13

CaL 1.3 L-type Calcium Channel (Moczydlowski & Latorre 1983)


Implements the high-threshold CaL 1.3 L-type calcium channel.
- Flux calculation: Uses the Goldman-Hodgkin-Katz (GHK) current equation.
- Permeability: pbar = 6.7e-6 cm/s (somatic default).
- State variables: m (activation, squared) and h (inactivation).
- Gating formula: ical = pbar * m^2 * (a * h + (1 - a)) * ghk(v, cali, calo)
  where 'a' is the inactivation contribution fraction (default: 0.17).
- Kinetics: Activation/inactivation rates (minf, mtau, hinf, htau) are calculated analytically.

- m_alpha = 0.1194 * v / (exp(v / 9.005) - 1)
- m_beta = 2.97 * exp(v / 31.4)
- mtau = 1 / (m_alpha + m_beta)
- minf = 1 / (1 + exp(- (v + 33.0) / 6.7)) 
- htau = 14.77
- hinf = 1 / (1 + exp((v + 13.4) / 11.9))

References:
- Moczydlowski E, Latorre R (1983) J Gen Physiol 82:511-542.
- Wolf JA et al. (2005) J Neurosci 25:9080-9095.



## Pottassium & Sodium

### NaF
Fast Transient Sodium Channel Current (NaF)


Implements the fast transient action-potential-generating sodium current (NaF).
- Maximum conductance: gbar = 1.5 S/cm2 (somatic default).
- State variables: m (activation, cubed) and h (inactivation).
- Gating formula: ina = gbar * m^3 * h * (v - ena)
- Kinetics: Activation/inactivation rate time constants (mtau, htau) are calculated using linear interpolation lookup tables over the range of -80 mV to 30 mV with a 10 mV step size.
- minf, hinf calculated analytically
- minf = 1 / (1 + exp((v - (-23.9)) / -11.8))
- hinf = 1 / (1 + exp((v - (-62.9)) / 10.7))
- if (v <= -80.0) {
        mtau = 0.023
        htau = 0.433
    } else if (v >= 30.0) {
        mtau = 0.020
        htau = 0.093
    } else {
        : Map voltage to table index (step size is 10 mV, starting at -80 mV)
        v_idx = floor((v - (-80.0)) / 10.0)
        fraction = ((v - (-80.0)) / 10.0) - v_idx
        
        : Perform linear interpolation based on index
        if (v_idx == 0) { 
            mtau = 0.023 + fraction * (0.03 - 0.023) 
            htau = 0.433 + fraction * (0.433 - 0.433)
        }
        else if (v_idx == 1) { 
            mtau = 0.03 + fraction * (0.037 - 0.03) 
            htau = 0.433 + fraction * (0.433 - 0.433)
        }
        else if (v_idx == 2) { 
            mtau = 0.037 + fraction * (0.043 - 0.037) 
            htau = 0.433 + fraction * (0.433 - 0.433)
        }
        else if (v_idx == 3) { 
            mtau = 0.043 + fraction * (0.067 - 0.043) 
            htau = 0.433 + fraction * (0.433 - 0.433)
        }
        else if (v_idx == 4) { 
            mtau = 0.067 + fraction * (0.107 - 0.067) 
            htau = 0.433 + fraction * (0.433 - 0.433)
        }
        else if (v_idx == 5) { 
            mtau = 0.107 + fraction * (0.053 - 0.107) 
            htau = 0.433 + fraction * (0.283 - 0.433)
        }
        else if (v_idx == 6) { 
            mtau = 0.053 + fraction * (0.05 - 0.053) 
            htau = 0.283 + fraction * (0.167 - 0.283)
        }
        else if (v_idx == 7) { 
            mtau = 0.05 + fraction * (0.04 - 0.05) 
            htau = 0.167 + fraction * (0.15 - 0.167)
        }
        else if (v_idx == 8) { 
            mtau = 0.04 + fraction * (0.027 - 0.04) 
            htau = 0.15 + fraction * (0.107 - 0.15)
        }
        else if (v_idx == 9) { 
            mtau = 0.027 + fraction * (0.02 - 0.027) 
            htau = 0.107 + fraction * (0.1 - 0.107)
        }
        else if (v_idx == 10) { 
            mtau = 0.02 + fraction * (0.02 - 0.02) 
            htau = 0.1 + fraction * (0.093 - 0.1)
        }
    


### NaP

Persistent Sodium Channel Current (NaP)

Implements the persistent sodium current (NaP).
- Maximum conductance: gbar = 4e-5 S/cm2 (somatic default).
- State variables: m (activation) and h (slow inactivation).
- Gating formula: ina = gbar * m * h * (v - ena)
- Kinetics: Activation time-constant mtau is calculated analytically. Inactivation time-constant htau is obtained using linear interpolation lookup tables in the range of -100 mV to 10 mV.
-  minf = 1.0 / (1.0 + exp((v - (-52.6)) / (-4.6)))
    hinf = 1.0 / (1.0 + exp((v - (-48.8)) / 10))

    if (v < -40){
    mtau = 0.025 + 0.14 * exp((v + 40) / 10)
    }
    else {
    mtau = 0.02 + 0.145 * exp(-(v + 40) / 10)
    }

    : --- HARDCODED LINEAR INTERPOLATION FOR NAP (htau) ---
    : Range bounds: -100.0 mV to 10.0 mV, Step size: 10.0 mV
    
    if (v <= -100.0) {
        htau = 1500.0
    } else if (v >= 10.0) {
        htau = 700.0
    } else {
        : Map voltage to table index (step size is 10 mV, starting at -100 mV)
        v_idx = floor((v - (-100.0)) / 10.0)
        fraction = ((v - (-100.0)) / 10.0) - v_idx
        
        : Perform linear interpolation based on index
        if (v_idx == 0) { 
            htau = 1500.0 + fraction * (1583.33 - 1500.0)
        }
        else if (v_idx == 1) { 
            htau = 1583.33 + fraction * (1733.33 - 1583.33)
        }
        else if (v_idx == 2) { 
            htau = 1733.33 + fraction * (2033.33 - 1733.33)
        }
        else if (v_idx == 3) { 
            htau = 2033.33 + fraction * (2100.0 - 2033.33)
        }
        else if (v_idx == 4) { 
            htau = 2100.0 + fraction * (1666.67 - 2100.0)
        }
        else if (v_idx == 5) { 
            htau = 1666.67 + fraction * (1416.67 - 1666.67)
        }
        else if (v_idx == 6) { 
            htau = 1416.67 + fraction * (1166.67 - 1416.67)
        }
        else if (v_idx == 7) { 
            htau = 1166.67 + fraction * (1000.0 - 1166.67)
        }
        else if (v_idx == 8) { 
            htau = 1000.0 + fraction * (900.0 - 1000.0)
        }
        else if (v_idx == 9) { 
            htau = 900.0 + fraction * (833.33 - 900.0)
        }
        else if (v_idx == 10) { 
            htau = 833.33 + fraction * (700.0 - 833.33)
        }
    }
}


### KAf

 Fast A-type Potassium Channel Current (KAf)

Fast-activating and fast-inactivating A-type potassium current (KAf) for NAcb MSNs.
- Maximum conductance: gbar = 0.225 S/cm2 (somatic default).
- State variables: m (activation, squared) and h (inactivation).
- Gating formula: ik = gbar * m^2 * h * (v - ek)
- Kinetics: Inactivation time-constant htau is fixed at 4.67 ms. Activation time-constant mtau 
  is derived using linear interpolation from a hardcoded lookup table in the range of -40 mV to 50 mV.
References:
- Wolf et al. (2005) J Neurosci 25:9080-9095.
- McGeorge & Allison (1998).


minf = 1 / (1 + exp((v - (-10.0)) / -17.7))
    htau = 4.67
    hinf = 1 / (1 + exp((v - (-75.6)) / 10.0))
    
    : --- HARDCODED LINEAR INTERPOLATION FOR KAF (mtau) ---
    : Range bounds: -40.0 mV to 50.0 mV, Step size: 10.0 mV
    
    if (v <= -40.0) {
        mtau = 0.6
    } else if (v >= 50.0) {
        mtau = 0.267
    } else {
        : Map voltage to table index (step size is 10 mV, starting at -40 mV)
        v_idx = floor((v - (-40.0)) / 10.0)
        fraction = ((v - (-40.0)) / 10.0) - v_idx
        
        : Perform linear interpolation based on index
        if (v_idx == 0) { 
            mtau = 0.6 + fraction * (0.367 - 0.6)
        }
        else if (v_idx == 1) { 
            mtau = 0.367 + fraction * (0.333 - 0.367)
        }
        else if (v_idx == 2) { 
            mtau = 0.333 + fraction * (0.333 - 0.333)
        }
        else if (v_idx == 3) { 
            mtau = 0.333 + fraction * (0.3 - 0.333)
        }
        else if (v_idx == 4) { 
            mtau = 0.3 + fraction * (0.267 - 0.3)
        }
        else if (v_idx == 5) { 
            mtau = 0.267 + fraction * (0.3 - 0.267)
        }
        else if (v_idx == 6) { 
            mtau = 0.3 + fraction * (0.3 - 0.3)
        }
        else if (v_idx == 7) { 
            mtau = 0.3 + fraction * (0.3 - 0.3)
        }
        else if (v_idx == 8) { 
            mtau = 0.3 + fraction * (0.267 - 0.3)
        }
    }
}


### KAs
 Slowly Inactivating A-type Potassium Channel Current (KAs)


Slowly activating and slowly inactivating potassium current (KAs).
- Maximum conductance: gbar = 0.0104 S/cm2 (somatic default).
- State variables: m (activation, squared) and h (inactivation).
- Gating formula: ik = gbar * m^2 * (a * h + (1 - a)) * (v - ek)
  where 'a' is the inactivation contribution fraction (default: 0.996).
- Kinetics: Gating rate time constants (mtau, htau) are calculated analytically.

    minf = 1.0 / (1.0 + exp((v - (-27.0)) / (-16.0)))
    
    mtau = 0.378 + 9.91 * exp(-pow(((v + 34.3) / 30.1), 2))

    hinf = 1.0 / (1.0 + exp((v - (-33.5)) / 21.5))
    
    h_alpha = 1.0 * exp(-(v + 90.96) / 29.01)
    h_beta = 1.0 * exp((v + 90.96) / 100.0)
    
    htau = 1097.4 / (h_alpha + h_beta)




### Kir
Inwardly Rectifying Potassium Channel Current (Kir)


Implements the inwardly rectifying potassium current (Kir) active at hyperpolarized potentials.
- Maximum conductance: gbar = 1.4e-4 S/cm2 (somatic default).
- State variables: m (activation).
- Gating formula: ik = gbar * m * (v - ek)
- Kinetics: Steady-state activation minf is calculated analytically. Time-constant mtau is 
  obtained using linear interpolation from a hardcoded lookup table between -100 mV and 0 mV.


    minf = 1 / (1 + exp((v + 82.0) / 13.0))

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
            mtau = 7.465 + fraction * (8.0 - 7.465)
        }
        else if (v_idx == 1) { 
            mtau = 8.0 + fraction * (9.435 - 8.0)
        }
        else if (v_idx == 2) { 
            mtau = 9.435 + fraction * (10.755 - 9.435)
        }
        else if (v_idx == 3) { 
            mtau = 10.755 + fraction * (12.12 - 10.755)
        }
        else if (v_idx == 4) { 
            mtau = 12.12 + fraction * (13.795 - 12.12)
        }
        else if (v_idx == 5) { 
            mtau = 13.795 + fraction * (15.385 - 13.795)
        }
        else if (v_idx == 6) { 
            mtau = 15.385 + fraction * (14.285 - 15.385)
        }
        else if (v_idx == 7) { 
            mtau = 14.285 + fraction * (11.765 - 14.285)
        }
        else if (v_idx == 8) { 
            mtau = 11.765 + fraction * (8.89 - 11.765)
        }
        else if (v_idx == 9) { 
            mtau = 8.89 + fraction * (8.0 - 8.89)
        }

### Krp
 Slowly Inactivating Delayed Rectifier Potassium Channel Current (Krp)


Implements a slowly inactivating / delayed rectifier-like potassium current (Krp).
- Maximum conductance: gbar = 0.001 S/cm2 (somatic default).
- State variables: m (activation) and h (inactivation).
- Gating formula: ik = gbar * m * (a * h + (1 - a)) * (v - ek)
  where 'a' represents the inactivation contribution fraction (default: 0.7).
- Kinetics: Both mtau and htau are derived using linear interpolation from lookup tables in 
  the range of -100 mV to 50 mV with a step size of 5 mV.

minf = 1 / (1 + exp((v - (-13.5)) / -11.8))
hinf = 1 / (1 + exp((v - (-54.7)) / 18.6))
    
    : Note: Insert your equations for minf and hinf here if you have them.

    : --- HARDCODED LINEAR INTERPOLATION FOR KRP (mtau & htau) ---
    : Range bounds: -100.0 mV to 50.0 mV, Step size: 5.0 mV
    
    if (v <= -100.0) {
        mtau = 13.33
        htau = 2333.33
    } else if (v >= 50.0) {
        mtau = 1.67
        htau = 666.67
    } else {
        : Map voltage to table index (step size is 5 mV, starting at -100 mV)
        v_idx = floor((v - (-100.0)) / 5.0)
        fraction = ((v - (-100.0)) / 5.0) - v_idx
        
        : Perform linear interpolation based on index
        if (v_idx == 0) { 
            mtau = 13.33 + fraction * (15.0 - 13.33) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 1) { 
            mtau = 15.0 + fraction * (16.27 - 15.0) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 2) { 
            mtau = 16.27 + fraction * (18.33 - 16.27) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 3) { 
            mtau = 18.33 + fraction * (21.47 - 18.33) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 4) { 
            mtau = 21.47 + fraction * (25.0 - 21.47) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 5) { 
            mtau = 25.0 + fraction * (27.97 - 25.0) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 6) { 
            mtau = 27.97 + fraction * (30.0 - 27.97) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 7) { 
            mtau = 30.0 + fraction * (31.17 - 30.0) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 8) { 
            mtau = 31.17 + fraction * (31.67 - 31.17) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 9) { 
            mtau = 31.67 + fraction * (31.8 - 31.67) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 10) { 
            mtau = 31.8 + fraction * (32.33 - 31.8) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 11) { 
            mtau = 32.33 + fraction * (33.07 - 32.33) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 12) { 
            mtau = 33.07 + fraction * (31.67 - 33.07) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 13) { 
            mtau = 31.67 + fraction * (26.57 - 31.67) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 14) { 
            mtau = 26.57 + fraction * (20.0 - 26.57) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 15) { 
            mtau = 20.0 + fraction * (14.83 - 20.0) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 16) { 
            mtau = 14.83 + fraction * (11.67 - 14.83) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 17) { 
            mtau = 11.67 + fraction * (9.77 - 11.67) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 18) { 
            mtau = 9.77 + fraction * (8.33 - 9.77) 
            htau = 2333.33 + fraction * (2333.33 - 2333.33)
        }
        else if (v_idx == 19) { 
            mtau = 8.33 + fraction * (6.67 - 8.33) 
            htau = 2333.33 + fraction * (2247.5 - 2333.33)
        }
        else if (v_idx == 20) { 
            mtau = 6.67 + fraction * (5.0 - 6.67) 
            htau = 2247.5 + fraction * (2000.0 - 2247.5)
        }
        else if (v_idx == 21) { 
            mtau = 5.0 + fraction * (3.87 - 5.0) 
            htau = 2000.0 + fraction * (1580.07 - 2000.0)
        }
        else if (v_idx == 22) { 
            mtau = 3.87 + fraction * (3.33 - 3.87) 
            htau = 1580.07 + fraction * (1166.67 - 1580.07)
        }
        else if (v_idx == 23) { 
            mtau = 3.33 + fraction * (3.2 - 3.33) 
            htau = 1166.67 + fraction * (927.77 - 1166.67)
        }
        else if (v_idx == 24) { 
            mtau = 3.2 + fraction * (3.33 - 3.2) 
            htau = 927.77 + fraction * (833.33 - 927.77)
        }
        else if (v_idx == 25) { 
            mtau = 3.33 + fraction * (3.5 - 3.33) 
            htau = 833.33 + fraction * (778.77 - 833.33)
        }
        else if (v_idx == 26) { 
            mtau = 3.5 + fraction * (3.33 - 3.5) 
            htau = 778.77 + fraction * (733.33 - 778.77)
        }
        else if (v_idx == 27) { 
            mtau = 3.33 + fraction * (2.67 - 3.33) 
            htau = 733.33 + fraction * (694.5 - 733.33)
        }
        else if (v_idx == 28) { 
            mtau = 2.67 + fraction * (1.67 - 2.67) 
            htau = 694.5 + fraction * (666.67 - 694.5)
        }
        else if (v_idx == 29) { 
            mtau = 1.67 + fraction * (1.67 - 1.67) 
            htau = 666.67 + fraction * (666.67 - 666.67)
        }
 
## skkca, bkkca




## Ca dynamics both pools
## Synapses (AMPA, NMDA, GABA)


# Morphology and conductance data

## Morphological dimensions
## Conductance data
## Strcutural insights
## Synapses distribution


# Experimental setups