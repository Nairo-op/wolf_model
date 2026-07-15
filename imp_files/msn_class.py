"""
msn_class.py
============

This module defines the `MSNNeuron` class, representing a multicompartmental 
replicated model of a Striatal Medium Spiny Neuron (MSN) from the Nucleus Accumbens (NAcb).
The biophysics, morphology, and channel densities are reconstructed to replicate 
the model described in -
Wolf et al. (2005) "Computational Model of the Striatal Medium Spiny Neuron: 
Biophysical Properties and State Transitions" (J. Neurosci).

Model Structure:
- Soma (1 segment)
- Primary Dendrites (4 branches, 1 segment each)
- Secondary Dendrites (8 branches, 1 segment each)
- Tertiary Dendrites (16 branches, 11 segments each)

Dendritic Spines:
To account for dendritic spines without modeling them explicitly as separate compartments, 
the passive membrane area (capacitance `cm` and leak conductance `g_pas`) is scaled up 
by a "Spine Factor" (F). Correspondingly, to preserve the passive input resistance and electrotonic 
properties, dendritic cable dimensions (diameter `diam` and length `L`) are scaled by:
    - diam_adjusted = diam_true * F^(3/2)
    - L_adjusted = L_true * F^(1/2)
This scaling method maintains the input resistance of the branch while matching the membrane area 
and capacitance of the spine-covered dendrite.

"""

import math
from neuron import h
import sys

h.load_file('stdrun.hoc')
# h.load_file('nrngui.hoc')
# h.load_file('wolf.ses')
h.celsius = 35.0


