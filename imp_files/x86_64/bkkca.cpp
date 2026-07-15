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
static constexpr auto number_of_floating_point_variables = 18;
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
#define kin kin__bkkca 
#define rates rates__bkkca 
 
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
#define gkbar _ml->template fpfield<0>(_iml)
#define gkbar_columnindex 0
#define ik _ml->template fpfield<1>(_iml)
#define ik_columnindex 1
#define cst _ml->template fpfield<2>(_iml)
#define cst_columnindex 2
#define ost _ml->template fpfield<3>(_iml)
#define ost_columnindex 3
#define ist _ml->template fpfield<4>(_iml)
#define ist_columnindex 4
#define ek _ml->template fpfield<5>(_iml)
#define ek_columnindex 5
#define cai _ml->template fpfield<6>(_iml)
#define cai_columnindex 6
#define k1 _ml->template fpfield<7>(_iml)
#define k1_columnindex 7
#define k2 _ml->template fpfield<8>(_iml)
#define k2_columnindex 8
#define k3 _ml->template fpfield<9>(_iml)
#define k3_columnindex 9
#define k4 _ml->template fpfield<10>(_iml)
#define k4_columnindex 10
#define q10 _ml->template fpfield<11>(_iml)
#define q10_columnindex 11
#define g _ml->template fpfield<12>(_iml)
#define g_columnindex 12
#define Dcst _ml->template fpfield<13>(_iml)
#define Dcst_columnindex 13
#define Dost _ml->template fpfield<14>(_iml)
#define Dost_columnindex 14
#define Dist _ml->template fpfield<15>(_iml)
#define Dist_columnindex 15
#define v _ml->template fpfield<16>(_iml)
#define v_columnindex 16
#define _g _ml->template fpfield<17>(_iml)
#define _g_columnindex 17
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
 static void _hoc_alpha(void);
 static void _hoc_alp(void);
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
 {"setdata_bkkca", _hoc_setdata},
 {"alpha_bkkca", _hoc_alpha},
 {"alp_bkkca", _hoc_alp},
 {"rates_bkkca", _hoc_rates},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_alpha(Prop*);
 static double _npy_alp(Prop*);
 static double _npy_rates(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"alpha", _npy_alpha},
 {"alp", _npy_alp},
 {"rates", _npy_rates},
 {0, 0}
};
#define alpha alpha_bkkca
#define alp alp_bkkca
 extern double alpha( _internalthreadargsprotocomma_ double , double , double , double , double );
 extern double alp( _internalthreadargsprotocomma_ double , double , double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"gkbar_bkkca", "S/cm2"},
 {"ik_bkkca", "mA/cm2"},
 {0, 0}
};
 static double cst0 = 0;
 static double delta_t = 0.01;
 static double ist0 = 0;
 static double ost0 = 0;
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
 
#define _cvode_ieq _ppvar[5].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"bkkca",
 "gkbar_bkkca",
 0,
 "ik_bkkca",
 0,
 "cst_bkkca",
 "ost_bkkca",
 "ist_bkkca",
 0,
 0};
 static Symbol* _ca_sym;
 static Symbol* _k_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0.001, /* gkbar */
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
    assert(_nrn_mechanism_get_num_vars(_prop) == 18);
 	/*initialize range parameters*/
 	gkbar = _parm_default[0]; /* 0.001 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 18);
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
 static void _thread_cleanup(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _bkkca_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	ion_reg("k", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 3);
  _extcall_thread.resize(2);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"gkbar"} /* 0 */,
                                       _nrn_mechanism_field<double>{"ik"} /* 1 */,
                                       _nrn_mechanism_field<double>{"cst"} /* 2 */,
                                       _nrn_mechanism_field<double>{"ost"} /* 3 */,
                                       _nrn_mechanism_field<double>{"ist"} /* 4 */,
                                       _nrn_mechanism_field<double>{"ek"} /* 5 */,
                                       _nrn_mechanism_field<double>{"cai"} /* 6 */,
                                       _nrn_mechanism_field<double>{"k1"} /* 7 */,
                                       _nrn_mechanism_field<double>{"k2"} /* 8 */,
                                       _nrn_mechanism_field<double>{"k3"} /* 9 */,
                                       _nrn_mechanism_field<double>{"k4"} /* 10 */,
                                       _nrn_mechanism_field<double>{"q10"} /* 11 */,
                                       _nrn_mechanism_field<double>{"g"} /* 12 */,
                                       _nrn_mechanism_field<double>{"Dcst"} /* 13 */,
                                       _nrn_mechanism_field<double>{"Dost"} /* 14 */,
                                       _nrn_mechanism_field<double>{"Dist"} /* 15 */,
                                       _nrn_mechanism_field<double>{"v"} /* 16 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 17 */,
                                       _nrn_mechanism_field<double*>{"_ion_cai", "ca_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_cao", "ca_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_ek", "k_ion"} /* 2 */,
                                       _nrn_mechanism_field<double*>{"_ion_ik", "k_ion"} /* 3 */,
                                       _nrn_mechanism_field<double*>{"_ion_dikdv", "k_ion"} /* 4 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 5 */);
  hoc_register_prop_size(_mechtype, 18, 6);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 bkkca /home/amajnas/wolf_model/imp_files/bkkca.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 0x1.81f0fae775425p+6;
 static double R = 0x1.0a1013e8990bep+3;
