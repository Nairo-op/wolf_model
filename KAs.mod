TITLE 

NEURON {
    SUFFIX kas
    USEION k READ ek WRITE ik
    RANGE gbar, ik, a
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S) = (siemens)
}

PARAMETER {
    gbar = 0.0104 (S/cm2) 
    a = 0.996             
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
    ik = gbar * m * m * (a * h + (1.0 - a)) * (v - ek)
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

    minf = 1.0 / (1.0 + exp((v - (-27.0)) / (-16.0)))
    
    mtau = 0.378 + 9.91 * exp(-pow(((v + 34.3) / 30.1), 2))

    hinf = 1.0 / (1.0 + exp((v - (-33.5)) / 21.5))
    
    m_alpha = 1.0 * exp(-(v + 90.96) / 29.01)
    m_beta = 1.0 * exp((v + 90.96) / 100.0)
    
    htau = 1097.4 / (m_alpha + m_beta)
}