class MSNNeuron:
    def __init__(self):


        e_pas = -70.0           # passive reversal potential (mV)
        e_na = 50.0             # sodium reversal potential (mV)
        e_k = -90               # potassium reversal potential (mV)
        # e_ca = ___            # calcium reversal potential (mV)
        # calcium potential will be calculated by the model based on the calcium dynamics and ghk equation

        # Store potential constants
        self.e_pas = e_pas
        self.e_na = e_na
        self.e_k = e_k
        
        # Ion concentrations
        # Concentrations are separated into two distinct pools:
        # 1. Standard Calcium Pool (ca): Handles N, P/Q, and R-type calcium currents.
        # 2. L/T-type Calcium Pool (cal): Handles L-type (CaL1.2, CaL1.3) and T-type calcium currents.
        h.cai0_ca_ion = 0.001
        h.cao0_ca_ion = 5.0
        h.cali0_cal_ion = 0.001
        h.calo0_cal_ion = 5.0

        # Define mechanism parameters
        self._define_biophysics()
        
        # Build the cell morphology and insert channels
        self._create_cell()

        # Add synapses and also initializing lists for synapse objects
        self.ampa_synapses = []
        self.nmda_synapses = []
        self.gaba_synapses = []
        self._add_syn()

    def _define_biophysics(self):
        """
        Defines the density of passive and active ionic currents in the soma and dendrites.
        """
        
        # gbar - S/cm2
        # pbar - cm/S

        # SOMATIC COMPARTMENT MECHANISMS
        self.soma_mechanisms = {
            'pas': {'g_pas': 11.5e-6},
            'naf': {'gbar_naf': 1.5},
            'nap': {'gbar_nap': 4.0e-5},
            'kaf': {'gbar_kaf': 0.225},
            'kas': {'gbar_kas': 0.0104},
            'kir': {'gbar_kir': 1.4e-4},
            'krp': {'gbar_krp': 0.001},
            'cal12': {'pbar_cal12': 6.7e-6},
            'cal13': {'pbar_cal13': 4.25e-7},
            'can': {'pbar_can': 1.0e-5},
            'car': {'pbar_car': 2.6e-5},
            'caq': {'pbar_caq': 6.0e-6},
            'cat': {'pbar_cat': 4.0e-7},
            'bkkca': {'gkbar_bkkca': 0.001},
            'skkca': {'gkbar_skkca': 0.145},
            'cadyn_lt': {}, 
            'cadyn_nqr': {}
        }

        # PRIMARY DENDRITIC COMPARTMENT MECHANISMS
        self.pdend_mech = {
            'pas': {'g_pas': 11.5e-6}, 
            'naf': {'gbar_naf': 0.0195}, 
            'nap': {'gbar_nap': 1.3802e-7 },
            'kaf': {'gbar_kaf': .225 },
            'kas': {'gbar_kas': 0.0104 }, 
            'kir': {'gbar_kir': 1.4e-4},
            'bkkca': {'gkbar_bkkca': 0.001}, 
            'skkca': {'gkbar_skkca': 0.145},
            'cal12': {'pbar_cal12': 6.7e-6}, 
            'cal13': {'pbar_cal13': 4.25e-7},
            'can': {'pbar_can': 1.0e-5}, 
            'car': {'pbar_car': 2.6e-5},
            'caq': {'pbar_caq': 6.0e-6}, 
            'cat': {'pbar_cat': 4.0e-7},
            'cadyn_lt': {},
            'cadyn_nqr': {}
        }

        # SECONDARY DENDRITIC COMPARTMENT MECHANISMS
        self.sdend_mech = {
            'pas': {'g_pas': 11.5e-6 }, 
            'naf': {'gbar_naf': 0.0195 }, 
            'nap': {'gbar_nap': 1.3802e-7 },
            'kaf': {'gbar_kaf': 0.020584 },
            'kas': {'gbar_kas': 0.00095142 },
            'kir': {'gbar_kir': 1.4e-4 }, 
            'bkkca': {'gkbar_bkkca': 0.001},
            'skkca': {'gkbar_skkca': 0.145},
            'cal12': {'pbar_cal12': 6.7e-6 }, 
            'cal13': {'pbar_cal13': 4.25e-7 },
            'can': {'pbar_can': 1.0e-5 }, 
            'car': {'pbar_car': 2.6e-5 },
            'caq': {'pbar_caq': 6.0e-6 },
            'cat': {'pbar_cat': 4.0e-7 },
            'cadyn_nqr': {},
            'cadyn_lt': {}  
        }

        # TERTIARY DENDRITIC COMPARTMENT MECHANISMS
        self.tdend_mech  = {
            'pas': {'g_pas': 11.5e-6 }, 
            'naf': {'gbar_naf': 0.0195 }, 
            'nap': {'gbar_nap': 1.3802e-7 },
            'kaf': {'gbar_kaf': 0.020584 },
            'kas': {'gbar_kas': 0.00095142 },  
            'kir': {'gbar_kir': 1.4e-4 }, 
            'bkkca': {'gkbar_bkkca': 0.001}, 
            'skkca': {'gkbar_skkca': 0.145},
            'cal12': {'pbar_cal12': 6.7e-6 }, 
            'cal13': {'pbar_cal13': 4.25e-7 },
            'can': {'pbar_can': 1.0e-5 }, 
            'car': {'pbar_car': 2.6e-5 },
            'caq': {'pbar_caq': 6.0e-6 }, 
            'cat': {'pbar_cat': 4.0e-7 },
            'cadyn_nqr': {},
            'cadyn_lt': {}
        }


    def _insert_mechanisms(self, sec, mech_dict):
        sec.Ra = 100       # Axial resistivity (ohm-cm)
        sec.cm = 1.0       # Specific membrane capacitance (uF/cm2)

        # Loop through mechanism definitions and insert them into the section
        for mechanism, parameters in mech_dict.items():
            sec.insert(mechanism)
            # Set parameters segment-by-segment 
            for param_name, param_value in parameters.items():
                for seg in sec:
                    setattr(seg, param_name, param_value)
        
         # Apply standard reversal potentials
        sec.e_pas = self.e_pas
        sec.ena = self.e_na
        sec.ek = self.e_k

    def _create_cell(self):

        # Soma dimensions
        s_diam = 16 
        s_l = 16 
        s_nseg = 1
        # s_cm = 1 
        # s_ra = 100 


        # Primary dendrite (Spine Factor F = 1.0)
        pdend_n = 1
        pdend_d = 2.25
        pdend_l = 20 
        # pdend_F = 1.0

        # Secondary Dendrite (Spine Factor F = 1.33)
        # sdend_F = 1.33
        sdend_n = 1
        # true_sdend_d = 1.0    # True diameter
        # true_sdend_l = 20.0   # True length
        sdend_d = 1.1           # adjusted diameter
        sdend_l = 24.23         # adjusted length

        # Tertiary dendrite (Spine Factor F = 3.0)
        # tdend_F = 3.0
        tdend_n = 11
        # true_tdend_d = 0.5    # True diameter
        # true_tdend_l = 190.0  # True length
        tdend_d = 0.72          # adjusted diameter
        tdend_l = 395.2         # adjusted length


        # Soma
        self.soma = h.Section(name='soma', cell=self)
        self.soma.nseg = s_nseg
        self.soma.diam = s_diam
        self.soma.L = s_l
        self._insert_mechanisms(self.soma, self.soma_mechanisms)

        # Primary Dendrites
        self.prim_dend = []

        for i in range(4):

            dend = h.Section(name=f'prim_{i}', cell=self)
            dend.nseg = pdend_n
            dend.diam = pdend_d
            dend.L = pdend_l
            self._insert_mechanisms(dend, self.pdend_mech)

            # Connect to soma
            if i < 2:
                dend.connect(self.soma(1), 0)
            else:
                dend.connect(self.soma(0), 0)
            self.prim_dend.append(dend)

        # Secondary Dendrites
        self.sec_dend = []

        for i in range(8):

            dend = h.Section(name=f'sec_{i}', cell=self)
            dend.nseg = sdend_n
            dend.diam = sdend_d
            dend.L = sdend_l
            self._insert_mechanisms(dend, self.sdend_mech)

            # Connect to primary parent
            pdend_index = math.floor(i // 2)
            dend.connect(self.prim_dend[pdend_index](1), 0)
            self.sec_dend.append(dend)

        # Tertiary Dendrites
        self.tert_dend = []

        for i in range(16):

            dend = h.Section(name=f'tert_{i}', cell=self)
            dend.nseg = tdend_n
            dend.diam = tdend_d
            dend.L = tdend_l
            self._insert_mechanisms(dend, self.tdend_mech)

            # Connect to secondary parent
            sdend_index = math.floor(i // 2)
            dend.connect(self.sec_dend[sdend_index](1), 0)
            self.tert_dend.append(dend)

    def _add_syn(self):
        """
        Distributes AMPA, NMDA, and GABA receptors across the soma and dendrites.
        Placements match the anatomical statistics described in Table 3 of Wolf et al. (2005).
        
        Total Glutamatergic Synapses (AMPA/NMDA colocalized at spines) [84 locations]:
        - Primary Dendrites: 1 per branch (4 total)
        - Secondary Dendrites: 2 per branch (16 total)
        - Tertiary Dendrites: 4 per branch (64 total)
        
        Total GABAergic Synapses (Inhibitory synapses on shaft/soma) [80 locations]:
        - Soma: 16 total
        - Primary Dendrites: 3 per branch (12 total)
        - Secondary Dendrites: 3 per branch (24 total)
        - Tertiary Dendrites: 2 per branch (32 total)
        """

        # SOMATIC SYNAPSES (GABA only)
        # 16 GABA synapses at the  soma
        for _ in range(16):
            gaba = h.GABA(self.soma(0.5))
            self.gaba_synapses.append(gaba)

        # PRIMARY DENDRITES
        for pdend in self.prim_dend:
            # Glutamatergic: 1 location at the center
            self.ampa_synapses.append(h.AMPA(pdend(0.5)))
            self.nmda_synapses.append(h.NMDA(pdend(0.5)))
            
            # GABAergic: 3 locations evenly spaced
            for j in range(3):
                pos = (j + 1) / 4.0  # 0.25, 0.5, 0.75
                self.gaba_synapses.append(h.GABA(pdend(pos)))

        #  SECONDARY DENDRITES
        for sdend in self.sec_dend:
            # Glutamatergic: 2 locations evenly spaced
            for j in range(2):
                pos = (j + 1) / 3.0  # ~0.33, ~0.66
                self.ampa_synapses.append(h.AMPA(sdend(pos)))
                self.nmda_synapses.append(h.NMDA(sdend(pos)))
                
            # GABAergic: 3 locations evenly spaced
            for j in range(3):
                pos = (j + 1) / 4.0  # 0.25, 0.5, 0.75
                self.gaba_synapses.append(h.GABA(sdend(pos)))

        # 4. TERTIARY DENDRITES
        for tdend in self.tert_dend:
            # Glutamatergic: 4 locations evenly spaced
            for j in range(4):
                pos = (j + 1) / 5.0  # 0.2, 0.4, 0.6, 0.8
                self.ampa_synapses.append(h.AMPA(tdend(pos)))
                self.nmda_synapses.append(h.NMDA(tdend(pos)))
                
            # GABAergic: 2 locations evenly spaced
            for j in range(2):
                pos = (j + 1) / 3.0  # ~0.33, ~0.66
                self.gaba_synapses.append(h.GABA(tdend(pos)))

