TITLE 

NEURON {
    SUFFIX kir
    USEION k READ ek WRITE ik
    RANGE gbar, ik
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S) = (siemens)
}

PARAMETER {
    gbar = 1.4e-4 (S/cm2)
}

STATE {
    m                                     
}

ASSIGNED {
    v (mV)
    ek (mV)
    ik (mA/cm2)
    minf
    mtau (ms)
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ik = gbar * m * (v - ek)
}

INITIAL {
    rates(v)
    m = minf
}

DERIVATIVE states {
    rates(v)
    m' = (minf - m) / mtau
}

PROCEDURE rates(v (mV)) {
    LOCAL v_idx, fraction
    
    minf = 1 / (1 + exp((v - (-82.0)) / 13.0))

    : --- HARDCODED LINEAR INTERPOLATION FOR KIR (mtau) ---
    : Range bounds: -100.0 mV to 0.0 mV, Step size: 10.0 mV
    
    if (v <= -100.0) {
        mtau = 14.93
    } else if (v >= 0.0) {
        mtau = 16.0
    } else {
        : Map voltage to table index (step size is 10 mV, starting at -100 mV)
        v_idx = floor((v - (-100.0)) / 10.0)
        fraction = ((v - (-100.0)) / 10.0) - v_idx
        
        : Perform linear interpolation based on index
        if (v_idx == 0) { 
            mtau = 14.93 + fraction * (16.0 - 14.93)
        }
        else if (v_idx == 1) { 
            mtau = 16.0 + fraction * (18.87 - 16.0)
        }
        else if (v_idx == 2) { 
            mtau = 18.87 + fraction * (21.51 - 18.87)
        }
        else if (v_idx == 3) { 
            mtau = 21.51 + fraction * (24.24 - 21.51)
        }
        else if (v_idx == 4) { 
            mtau = 24.24 + fraction * (27.59 - 24.24)
        }
        else if (v_idx == 5) { 
            mtau = 27.59 + fraction * (30.77 - 27.59)
        }
        else if (v_idx == 6) { 
            mtau = 30.77 + fraction * (28.57 - 30.77)
        }
        else if (v_idx == 7) { 
            mtau = 28.57 + fraction * (23.53 - 28.57)
        }
        else if (v_idx == 8) { 
            mtau = 23.53 + fraction * (17.78 - 23.53)
        }
        else if (v_idx == 9) { 
            mtau = 17.78 + fraction * (16.0 - 17.78)
        }
    }
}