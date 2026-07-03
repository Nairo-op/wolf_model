/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#define _pval pval
// clang-format off
#include "md1redef.h"
#include "section_fwd.hpp"
#include "nrniv_mf.h"
#include "md2redef.h"
#include "nrnconf.h"
// clang-format on
#include "neuron/cache/mechanism_range.hpp"
static constexpr auto number_of_datum_variables = 3;
static constexpr auto number_of_floating_point_variables = 14;
namespace {
template <typename T>
using _nrn_mechanism_std_vector = std::vector<T>;
using _nrn_model_sorted_token = neuron::model_sorted_token;
using _nrn_mechanism_cache_range = neuron::cache::MechanismRange<number_of_floating_point_variables, number_of_datum_variables>;
using _nrn_mechanism_cache_instance = neuron::cache::MechanismInstance<number_of_floating_point_variables, number_of_datum_variables>;
using _nrn_non_owning_id_without_container = neuron::container::non_owning_identifier_without_container;
template <typename T>
using _nrn_mechanism_field = neuron::mechanism::field<T>;
template <typename... Args>
void _nrn_mechanism_register_data_fields(Args&&... args) {
  neuron::mechanism::register_data_fields(std::forward<Args>(args)...);
}
}
 
#if !NRNGPU
#undef exp
#define exp hoc_Exp
#if NRN_ENABLE_ARCH_INDEP_EXP_POW
#undef pow
#define pow hoc_pow
#endif
#endif
 
#define nrn_init _nrn_init__krp
#define _nrn_initial _nrn_initial__krp
#define nrn_cur _nrn_cur__krp
#define _nrn_current _nrn_current__krp
#define nrn_jacob _nrn_jacob__krp
#define nrn_state _nrn_state__krp
#define _net_receive _net_receive__krp 
#define rates rates__krp 
#define states states__krp 
 
#define _threadargscomma_ _ml, _iml, _ppvar, _thread, _globals, _nt,
#define _threadargsprotocomma_ Memb_list* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt,
#define _internalthreadargsprotocomma_ _nrn_mechanism_cache_range* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt,
#define _threadargs_ _ml, _iml, _ppvar, _thread, _globals, _nt
#define _threadargsproto_ Memb_list* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt
#define _internalthreadargsproto_ _nrn_mechanism_cache_range* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *hoc_getarg(int);
 
