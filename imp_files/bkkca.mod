TITLE Large-Conductance Calcium-Activated Potassium Channel (BK)

COMMENT
=============================================================================
Biophysical Description:
------------------------
Implements a large-conductance, calcium-activated potassium channel (BK, Maxi-K,
or KCa1.1), which participates in action potential repolarization and shapes the 
fast afterhyperpolarization (fAHP). BK channels are activated synergistically 
by both membrane depolarization and intracellular calcium binding.

In striatal medium spiny projection neurons (MSNs), BK channels are functionally 
coupled to calcium influx through N-, P/Q-, and R-type calcium channels. Thus, 
this mechanism reads from the "ca" pool (cai) representing these high-threshold 
activated VGCCs, as opposed to the L/T-type pool ("cal").

Kinetic Scheme:
---------------
To account for the voltage-dependent inactivation observed in certain neuronal BK 
currents (e.g., when associated with beta2 auxiliary subunits), this model uses 
a 3-state cyclic Markov kinetic model consisting of Closed (cst), Open (ost), 
and Inactivated (ist) states:

        k3(Ca, V)
   Closed [cst] <=========> Open [ost]
         ^                  /
          \                /
        k2 \              / k1(V) [Inactivation]
            \            v
             Inactivated [ist]

State Transitions:
1. cst <-> ost: Reversible activation gating.
   - The opening rate (k3) is modeled with a voltage-dependent term scaled by the 
     third power of intracellular calcium concentration (representing cooperative 
     binding of 3 Ca2+ ions):
       k3 = alpha(V) * Ka * [Ca]i^3
     where Ka = 1.0e8 mM^-3 ms^-1 (forward calcium association rate constant).
   - The closing rate (k4) is purely voltage-dependent.
2. ost -> ist: Open-to-Inactivated transition governed by the voltage-dependent rate k1(V).
3. ist -> cst: Recovery from inactivation back to the closed state with rate k2(V).

Historical & Biophysical Context:
---------------------------------
While BK channels are classic biophysical targets characterized by Moczydlowski 
and Latorre (1983), the 3-state cyclic scheme with inactivation implemented here 
is based on Shao et al. (1999) "The role of BK-type Ca2+-dependent K+ channels in 
spike broadening during repetitive firing in rat hippocampal pyramidal cells" 
(J. Physiol. 521:135-146). The total conductance of the BK current in this MSN 
model (gkbar = 0.001 S/cm2) was tuned to regulate action potential width and shape 
repetitive firing dynamics (Wolf et al. 2005).

Transition Rate Constants:
--------------------------
- Inactivation rates (k1, k2) and deactivation rate (k4) are modeled using a 
  modified Boltzmann voltage dependence:
    k1 = alp(tmin=0.1 ms, V, Vhalf=-10.0 mV, k=1.0 mV)
    k2 = alp(tmin=0.1 ms, V, Vhalf=-120.0 mV, k=-10.0 mV)
    k4 = alp(tmin=0.01 ms, V, Vhalf=-44.0 mV, k=-5.0 mV)
- Activation rate (k3) incorporates voltage-dependent kinetics and cooperative 
  calcium gating:
    k3 = alpha(tmin=0.001 ms, tmax=1.0 ms, V, Vhalf=-20.0 mV, k=7.0 mV) * 1.0e8 * [Ca]i^3
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
    SUFFIX bkkca                    : Registers mechanism under suffix 'bkkca'
    USEION ca READ cai              : Accesses intracellular calcium concentration (cai) from N/Q/R-type pool
    USEION k READ ek WRITE ik       : Reads potassium reversal potential (ek) and writes current density (ik)
    RANGE gkbar, ik                 : Range variables: peak conductance and current density
}

PARAMETER {
    gkbar = 1.0e-3 (S/cm2)          : Maximal channel conductance
    celsius        (degC)           : Global temperature variable from NEURON
    ek             (mV)             : Potassium reversal potential
}

