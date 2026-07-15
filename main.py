"""
main.py
=======

This script initializes the Striatal Medium Spiny Neuron (MSN) multicompartmental model
from Wolf et al. (2005) and launches a pre-configured graphical interface (NEURON GUI)
with multiple interactive panels and graphs.

Usage:
------
1. Normal execution:
   python3 main.py
2. Interactive mode (recommended to keep python shell active):
   python3 -i main.py
"""

import os
import sys
import time
from neuron import h, gui
from imp_files.utilities import load_mechanisms

# Load compiled mechanisms DLL/SO using the utility function
load_mechanisms()

# Importing cell class and instantiate
from imp_files.msn_class import MSNNeuron

print("Initializing Striatal MSN Multicompartmental Cell...")
cell = MSNNeuron()

# Create a default somatic current clamp (IClamp)
stim = h.IClamp(cell.soma(0.5))
stim.delay = 200.0   # ms (onset time)
stim.dur = 500.0     # ms (pulse duration)
stim.amp = 0.271     # nA (elicits action potential firing)

# Map Python objects to HOC global namespace for GUI tracking
h('objref py, stim')
h.py = cell
h.stim = stim

# Set default simulation parameters in HOC
h.v_init = -87.75     # Resting membrane potential down state
h.tstop = 900.0       # Total simulation duration (ms)
h.dt = 0.01          # High resolution solver step size (ms)
h.steps_per_ms = 100  # Number of points plotted per ms

# Load session file
session_file = "main.ses"
if os.path.exists(session_file):
    print(f"Loading pre-configured GUI session layout: {session_file}")
    h.load_file(session_file)
else:
    print(f"Error: GUI session layout file '{session_file}' not found.")

print("\n=====================================================================")
print("Interactive NEURON GUI (Loaded)")
print("=====================================================================")
print("- Click 'Init & Run' in the 'RunControl' panel to start the simulation.")
print("- Change current clamp values in the 'Somatic IClamp Control' panel.")
print("=====================================================================\n")

# To keep the GUI window alive if run in non-interactive terminal mode
if not sys.flags.interactive:
    print("Running GUI loop. Press Ctrl+C in this terminal to exit.")
    try:
        while True:
            time.sleep(0.5)
    except KeyboardInterrupt:
        print("\nExiting model GUI.")
