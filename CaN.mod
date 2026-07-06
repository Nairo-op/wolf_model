TITLE 

NEURON {
    SUFFIX can
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
    pbar = 1.0e-5 (cm/s) 
    a = 0.21
    FARADAY = 96485 (coulomb)
    R = 8.3145 (joule/degC)             
}

ASSIGNED {
    v (mV)
    eca (mV)
    cai (mM)
    cao (mM)
    ica (mA/cm2)
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
    ica = pbar * m * m * (a * h + (1.0 - a)) *  ghk(v, cai, cao)
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

    
    m_alpha = 0.1157 * (v + 17.19)/ (exp((v + 17.19)/15.22) - 1)
    m_beta = 1.15 * exp(v / 23.82)

    minf = 1 / ( 1 + exp(-(v + 8.7) / 7.4))
    mtau = 1 / (m_alpha + m_beta)

    htau = 23.33
    hinf = 1 / (1 + exp((v + 74.8) / 6.5))
}

FUNCTION ghk(v(mV), cai(mM), cao(mM) ) (millicoul/cm3) {
    LOCAL v_nu, f

    f = (1000) * R * (celsius + 273.15) / (2 * FARADAY) :RT/zF

    if (fabs(v) < 1e-4) {
        ghk = f * (cai - cao)
    } else {
        v_nu = v / f
        ghk = v_nu * (cai - cao * exp(-v_nu)) / (1 - exp(-v_nu))
    }
}