TITLE GABAergic Inhibitory Synaptic Current

COMMENT
Implements a GABAergic inhibitory synaptic current using a dual-exponential conductance model.
- Activation (rise) time constant: tau1 = 0.25 ms (default)
- Inactivation (decay) time constant: tau2 = 3.75 ms (default)
- Reversal potential: e = -60 mV (default)
- State variables: m and h represent the activation and inactivation state variables.
- Conductance: g = h - m
- Current: i = g * (v - e)
Synaptic events are triggered via NET_RECEIVE which increments the conductance states.
ENDCOMMENT

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