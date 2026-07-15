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
static constexpr auto number_of_floating_point_variables = 12;
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
 
#define nrn_init _nrn_init__cadyn_nqr
#define _nrn_initial _nrn_initial__cadyn_nqr
#define nrn_cur _nrn_cur__cadyn_nqr
#define _nrn_current _nrn_current__cadyn_nqr
#define nrn_jacob _nrn_jacob__cadyn_nqr
#define nrn_state _nrn_state__cadyn_nqr
#define _net_receive _net_receive__cadyn_nqr 
#define state state__cadyn_nqr 
 
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
#define drive _ml->template fpfield<0>(_iml)
#define drive_columnindex 0
#define cainf _ml->template fpfield<1>(_iml)
#define cainf_columnindex 1
#define taur _ml->template fpfield<2>(_iml)
#define taur_columnindex 2
#define pump _ml->template fpfield<3>(_iml)
#define pump_columnindex 3
#define F _ml->template fpfield<4>(_iml)
#define F_columnindex 4
#define cai _ml->template fpfield<5>(_iml)
#define cai_columnindex 5
#define Dcai _ml->template fpfield<6>(_iml)
#define Dcai_columnindex 6
#define ica _ml->template fpfield<7>(_iml)
#define ica_columnindex 7
#define drive_channel _ml->template fpfield<8>(_iml)
#define drive_channel_columnindex 8
#define drive_pump _ml->template fpfield<9>(_iml)
#define drive_pump_columnindex 9
#define v _ml->template fpfield<10>(_iml)
#define v_columnindex 10
#define _g _ml->template fpfield<11>(_iml)
#define _g_columnindex 11
#define _ion_ica *(_ml->dptr_field<0>(_iml))
#define _p_ion_ica static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_cai *(_ml->dptr_field<1>(_iml))
#define _p_ion_cai static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_cao *(_ml->dptr_field<2>(_iml))
#define _p_ion_cao static_cast<neuron::container::data_handle<double>>(_ppvar[2])
#define _ion_ca_erev *_ml->dptr_field<3>(_iml)
#define _style_ca	*_ppvar[4].get<int*>()
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 /* declaration of user functions */
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
 {"setdata_cadyn_nqr", _hoc_setdata},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {0, 0}
};
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define depth depth_cadyn_nqr
 double depth = 0.1;
#define kd kd_cadyn_nqr
 double kd = 0.0001;
