TITLE 

NEURON {
    SUFFIX nap
    USEION na READ ena WRITE ina
    RANGE gbar, ina
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S) = (siemens)
}

PARAMETER {
    gbar = 4.0e-5 (S/cm2) : for soma
    : for dendrite gbar = 1.38 * 10^(-7) (S/cm2)
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
    ina = gbar * m * h * (v - ena)
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

    minf = 1.0 / (1.0 + exp((v - (-52.6)) / (-4.6)))
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