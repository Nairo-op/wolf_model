TITLE Slowly Inactivating Delayed Rectifier Potassium Channel Current (Krp)

COMMENT
Implements a slowly inactivating / delayed rectifier-like potassium current (Krp).
- Maximum conductance: gbar = 0.001 S/cm2 (somatic default).
- State variables: m (activation) and h (inactivation).
- Gating formula: ik = gbar * m * (a * h + (1 - a)) * (v - ek)
  where 'a' represents the inactivation contribution fraction (default: 0.7).
- Kinetics: Both mtau and htau are derived using linear interpolation from lookup tables in 
  the range of -100 mV to 50 mV with a step size of 5 mV.
ENDCOMMENT

NEURON {
    SUFFIX krp
    USEION k READ ek WRITE ik
    RANGE gbar, ik, a, minf, hinf, mtau, htau
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S) = (siemens)
}

PARAMETER {
    gbar = 0.001 (S/cm2) 
    a = 0.7             
}

ASSIGNED {
    v (mV)
    ek (mV)
    ik (mA/cm2)
    minf
    mtau (ms)
    hinf
    htau (ms)
}

STATE {
    m                     
    h                     
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ik = gbar * m * (a * h + (1.0 - a)) * (v - ek)
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
    }
}