TITLE CaL 1.2 L-type Calcium Channel (Moczydlowski & Latorre 1983)

COMMENT
Implements the high-threshold CaL 1.2 L-type calcium channel.
- Flux calculation: Uses the Goldman-Hodgkin-Katz (GHK) current equation.
- Permeability: pbar = 6.7e-6 cm/s (somatic default).
- State variables: m (activation, squared) and h (inactivation).
- Gating formula: ical = pbar * m^2 * (a * h + (1 - a)) * ghk(v, cali, calo)
  where 'a' is the inactivation contribution fraction (default: 0.17).
- Kinetics: Activation/inactivation rates (minf, mtau, hinf, htau) are calculated analytically.
References:
- Moczydlowski E, Latorre R (1983) J Gen Physiol 82:511-542.
- Wolf JA et al. (2005) J Neurosci 25:9080-9095.
ENDCOMMENT


NEURON {
    SUFFIX cal12
    USEION cal READ ecal, cali, calo WRITE ical VALENCE 2
    RANGE pbar, ical, a, minf, hinf, htau, mtau
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (molar) = (1/liter)
    (mM) = (millimolar)
    (cm/s) = (centimeter/second)
}

PARAMETER {
    FARADAY =  96485 (coulombs)
    R = 8.3145 (joule/degC)
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
    LOCAL m_alpha, m_beta, v_diff

    : applying L hopitals rule here
    v_diff = v + 8.124
    if (fabs(v_diff) < 1e-6) {
        m_alpha = 0.1194 * 9.005 * (1.0 - v_diff / 9.005 / 2.0)
    } else {
        m_alpha = 0.1194 * v_diff / (exp(v_diff / 9.005) - 1)
    }
    m_beta = 2.97 * exp(v / 31.4)

    minf = 1 / (1 + exp(- (v + 8.9) / 6.7)) 
    mtau = 1 / (m_alpha + m_beta)

    htau = 14.77
    hinf = 1 / (1 + exp((v + 13.4) / 11.9))
}

FUNCTION ghk(v(mV), ci(mM), co(mM)) (millicoul/cm3) {
    LOCAL w, e

    w = v * (0.001) * 2 * FARADAY / (R * (celsius + 273.16))

    if (fabs(w) > 1e-4) {
        e = w / (exp(w) - 1)
    } else {
        e = 1 - w / 2
    }
    
    ghk = - (0.001) * 2 * FARADAY * (co - ci * exp(w)) * e
}