static int _reset;
static const char *modelname = "Large-Conductance Calcium-Activated Potassium Channel (BK)";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_internalthreadargsprotocomma_ double);
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(static_cast<SparseObj*>(_so), _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 1;
 static int _cvspth1 = 0;
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[3], _dlist1[3]; static double *_temp1;
 static int kin (void* _so, double* _rhs, _internalthreadargsproto_);
 
static int kin (void* _so, double* _rhs, _internalthreadargsproto_)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<3;_i++){
  	_RHS1(_i) = -_dt1*(_ml->data(_iml, _slist1[_i]) - _ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
} }
 rates ( _threadargscomma_ v ) ;
   /* ~ cst <-> ost ( k3 , k4 )*/
 f_flux =  k3 * cst ;
 b_flux =  k4 * ost ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  k3 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  k4 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ ost <-> ist ( k1 , 0.0 )*/
 f_flux =  k1 * ost ;
 b_flux =  0.0 * ist ;
 _RHS1( 2) -= (f_flux - b_flux);
 
 _term =  k1 ;
 _MATELM1( 2 ,2)  += _term;
 _term =  0.0 ;
 _MATELM1( 2 ,0)  -= _term;
 /*REACTION*/
  /* ~ ist <-> cst ( k2 , 0.0 )*/
 f_flux =  k2 * ist ;
 b_flux =  0.0 * cst ;
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  k2 ;
 _MATELM1( 1 ,0)  -= _term;
 _term =  0.0 ;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* cst + ost + ist = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= ist ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= ost ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= cst ;
 /*CONSERVATION*/
   } return _reset;
 }
 
static int  rates ( _internalthreadargsprotocomma_ double _lv ) {
   double _lca_safe ;
 _lca_safe = cai ;
   if ( _lca_safe < 0.0 ) {
     _lca_safe = 0.0 ;
     }
   k1 = alp ( _threadargscomma_ 0.1 , _lv , - 10.0 , 1.0 ) ;
   k2 = alp ( _threadargscomma_ 0.1 , _lv , - 120.0 , - 10.0 ) ;
   k3 = alpha ( _threadargscomma_ 0.001 , 1.0 , _lv , - 20.0 , 7.0 ) * 1.0e8 * pow ( _lca_safe * 1.0 , 3.0 ) ;
   k4 = alp ( _threadargscomma_ 0.01 , _lv , - 44.0 , - 5.0 ) ;
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
 
double alpha ( _internalthreadargsprotocomma_ double _ltmin , double _ltmax , double _lv , double _lvhalf , double _lk ) {
   double _lalpha;
 _lalpha = 1.0 / ( _ltmin + 1.0 / ( 1.0 / ( _ltmax - _ltmin ) + exp ( ( _lv - _lvhalf ) / _lk ) * 1.0 ) ) ;
   
return _lalpha;
 }
 
static void _hoc_alpha(void) {
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
 _r =  alpha ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) );
 hoc_retpushx(_r);
}
 
static double _npy_alpha(Prop* _prop) {
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
 _r =  alpha ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) );
 return(_r);
}
 
