/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
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
#include <vector>
using std::size_t;
static auto& std_cerr_stream = std::cerr;
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
 
#define nrn_init _nrn_init__bkkca
#define _nrn_initial _nrn_initial__bkkca
#define nrn_cur _nrn_cur__bkkca
#define _nrn_current _nrn_current__bkkca
#define nrn_jacob _nrn_jacob__bkkca
#define nrn_state _nrn_state__bkkca
#define _net_receive _net_receive__bkkca 
#define rate rate__bkkca 
#define state state__bkkca 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _internalthreadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
#define _internalthreadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *hoc_getarg(int);
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define stau _ml->template fpfield<0>(_iml)
#define stau_columnindex 0
#define qfact _ml->template fpfield<1>(_iml)
#define qfact_columnindex 1
#define gkbar _ml->template fpfield<2>(_iml)
#define gkbar_columnindex 2
#define abar _ml->template fpfield<3>(_iml)
#define abar_columnindex 3
#define bbar _ml->template fpfield<4>(_iml)
#define bbar_columnindex 4
#define ik _ml->template fpfield<5>(_iml)
#define ik_columnindex 5
#define o _ml->template fpfield<6>(_iml)
#define o_columnindex 6
#define cai _ml->template fpfield<7>(_iml)
#define cai_columnindex 7
#define ek _ml->template fpfield<8>(_iml)
#define ek_columnindex 8
#define Do _ml->template fpfield<9>(_iml)
#define Do_columnindex 9
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
 static _nrn_mechanism_cache_instance _ml_real{nullptr};
static _nrn_mechanism_cache_range *_ml{&_ml_real};
static size_t _iml{0};
static Datum *_ppvar;
 static int hoc_nrnpointerindex =  -1;
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
 {"setdata_bkkca", _hoc_setdata},
 {"alp_bkkca", _hoc_alp},
 {"bet_bkkca", _hoc_bet},
 {"exp1_bkkca", _hoc_exp1},
 {"rate_bkkca", _hoc_rate},
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
#define alp alp_bkkca
#define bet bet_bkkca
#define exp1 exp1_bkkca
 extern double alp( double , double );
 extern double bet( double , double );
 extern double exp1( double , double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define d2 d2_bkkca
 double d2 = 1;
#define d1 d1_bkkca
 double d1 = 0.84;
#define k2 k2_bkkca
 double k2 = 0.011;
#define k1 k1_bkkca
 double k1 = 0.18;
#define oinf oinf_bkkca
 double oinf = 0;
#define tau tau_bkkca
 double tau = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"k1_bkkca", "mM"},
 {"k2_bkkca", "mM"},
 {"tau_bkkca", "ms"},
 {"gkbar_bkkca", "mho/cm2"},
 {"abar_bkkca", "/ms"},
 {"bbar_bkkca", "/ms"},
 {"ik_bkkca", "mA/cm2"},
 {0, 0}
};
 static double delta_t = 0.01;
 static double o0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"d1_bkkca", &d1_bkkca},
 {"d2_bkkca", &d2_bkkca},
 {"k1_bkkca", &k1_bkkca},
 {"k2_bkkca", &k2_bkkca},
 {"oinf_bkkca", &oinf_bkkca},
 {"tau_bkkca", &tau_bkkca},
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
 neuron::legacy::set_globals_from_prop(_prop, _ml_real, _ml, _iml);
_ppvar = _nrn_mechanism_access_dparam(_prop);
 Node * _node = _nrn_mechanism_access_node(_prop);
v = _nrn_mechanism_access_voltage(_node);
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
"bkkca",
 "stau_bkkca",
 "qfact_bkkca",
 "gkbar_bkkca",
 "abar_bkkca",
 "bbar_bkkca",
 0,
 "ik_bkkca",
 0,
 "o_bkkca",
 0,
 0};
 static Symbol* _ca_sym;
 static Symbol* _k_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     1, /* stau */
     1, /* qfact */
     0.001, /* gkbar */
     0.48, /* abar */
     0.28, /* bbar */
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
 	qfact = _parm_default[1]; /* 1 */
 	gkbar = _parm_default[2]; /* 0.001 */
 	abar = _parm_default[3]; /* 0.48 */
 	bbar = _parm_default[4]; /* 0.28 */
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

 extern "C" void _bkkca_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("ca", -10000.);
 	ion_reg("k", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"stau"} /* 0 */,
                                       _nrn_mechanism_field<double>{"qfact"} /* 1 */,
                                       _nrn_mechanism_field<double>{"gkbar"} /* 2 */,
                                       _nrn_mechanism_field<double>{"abar"} /* 3 */,
                                       _nrn_mechanism_field<double>{"bbar"} /* 4 */,
                                       _nrn_mechanism_field<double>{"ik"} /* 5 */,
                                       _nrn_mechanism_field<double>{"o"} /* 6 */,
                                       _nrn_mechanism_field<double>{"cai"} /* 7 */,
                                       _nrn_mechanism_field<double>{"ek"} /* 8 */,
                                       _nrn_mechanism_field<double>{"Do"} /* 9 */,
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
 	ivoc_help("help ?1 bkkca /home/amajnas/wolf_model/bkkca.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 0x1.81f0fae775425p+6;
 static double R = 0x1.0a1013e8990bep+3;
static int _reset;
static const char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rate(double, double);
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[1], _dlist1[1];
 static int state(_internalthreadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rate ( _threadargscomma_ v , cai ) ;
   Do = ( oinf - o ) / ( tau / qfact ) ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rate ( _threadargscomma_ v , cai ) ;
 Do = Do  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ( tau / qfact ) )) ;
  return 0;
}
 /*END CVODE*/
 static int state () {_reset=0;
 {
   rate ( _threadargscomma_ v , cai ) ;
    o = o + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ( tau / qfact ))))*(- ( ( ( oinf ) ) / ( tau / qfact ) ) / ( ( ( ( - 1.0 ) ) ) / ( tau / qfact ) ) - o) ;
   }
  return 0;
}
 
