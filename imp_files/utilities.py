import os
import sys
from concurrent.futures import ProcessPoolExecutor, as_completed

"""
utilities.py
============

This module contains utility functions for managing parallel simulations and 
printing standard terminal progress indicators during long parameter sweeps.

Note on Parallel execution in NEURON:
Because NEURON's underlying C++ engine uses global variables and is strictly 
thread-bound for simulation control state (e.g., global time `h.t`, state vectors, 
and solver objects), running simulations in parallel threads will lead to memory 
corruption and incorrect calculations. 

To run parameter sweeps in parallel safely, we must use separate CPU processes 
(`ProcessPoolExecutor`) rather than threads. This isolates the NEURON simulator instance 
within separate memory namespaces per process.

"""

# Utility functions for running parallel simulations and updating progress bars
# useful for visualizing and handling loops across multiple threads

def _update_progress_bar(completed, total, label="Simulating Sweeps", bar_length=20):
    """
    Displays an in-place text-based progress bar on the console.
    
    Parameters:
    - completed (int): Number of finished simulation tasks.
    - total (int): Total number of simulation tasks.
    - label (str): Describing the active simulation phase.
    - bar_length (int): Characters used for the progress bar rendering.
    """
    percent = float(completed) / total
    arrow = '▒' * int(round(percent * bar_length))
    spaces = ' ' * (bar_length - len(arrow))
    sys.stdout.write(f"\r{label}: |{arrow}{spaces}| {int(percent * 100)}% ({completed}/{total} completed)")
    sys.stdout.flush()

def run_parallel_sweeps(target_function, parameter_list, label="Simulating Sweeps"):
    """
    Executes multiple independent simulations in parallel across separate CPU processes.
    Aggregates the results into a dictionary and logs progress to the console.
    
    Parameters:
    - target_function (callable): The simulation execution function. Must be pickleable.
    - parameter_list (list): List of input parameters/configurations to pass to the target function.
    - label (str): Label for the progress bar console output.
    
    Returns:
    - results (dict): Mapping parameter inputs to their respective simulation outputs.
    """
    total_tasks = len(parameter_list)
    results = {}
    completed = 0
    
    _update_progress_bar(completed, total_tasks, label=label)
    
    with ProcessPoolExecutor() as executor:
        futures = {executor.submit(target_function, param): param for param in parameter_list}
        for future in as_completed(futures):
            param = futures[future]
            results[param] = future.result()
            completed += 1
            _update_progress_bar(completed, total_tasks, label=label)
    print()
    return results

def load_mechanisms():
    """
    Locates and loads compiled NMODL mechanisms DLL/SO (libnrnmech.so or nrnmech.dll).
    Avoids redundant loading if mechanisms are already present in the NEURON environment.
    """
    from neuron import h
    
    # Check if a known mechanism parameter is already present to prevent redundant loading
    if hasattr(h, 'cai0_ca_ion'):
        return
        
    target_binary = 'libnrnmech.so' if sys.platform != 'win32' else 'nrnmech.dll'
    mech_path = None

    for root, dirs, files in os.walk(os.getcwd()):
        if target_binary in files:
            mech_path = os.path.join(root, target_binary)
            break

    if mech_path:
        try:
            h.nrn_load_dll(mech_path)
            print(f"Successfully loaded compiled mechanisms from: {mech_path}")
        except RuntimeError as e:
            if "already exists" not in str(e):
                raise e
    else:
        print(f"Warning: Could not find '{target_binary}'. Please run 'nrnivmodl' first.")