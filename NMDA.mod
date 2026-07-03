NEURON {
    POINT_PROCESS NMDA
    RANGE tau1, tau2, e, i, g, mg
    NONSPECIFIC_CURRENT i
}

UNITS {
    (nA) = (nanoamp)
    (mV) = (millivolt)
    (uS) = (microsiemens)
    (mM) = (milli/liter)
}

PARAMETER {
    tau1 = 2.82 (ms)    : rise time
    tau2 = 160 (ms)     : decay time
    e = 0 (mV)          : reversal potential
    mg = 1.0 (mM)       : external Magnesium concentration
}

ASSIGNED {
    v (mV)
    i (nA)
    g (uS)
    factor
    B
}

STATE {
    m
    h
}

INITIAL {
    LOCAL tp
    m = 0
    h = 0
    if (tau1/tau2 > .9999) {
        tau1 = .9999*tau2
    }
    tp = (tau1*tau2)/(tau2 - tau1) * log(tau2/tau1)
    factor = -1 / (exp(-tp/tau1) - exp(-tp/tau2))
}

BREAKPOINT {
    SOLVE state METHOD cnexp
    : Magnesium block 
    B = 1 / (1 + (mg / 3.57) * exp(-v * 0.062))
    
    g = (h - m) * B
    i = g * (v - e)
}

DERIVATIVE state {
    m' = -m/tau1
    h' = -h/tau2
}

NET_RECEIVE(weight (uS)) {
    : weight : 0.0003 uS baseline
    m = m + weight*factor
    h = h + weight*factor
}