double alp (  double _lv , double _lca ) {
   double _lalp;
 _lalp = abar / ( 1.0 + exp1 ( _threadargscomma_ k1 , d1 , _lv ) / _lca ) ;
   
return _lalp;
 }
 
static void _hoc_alp(void) {
  double _r;
  
  if(!_prop_id) {
    hoc_execerror("No data for alp_bkkca. Requires prior call to setdata_bkkca and that the specified mechanism instance still be in existence.", NULL);
  } else {
    _setdata(_extcall_prop);
  }
   _r =  alp (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_alp(Prop* _prop) {
    double _r{0.0};
    neuron::legacy::set_globals_from_prop(_prop, _ml_real, _ml, _iml);
  _ppvar = _nrn_mechanism_access_dparam(_prop);
 _r =  alp (  *getarg(1) , *getarg(2) );
 return(_r);
}
 
double bet (  double _lv , double _lca ) {
   double _lbet;
 _lbet = bbar / ( 1.0 + _lca / exp1 ( _threadargscomma_ k2 , d2 , _lv ) ) ;
   
return _lbet;
 }
 
static void _hoc_bet(void) {
  double _r;
  
  if(!_prop_id) {
    hoc_execerror("No data for bet_bkkca. Requires prior call to setdata_bkkca and that the specified mechanism instance still be in existence.", NULL);
  } else {
    _setdata(_extcall_prop);
  }
   _r =  bet (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_bet(Prop* _prop) {
    double _r{0.0};
    neuron::legacy::set_globals_from_prop(_prop, _ml_real, _ml, _iml);
  _ppvar = _nrn_mechanism_access_dparam(_prop);
 _r =  bet (  *getarg(1) , *getarg(2) );
 return(_r);
}
 
double exp1 (  double _lk , double _ld , double _lv ) {
   double _lexp1;
 _lexp1 = _lk * exp ( - 2.0 * _ld * FARADAY * _lv / R / ( 273.15 + celsius ) ) ;
   
return _lexp1;
 }
 
static void _hoc_exp1(void) {
  double _r;
    _r =  exp1 (  *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static double _npy_exp1(Prop* _prop) {
    double _r{0.0};
    neuron::legacy::set_globals_from_prop(_prop, _ml_real, _ml, _iml);
  _ppvar = _nrn_mechanism_access_dparam(_prop);
 _r =  exp1 (  *getarg(1) , *getarg(2) , *getarg(3) );
 return(_r);
}
 
static int  rate (  double _lv , double _lca ) {
   double _la ;
 _la = alp ( _threadargscomma_ _lv , _lca ) ;
   tau = stau / ( _la + bet ( _threadargscomma_ _lv , _lca ) ) ;
   oinf = _la * tau ;
    return 0; }
 
static void _hoc_rate(void) {
  double _r;
  
  if(!_prop_id) {
    hoc_execerror("No data for rate_bkkca. Requires prior call to setdata_bkkca and that the specified mechanism instance still be in existence.", NULL);
  } else {
    _setdata(_extcall_prop);
  }
   _r = 1.;
 rate (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_rate(Prop* _prop) {
    double _r{0.0};
    neuron::legacy::set_globals_from_prop(_prop, _ml_real, _ml, _iml);
  _ppvar = _nrn_mechanism_access_dparam(_prop);
 _r = 1.;
 rate (  *getarg(1) , *getarg(2) );
 return(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
      Node* _nd{};
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
     _ode_spec1 ();
  }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 1; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _ode_matsol1 ();
 }
 
static void _ode_matsol(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
      Node* _nd{};
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

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  o = o0;
 {
   rate ( _threadargscomma_ v , cai ) ;
   o = oinf ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type){
Node *_nd; double _v; int* _ni; int _cntml;
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
_ml = &_lmr;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
   _v = _vec_v[_ni[_iml]];
 v = _v;
  cai = _ion_cai;
  ek = _ion_ek;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ik = gkbar * o * ( v - ek ) ;
   }
 _current += ik;

} return _current;
}

static void nrn_cur(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type){
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_rhs = _nt->node_rhs_storage();
auto const _vec_sav_rhs = _nt->node_sav_rhs_storage();
auto const _vec_v = _nt->node_voltage_storage();
Node *_nd; int* _ni; double _rhs, _v; int _cntml;
_ml = &_lmr;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
   _v = _vec_v[_ni[_iml]];
  cai = _ion_cai;
  ek = _ion_ek;
 auto const _g_local = _nrn_current(_v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g_local - _rhs)/.001;
  _ion_ik += ik ;
	 _vec_rhs[_ni[_iml]] -= _rhs;
 
}}

static void nrn_jacob(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_d = _nt->node_d_storage();
auto const _vec_sav_d = _nt->node_sav_d_storage();
auto* const _ml = &_lmr;
Node *_nd; int* _ni; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
  _vec_d[_ni[_iml]] += _g;
 
}}

static void nrn_state(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _cntml;
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
_ml = &_lmr;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
 _nd = _ml_arg->_nodelist[_iml];
   _v = _vec_v[_ni[_iml]];
 v=_v;
{
  cai = _ion_cai;
  ek = _ion_ek;
 { error =  state();
 if(error){
  std_cerr_stream << "at line 47 in file bkkca.mod:\nBREAKPOINT {\n";
  std_cerr_stream << _ml << ' ' << _iml << '\n';
  abort_run(error);
}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {o_columnindex, 0};  _dlist1[0] = {Do_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/amajnas/wolf_model/bkkca.mod";
    const char* nmodl_file_text = 
  ": Calcium activated K channel.\n"
  ": From Moczydlowski and Latorre (1983) J. Gen. Physiol. 82\n"
  ": Model 3. (Scheme R1 page 523)\n"
  "\n"
  "UNITS {\n"
  "	(molar) = (1/liter)\n"
  "	(mV) =	(millivolt)\n"
  "	(mA) =	(milliamp)\n"
  "	(mM) =	(millimolar)\n"
  "	FARADAY = (faraday)  (kilocoulombs)\n"
  "	R = (k-mole) (joule/degC)\n"
  "}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX bkkca\n"
  "	USEION ca READ cai\n"
  "	USEION k READ ek WRITE ik\n"
  "	RANGE gkbar, ik, qfact, abar, bbar, stau\n"
  "	GLOBAL oinf, tau\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	stau = 1\n"
  "	qfact = 1\n"
  "	celsius	(degC) : 35\n"
  "	v		(mV)\n"
  "	gkbar=0.001	(mho/cm2)	: Maximum Permeability\n"
  "	cai		(mM) \n"
  "	ek		(mV)\n"
  "\n"
  "	d1 = .84	      :page 527 Table II channel A\n"
  "	d2 = 1.0			:our index 2 is the paper's subscript 4\n"
  "	k1 = .18	(mM)\n"
  "	k2 = .011	(mM)\n"
  "	abar = .48	(/ms)\n"
  "	bbar = .28	(/ms) :page 524. our bbar is the paper's alpha\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	ik		(mA/cm2)\n"
  "	oinf\n"
  "	tau		(ms)\n"
  "}\n"
  "\n"
  "STATE {	o }		: fraction of open channels\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE state METHOD cnexp\n"
  "	ik = gkbar * o * (v - ek)\n"
  "}\n"
  "\n"
  "DERIVATIVE state {\n"
  "	rate(v, cai)\n"
  "	o' = (oinf - o) / (tau/qfact)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	rate(v, cai)\n"
  "	o = oinf\n"
  ":	VERBATIM\n"
  ":		printf(\"R = %f\\n\",R);\n"
  ":		printf(\"F = %f\\n\",FARADAY);\n"
  ":	ENDVERBATIM\n"
  "}\n"
  "\n"
  ": From R1 page 523. beta in the paper is the rate from closed to open\n"
  ": and we call it alp here.\n"
  "\n"
  "\n"
  "FUNCTION alp(v (mV), ca (mM)) (1/ms) { :callable from hoc\n"
  "	alp = abar/(1 + exp1(k1,d1,v)/ca)\n"
  "}\n"
  "\n"
  "FUNCTION bet(v (mV), ca (mM)) (1/ms) { :callable from hoc\n"
  "	bet = bbar/(1 + ca/exp1(k2,d2,v))\n"
  "}\n"
  "\n"
  "FUNCTION exp1(k (mM), d, v (mV)) (mM) { :callable from hoc\n"
  "	exp1 = k * exp( - 2 * d * FARADAY * v / R / (273.15 + celsius))\n"
  "}\n"
  "\n"
  "PROCEDURE rate(v (mV), ca (mM)) { \n"
  "	:callable from hoc\n"
  "	LOCAL a\n"
  "	a = alp(v,ca)\n"
  "	tau = stau / (a + bet(v, ca))\n"
  "	oinf = a * tau\n"
  "}\n"
  "\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
