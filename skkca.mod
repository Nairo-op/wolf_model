TITLE Calcium activated K channel (Moczydlowski and Latorre 1983)

UNITS {
    (molar) = (1/liter)
    (mV) =  (millivolt)
    (mA) =  (milliamp)
    (mM) =  (millimolar)
    FARADAY = (faraday)  (kilocoulombs)
    R = (k-mole) (joule/degC)
}

NEURON {
    SUFFIX skkca
    USEION ca READ cai
    USEION k READ ek WRITE ik
    RANGE gkbar, ik, stau
    GLOBAL oinf, tau
}

PARAMETER {
    stau = 1
    v       (mV)
    gkbar = 0.145    (mho/cm2)
    cai     (mM) 
    ek      (mV)
    celsius (degC)    : Read from NEURON environment
    
    : Model parameters from Moczydlowski & Latorre (1983) / typical defaults
    d1 = 0.84         : Gating valence for activation
    d2 = 1.0          : Gating valence for deactivation
    k1 = 0.48 (mM):0.48e-3 (mM) : Dissociation constant 1 : scaling up by 1000 to convert from uM to mM
    k2 = 0.13e-3 (mM):0.13e-3 (mM) : Dissociation constant 2 : scaling up by 1000 to convert from uM to mM
    abar = 0.28  (/ms): Max forward rate
    bbar = 0.48  (/ms): Max backward rate
}

ASSIGNED {
    ik      (mA/cm2)
    oinf    
    tau     (ms)
}

STATE { o }     : fraction of open channels

BREAKPOINT {
    SOLVE state METHOD cnexp
    ik = gkbar * o * (v - ek)
}

DERIVATIVE state {
    rate(v, cai)
    o' = (oinf - o)/(tau)
}

INITIAL {
    rate(v, cai)
    o = oinf
}

PROCEDURE rate(v (mV), ca (mM)) {
    LOCAL a, b
    a = alp(v, ca)
    b = bet(v, ca)
    tau = stau / (a + b)
    oinf = a / (a + b)
}

FUNCTION alp(v (mV), c (mM)) (1/ms) { 
    alp = c * abar / (c + exp1(k1, d1, v))
}

FUNCTION bet(v (mV), c (mM)) (1/ms) { 
    bet = bbar / (1 + c / exp1(k2, d2, v))
}

FUNCTION exp1(k (mM), d, v (mV)) (mM) { 
    exp1 = k * exp(-2 * d * FARADAY * v / (R * (273.15 + celsius)))
}