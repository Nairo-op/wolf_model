TITLE Small-Conductance Calcium-Activated Potassium Channel (SK)

COMMENT
=============================================================================
Biophysical Description:
------------------------
Implements a small-conductance, calcium-activated potassium channel (SK, KCa2),
which contributes to the medium afterhyperpolarization (mAHP), regulates action
potential firing frequency, and mediates spike-frequency adaptation in neurons.

In striatal medium spiny projection neurons (MSNs), experimental evidence 
(e.g., Vilchis et al., 2000) indicates that calcium-dependent potassium channels
are selectively activated by calcium influx from specific voltage-gated calcium 
channels (VGCCs). Thus, this model is linked to the "ca" pool (representing N-, 
P/Q-, and R-type calcium currents) rather than the "cal" pool (representing L- 
and T-type calcium currents).

Scientific Basis & Model Formulation:
-------------------------------------
The model is mathematically formulated as a two-state Markov-like transition 
scheme (Closed <-> Open) represented by a single Hodgkin-Huxley style gating 
state variable 'o' (the open fraction of channels):

    do/dt = (oinf - o) / (tau / qfact)

The activation rate (alp) and deactivation rate (bet) are functions of both 
intracellular calcium concentration ([Ca]i) and membrane potential (V):

    alp = [Ca]i * abar / ([Ca]i + K1(V))
    bet = bbar / (1 + [Ca]i / K2(V))

Where the voltage-dependent dissociation constants (K1 and K2) are scaled as:

    Ki(V) = ki * exp( -2 * di * F * V / (R * T) )

Here:
- [Ca]i: Intracellular calcium concentration from the N-, Q-, and R-type pool (cai, mM).
- V: Membrane potential (v, mV).
- celsius: Temperature in degrees Celsius (from NEURON's global namespace, set to 35 C).
- F (FARADAY): Faraday constant (96.4853 kilocoulombs/equivalent).
- R (Gas Constant): Universal gas constant (8.3144 Joules/(mole*Kelvin)).
- T: Absolute temperature in Kelvin (273.15 + celsius).
- d1, d2: Gating valences for activation and deactivation, respectively.
- k1, k2: Dissociation constants at 0 mV.
- abar, bbar: Maximum forward (activation) and backward (deactivation) rate constants.
- qfact: Q10 temperature sensitivity factor (set to 1.0 in Wolf et al. 2005).

Historical Correction / Model Origin:
-------------------------------------
Although implemented here to represent the small-conductance SK channel, the 
mathematical formalism and kinetic rate parameters (abar, bbar, k1, k2, d1, d2) 
originate from the two-state gating model characterized for the large-conductance 
(BK) channel by Moczydlowski and Latorre (1983) "Gating Kinetics of Ca2+-Activated 
K+ Channels from Rat Muscle" (J. Gen. Physiol. 82:511-542). In the Wolf et al. (2005) 
MSN model, these equations were adapted to simulate the SK current (skkca) by setting 
the peak specific conductance (gkbar) to 0.145 S/cm2.

Model Parameters (Wolf et al. 2005):
------------------------------------
- d1 (valence) = 0.84
- d2 (valence) = 1.00
- k1 (mM) = 0.18    (180 uM dissociation constant at 0 mV)
- k2 (mM) = 0.011   (11 uM dissociation constant at 0 mV)
- abar (/ms) = 0.48
- bbar (/ms) = 0.28
- gkbar (S/cm2) = 0.145
=============================================================================
ENDCOMMENT

UNITS {
    (molar) = (1/liter)
    (mV) =  (millivolt)
    (mA) =  (milliamp)
    (mM) =  (millimolar)
    FARADAY = (faraday)  (kilocoulombs)
    R = (k-mole) (joule/degC)
}

NEURON {
    SUFFIX skkca                    : Registers mechanism under the suffix 'skkca'
    USEION ca READ cai              : Accesses intracellular calcium concentration (cai) from N/Q/R-type pool
    USEION k READ ek WRITE ik       : Reads potassium reversal potential (ek) and writes current density (ik)
    RANGE gkbar, ik, stau           : Range variables: peak conductance, current density, time scaling
}

PARAMETER {
    stau = 1.0                      : Gating time-constant scaling factor
    qfact = 1.0                     : Q10 temperature factor (1.0 in Wolf et al. 2005)
    v       (mV)                    : Membrane potential
    gkbar = 0.145    (mho/cm2)      : Maximal channel conductance
    cai     (mM)                    : Intracellular calcium concentration
    ek      (mV)                    : Potassium reversal potential
    celsius (degC)                  : Global temperature variable from NEURON
    
    : Gating kinetics parameters from Moczydlowski & Latorre (1983)
    d1 = 0.84                       : Gating valence (activation)
    d2 = 1.0                        : Gating valence (deactivation)
    k1 = 0.18 (mM)                  : Dissociation constant for activation at 0 mV
    k2 = 0.011 (mM)                 : Dissociation constant for deactivation at 0 mV
    abar = 0.48  (/ms)              : Maximum forward rate constant
    bbar = 0.28  (/ms)              : Maximum backward rate constant
}

ASSIGNED {
    ik      (mA/cm2)                : Calculated potassium current density
    oinf                            : Steady-state open probability
    tau     (ms)                    : Time constant of activation gating
}

STATE { 
    o                               : State variable representing the fraction of open channels
}

BREAKPOINT {
    SOLVE state METHOD cnexp        : Solve the differential equation for gating variable 'o'
    ik = gkbar * o * (v - ek)       : Current calculation using Ohm's law
}

DERIVATIVE state {
    rate(v, cai, celsius)
    o' = (oinf - o) / (tau / qfact) : Gating state variable derivative
}

INITIAL {
    rate(v, cai, celsius)
    o = oinf                        : Set open fraction to steady state initial value
}

PROCEDURE rate(v (mV), ca (mM), celsius (degC)) {
    LOCAL a, b
    a = alp(v, ca, celsius)
    b = bet(v, ca, celsius)
    tau = stau / (a + b)            : Activation time constant
    oinf = a / (a + b)              : Steady-state open probability
}

FUNCTION alp(v (mV), c (mM), celsius (degC)) (1/ms) { 
    : Forward activation rate alpha(V, [Ca]i)
    : alpha = [Ca]i * abar / ([Ca]i + K1(V))
    alp = c * abar / (c + exp1(k1, d1, v, celsius))
}

FUNCTION bet(v (mV), c (mM), celsius (degC)) (1/ms) { 
    : Backward deactivation rate beta(V, [Ca]i)
    : beta = bbar / (1 + [Ca]i / K2(V))
    bet = bbar / (1 + c / exp1(k2, d2, v, celsius))
}

FUNCTION exp1(k (mM), d, v (mV), celsius (degC)) (mM) { 
    : Voltage-dependent dissociation constant Ki(V)
    : Ki(V) = ki * exp( -2 * di * F * V / (R * T) )
    : Note: Uses thermodynamic scaling where FARADAY and R constants are converted
    : to yield a dimensionless exponent for v in millivolts.
    exp1 = k * exp(-2 * d * FARADAY * v  / (R * (273.15 + celsius)))
}