#define t _nt->_t
#define dt _nt->_dt
#define gbar _ml->template fpfield<0>(_iml)
#define gbar_columnindex 0
#define a _ml->template fpfield<1>(_iml)
#define a_columnindex 1
#define ik _ml->template fpfield<2>(_iml)
#define ik_columnindex 2
#define m _ml->template fpfield<3>(_iml)
#define m_columnindex 3
#define h _ml->template fpfield<4>(_iml)
#define h_columnindex 4
#define ek _ml->template fpfield<5>(_iml)
#define ek_columnindex 5
#define minf _ml->template fpfield<6>(_iml)
#define minf_columnindex 6
#define mtau _ml->template fpfield<7>(_iml)
#define mtau_columnindex 7
#define hinf _ml->template fpfield<8>(_iml)
#define hinf_columnindex 8
#define htau _ml->template fpfield<9>(_iml)
#define htau_columnindex 9
#define Dm _ml->template fpfield<10>(_iml)
#define Dm_columnindex 10
#define Dh _ml->template fpfield<11>(_iml)
#define Dh_columnindex 11
#define v _ml->template fpfield<12>(_iml)
#define v_columnindex 12
#define _g _ml->template fpfield<13>(_iml)
#define _g_columnindex 13
#define _ion_ek *(_ml->dptr_field<0>(_iml))
#define _p_ion_ek static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_ik *(_ml->dptr_field<1>(_iml))
#define _p_ion_ik static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_dikdv *(_ml->dptr_field<2>(_iml))
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_rates(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mechtype);
#endif
 static void _hoc_setdata();
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 {"setdata_krp", _hoc_setdata},
 {"rates_krp", _hoc_rates},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_rates(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"rates", _npy_rates},
 {0, 0}
};
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"gbar_krp", "S/cm2"},
 {"ik_krp", "mA/cm2"},
 {0, 0}
};
 static double delta_t = 0.01;
 static double h0 = 0;
 static double m0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {0, 0}
};
 static DoubVec hoc_vdoub[] = {
 {0, 0, 0}
};
 static double _sav_indep;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 _prop_id = _nrn_get_prop_id(_prop);
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 static void nrn_alloc(Prop*);
static void nrn_init(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_state(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 static void nrn_cur(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_jacob(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(Prop*, int, neuron::container::data_handle<double>*, neuron::container::data_handle<double>*, double*, int);
static void _ode_spec(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void _ode_matsol(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 
#define _cvode_ieq _ppvar[3].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"krp",
 "gbar_krp",
 "a_krp",
 0,
 "ik_krp",
 0,
 "m_krp",
 "h_krp",
 0,
 0};
 static Symbol* _k_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0.001, /* gbar */
     0.7, /* a */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
   _ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 14);
 	/*initialize range parameters*/
 	gbar = _parm_default[0]; /* 0.001 */
 	a = _parm_default[1]; /* 0.7 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 14);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 0); /* ek */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ik */
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dikdv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 {0, 0}
};
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _Krp_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"gbar"} /* 0 */,
                                       _nrn_mechanism_field<double>{"a"} /* 1 */,
                                       _nrn_mechanism_field<double>{"ik"} /* 2 */,
                                       _nrn_mechanism_field<double>{"m"} /* 3 */,
                                       _nrn_mechanism_field<double>{"h"} /* 4 */,
                                       _nrn_mechanism_field<double>{"ek"} /* 5 */,
                                       _nrn_mechanism_field<double>{"minf"} /* 6 */,
                                       _nrn_mechanism_field<double>{"mtau"} /* 7 */,
                                       _nrn_mechanism_field<double>{"hinf"} /* 8 */,
                                       _nrn_mechanism_field<double>{"htau"} /* 9 */,
                                       _nrn_mechanism_field<double>{"Dm"} /* 10 */,
                                       _nrn_mechanism_field<double>{"Dh"} /* 11 */,
                                       _nrn_mechanism_field<double>{"v"} /* 12 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 13 */,
                                       _nrn_mechanism_field<double*>{"_ion_ek", "k_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_ik", "k_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_dikdv", "k_ion"} /* 2 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 3 */);
  hoc_register_prop_size(_mechtype, 14, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 krp /home/amajnas/wolf_model/Krp.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static const char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_internalthreadargsprotocomma_ double);
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[2], _dlist1[2];
 static int states(_internalthreadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (_internalthreadargsproto_) {int _reset = 0; {
   rates ( _threadargscomma_ v ) ;
   Dm = ( minf - m ) / mtau ;
   Dh = ( hinf - h ) / htau ;
   }
 return _reset;
}
 static int _ode_matsol1 (_internalthreadargsproto_) {
 rates ( _threadargscomma_ v ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / mtau )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / htau )) ;
  return 0;
}
 /*END CVODE*/
 static int states (_internalthreadargsproto_) { {
   rates ( _threadargscomma_ v ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / mtau)))*(- ( ( ( minf ) ) / mtau ) / ( ( ( ( - 1.0 ) ) ) / mtau ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / htau)))*(- ( ( ( hinf ) ) / htau ) / ( ( ( ( - 1.0 ) ) ) / htau ) - h) ;
   }
  return 0;
}
 
