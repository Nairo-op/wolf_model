TITLE CaL 1.2 L-type calcium channel (Moczydlowski and Latorre 1983)

NEURON {
    SUFFIX cal12
    USEION cal READ ecal, cali, calo WRITE ical VALENCE 2
    RANGE pbar, ical, a
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
    pbar = 6.7e-6 (cm/s) 
    a = 0.17             
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
    ical = pbar * m * m * (a * h + (1.0 - a)) * ghk(v, cali, calo)
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

    minf = 1 / (1 + exp(- (v + 8.9) / 6.7)) 
    mtau = 1 / (m_alpha + m_beta)

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