ASSIGNED {
    v       (mV)                    : Membrane potential
    cai     (mM)                    : Intracellular calcium concentration
    ik      (mA/cm2)                : Potassium current density
    k1      (/ms)                   : Open -> Inactivated rate constant
    k2      (/ms)                   : Inactivated -> Closed rate constant
    k3      (/ms)                   : Closed -> Open rate constant (Ca and V dependent)
    k4      (/ms)                   : Open -> Closed rate constant (V dependent)
    q10     (1)                     : Temperature coefficient placeholder
    g       (mho/cm2)               : Dynamic chord conductance
}

STATE { 
    cst                             : Closed state fraction
    ost                             : Open state fraction
    ist                             : Inactivated state fraction
}

BREAKPOINT { 
    SOLVE kin METHOD sparse         : Solve the kinetic state equations using sparse matrix methods
    g = gkbar * ost
    ik = g * (v - ek)               : Ohm's law current calculation
}

INITIAL {
    SOLVE kin STEADYSTATE sparse    : Compute steady-state initialization for states
}

KINETIC kin {
    rates(v)
    ~ cst <-> ost  (k3, k4)          : Closed-Open activation loop
    ~ ost <-> ist  (k1, 0.0)         : Open-to-Inactivated transition
    ~ ist <-> cst  (k2, 0.0)         : Recovery transition
    CONSERVE cst + ost + ist = 1    : Conservation equation: total state occupancy is 1.0
}

PROCEDURE rates(v (mV)) {
    LOCAL ca_safe
    ca_safe = cai
    if (ca_safe < 0) { ca_safe = 0 } : Numerical safety guard to prevent negative concentration values
    
    : k1 (Open -> Inactivated): Sigmoidal voltage-dependent inactivation rate constant.
    : Channels inactivate rapidly upon depolarization.
    k1 = alp(0.1, v, -10.0, 1.0)
    
    : k2 (Inactivated -> Closed): Sigmoidal voltage-dependent recovery rate constant.
    : Recovery from inactivation is favored at hyperpolarized potentials.
    k2 = alp(0.1, v, -120.0, -10.0)
    
    : k3 (Closed -> Open): Activation rate constant.
    : Combines a sigmoidal voltage-dependence term alpha(v) with a third-order cooperative 
    : calcium binding term (cai^3).
    : 1.0e8 (mM^-3 ms^-1) is the forward rate constant for calcium binding.
    k3 = alpha(0.001, 1.0, v, -20.0, 7.0) * 1.0e8 * pow(ca_safe * 1.0(/mM), 3)
    
    : k4 (Open -> Closed): Deactivation rate constant.
    : Purely voltage-dependent closing rate.
    k4 = alp(0.01, v, -44.0, -5.0)
}

: Gating kinetics scaling function alpha(V)
: Computes a sigmoidal transition rate with a defined minimum (1/tmax) and maximum (1/tmin) rate limit.
: Mathematical form: 1 / (tmin + 1 / ( (tmax - tmin)^-1 + exp((v - vhalf)/k) ))
FUNCTION alpha(tmin(ms), tmax(ms), v(mV), vhalf(mV), k(mV))(/ms) {
    alpha = 1.0 / (tmin + 1.0 / (1.0 / (tmax - tmin) + exp((v - vhalf) / k) * 1.0(/ms)))
}

: Sigmoidal rate transition function alp(V)
: Computes a rate constant that decreases sigmoidally with voltage (for k < 0, e.g. k2, k4) 
: or increases sigmoidally (for k > 0, e.g. k1).
: Mathematical form: 1 / (tmin + exp((v - vhalf)/k) * 1(ms))
FUNCTION alp(tmin(ms), v(mV), vhalf(mV), k(mV))(/ms) {
    alp = 1.0 / (tmin + exp((v - vhalf) / k) * 1.0(ms))
}
