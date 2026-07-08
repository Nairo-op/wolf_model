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
static constexpr auto number_of_floating_point_variables = 15;
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
 
#define nrn_init _nrn_init__cat
#define _nrn_initial _nrn_initial__cat
#define nrn_cur _nrn_cur__cat
#define _nrn_current _nrn_current__cat
#define nrn_jacob _nrn_jacob__cat
#define nrn_state _nrn_state__cat
#define _net_receive _net_receive__cat 
#define rates rates__cat 
#define states states__cat 
 
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
#define pbar _ml->template fpfield<0>(_iml)
#define pbar_columnindex 0
#define m _ml->template fpfield<1>(_iml)
#define m_columnindex 1
#define h _ml->template fpfield<2>(_iml)
#define h_columnindex 2
#define ecal _ml->template fpfield<3>(_iml)
#define ecal_columnindex 3
#define ical _ml->template fpfield<4>(_iml)
#define ical_columnindex 4
#define cali _ml->template fpfield<5>(_iml)
#define cali_columnindex 5
#define calo _ml->template fpfield<6>(_iml)
#define calo_columnindex 6
#define minf _ml->template fpfield<7>(_iml)
#define minf_columnindex 7
#define mtau _ml->template fpfield<8>(_iml)
#define mtau_columnindex 8
#define hinf _ml->template fpfield<9>(_iml)
#define hinf_columnindex 9
#define htau _ml->template fpfield<10>(_iml)
#define htau_columnindex 10
#define Dm _ml->template fpfield<11>(_iml)
#define Dm_columnindex 11
#define Dh _ml->template fpfield<12>(_iml)
#define Dh_columnindex 12
#define v _ml->template fpfield<13>(_iml)
#define v_columnindex 13
#define _g _ml->template fpfield<14>(_iml)
#define _g_columnindex 14
#define _ion_ecal *(_ml->dptr_field<0>(_iml))
#define _p_ion_ecal static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_cali *(_ml->dptr_field<1>(_iml))
#define _p_ion_cali static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_calo *(_ml->dptr_field<2>(_iml))
#define _p_ion_calo static_cast<neuron::container::data_handle<double>>(_ppvar[2])
#define _ion_ical *(_ml->dptr_field<3>(_iml))
#define _p_ion_ical static_cast<neuron::container::data_handle<double>>(_ppvar[3])
#define _ion_dicaldv *(_ml->dptr_field<4>(_iml))
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_ghk(void);
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
 {"setdata_cat", _hoc_setdata},
 {"ghk_cat", _hoc_ghk},
 {"rates_cat", _hoc_rates},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_ghk(Prop*);
 static double _npy_rates(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"ghk", _npy_ghk},
 {"rates", _npy_rates},
 {0, 0}
};
#define ghk ghk_cat
 extern double ghk( _internalthreadargsprotocomma_ double , double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define FARADAY FARADAY_cat
 double FARADAY = 96485;
#define R R_cat
 double R = 8.3145;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"FARADAY_cat", "coulomb"},
 {"R_cat", "joule/degC"},
 {"pbar_cat", "cm/s"},
 {0, 0}
};
 static double delta_t = 0.01;
 static double h0 = 0;
 static double m0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"FARADAY_cat", &FARADAY_cat},
 {"R_cat", &R_cat},
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
"cat",
 "pbar_cat",
 0,
 0,
 "m_cat",
 "h_cat",
 0,
 0};
 static Symbol* _cal_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     4e-07, /* pbar */
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
    assert(_nrn_mechanism_get_num_vars(_prop) == 15);
 	/*initialize range parameters*/
 	pbar = _parm_default[0]; /* 4e-07 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 15);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_cal_sym);
 nrn_promote(prop_ion, 1, 1);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 0); /* ecal */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 1); /* cali */
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 2); /* calo */
 	_ppvar[3] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ical */
 	_ppvar[4] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dicaldv */
 
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

 extern "C" void _CaT_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("cal", -10000.);
 	_cal_sym = hoc_lookup("cal_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"pbar"} /* 0 */,
                                       _nrn_mechanism_field<double>{"m"} /* 1 */,
                                       _nrn_mechanism_field<double>{"h"} /* 2 */,
                                       _nrn_mechanism_field<double>{"ecal"} /* 3 */,
                                       _nrn_mechanism_field<double>{"ical"} /* 4 */,
                                       _nrn_mechanism_field<double>{"cali"} /* 5 */,
                                       _nrn_mechanism_field<double>{"calo"} /* 6 */,
                                       _nrn_mechanism_field<double>{"minf"} /* 7 */,
                                       _nrn_mechanism_field<double>{"mtau"} /* 8 */,
                                       _nrn_mechanism_field<double>{"hinf"} /* 9 */,
                                       _nrn_mechanism_field<double>{"htau"} /* 10 */,
                                       _nrn_mechanism_field<double>{"Dm"} /* 11 */,
                                       _nrn_mechanism_field<double>{"Dh"} /* 12 */,
                                       _nrn_mechanism_field<double>{"v"} /* 13 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 14 */,
                                       _nrn_mechanism_field<double*>{"_ion_ecal", "cal_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_cali", "cal_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_calo", "cal_ion"} /* 2 */,
                                       _nrn_mechanism_field<double*>{"_ion_ical", "cal_ion"} /* 3 */,
                                       _nrn_mechanism_field<double*>{"_ion_dicaldv", "cal_ion"} /* 4 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 5 */);
  hoc_register_prop_size(_mechtype, 15, 6);
  hoc_register_dparam_semantics(_mechtype, 0, "cal_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "cal_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cal_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cal_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cal_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cat /home/amajnas/wolf_model/CaT.mod\n");
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
 minf = 1.0 / ( 1.0 + exp ( - ( _lv + ( 51.73 ) ) / 6.53 ) ) ;
   hinf = 1.0 / ( 1.0 + exp ( ( _lv + ( 80.0 ) ) / 6.7 ) ) ;
   if ( _lv <= - 65.0 ) {
     mtau = 6.73 ;
     htau = 127.33 ;
     }
   else if ( _lv >= 10.0 ) {
     mtau = 1.1 ;
     htau = 36.67 ;
     }
   else {
     _lv_idx = floor ( ( _lv - ( - 65.0 ) ) / 5.0 ) ;
     _lfraction = ( ( _lv - ( - 65.0 ) ) / 5.0 ) - _lv_idx ;
     if ( _lv_idx  == 0.0 ) {
       mtau = 6.73 + _lfraction * ( 6.73 - 6.73 ) ;
       htau = 127.33 + _lfraction * ( 69.33 - 127.33 ) ;
       }
     else if ( _lv_idx  == 1.0 ) {
       mtau = 6.73 + _lfraction * ( 4.37 - 6.73 ) ;
       htau = 69.33 + _lfraction * ( 54.0 - 69.33 ) ;
       }
     else if ( _lv_idx  == 2.0 ) {
       mtau = 4.37 + _lfraction * ( 2.9 - 4.37 ) ;
       htau = 54.0 + _lfraction * ( 43.0 - 54.0 ) ;
       }
     else if ( _lv_idx  == 3.0 ) {
       mtau = 2.9 + _lfraction * ( 2.27 - 2.9 ) ;
       htau = 43.0 + _lfraction * ( 39.67 - 43.0 ) ;
       }
     else if ( _lv_idx  == 4.0 ) {
       mtau = 2.27 + _lfraction * ( 1.87 - 2.27 ) ;
       htau = 39.67 + _lfraction * ( 35.67 - 39.67 ) ;
       }
     else if ( _lv_idx  == 5.0 ) {
       mtau = 1.87 + _lfraction * ( 1.47 - 1.87 ) ;
       htau = 35.67 + _lfraction * ( 35.67 - 35.67 ) ;
       }
     else if ( _lv_idx  == 6.0 ) {
       mtau = 1.47 + _lfraction * ( 1.27 - 1.47 ) ;
       htau = 35.67 + _lfraction * ( 35.67 - 35.67 ) ;
       }
     else if ( _lv_idx  == 7.0 ) {
       mtau = 1.27 + _lfraction * ( 1.2 - 1.27 ) ;
       htau = 35.67 + _lfraction * ( 36.0 - 35.67 ) ;
       }
     else if ( _lv_idx  == 8.0 ) {
       mtau = 1.2 + _lfraction * ( 1.1 - 1.2 ) ;
       htau = 36.0 + _lfraction * ( 36.33 - 36.0 ) ;
       }
     else if ( _lv_idx  == 9.0 ) {
       mtau = 1.1 + _lfraction * ( 1.2 - 1.1 ) ;
       htau = 36.33 + _lfraction * ( 36.33 - 36.33 ) ;
       }
     else if ( _lv_idx  == 10.0 ) {
       mtau = 1.2 + _lfraction * ( 1.2 - 1.2 ) ;
       htau = 36.33 + _lfraction * ( 36.67 - 36.33 ) ;
       }
     else if ( _lv_idx  == 11.0 ) {
       mtau = 1.2 + _lfraction * ( 1.1 - 1.2 ) ;
       htau = 36.67 + _lfraction * ( 36.67 - 36.67 ) ;
       }
     else if ( _lv_idx  == 12.0 ) {
       mtau = 1.1 + _lfraction * ( 1.1 - 1.1 ) ;
       htau = 36.67 + _lfraction * ( 36.67 - 36.67 ) ;
       }
     else if ( _lv_idx  == 13.0 ) {
       mtau = 1.1 + _lfraction * ( 1.1 - 1.1 ) ;
       htau = 36.67 + _lfraction * ( 36.67 - 36.67 ) ;
       }
     else if ( _lv_idx  == 14.0 ) {
       mtau = 1.1 + _lfraction * ( 1.1 - 1.1 ) ;
       htau = 36.67 + _lfraction * ( 36.67 - 36.67 ) ;
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
 
double ghk ( _internalthreadargsprotocomma_ double _lv , double _lci , double _lco ) {
   double _lghk;
 double _lw , _le ;
 _lw = _lv * ( 0.001 ) * 2.0 * FARADAY / ( R * ( celsius + 273.16 ) ) ;
   if ( fabs ( _lw ) > 1e-4 ) {
     _le = _lw / ( exp ( _lw ) - 1.0 ) ;
     }
   else {
     _le = 1.0 - _lw / 2.0 ;
     }
   _lghk = - ( 0.001 ) * 2.0 * FARADAY * ( _lco - _lci * exp ( _lw ) ) * _le ;
   
return _lghk;
 }
 
static void _hoc_ghk(void) {
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
 _r =  ghk ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static double _npy_ghk(Prop* _prop) {
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
 _r =  ghk ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
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
  ecal = _ion_ecal;
  cali = _ion_cali;
  calo = _ion_calo;
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
  ecal = _ion_ecal;
  cali = _ion_cali;
  calo = _ion_calo;
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
  ecal = _ion_ecal;
  cali = _ion_cali;
  calo = _ion_calo;
 initmodel(_threadargs_);
 }
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   ical = pbar * m * m * m * h * ghk ( _threadargscomma_ v , cali , calo ) ;
   }
 _current += ical;

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
  ecal = _ion_ecal;
  cali = _ion_cali;
  calo = _ion_calo;
 auto const _g_local = _nrn_current(_threadargscomma_ _v + .001);
 	{ double _dical;
  _dical = ical;
 _rhs = _nrn_current(_threadargscomma_ _v);
  _ion_dicaldv += (_dical - ical)/.001 ;
 	}
 _g = (_g_local - _rhs)/.001;
  _ion_ical += ical ;
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
  ecal = _ion_ecal;
  cali = _ion_cali;
  calo = _ion_calo;
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
    const char* nmodl_filename = "/home/amajnas/wolf_model/CaT.mod";
    const char* nmodl_file_text = 
  "TITLE \n"
  "\n"
  "NEURON {\n"
  "    SUFFIX cat\n"
  "    USEION cal READ ecal, cali, calo WRITE ical\n"
  "    RANGE pbar, icl, a\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "    (mV) = (millivolt)\n"
  "    (mA) = (milliamp)\n"
  "    (S) = (siemens)\n"
  "    (mM) = (milli/liter)\n"
  "    (molar) = (1/liter)\n"
  "    (cm/s) = (centimeter/second)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    pbar = 4e-7 (cm/s)\n"
  "    FARADAY = 96485 (coulomb)\n"
  "    R = 8.3145 (joule/degC)            \n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    v (mV)\n"
  "    ecal (mV)\n"
  "    ical (mA/cm2)\n"
  "    cali (mM)\n"
  "    calo (mM)\n"
  "    minf\n"
  "    mtau (ms)\n"
  "    hinf\n"
  "    htau (ms)\n"
  "    celsius (degC)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "    m                        \n"
  "    h                     \n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    SOLVE states METHOD cnexp\n"
  "    ical = pbar * m * m * m * h * ghk(v, cali, calo)\n"
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
  "\n"
  "PROCEDURE rates(v (mV)) {\n"
  "    LOCAL v_idx, fraction\n"
  "    \n"
  "    minf = 1 / (1 + exp(- (v + (51.73)) / 6.53))\n"
  "    hinf = 1 / (1 + exp((v + (80.0)) / 6.7))\n"
  "\n"
  "    : --- HARDCODED LINEAR INTERPOLATION FOR CAT (mtau & htau) ---\n"
  "    : Range bounds: -65.0 mV to 10.0 mV, Step size: 5.0 mV\n"
  "    \n"
  "    if (v <= -65.0) {\n"
  "        mtau = 6.73\n"
  "        htau = 127.33\n"
  "    } else if (v >= 10.0) {\n"
  "        mtau = 1.1\n"
  "        htau = 36.67\n"
  "    } else {\n"
  "        : Map voltage to table index (step size is 5 mV, starting at -65 mV)\n"
  "        v_idx = floor((v - (-65.0)) / 5.0)\n"
  "        fraction = ((v - (-65.0)) / 5.0) - v_idx\n"
  "        \n"
  "        : Perform linear interpolation based on index\n"
  "        if (v_idx == 0) { \n"
  "            mtau = 6.73 + fraction * (6.73 - 6.73) \n"
  "            htau = 127.33 + fraction * (69.33 - 127.33)\n"
  "        }\n"
  "        else if (v_idx == 1) { \n"
  "            mtau = 6.73 + fraction * (4.37 - 6.73) \n"
  "            htau = 69.33 + fraction * (54.0 - 69.33)\n"
  "        }\n"
  "        else if (v_idx == 2) { \n"
  "            mtau = 4.37 + fraction * (2.9 - 4.37) \n"
  "            htau = 54.0 + fraction * (43.0 - 54.0)\n"
  "        }\n"
  "        else if (v_idx == 3) { \n"
  "            mtau = 2.9 + fraction * (2.27 - 2.9) \n"
  "            htau = 43.0 + fraction * (39.67 - 43.0)\n"
  "        }\n"
  "        else if (v_idx == 4) { \n"
  "            mtau = 2.27 + fraction * (1.87 - 2.27) \n"
  "            htau = 39.67 + fraction * (35.67 - 39.67)\n"
  "        }\n"
  "        else if (v_idx == 5) { \n"
  "            mtau = 1.87 + fraction * (1.47 - 1.87) \n"
  "            htau = 35.67 + fraction * (35.67 - 35.67)\n"
  "        }\n"
  "        else if (v_idx == 6) { \n"
  "            mtau = 1.47 + fraction * (1.27 - 1.47) \n"
  "            htau = 35.67 + fraction * (35.67 - 35.67)\n"
  "        }\n"
  "        else if (v_idx == 7) { \n"
  "            mtau = 1.27 + fraction * (1.2 - 1.27) \n"
  "            htau = 35.67 + fraction * (36.0 - 35.67)\n"
  "        }\n"
  "        else if (v_idx == 8) { \n"
  "            mtau = 1.2 + fraction * (1.1 - 1.2) \n"
  "            htau = 36.0 + fraction * (36.33 - 36.0)\n"
  "        }\n"
  "        else if (v_idx == 9) { \n"
  "            mtau = 1.1 + fraction * (1.2 - 1.1) \n"
  "            htau = 36.33 + fraction * (36.33 - 36.33)\n"
  "        }\n"
  "        else if (v_idx == 10) { \n"
  "            mtau = 1.2 + fraction * (1.2 - 1.2) \n"
  "            htau = 36.33 + fraction * (36.67 - 36.33)\n"
  "        }\n"
  "        else if (v_idx == 11) { \n"
  "            mtau = 1.2 + fraction * (1.1 - 1.2) \n"
  "            htau = 36.67 + fraction * (36.67 - 36.67)\n"
  "        }\n"
  "        else if (v_idx == 12) { \n"
  "            mtau = 1.1 + fraction * (1.1 - 1.1) \n"
  "            htau = 36.67 + fraction * (36.67 - 36.67)\n"
  "        }\n"
  "        else if (v_idx == 13) { \n"
  "            mtau = 1.1 + fraction * (1.1 - 1.1) \n"
  "            htau = 36.67 + fraction * (36.67 - 36.67)\n"
  "        }\n"
  "        else if (v_idx == 14) { \n"
  "            mtau = 1.1 + fraction * (1.1 - 1.1) \n"
  "            htau = 36.67 + fraction * (36.67 - 36.67)\n"
  "        }\n"
  "    }\n"
  "}\n"
  "\n"
  "FUNCTION ghk(v(mV), ci(mM), co(mM)) (millicoul/cm3) {\n"
  "    LOCAL w, e\n"
  "\n"
  "    w = v * (0.001) * 2 * FARADAY / (R * (celsius + 273.16))\n"
  "\n"
  "    if (fabs(w) > 1e-4) {\n"
  "        e = w / (exp(w) - 1)\n"
  "    } else {\n"
  "        e = 1 - w / 2\n"
  "    }\n"
  "    \n"
  "    ghk = - (0.001) * 2 * FARADAY * (co - ci* exp(w)) * e\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
