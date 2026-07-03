TITLE 

NEURON {
    SUFFIX kaf
    USEION k READ ek WRITE ik
    RANGE gbar, ik
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S) = (siemens)
}

PARAMETER {
    gbar = 0.225 (S/cm2)
    : 0.021 (S/cm2) in Distal dendrites
}

STATE {
    m                     
    h                     
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

BREAKPOINT {
    SOLVE states METHOD cnexp
    ik = gbar * m^2 * h * (v - ek)
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