static int  rates ( _internalthreadargsprotocomma_ double _lv ) {
   double _lv_idx , _lfraction ;
 minf = 1.0 / ( 1.0 + exp ( ( _lv - ( - 13.5 ) ) / - 11.8 ) ) ;
   hinf = 1.0 / ( 1.0 + exp ( ( _lv - ( - 54.7 ) ) / 18.6 ) ) ;
   if ( _lv <= - 100.0 ) {
     mtau = 13.33 ;
     htau = 2333.33 ;
     }
   else if ( _lv >= 50.0 ) {
     mtau = 1.67 ;
     htau = 666.67 ;
     }
   else {
     _lv_idx = floor ( ( _lv - ( - 100.0 ) ) / 5.0 ) ;
     _lfraction = ( ( _lv - ( - 100.0 ) ) / 5.0 ) - _lv_idx ;
     if ( _lv_idx  == 0.0 ) {
       mtau = 13.33 + _lfraction * ( 15.0 - 13.33 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 1.0 ) {
       mtau = 15.0 + _lfraction * ( 16.27 - 15.0 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 2.0 ) {
       mtau = 16.27 + _lfraction * ( 18.33 - 16.27 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 3.0 ) {
       mtau = 18.33 + _lfraction * ( 21.47 - 18.33 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 4.0 ) {
       mtau = 21.47 + _lfraction * ( 25.0 - 21.47 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 5.0 ) {
       mtau = 25.0 + _lfraction * ( 27.97 - 25.0 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 6.0 ) {
       mtau = 27.97 + _lfraction * ( 30.0 - 27.97 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 7.0 ) {
       mtau = 30.0 + _lfraction * ( 31.17 - 30.0 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 8.0 ) {
       mtau = 31.17 + _lfraction * ( 31.67 - 31.17 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 9.0 ) {
       mtau = 31.67 + _lfraction * ( 31.8 - 31.67 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 10.0 ) {
       mtau = 31.8 + _lfraction * ( 32.33 - 31.8 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 11.0 ) {
       mtau = 32.33 + _lfraction * ( 33.07 - 32.33 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 12.0 ) {
       mtau = 33.07 + _lfraction * ( 31.67 - 33.07 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 13.0 ) {
       mtau = 31.67 + _lfraction * ( 26.57 - 31.67 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 14.0 ) {
       mtau = 26.57 + _lfraction * ( 20.0 - 26.57 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 15.0 ) {
       mtau = 20.0 + _lfraction * ( 14.83 - 20.0 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 16.0 ) {
       mtau = 14.83 + _lfraction * ( 11.67 - 14.83 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 17.0 ) {
       mtau = 11.67 + _lfraction * ( 9.77 - 11.67 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 18.0 ) {
       mtau = 9.77 + _lfraction * ( 8.33 - 9.77 ) ;
       htau = 2333.33 + _lfraction * ( 2333.33 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 19.0 ) {
       mtau = 8.33 + _lfraction * ( 6.67 - 8.33 ) ;
       htau = 2333.33 + _lfraction * ( 2247.5 - 2333.33 ) ;
       }
     else if ( _lv_idx  == 20.0 ) {
       mtau = 6.67 + _lfraction * ( 5.0 - 6.67 ) ;
       htau = 2247.5 + _lfraction * ( 2000.0 - 2247.5 ) ;
       }
     else if ( _lv_idx  == 21.0 ) {
       mtau = 5.0 + _lfraction * ( 3.87 - 5.0 ) ;
       htau = 2000.0 + _lfraction * ( 1580.07 - 2000.0 ) ;
       }
     else if ( _lv_idx  == 22.0 ) {
       mtau = 3.87 + _lfraction * ( 3.33 - 3.87 ) ;
       htau = 1580.07 + _lfraction * ( 1166.67 - 1580.07 ) ;
       }
     else if ( _lv_idx  == 23.0 ) {
       mtau = 3.33 + _lfraction * ( 3.2 - 3.33 ) ;
       htau = 1166.67 + _lfraction * ( 927.77 - 1166.67 ) ;
       }
     else if ( _lv_idx  == 24.0 ) {
       mtau = 3.2 + _lfraction * ( 3.33 - 3.2 ) ;
       htau = 927.77 + _lfraction * ( 833.33 - 927.77 ) ;
       }
     else if ( _lv_idx  == 25.0 ) {
       mtau = 3.33 + _lfraction * ( 3.5 - 3.33 ) ;
       htau = 833.33 + _lfraction * ( 778.77 - 833.33 ) ;
       }
     else if ( _lv_idx  == 26.0 ) {
       mtau = 3.5 + _lfraction * ( 3.33 - 3.5 ) ;
       htau = 778.77 + _lfraction * ( 733.33 - 778.77 ) ;
       }
     else if ( _lv_idx  == 27.0 ) {
       mtau = 3.33 + _lfraction * ( 2.67 - 3.33 ) ;
       htau = 733.33 + _lfraction * ( 694.5 - 733.33 ) ;
       }
     else if ( _lv_idx  == 28.0 ) {
       mtau = 2.67 + _lfraction * ( 1.67 - 2.67 ) ;
       htau = 694.5 + _lfraction * ( 666.67 - 694.5 ) ;
       }
     else if ( _lv_idx  == 29.0 ) {
       mtau = 1.67 + _lfraction * ( 1.67 - 1.67 ) ;
       htau = 666.67 + _lfraction * ( 666.67 - 666.67 ) ;
       }
     }
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r = 1.;
 rates ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_rates(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r = 1.;
 rates ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
   Datum* _ppvar;
   size_t _iml;   _nrn_mechanism_cache_range* _ml;   Node* _nd{};
  double _v{};
  int _cntml;
  _nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
  _ml = &_lmr;
  _cntml = _ml_arg->_nodecount;
  Datum *_thread{_ml_arg->_thread};
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _ppvar = _ml_arg->_pdata[_iml];
    _nd = _ml_arg->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
     _ode_spec1 (_threadargs_);
  }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  Datum* _ppvar;
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 2; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _ode_matsol1 (_threadargs_);
 }
 
static void _ode_matsol(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
   Datum* _ppvar;
   size_t _iml;   _nrn_mechanism_cache_range* _ml;   Node* _nd{};
  double _v{};
  int _cntml;
  _nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
  _ml = &_lmr;
  _cntml = _ml_arg->_nodecount;
  Datum *_thread{_ml_arg->_thread};
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _ppvar = _ml_arg->_pdata[_iml];
    _nd = _ml_arg->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  h = h0;
  m = m0;
 {
   rates ( _threadargscomma_ v ) ;
   m = minf ;
   h = hinf ;
   }
 
}
}

static void nrn_init(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type){
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
   _v = _vec_v[_ni[_iml]];
 v = _v;
  ek = _ion_ek;
 initmodel(_threadargs_);
 }
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   ik = gbar * m * ( a * h + ( 1.0 - a ) ) * ( v - ek ) ;
   }
 _current += ik;

} return _current;
}

static void nrn_cur(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_rhs = _nt->node_rhs_storage();
auto const _vec_sav_rhs = _nt->node_sav_rhs_storage();
auto const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
   _v = _vec_v[_ni[_iml]];
  ek = _ion_ek;
 auto const _g_local = _nrn_current(_threadargscomma_ _v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_threadargscomma_ _v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g_local - _rhs)/.001;
  _ion_ik += ik ;
	 _vec_rhs[_ni[_iml]] -= _rhs;
 
}
 
}

static void nrn_jacob(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_d = _nt->node_d_storage();
auto const _vec_sav_d = _nt->node_sav_d_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
  _vec_d[_ni[_iml]] += _g;
 
}
 
}

static void nrn_state(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni;
_ni = _ml_arg->_nodeindices;
size_t _cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (size_t _iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
 _nd = _ml_arg->_nodelist[_iml];
   _v = _vec_v[_ni[_iml]];
 v=_v;
{
  ek = _ion_ek;
 {   states(_threadargs_);
  } }}

}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {m_columnindex, 0};  _dlist1[0] = {Dm_columnindex, 0};
 _slist1[1] = {h_columnindex, 0};  _dlist1[1] = {Dh_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/amajnas/wolf_model/Krp.mod";
    const char* nmodl_file_text = 
  "TITLE \n"
  "\n"
  "NEURON {\n"
  "    SUFFIX krp\n"
  "    USEION k READ ek WRITE ik\n"
  "    RANGE gbar, ik, a\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "    (mV) = (millivolt)\n"
  "    (mA) = (milliamp)\n"
  "    (S) = (siemens)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    gbar = 0.001 (S/cm2) \n"
  "    a = 0.7             \n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    v (mV)\n"
  "    ek (mV)\n"
  "    ik (mA/cm2)\n"
  "    minf\n"
  "    mtau (ms)\n"
  "    hinf\n"
  "    htau (ms)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "    m                     \n"
  "    h                     \n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    SOLVE states METHOD cnexp\n"
  "    ik = gbar * m * (a * h + (1.0 - a)) * (v - ek)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    rates(v)\n"
  "    m = minf\n"
  "    h = hinf\n"
  "}\n"
  "\n"
  "DERIVATIVE states {\n"
  "    rates(v)\n"
  "    m' = (minf - m) / mtau\n"
  "    h' = (hinf - h) / htau\n"
  "}\n"
  "\n"
  "PROCEDURE rates(v (mV)) {\n"
  "    LOCAL v_idx, fraction\n"
  "    minf = 1 / (1 + exp((v - (-13.5)) / -11.8))\n"
  "    hinf = 1 / (1 + exp((v - (-54.7)) / 18.6))\n"
  "    \n"
  "    : Note: Insert your equations for minf and hinf here if you have them.\n"
  "\n"
  "    : --- HARDCODED LINEAR INTERPOLATION FOR KRP (mtau & htau) ---\n"
  "    : Range bounds: -100.0 mV to 50.0 mV, Step size: 5.0 mV\n"
  "    \n"
  "    if (v <= -100.0) {\n"
  "        mtau = 13.33\n"
  "        htau = 2333.33\n"
  "    } else if (v >= 50.0) {\n"
  "        mtau = 1.67\n"
  "        htau = 666.67\n"
  "    } else {\n"
  "        : Map voltage to table index (step size is 5 mV, starting at -100 mV)\n"
  "        v_idx = floor((v - (-100.0)) / 5.0)\n"
  "        fraction = ((v - (-100.0)) / 5.0) - v_idx\n"
  "        \n"
  "        : Perform linear interpolation based on index\n"
  "        if (v_idx == 0) { \n"
  "            mtau = 13.33 + fraction * (15.0 - 13.33) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 1) { \n"
  "            mtau = 15.0 + fraction * (16.27 - 15.0) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 2) { \n"
  "            mtau = 16.27 + fraction * (18.33 - 16.27) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 3) { \n"
  "            mtau = 18.33 + fraction * (21.47 - 18.33) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 4) { \n"
  "            mtau = 21.47 + fraction * (25.0 - 21.47) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 5) { \n"
  "            mtau = 25.0 + fraction * (27.97 - 25.0) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 6) { \n"
  "            mtau = 27.97 + fraction * (30.0 - 27.97) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 7) { \n"
  "            mtau = 30.0 + fraction * (31.17 - 30.0) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 8) { \n"
  "            mtau = 31.17 + fraction * (31.67 - 31.17) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 9) { \n"
  "            mtau = 31.67 + fraction * (31.8 - 31.67) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 10) { \n"
  "            mtau = 31.8 + fraction * (32.33 - 31.8) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 11) { \n"
  "            mtau = 32.33 + fraction * (33.07 - 32.33) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 12) { \n"
  "            mtau = 33.07 + fraction * (31.67 - 33.07) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 13) { \n"
  "            mtau = 31.67 + fraction * (26.57 - 31.67) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 14) { \n"
  "            mtau = 26.57 + fraction * (20.0 - 26.57) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 15) { \n"
  "            mtau = 20.0 + fraction * (14.83 - 20.0) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 16) { \n"
  "            mtau = 14.83 + fraction * (11.67 - 14.83) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 17) { \n"
  "            mtau = 11.67 + fraction * (9.77 - 11.67) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 18) { \n"
  "            mtau = 9.77 + fraction * (8.33 - 9.77) \n"
  "            htau = 2333.33 + fraction * (2333.33 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 19) { \n"
  "            mtau = 8.33 + fraction * (6.67 - 8.33) \n"
  "            htau = 2333.33 + fraction * (2247.5 - 2333.33)\n"
  "        }\n"
  "        else if (v_idx == 20) { \n"
  "            mtau = 6.67 + fraction * (5.0 - 6.67) \n"
  "            htau = 2247.5 + fraction * (2000.0 - 2247.5)\n"
  "        }\n"
  "        else if (v_idx == 21) { \n"
  "            mtau = 5.0 + fraction * (3.87 - 5.0) \n"
  "            htau = 2000.0 + fraction * (1580.07 - 2000.0)\n"
  "        }\n"
  "        else if (v_idx == 22) { \n"
  "            mtau = 3.87 + fraction * (3.33 - 3.87) \n"
  "            htau = 1580.07 + fraction * (1166.67 - 1580.07)\n"
  "        }\n"
  "        else if (v_idx == 23) { \n"
  "            mtau = 3.33 + fraction * (3.2 - 3.33) \n"
  "            htau = 1166.67 + fraction * (927.77 - 1166.67)\n"
  "        }\n"
  "        else if (v_idx == 24) { \n"
  "            mtau = 3.2 + fraction * (3.33 - 3.2) \n"
  "            htau = 927.77 + fraction * (833.33 - 927.77)\n"
  "        }\n"
  "        else if (v_idx == 25) { \n"
  "            mtau = 3.33 + fraction * (3.5 - 3.33) \n"
  "            htau = 833.33 + fraction * (778.77 - 833.33)\n"
  "        }\n"
  "        else if (v_idx == 26) { \n"
  "            mtau = 3.5 + fraction * (3.33 - 3.5) \n"
  "            htau = 778.77 + fraction * (733.33 - 778.77)\n"
  "        }\n"
  "        else if (v_idx == 27) { \n"
  "            mtau = 3.33 + fraction * (2.67 - 3.33) \n"
  "            htau = 733.33 + fraction * (694.5 - 733.33)\n"
  "        }\n"
  "        else if (v_idx == 28) { \n"
  "            mtau = 2.67 + fraction * (1.67 - 2.67) \n"
  "            htau = 694.5 + fraction * (666.67 - 694.5)\n"
  "        }\n"
  "        else if (v_idx == 29) { \n"
  "            mtau = 1.67 + fraction * (1.67 - 1.67) \n"
  "            htau = 666.67 + fraction * (666.67 - 666.67)\n"
  "        }\n"
  "    }\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