#define kt kt_cadyn_nqr
 double kt = 0.0001;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"depth_cadyn_nqr", "um"},
 {"kt_cadyn_nqr", "mM/ms"},
 {"kd_cadyn_nqr", "mM"},
 {"drive_cadyn_nqr", "1"},
 {"cainf_cadyn_nqr", "mM"},
 {"taur_cadyn_nqr", "ms"},
 {0, 0}
};
 static double cai0 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"depth_cadyn_nqr", &depth_cadyn_nqr},
 {"kt_cadyn_nqr", &kt_cadyn_nqr},
 {"kd_cadyn_nqr", &kd_cadyn_nqr},
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
"cadyn_nqr",
 "drive_cadyn_nqr",
 "cainf_cadyn_nqr",
 "taur_cadyn_nqr",
 "pump_cadyn_nqr",
 "F_cadyn_nqr",
 0,
 0,
 0,
 0};
 static Symbol* _ca_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     10000, /* drive */
     1e-05, /* cainf */
     43, /* taur */
     0.02, /* pump */
     1, /* F */
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
    assert(_nrn_mechanism_get_num_vars(_prop) == 12);
 	/*initialize range parameters*/
 	drive = _parm_default[0]; /* 10000 */
 	cainf = _parm_default[1]; /* 1e-05 */
 	taur = _parm_default[2]; /* 43 */
 	pump = _parm_default[3]; /* 0.02 */
 	F = _parm_default[4]; /* 1 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 12);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ica */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 1); /* cai */
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 2); /* cao */
 	_ppvar[3] = _nrn_mechanism_get_param_handle(prop_ion, 0); // erev ca
 	_ppvar[4] = {neuron::container::do_not_search, &(_nrn_mechanism_access_dparam(prop_ion)[0].literal_value<int>())}; /* iontype for ca */
 
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

 extern "C" void _cadyn_nqr_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"drive"} /* 0 */,
                                       _nrn_mechanism_field<double>{"cainf"} /* 1 */,
                                       _nrn_mechanism_field<double>{"taur"} /* 2 */,
                                       _nrn_mechanism_field<double>{"pump"} /* 3 */,
                                       _nrn_mechanism_field<double>{"F"} /* 4 */,
                                       _nrn_mechanism_field<double>{"cai"} /* 5 */,
                                       _nrn_mechanism_field<double>{"Dcai"} /* 6 */,
                                       _nrn_mechanism_field<double>{"ica"} /* 7 */,
                                       _nrn_mechanism_field<double>{"drive_channel"} /* 8 */,
                                       _nrn_mechanism_field<double>{"drive_pump"} /* 9 */,
                                       _nrn_mechanism_field<double>{"v"} /* 10 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 11 */,
                                       _nrn_mechanism_field<double*>{"_ion_ica", "ca_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_cai", "ca_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_cao", "ca_ion"} /* 2 */,
                                       _nrn_mechanism_field<double*>{"_ion_ca_erev", "ca_ion"} /* 3 */,
                                       _nrn_mechanism_field<int*>{"_style_ca", "#ca_ion"} /* 4 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 5 */);
  hoc_register_prop_size(_mechtype, 12, 6);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "#ca_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "cvodeieq");
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cadyn_nqr /home/amajnas/wolf_model/imp_files/cadyn_nqr.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96489;
static int _reset;
static const char *modelname = "Submembrane Calcium Dynamics for N, P/Q, and R-type Pools (cadyn_nqr)";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[1], _dlist1[1];
 static int state(_internalthreadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (_internalthreadargsproto_) {int _reset = 0; {
   drive_channel = - drive * ica / ( 2.0 * FARADAY * depth * F ) ;
   if ( drive_channel <= 0. ) {
     drive_channel = 0. ;
     }
   drive_pump = - kt * cai / ( cai + kd ) ;
   Dcai = ( drive_channel + pump * drive_pump + ( cainf - cai ) / taur ) ;
   }
 return _reset;
}
 static int _ode_matsol1 (_internalthreadargsproto_) {
 drive_channel = - drive * ica / ( 2.0 * FARADAY * depth * F ) ;
 if ( drive_channel <= 0. ) {
   drive_channel = 0. ;
   }
 drive_pump = - kt * cai / ( cai + kd ) ;
 Dcai = Dcai  / (1. - dt*( ( ( ( ( - 1.0 ) ) ) / taur ) )) ;
  return 0;
}
 /*END CVODE*/
 static int state (_internalthreadargsproto_) { {
   drive_channel = - drive * ica / ( 2.0 * FARADAY * depth * F ) ;
   if ( drive_channel <= 0. ) {
     drive_channel = 0. ;
     }
   drive_pump = - kt * cai / ( cai + kd ) ;
    cai = cai + (1. - exp(dt*(( ( ( ( - 1.0 ) ) ) / taur ))))*(- ( ( drive_channel + ( pump )*( drive_pump ) + ( ( cainf ) ) / taur ) ) / ( ( ( ( ( - 1.0 ) ) ) / taur ) ) - cai) ;
   }
  return 0;
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
  ica = _ion_ica;
  cai = _ion_cai;
  cai = _ion_cai;
     _ode_spec1 (_threadargs_);
  _ion_cai = cai;
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
 	_pv[0] = _p_ion_cai;
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
  ica = _ion_ica;
  cai = _ion_cai;
  cai = _ion_cai;
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
 {
   cai = cainf ;
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
  ica = _ion_ica;
  cai = _ion_cai;
  cai = _ion_cai;
 initmodel(_threadargs_);
  _ion_cai = cai;
  nrn_wrote_conc(_ca_sym, _ion_ca_erev, _ion_cai, _ion_cao, _style_ca);
}
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{
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
  ica = _ion_ica;
  cai = _ion_cai;
  cai = _ion_cai;
 {   state(_threadargs_);
  } {
   }
  _ion_cai = cai;
}}

}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {cai_columnindex, 0};  _dlist1[0] = {Dcai_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/amajnas/wolf_model/imp_files/cadyn_nqr.mod";
    const char* nmodl_file_text = 
  "TITLE Submembrane Calcium Dynamics for N, P/Q, and R-type Pools (cadyn_nqr)\n"
  "\n"
  "COMMENT\n"
  "Models the submembrane calcium concentration (cai) in the pool corresponding to N-type, P/Q-type, \n"
  "and R-type calcium channel currents.\n"
  "- Inward calcium influx: converts ica into concentration change based on the depth of the \n"
  "  submembrane shell (depth = 0.1 um) and spine factor (F = 1).\n"
  "- Outward active extrusion: represented by a Michaelis-Menten ATPase calcium pump (kt = 1e-4 mM/ms, kd = 1e-4 mM).\n"
  "- Passive diffusion/buffering: represented by exponential decay to a baseline concentration (cainf = 1e-5 mM)\n"
  "  with a removal time constant (taur = 43 ms).\n"
  "- Dynamic equation: cai' = drive_channel + pump * drive_pump + (cainf - cai) / taur\n"
  "References:\n"
  "- Destexhe A, Babloyantz A, Sejnowski TJ (1993) Biophys J 65:1538-1552.\n"
  "- Jackson MB, Redman SJ (2003) J Neurosci 23:1612-1621.\n"
  "ENDCOMMENT\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX cadyn_nqr\n"
  "	USEION ca READ ica, cai WRITE cai\n"
  "	RANGE pump, cainf, taur, drive, F\n"
  "}\n"
  "\n"
  "\n"
  "UNITS {\n"
  "	(molar) = (1/liter)	\n"
  "	(mM)	= (millimolar)\n"
  "	(um)	= (micron)\n"
  "	(mA)	= (milliamp)\n"
  "	(msM)	= (ms mM)\n"
  "}\n"
  "\n"
  "CONSTANT {\n"
  "	FARADAY = 96489		(coul)		: moles do not appear in units\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    drive   = 10000  (1)\n"
  "	depth	= 0.1	(um)		: depth of shell\n"
  "	cainf	= 1e-5	(mM)		: gives eca = 108 mV\n"
  "	taur	= 43	(ms)		: \n"
  "	kt	= 1e-4	(mM/ms)			: left over from Destexhe\n"
  "	kd	= 1e-4	(mM)\n"
  "	\n"
  "	pump = 0.02					: turn pump up/down\n"
  "	F = 1 						: spine factor\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	cai		(mM) \n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	cai = cainf\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	ica		(mA/cm2)\n"
  "	drive_channel	(mM/ms)\n"
  "	drive_pump	(mM/ms)\n"
  "}\n"
  "	\n"
  "BREAKPOINT {\n"
  "	SOLVE state METHOD cnexp\n"
  "}\n"
  "\n"
  "DERIVATIVE state { \n"
  "	drive_channel =  - drive * ica / (2 * FARADAY * depth * F)\n"
  "	    : this part converts the incoming calcium (from channels) into\n"
  "	    : a corresponding change in internal concentration\n"
  "\n"
  "	if (drive_channel <= 0.) { drive_channel = 0. }	: cannot pump inward\n"
  "\n"
  "	drive_pump = -kt * cai / (cai + kd )		: Michaelis-Menten\n"
  "	    : this accounts for calcium being pumped back out - M-M\n"
  "	    : represents mechanism that is rate-limited by low ion conc.\n"
  "	    : at one end and max pumping rate at high end\n"
  "	\n"
  "	cai' = ( drive_channel + pump*drive_pump + (cainf-cai)/taur )\n"
  "	    : (cainf-cai)/taur represents exponential decay towards cainf\n"
  "	    : at a time constant of taur from diffusive processe\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "COMMENT\n"
  "Internal calcium concentration due to calcium currents and pump.\n"
  "\n"
  "Differential equations.\n"
  "\n"
  " This file contains two mechanisms:\n"
  " 1. Simple model of ATPase pump with 3 kinetic constants (Destexhe 1992)\n"
  "       Cai + P <-> CaP -> Cao + P  (k1,k2,k3)\n"
  "\n"
  "   A Michaelis-Menten approximation is assumed, which reduces the complexity\n"
  "   of the system to 2 parameters: \n"
  "       kt = <tot enzyme concentration> * k3  -> TIME CONSTANT OF THE PUMP\n"
  "	kd = k2/k1 (dissociation constant)    -> EQUILIBRIUM CALCIUM VALUE\n"
  "   The values of these parameters are chosen assuming a high affinity of \n"
  "   the pump to calcium and a low transport capacity (cfr. Blaustein, \n"
  "   TINS, 11: 438, 1988, and references therein).  \n"
  "\n"
  "   For further information about this this mechanism, see Destexhe, A. \n"
  "   Babloyantz, A. and Sejnowski, TJ.  Ionic mechanisms for intrinsic slow \n"
  "   oscillations in thalamic relay neurons. Biophys. J. 65: 1538-1552, 1993.\n"
  "\n"
  "\n"
  " 2. Simple first-order decay or buffering:\n"
  "\n"
  "       Cai + B <-> ...\n"
  "\n"
  "   which can be written as:\n"
  "\n"
  "       dCai/dt = (cainf - Cai) / taur\n"
  "\n"
  "   where cainf is the equilibrium intracellular calcium value (usually\n"
  "   in the range of 200-300 nM) and taur is the time constant of calcium \n"
  "   removal.\n"
  "\n"
  "All variables are range variables\n"
  "\n"
  "Written by Alain Destexhe, Salk Institute, Nov 12, 1992\n"
  "\n"
  "\n"
  "\n"
  "Citations:\n"
  " \n"
  "Destexhe, A. Babloyantz, A. and Sejnowski, TJ.  Ionic mechanisms for\n"
  "intrinsic slow oscillations in thalamic relay neurons. Biophys. J. 65:\n"
  "1538-1552, 1993.\n"
  "\n"
  "Jackson MB, Redman SJ (2003) Calcium dynamics, buffering, and buffer\n"
  "saturation in the boutons of dentate granule-cell axons in the hilus. J\n"
  "Neurosci 23:1612-1621.\n"
  "\n"
  "ENDCOMMENT\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