double alp ( _internalthreadargsprotocomma_ double _ltmin , double _lv , double _lvhalf , double _lk ) {
   double _lalp;
 _lalp = 1.0 / ( _ltmin + exp ( ( _lv - _lvhalf ) / _lk ) * 1.0 ) ;
   
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
 _r =  alp ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
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
 _r =  alp ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 return(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec1(_internalthreadargsproto_) {
  int _reset=0;
  {
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<3;_i++) _ml->data(_iml, _dlist1[_i]) = 0.0;}
 rates ( _threadargscomma_ v ) ;
 /* ~ cst <-> ost ( k3 , k4 )*/
 f_flux =  k3 * cst ;
 b_flux =  k4 * ost ;
 Dcst -= (f_flux - b_flux);
 Dost += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ost <-> ist ( k1 , 0.0 )*/
 f_flux =  k1 * ost ;
 b_flux =  0.0 * ist ;
 Dost -= (f_flux - b_flux);
 Dist += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ist <-> cst ( k2 , 0.0 )*/
 f_flux =  k2 * ist ;
 b_flux =  0.0 * cst ;
 Dist -= (f_flux - b_flux);
 Dcst += (f_flux - b_flux);
 
 /*REACTION*/
   /* cst + ost + ist = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, _internalthreadargsproto_) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<3;_i++){
  	_RHS1(_i) = _dt1*(_ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
} }
 rates ( _threadargscomma_ v ) ;
 /* ~ cst <-> ost ( k3 , k4 )*/
 _term =  k3 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  k4 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ ost <-> ist ( k1 , 0.0 )*/
 _term =  k1 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 0 ,2)  -= _term;
 _term =  0.0 ;
 _MATELM1( 2 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ ist <-> cst ( k2 , 0.0 )*/
 _term =  k2 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 1 ,0)  -= _term;
 _term =  0.0 ;
 _MATELM1( 0 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* cst + ost + ist = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 3;}
 
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
  for (int _i=0; _i < 3; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _cvode_sparse_thread(&(_thread[_cvspth1].literal_value<void*>()), 3, _dlist1, neuron::scopmath::row_view{_ml, _iml}, _ode_matsol1, _threadargs_);
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
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_cvspth1].get<void*>()));
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_spth1].get<void*>()));
 }

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  cst = cst0;
  ist = ist0;
  ost = ost0;
 {
    _ss_sparse_thread(&(_thread[_spth1].literal_value<void*>()), 3, _slist1, _dlist1, neuron::scopmath::row_view{_ml, _iml}, &t, dt, kin, _linmat1, _threadargs_);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 3; ++_i) {
      _ml->data(_iml, _slist1[_i]) += dt*_ml->data(_iml, _dlist1[_i]);
    }}
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
   g = gkbar * ost ;
   ik = g * ( v - ek ) ;
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
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
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
 {  sparse_thread(&(_thread[_spth1].literal_value<void*>()), 3, _slist1, _dlist1, neuron::scopmath::row_view{_ml, _iml}, &t, dt, kin, _linmat1, _threadargs_);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 3; ++_i) {
      _ml->data(_iml, _slist1[_i]) += dt*_ml->data(_iml, _dlist1[_i]);
    }}
 } }}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {ist_columnindex, 0};  _dlist1[0] = {Dist_columnindex, 0};
 _slist1[1] = {cst_columnindex, 0};  _dlist1[1] = {Dcst_columnindex, 0};
 _slist1[2] = {ost_columnindex, 0};  _dlist1[2] = {Dost_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/amajnas/wolf_model/imp_files/bkkca.mod";
    const char* nmodl_file_text = 
  "TITLE Large-Conductance Calcium-Activated Potassium Channel (BK)\n"
  "\n"
  "COMMENT\n"
  "=============================================================================\n"
  "Biophysical Description:\n"
  "------------------------\n"
  "Implements a large-conductance, calcium-activated potassium channel (BK, Maxi-K,\n"
  "or KCa1.1), which participates in action potential repolarization and shapes the \n"
  "fast afterhyperpolarization (fAHP). BK channels are activated synergistically \n"
  "by both membrane depolarization and intracellular calcium binding.\n"
  "\n"
  "In striatal medium spiny projection neurons (MSNs), BK channels are functionally \n"
  "coupled to calcium influx through N-, P/Q-, and R-type calcium channels. Thus, \n"
  "this mechanism reads from the \"ca\" pool (cai) representing these high-threshold \n"
  "activated VGCCs, as opposed to the L/T-type pool (\"cal\").\n"
  "\n"
  "Kinetic Scheme:\n"
  "---------------\n"
  "To account for the voltage-dependent inactivation observed in certain neuronal BK \n"
  "currents (e.g., when associated with beta2 auxiliary subunits), this model uses \n"
  "a 3-state cyclic Markov kinetic model consisting of Closed (cst), Open (ost), \n"
  "and Inactivated (ist) states:\n"
  "\n"
  "        k3(Ca, V)\n"
  "   Closed [cst] <=========> Open [ost]\n"
  "         ^                  /\n"
  "          \\                /\n"
  "        k2 \\              / k1(V) [Inactivation]\n"
  "            \\            v\n"
  "             Inactivated [ist]\n"
  "\n"
  "State Transitions:\n"
  "1. cst <-> ost: Reversible activation gating.\n"
  "   - The opening rate (k3) is modeled with a voltage-dependent term scaled by the \n"
  "     third power of intracellular calcium concentration (representing cooperative \n"
  "     binding of 3 Ca2+ ions):\n"
  "       k3 = alpha(V) * Ka * [Ca]i^3\n"
  "     where Ka = 1.0e8 mM^-3 ms^-1 (forward calcium association rate constant).\n"
  "   - The closing rate (k4) is purely voltage-dependent.\n"
  "2. ost -> ist: Open-to-Inactivated transition governed by the voltage-dependent rate k1(V).\n"
  "3. ist -> cst: Recovery from inactivation back to the closed state with rate k2(V).\n"
  "\n"
  "Historical & Biophysical Context:\n"
  "---------------------------------\n"
  "While BK channels are classic biophysical targets characterized by Moczydlowski \n"
  "and Latorre (1983), the 3-state cyclic scheme with inactivation implemented here \n"
  "is based on Shao et al. (1999) \"The role of BK-type Ca2+-dependent K+ channels in \n"
  "spike broadening during repetitive firing in rat hippocampal pyramidal cells\" \n"
  "(J. Physiol. 521:135-146). The total conductance of the BK current in this MSN \n"
  "model (gkbar = 0.001 S/cm2) was tuned to regulate action potential width and shape \n"
  "repetitive firing dynamics (Wolf et al. 2005).\n"
  "\n"
  "Transition Rate Constants:\n"
  "--------------------------\n"
  "- Inactivation rates (k1, k2) and deactivation rate (k4) are modeled using a \n"
  "  modified Boltzmann voltage dependence:\n"
  "    k1 = alp(tmin=0.1 ms, V, Vhalf=-10.0 mV, k=1.0 mV)\n"
  "    k2 = alp(tmin=0.1 ms, V, Vhalf=-120.0 mV, k=-10.0 mV)\n"
  "    k4 = alp(tmin=0.01 ms, V, Vhalf=-44.0 mV, k=-5.0 mV)\n"
  "- Activation rate (k3) incorporates voltage-dependent kinetics and cooperative \n"
  "  calcium gating:\n"
  "    k3 = alpha(tmin=0.001 ms, tmax=1.0 ms, V, Vhalf=-20.0 mV, k=7.0 mV) * 1.0e8 * [Ca]i^3\n"
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
  "    SUFFIX bkkca                    : Registers mechanism under suffix 'bkkca'\n"
  "    USEION ca READ cai              : Accesses intracellular calcium concentration (cai) from N/Q/R-type pool\n"
  "    USEION k READ ek WRITE ik       : Reads potassium reversal potential (ek) and writes current density (ik)\n"
  "    RANGE gkbar, ik                 : Range variables: peak conductance and current density\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    gkbar = 1.0e-3 (S/cm2)          : Maximal channel conductance\n"
  "    celsius        (degC)           : Global temperature variable from NEURON\n"
  "    ek             (mV)             : Potassium reversal potential\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    v       (mV)                    : Membrane potential\n"
  "    cai     (mM)                    : Intracellular calcium concentration\n"
  "    ik      (mA/cm2)                : Potassium current density\n"
  "    k1      (/ms)                   : Open -> Inactivated rate constant\n"
  "    k2      (/ms)                   : Inactivated -> Closed rate constant\n"
  "    k3      (/ms)                   : Closed -> Open rate constant (Ca and V dependent)\n"
  "    k4      (/ms)                   : Open -> Closed rate constant (V dependent)\n"
  "    q10     (1)                     : Temperature coefficient placeholder\n"
  "    g       (mho/cm2)               : Dynamic chord conductance\n"
  "}\n"
  "\n"
  "STATE { \n"
  "    cst                             : Closed state fraction\n"
  "    ost                             : Open state fraction\n"
  "    ist                             : Inactivated state fraction\n"
  "}\n"
  "\n"
  "BREAKPOINT { \n"
  "    SOLVE kin METHOD sparse         : Solve the kinetic state equations using sparse matrix methods\n"
  "    g = gkbar * ost\n"
  "    ik = g * (v - ek)               : Ohm's law current calculation\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    SOLVE kin STEADYSTATE sparse    : Compute steady-state initialization for states\n"
  "}\n"
  "\n"
  "KINETIC kin {\n"
  "    rates(v)\n"
  "    ~ cst <-> ost  (k3, k4)          : Closed-Open activation loop\n"
  "    ~ ost <-> ist  (k1, 0.0)         : Open-to-Inactivated transition\n"
  "    ~ ist <-> cst  (k2, 0.0)         : Recovery transition\n"
  "    CONSERVE cst + ost + ist = 1    : Conservation equation: total state occupancy is 1.0\n"
  "}\n"
  "\n"
  "PROCEDURE rates(v (mV)) {\n"
  "    LOCAL ca_safe\n"
  "    ca_safe = cai\n"
  "    if (ca_safe < 0) { ca_safe = 0 } : Numerical safety guard to prevent negative concentration values\n"
  "    \n"
  "    : k1 (Open -> Inactivated): Sigmoidal voltage-dependent inactivation rate constant.\n"
  "    : Channels inactivate rapidly upon depolarization.\n"
  "    k1 = alp(0.1, v, -10.0, 1.0)\n"
  "    \n"
  "    : k2 (Inactivated -> Closed): Sigmoidal voltage-dependent recovery rate constant.\n"
  "    : Recovery from inactivation is favored at hyperpolarized potentials.\n"
  "    k2 = alp(0.1, v, -120.0, -10.0)\n"
  "    \n"
  "    : k3 (Closed -> Open): Activation rate constant.\n"
  "    : Combines a sigmoidal voltage-dependence term alpha(v) with a third-order cooperative \n"
  "    : calcium binding term (cai^3).\n"
  "    : 1.0e8 (mM^-3 ms^-1) is the forward rate constant for calcium binding.\n"
  "    k3 = alpha(0.001, 1.0, v, -20.0, 7.0) * 1.0e8 * pow(ca_safe * 1.0(/mM), 3)\n"
  "    \n"
  "    : k4 (Open -> Closed): Deactivation rate constant.\n"
  "    : Purely voltage-dependent closing rate.\n"
  "    k4 = alp(0.01, v, -44.0, -5.0)\n"
  "}\n"
  "\n"
  ": Gating kinetics scaling function alpha(V)\n"
  ": Computes a sigmoidal transition rate with a defined minimum (1/tmax) and maximum (1/tmin) rate limit.\n"
  ": Mathematical form: 1 / (tmin + 1 / ( (tmax - tmin)^-1 + exp((v - vhalf)/k) ))\n"
  "FUNCTION alpha(tmin(ms), tmax(ms), v(mV), vhalf(mV), k(mV))(/ms) {\n"
  "    alpha = 1.0 / (tmin + 1.0 / (1.0 / (tmax - tmin) + exp((v - vhalf) / k) * 1.0(/ms)))\n"
  "}\n"
  "\n"
  ": Sigmoidal rate transition function alp(V)\n"
  ": Computes a rate constant that decreases sigmoidally with voltage (for k < 0, e.g. k2, k4) \n"
  ": or increases sigmoidally (for k > 0, e.g. k1).\n"
  ": Mathematical form: 1 / (tmin + exp((v - vhalf)/k) * 1(ms))\n"
  "FUNCTION alp(tmin(ms), v(mV), vhalf(mV), k(mV))(/ms) {\n"
  "    alp = 1.0 / (tmin + exp((v - vhalf) / k) * 1.0(ms))\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
