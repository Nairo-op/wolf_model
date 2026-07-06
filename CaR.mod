TITLE CaR type channel

NEURON {
    SUFFIX car
    USEION ca READ eca, cai, cao WRITE ica
    RANGE pbar, ica, a
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
    pbar = 2.6e-5 (cm/s)
    FARADAY = 96485 (coulomb)
    R = 8.3145 (joule/degC)            
}

ASSIGNED {
    v (mV)
    eca (mV)
    ica (mA/cm2)
    cao (mM)
    cai (mM)
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
    ica = pbar * m * m * m * h *  ghk(v, cai, cao)
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
    
    mtau = 1.7
    
    minf = 1 / (1 + exp( - (v + 10.3) / 6.6))

    hinf = 1 / (1 + exp((v + (33.3)) / 17.0))

    : --- HARDCODED LINEAR INTERPOLATION FOR CAR (htau) ---
    : Range bounds: -30.0 mV to 10.0 mV, Step size: 10.0 mV
    
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
    }
}

FUNCTION ghk(v(mV), cai(mM), cao(mM) ) (millicoul/cm3) {
    LOCAL v_nu, f

    f = (1000) * R * (celsius + 273.15) / (2 * FARADAY) :RT/zF

    if (fabs(v) < 1e-4) {
        ghk = f * (cai - cao )
    } else {
        v_nu = v / f
        ghk = v_nu * (cai - cao * exp(-v_nu)) / (1 - exp(-v_nu))
    }
}