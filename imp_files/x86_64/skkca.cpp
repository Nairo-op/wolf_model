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
static constexpr auto number_of_datum_variables = 5;
static constexpr auto number_of_floating_point_variables = 11;
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
 
#define nrn_init _nrn_init__skkca
#define _nrn_initial _nrn_initial__skkca
#define nrn_cur _nrn_cur__skkca
#define _nrn_current _nrn_current__skkca
#define nrn_jacob _nrn_jacob__skkca
#define nrn_state _nrn_state__skkca
#define _net_receive _net_receive__skkca 
#define rate rate__skkca 
#define state state__skkca 
 
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
#define stau _ml->template fpfield<0>(_iml)
#define stau_columnindex 0
#define gkbar _ml->template fpfield<1>(_iml)
#define gkbar_columnindex 1
#define ik _ml->template fpfield<2>(_iml)
#define ik_columnindex 2
#define o _ml->template fpfield<3>(_iml)
#define o_columnindex 3
#define cai _ml->template fpfield<4>(_iml)
#define cai_columnindex 4
#define ek _ml->template fpfield<5>(_iml)
#define ek_columnindex 5
#define oinf _ml->template fpfield<6>(_iml)
#define oinf_columnindex 6
#define tau _ml->template fpfield<7>(_iml)
#define tau_columnindex 7
#define Do _ml->template fpfield<8>(_iml)
#define Do_columnindex 8
#define v _ml->template fpfield<9>(_iml)
#define v_columnindex 9
#define _g _ml->template fpfield<10>(_iml)
#define _g_columnindex 10
#define _ion_cai *(_ml->dptr_field<0>(_iml))
#define _p_ion_cai static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_cao *(_ml->dptr_field<1>(_iml))
#define _p_ion_cao static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_ek *(_ml->dptr_field<2>(_iml))
#define _p_ion_ek static_cast<neuron::container::data_handle<double>>(_ppvar[2])
#define _ion_ik *(_ml->dptr_field<3>(_iml))
#define _p_ion_ik static_cast<neuron::container::data_handle<double>>(_ppvar[3])
#define _ion_dikdv *(_ml->dptr_field<4>(_iml))
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_alp(void);
 static void _hoc_bet(void);
 static void _hoc_exp1(void);
 static void _hoc_rate(void);
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
 {"setdata_skkca", _hoc_setdata},
 {"alp_skkca", _hoc_alp},
 {"bet_skkca", _hoc_bet},
 {"exp1_skkca", _hoc_exp1},
 {"rate_skkca", _hoc_rate},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_alp(Prop*);
 static double _npy_bet(Prop*);
 static double _npy_exp1(Prop*);
 static double _npy_rate(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"alp", _npy_alp},
 {"bet", _npy_bet},
 {"exp1", _npy_exp1},
 {"rate", _npy_rate},
 {0, 0}
};
#define alp alp_skkca
#define bet bet_skkca
#define exp1 exp1_skkca
 extern double alp( _internalthreadargsprotocomma_ double , double , double );
 extern double bet( _internalthreadargsprotocomma_ double , double , double );
 extern double exp1( _internalthreadargsprotocomma_ double , double , double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define abar abar_skkca
 double abar = 0.48;
#define bbar bbar_skkca
 double bbar = 0.28;
#define d2 d2_skkca
 double d2 = 1;
#define d1 d1_skkca
 double d1 = 0.84;
#define k2 k2_skkca
 double k2 = 0.011;
#define k1 k1_skkca
 double k1 = 0.18;
#define qfact qfact_skkca
 double qfact = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"k1_skkca", "mM"},
 {"k2_skkca", "mM"},
 {"abar_skkca", "/ms"},
 {"bbar_skkca", "/ms"},
 {"gkbar_skkca", "mho/cm2"},
 {"ik_skkca", "mA/cm2"},
 {0, 0}
};
 static double delta_t = 0.01;
 static double o0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"qfact_skkca", &qfact_skkca},
 {"d1_skkca", &d1_skkca},
 {"d2_skkca", &d2_skkca},
 {"k1_skkca", &k1_skkca},
 {"k2_skkca", &k2_skkca},
 {"abar_skkca", &abar_skkca},
 {"bbar_skkca", &bbar_skkca},
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
 
