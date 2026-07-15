TITLE Inwardly Rectifying Potassium Channel Current (Kir)

COMMENT
Implements the inwardly rectifying potassium current (Kir) active at hyperpolarized potentials.
- Maximum conductance: gbar = 1.4e-4 S/cm2 (somatic default).
- State variables: m (activation).
- Gating formula: ik = gbar * m * (v - ek)
- Kinetics: Steady-state activation minf is calculated analytically. Time-constant mtau is 
  obtained using linear interpolation from a hardcoded lookup table between -100 mV and 0 mV.
ENDCOMMENT

NEURON {
    SUFFIX kir
    USEION k READ ek WRITE ik
    RANGE gbar, ik, minf, mtau
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S) = (siemens)
}

CONSTANT{
    Q10 = 3.0 (1)
}
PARAMETER {
    gbar = 1.4e-4 (S/cm2)
}

STATE {
    m                                     
}

ASSIGNED {
    v (mV)
    ek (mV)
    ik (mA/cm2)
    minf
    mtau (ms)
    qt  (1)

}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ik = gbar * m * (v - ek)
}

INITIAL {
    qt = Q10^((celsius - 35)/10) : since we are running in 35 degree we dont need this now
    rates(v)
    m = minf
}

DERIVATIVE states {
    rates(v)
    m' = (minf - m) / mtau
}

PROCEDURE rates(v (mV)) {
    LOCAL v_idx, fraction
    
    minf = 1 / (1 + exp((v + 82.0) / 13.0))

    : --- HARDCODED LINEAR INTERPOLATION FOR KIR (mtau) ---
    : Range bounds: -100.0 mV to 0.0 mV, Step size: 10.0 mV
    
    if (v <= -100.0) {
        : mtau = 14.93
        mtau = 7.465
    } else if (v >= 0.0) {
        : mtau = 16.0
        mtau = 8.0
    } else {
        : Map voltage to table index (step size is 10 mV, starting at -100 mV)
        v_idx = floor((v - (-100.0)) / 10.0)
        fraction = ((v - (-100.0)) / 10.0) - v_idx
        
        : Perform linear interpolation based on index
        if (v_idx == 0) { 
            mtau = 7.465 + fraction * (8.0 - 7.465)
        }
        else if (v_idx == 1) { 
            mtau = 8.0 + fraction * (9.435 - 8.0)
        }
        else if (v_idx == 2) { 
            mtau = 9.435 + fraction * (10.755 - 9.435)
        }
        else if (v_idx == 3) { 
            mtau = 10.755 + fraction * (12.12 - 10.755)
        }
        else if (v_idx == 4) { 
            mtau = 12.12 + fraction * (13.795 - 12.12)
        }
        else if (v_idx == 5) { 
            mtau = 13.795 + fraction * (15.385 - 13.795)
        }
        else if (v_idx == 6) { 
            mtau = 15.385 + fraction * (14.285 - 15.385)
        }
        else if (v_idx == 7) { 
            mtau = 14.285 + fraction * (11.765 - 14.285)
        }
        else if (v_idx == 8) { 
            mtau = 11.765 + fraction * (8.89 - 11.765)
        }
        else if (v_idx == 9) { 
            mtau = 8.89 + fraction * (8.0 - 8.89)
        }
    }
}