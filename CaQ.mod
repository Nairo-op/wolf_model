TITLE Calcium Q-type current

NEURON {
    SUFFIX caq
    USEION ca READ eca, cai, cao WRITE ica
    RANGE pbar, ica
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
    pbar = 6.0e-6 (cm/s)            
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
    celsius (degC)
}

STATE {
    m                                         
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ica = pbar * m * m * ghk(v, cai, cao)
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
    LOCAL m_alpha, m_beta

    mtau = 0.377
    minf = 1 / (1 + exp( - (v + 9.0) / 6.6))
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