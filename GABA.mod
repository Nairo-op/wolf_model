NEURON {
    POINT_PROCESS GABA
    RANGE tau1, tau2, e, i, g
    NONSPECIFIC_CURRENT i
}

UNITS {
    (nA) = (nanoamp)
    (mV) = (millivolt)
    (uS) = (microsiemens)
}

PARAMETER {
    tau1 = 0.25 (ms)     : rise time (tau_on)
    tau2 = 3.75 (ms)    : decay time (tau_off)
    e = -60 (mV)          : reversal potential
}

ASSIGNED {
    v (mV)
    i (nA)
    g (uS)
    factor
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
    g = h - m
    i = g * (v - e)
}

DERIVATIVE state {
    m' = -m/tau1
    h' = -h/tau2
}

NET_RECEIVE(weight (uS)) {
    : weight from paper: 0.000593 uS for a single-channel baseline
    m = m + weight*factor
    h = h + weight*factor
}