#define _cvode_ieq _ppvar[5].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"skkca",
 "stau_skkca",
 "gkbar_skkca",
 0,
 "ik_skkca",
 0,
 "o_skkca",
 0,
 0};
 static Symbol* _ca_sym;
 static Symbol* _k_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     1, /* stau */
     0.145, /* gkbar */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
   _ppvar = nrn_prop_datum_alloc(_mechtype, 6, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 11);
 	/*initialize range parameters*/
 	stau = _parm_default[0]; /* 1 */
 	gkbar = _parm_default[1]; /* 0.145 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 11);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 1); /* cai */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 2); /* cao */
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 0); /* ek */
 	_ppvar[3] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ik */
 	_ppvar[4] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dikdv */
 
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

 extern "C" void _skkca_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	ion_reg("k", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
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
                                       _nrn_mechanism_field<double>{"stau"} /* 0 */,
                                       _nrn_mechanism_field<double>{"gkbar"} /* 1 */,
                                       _nrn_mechanism_field<double>{"ik"} /* 2 */,
                                       _nrn_mechanism_field<double>{"o"} /* 3 */,
                                       _nrn_mechanism_field<double>{"cai"} /* 4 */,
                                       _nrn_mechanism_field<double>{"ek"} /* 5 */,
                                       _nrn_mechanism_field<double>{"oinf"} /* 6 */,
                                       _nrn_mechanism_field<double>{"tau"} /* 7 */,
                                       _nrn_mechanism_field<double>{"Do"} /* 8 */,
                                       _nrn_mechanism_field<double>{"v"} /* 9 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 10 */,
                                       _nrn_mechanism_field<double*>{"_ion_cai", "ca_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_cao", "ca_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_ek", "k_ion"} /* 2 */,
                                       _nrn_mechanism_field<double*>{"_ion_ik", "k_ion"} /* 3 */,
                                       _nrn_mechanism_field<double*>{"_ion_dikdv", "k_ion"} /* 4 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 5 */);
  hoc_register_prop_size(_mechtype, 11, 6);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 skkca /home/amajnas/wolf_model/imp_files/skkca.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 0x1.81f0fae775425p+6;
 static double R = 0x1.0a1013e8990bep+3;
static int _reset;
static const char *modelname = "Small-Conductance Calcium-Activated Potassium Channel (SK)";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rate(_internalthreadargsprotocomma_ double, double, double);
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[1], _dlist1[1];
 static int state(_internalthreadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (_internalthreadargsproto_) {int _reset = 0; {
   rate ( _threadargscomma_ v , cai , celsius ) ;
   Do = ( oinf - o ) / ( tau / qfact ) ;
   }
 return _reset;
}
 static int _ode_matsol1 (_internalthreadargsproto_) {
 rate ( _threadargscomma_ v , cai , celsius ) ;
 Do = Do  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ( tau / qfact ) )) ;
  return 0;
}
 /*END CVODE*/
 static int state (_internalthreadargsproto_) { {
   rate ( _threadargscomma_ v , cai , celsius ) ;
    o = o + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ( tau / qfact ))))*(- ( ( ( oinf ) ) / ( tau / qfact ) ) / ( ( ( ( - 1.0 ) ) ) / ( tau / qfact ) ) - o) ;
   }
  return 0;
}
 
static int  rate ( _internalthreadargsprotocomma_ double _lv , double _lca , double _lcelsius ) {
   double _la , _lb ;
 _la = alp ( _threadargscomma_ _lv , _lca , _lcelsius ) ;
   _lb = bet ( _threadargscomma_ _lv , _lca , _lcelsius ) ;
   tau = stau / ( _la + _lb ) ;
   oinf = _la / ( _la + _lb ) ;
    return 0; }
 
