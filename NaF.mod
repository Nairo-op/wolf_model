TITLE 

NEURON {
    SUFFIX naf
    USEION na READ ena WRITE ina
    RANGE gbar, ina
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S) = (siemens)
}

PARAMETER {
    gbar = 1.5 (S/cm2)
}

STATE {
    m                     
    h                     
}

ASSIGNED {
    v (mV)
    ena (mV)
    ina (mA/cm2)
    minf
    mtau (ms)
    hinf
    htau (ms)
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ina = gbar * m * m * m * h * (v - ena)
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

    minf = 1 / (1 + exp((v - (-23.9)) / -11.8))
    hinf = 1 / (1 + exp((v - (-62.9)) / 10.7))

    : --- HARDCODED LINEAR INTERPOLATION FOR NAF (mtau & htau) ---
    : Range bounds: -80.0 mV to 30.0 mV, Step size: 10.0 mV
    
    if (v <= -80.0) {
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
    }
}
