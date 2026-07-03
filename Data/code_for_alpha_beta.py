import pandas as pd
import numpy as np
import scipy.optimize as opt

df = pd.read_csv("channel_kinetics_lookups.csv")

boltzmann_params = {
    "Naf": {"m_v12": -23.9, "m_k": -11.8, "h_v12": -62.9, "h_k": 10.7},
    "Nap": {"m_v12": -52.6, "m_k": -4.6,  "h_v12": -48.8, "h_k": 10.0},
    "Krp": {"m_v12": -13.5, "m_k": -11.8, "h_v12": -54.7, "h_k": 18.6},
    "Kaf": {"m_v12": -10.0, "m_k": -17.7, "h_v12": -75.6, "h_k": 10.0},
    "Kir": {"m_v12": -82.0, "m_k": 13.0},
    "CaR": {"m_v12": -10.3, "m_k": -6.6,  "h_v12": -33.3, "h_k": 17.0},
    "Cat": {"m_v12": -51.73, "m_k": -6.53, "h_v12": -80.0, "h_k": 6.7}
}

def boltzmann_inf(V, v12, k):
    return 1.0 / (1.0 + np.exp((V - v12) / k))

fitted_equations = {}

for channel in df['Channel'].unique():
    sub = df[df['Channel'] == channel]
    V = sub['Vm'].values
    params = boltzmann_params.get(channel, {})
    
    fitted_equations[channel] = {}
    
    #  gating variable 'm' if present
    if 'mTau' in sub.columns and not sub['mTau'].isnull().all():
        mtau = sub['mTau'].values
        # 3rd-order polynomial fit 
        p_m = np.polyfit(V, mtau, 3)
        fitted_equations[channel]['m'] = {
            'tau_expr': f"{p_m[0]:.4e}*V^3 + {p_m[1]:.4e}*V^2 + {p_m[2]:.4e}*V + {p_m[3]:.4f}",
            'v12': params.get('m_v12'),
            'k': params.get('m_k')
        }
        
    #  gating variable 'h' if present
    if 'hTau' in sub.columns and not sub['hTau'].isnull().all():
        htau = sub['hTau'].values
        p_h = np.polyfit(V, htau, 3)
        fitted_equations[channel]['h'] = {
            'tau_expr': f"{p_h[0]:.4e}*V^3 + {p_h[1]:.4e}*V^2 + {p_h[2]:.4e}*V + {p_h[3]:.4f}",
            'v12': params.get('h_v12'),
            'k': params.get('h_k')
        }

# transition rates alpha & beta
for ch, gates in fitted_equations.items():
    print(f"\nChannel Mechanisms: {ch}")
    print('-----')
    for gate, data in gates.items():
        print(f"  Gating Particle [{gate}]:")
        print(f"    {gate}_inf(V) = 1 / (1 + exp((V - ({data['v12']})) / {data['k']}))")
        print(f"    {gate}_tau(V) = {data['tau_expr']}")
        print(f"    alpha_{gate}(V) = {gate}_inf(V) / {gate}_tau(V)")
        print(f"    beta_{gate}(V)  = (1 - {gate}_inf(V)) / {gate}_tau(V)")