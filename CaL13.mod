TITLE CaL 1.3 L-type calcium channel (Moczydlowski and Latorre 1983)

NEURON {
    SUFFIX cal13
    USEION cl READ cli, clo, ecl WRITE icl VALENCE 2
    RANGE pbar, icl
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (molar) = (1/liter)
    (mM) = (millimolar)
    (cm/s) = (centimeter/second)
    FARADAY = (faraday) (kilocoulombs)
    R = (k-mole) (joule/degC)
}

PARAMETER {
    pbar = 4.25e-7 (cm/s)            
}

ASSIGNED {
    v (mV)
    ecl (mV)
    icl (mA/cm2)
    cli (mM)
    clo (mM)
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
    icl = pbar * m * m * h * ghk(v, cli, clo)
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
    LOCAL m_alpha, m_beta
    
    m_alpha = 0.1194 * (v + 8.124) / (exp((v + 8.124) / 9.005) - 1)
    m_beta = 2.97 * exp(v / 31.4)

    mtau = 1 / (m_alpha + m_beta)
    minf = 1 / (1 + exp(- (v + 33.0) / 6.7)) 

    htau = 14.77
    hinf = 1 / (1 + exp((v + 13.4) / 11.9))
}

FUNCTION ghk(v(mV), cli(mM), clo(mM)) (millicoul/cm3) {
    LOCAL w, e

    w = v * (0.001) * 2 * FARADAY / (R * (celsius + 273.16))

    if (fabs(w) > 1e-4) {
        e = w / (exp(w) - 1)
    } else {
        e = 1 - w / 2
    }
    
    ghk = - (0.001) * 2 * FARADAY * (clo - cli * exp(w)) * e
}