TITLE T-type Calcium Channel Current (CaT)

COMMENT
Implements the low-threshold T-type calcium channel (CaT) using the GHK current equation.
- Permeability: pbar = 4e-7 cm/s (somatic default).
- State variables: m (activation, cubed) and h (inactivation).
- Gating formula: ical = pbar * m^3 * h * ghk(v, cali, calo)
- Kinetics: Gating rate time constants (mtau, htau) are calculated using hardcoded linear 
  interpolation lookup tables over the range of -65 mV to 10 mV with a step size of 5 mV.
ENDCOMMENT

NEURON {
    SUFFIX cat
    USEION cal READ ecal, cali, calo WRITE ical
    RANGE pbar, icl, a, minf, hinf, htau, mtau
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S) = (siemens)
    (mM) = (milli/liter)
    (molar) = (1/liter)
    (cm/s) = (centimeter/second)
}

PARAMETER {
    pbar = 4e-7 (cm/s)
    FARADAY = 96485 (coulomb)
    R = 8.3145 (joule/degC)            
}

ASSIGNED {
    v (mV)
    ecal (mV)
    ical (mA/cm2)
    cali (mM)
    calo (mM)
    minf
    mtau (ms)
    hinf
    htau (ms)
    celsius (degC)
}

STATE {
    m                        
    h                     
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ical = pbar * m * m * m * h * ghk(v, cali, calo)
}

INITIAL {
    rates(v)
    m = minf
    h = hinf
}

DERIVATIVE states {
    rates(v)
    m' = (minf - m) / mtau
    h' = (hinf - h) / htau
}


PROCEDURE rates(v (mV)) {
    LOCAL v_idx, fraction
    
    minf = 1 / (1 + exp(- (v + (51.73)) / 6.53))
    hinf = 1 / (1 + exp((v + (80.0)) / 6.7))

    : --- HARDCODED LINEAR INTERPOLATION FOR CAT (mtau & htau) ---
    : Range bounds: -65.0 mV to 10.0 mV, Step size: 5.0 mV
    
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
}

FUNCTION ghk(v(mV), ci(mM), co(mM)) (millicoul/cm3) {
    LOCAL w, e

    w = v * (0.001) * 2 * FARADAY / (R * (celsius + 273.16))

    if (fabs(w) > 1e-4) {
        e = w / (exp(w) - 1)
    } else {
        e = 1 - w / 2
    }
    
    ghk = - (0.001) * 2 * FARADAY * (co - ci* exp(w)) * e
}