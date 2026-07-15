TITLE Q-type Calcium Channel Current (CaQ)

COMMENT
Implements the Q-type calcium channel (CaQ) using the GHK current equation.
- Permeability: pbar = 6e-6 cm/s (somatic default).
- State variables: m (activation, squared). No inactivation is modeled.
- Gating formula: ica = pbar * m^2 * ghk(v, cai, cao)
- Kinetics: Steady-state activation minf is voltage-dependent; time constant mtau is fixed at 0.377 ms.
ENDCOMMENT

NEURON {
    SUFFIX caq
    USEION ca READ eca, cai, cao WRITE ica
    RANGE pbar, ica, minf, mtau
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

FUNCTION ghk(v(mV), ci(mM), co(mM)) (millicoul/cm3) {
    LOCAL w, e

    w = v * (0.001) * 2 * FARADAY / (R * (celsius + 273.16))

    if (fabs(w) > 1e-4) {
        e = w / (exp(w) - 1)
    } else {
        e = 1 - w / 2
    }
    
    ghk = - (0.001) * 2 * FARADAY * (co - ci* exp(w)) * e
}