static void _hoc_rate(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for rate_skkca. Requires prior call to setdata_skkca and that the specified mechanism instance still be in existence.", NULL);
  }
  Prop* _local_prop = _extcall_prop;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r = 1.;
 rate ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static double _npy_rate(Prop* _prop) {
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
 rate ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 return(_r);
}
 
double alp ( _internalthreadargsprotocomma_ double _lv , double _lc , double _lcelsius ) {
   double _lalp;
 _lalp = _lc * abar / ( _lc + exp1 ( _threadargscomma_ k1 , d1 , _lv , _lcelsius ) ) ;
   
return _lalp;
 }
 
static void _hoc_alp(void) {
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
 _r =  alp ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static double _npy_alp(Prop* _prop) {
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
 _r =  alp ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 return(_r);
}
 
double bet ( _internalthreadargsprotocomma_ double _lv , double _lc , double _lcelsius ) {
   double _lbet;
 _lbet = bbar / ( 1.0 + _lc / exp1 ( _threadargscomma_ k2 , d2 , _lv , _lcelsius ) ) ;
   
return _lbet;
 }
 
static void _hoc_bet(void) {
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
 _r =  bet ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static double _npy_bet(Prop* _prop) {
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
 _r =  bet ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 return(_r);
}
 
double exp1 ( _internalthreadargsprotocomma_ double _lk , double _ld , double _lv , double _lcelsius ) {
   double _lexp1;
 _lexp1 = _lk * exp ( - 2.0 * _ld * FARADAY * _lv / ( R * ( 273.15 + _lcelsius ) ) ) ;
   
return _lexp1;
 }
 
static void _hoc_exp1(void) {
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
 _r =  exp1 ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 hoc_retpushx(_r);
}
 
static double _npy_exp1(Prop* _prop) {
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
 _r =  exp1 ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 return(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
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
  cai = _ion_cai;
  ek = _ion_ek;
     _ode_spec1 (_threadargs_);
  }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  Datum* _ppvar;
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 1; ++_i) {
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
  cai = _ion_cai;
  ek = _ion_ek;
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  o = o0;
 {
   rate ( _threadargscomma_ v , cai , celsius ) ;
   o = oinf ;
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
  cai = _ion_cai;
  ek = _ion_ek;
 initmodel(_threadargs_);
 }
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   ik = gkbar * o * ( v - ek ) ;
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
  cai = _ion_cai;
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
  cai = _ion_cai;
  ek = _ion_ek;
 {   state(_threadargs_);
  } }}

}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {o_columnindex, 0};  _dlist1[0] = {Do_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/amajnas/wolf_model/imp_files/skkca.mod";
    const char* nmodl_file_text = 
  "TITLE Small-Conductance Calcium-Activated Potassium Channel (SK)\n"
  "\n"
  "COMMENT\n"
  "=============================================================================\n"
  "Biophysical Description:\n"
  "------------------------\n"
  "Implements a small-conductance, calcium-activated potassium channel (SK, KCa2),\n"
  "which contributes to the medium afterhyperpolarization (mAHP), regulates action\n"
  "potential firing frequency, and mediates spike-frequency adaptation in neurons.\n"
  "\n"
  "In striatal medium spiny projection neurons (MSNs), experimental evidence \n"
  "(e.g., Vilchis et al., 2000) indicates that calcium-dependent potassium channels\n"
  "are selectively activated by calcium influx from specific voltage-gated calcium \n"
  "channels (VGCCs). Thus, this model is linked to the \"ca\" pool (representing N-, \n"
  "P/Q-, and R-type calcium currents) rather than the \"cal\" pool (representing L- \n"
  "and T-type calcium currents).\n"
  "\n"
  "Scientific Basis & Model Formulation:\n"
  "-------------------------------------\n"
  "The model is mathematically formulated as a two-state Markov-like transition \n"
  "scheme (Closed <-> Open) represented by a single Hodgkin-Huxley style gating \n"
  "state variable 'o' (the open fraction of channels):\n"
  "\n"
  "    do/dt = (oinf - o) / (tau / qfact)\n"
  "\n"
  "The activation rate (alp) and deactivation rate (bet) are functions of both \n"
  "intracellular calcium concentration ([Ca]i) and membrane potential (V):\n"
  "\n"
  "    alp = [Ca]i * abar / ([Ca]i + K1(V))\n"
  "    bet = bbar / (1 + [Ca]i / K2(V))\n"
  "\n"
  "Where the voltage-dependent dissociation constants (K1 and K2) are scaled as:\n"
  "\n"
  "    Ki(V) = ki * exp( -2 * di * F * V / (R * T) )\n"
  "\n"
  "Here:\n"
  "- [Ca]i: Intracellular calcium concentration from the N-, Q-, and R-type pool (cai, mM).\n"
  "- V: Membrane potential (v, mV).\n"
  "- celsius: Temperature in degrees Celsius (from NEURON's global namespace, set to 35 C).\n"
  "- F (FARADAY): Faraday constant (96.4853 kilocoulombs/equivalent).\n"
  "- R (Gas Constant): Universal gas constant (8.3144 Joules/(mole*Kelvin)).\n"
  "- T: Absolute temperature in Kelvin (273.15 + celsius).\n"
  "- d1, d2: Gating valences for activation and deactivation, respectively.\n"
  "- k1, k2: Dissociation constants at 0 mV.\n"
  "- abar, bbar: Maximum forward (activation) and backward (deactivation) rate constants.\n"
  "- qfact: Q10 temperature sensitivity factor (set to 1.0 in Wolf et al. 2005).\n"
  "\n"
  "Historical Correction / Model Origin:\n"
  "-------------------------------------\n"
  "Although implemented here to represent the small-conductance SK channel, the \n"
  "mathematical formalism and kinetic rate parameters (abar, bbar, k1, k2, d1, d2) \n"
  "originate from the two-state gating model characterized for the large-conductance \n"
  "(BK) channel by Moczydlowski and Latorre (1983) \"Gating Kinetics of Ca2+-Activated \n"
  "K+ Channels from Rat Muscle\" (J. Gen. Physiol. 82:511-542). In the Wolf et al. (2005) \n"
  "MSN model, these equations were adapted to simulate the SK current (skkca) by setting \n"
  "the peak specific conductance (gkbar) to 0.145 S/cm2.\n"
  "\n"
  "Model Parameters (Wolf et al. 2005):\n"
  "------------------------------------\n"
  "- d1 (valence) = 0.84\n"
  "- d2 (valence) = 1.00\n"
  "- k1 (mM) = 0.18    (180 uM dissociation constant at 0 mV)\n"
  "- k2 (mM) = 0.011   (11 uM dissociation constant at 0 mV)\n"
  "- abar (/ms) = 0.48\n"
  "- bbar (/ms) = 0.28\n"
  "- gkbar (S/cm2) = 0.145\n"
  "=============================================================================\n"
  "ENDCOMMENT\n"
  "\n"
  "UNITS {\n"
  "    (molar) = (1/liter)\n"
  "    (mV) =  (millivolt)\n"
  "    (mA) =  (milliamp)\n"
  "    (mM) =  (millimolar)\n"
  "    FARADAY = (faraday)  (kilocoulombs)\n"
  "    R = (k-mole) (joule/degC)\n"
  "}\n"
  "\n"
  "NEURON {\n"
  "    SUFFIX skkca                    : Registers mechanism under the suffix 'skkca'\n"
  "    USEION ca READ cai              : Accesses intracellular calcium concentration (cai) from N/Q/R-type pool\n"
  "    USEION k READ ek WRITE ik       : Reads potassium reversal potential (ek) and writes current density (ik)\n"
  "    RANGE gkbar, ik, stau           : Range variables: peak conductance, current density, time scaling\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    stau = 1.0                      : Gating time-constant scaling factor\n"
  "    qfact = 1.0                     : Q10 temperature factor (1.0 in Wolf et al. 2005)\n"
  "    v       (mV)                    : Membrane potential\n"
  "    gkbar = 0.145    (mho/cm2)      : Maximal channel conductance\n"
  "    cai     (mM)                    : Intracellular calcium concentration\n"
  "    ek      (mV)                    : Potassium reversal potential\n"
  "    celsius (degC)                  : Global temperature variable from NEURON\n"
  "    \n"
  "    : Gating kinetics parameters from Moczydlowski & Latorre (1983)\n"
  "    d1 = 0.84                       : Gating valence (activation)\n"
  "    d2 = 1.0                        : Gating valence (deactivation)\n"
  "    k1 = 0.18 (mM)                  : Dissociation constant for activation at 0 mV\n"
  "    k2 = 0.011 (mM)                 : Dissociation constant for deactivation at 0 mV\n"
  "    abar = 0.48  (/ms)              : Maximum forward rate constant\n"
  "    bbar = 0.28  (/ms)              : Maximum backward rate constant\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    ik      (mA/cm2)                : Calculated potassium current density\n"
  "    oinf                            : Steady-state open probability\n"
  "    tau     (ms)                    : Time constant of activation gating\n"
  "}\n"
  "\n"
  "STATE { \n"
  "    o                               : State variable representing the fraction of open channels\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    SOLVE state METHOD cnexp        : Solve the differential equation for gating variable 'o'\n"
  "    ik = gkbar * o * (v - ek)       : Current calculation using Ohm's law\n"
  "}\n"
  "\n"
  "DERIVATIVE state {\n"
  "    rate(v, cai, celsius)\n"
  "    o' = (oinf - o) / (tau / qfact) : Gating state variable derivative\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    rate(v, cai, celsius)\n"
  "    o = oinf                        : Set open fraction to steady state initial value\n"
  "}\n"
  "\n"
  "PROCEDURE rate(v (mV), ca (mM), celsius (degC)) {\n"
  "    LOCAL a, b\n"
  "    a = alp(v, ca, celsius)\n"
  "    b = bet(v, ca, celsius)\n"
  "    tau = stau / (a + b)            : Activation time constant\n"
  "    oinf = a / (a + b)              : Steady-state open probability\n"
  "}\n"
  "\n"
  "FUNCTION alp(v (mV), c (mM), celsius (degC)) (1/ms) { \n"
  "    : Forward activation rate alpha(V, [Ca]i)\n"
  "    : alpha = [Ca]i * abar / ([Ca]i + K1(V))\n"
  "    alp = c * abar / (c + exp1(k1, d1, v, celsius))\n"
  "}\n"
  "\n"
  "FUNCTION bet(v (mV), c (mM), celsius (degC)) (1/ms) { \n"
  "    : Backward deactivation rate beta(V, [Ca]i)\n"
  "    : beta = bbar / (1 + [Ca]i / K2(V))\n"
  "    bet = bbar / (1 + c / exp1(k2, d2, v, celsius))\n"
  "}\n"
  "\n"
  "FUNCTION exp1(k (mM), d, v (mV), celsius (degC)) (mM) { \n"
  "    : Voltage-dependent dissociation constant Ki(V)\n"
  "    : Ki(V) = ki * exp( -2 * di * F * V / (R * T) )\n"
  "    : Note: Uses thermodynamic scaling where FARADAY and R constants are converted\n"
  "    : to yield a dimensionless exponent for v in millivolts.\n"
  "    exp1 = k * exp(-2 * d * FARADAY * v  / (R * (273.15 + celsius)))\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
