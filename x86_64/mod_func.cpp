#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern "C" void _AMPA_reg(void);
extern "C" void _CaL12_reg(void);
extern "C" void _CaL13_reg(void);
extern "C" void _CaN_reg(void);
extern "C" void _CaQ_reg(void);
extern "C" void _CaR_reg(void);
extern "C" void _CaT_reg(void);
extern "C" void _GABA_reg(void);
extern "C" void _KAf_reg(void);
extern "C" void _KAs_reg(void);
extern "C" void _Kir_reg(void);
extern "C" void _Krp_reg(void);
extern "C" void _NMDA_reg(void);
extern "C" void _NaF_reg(void);
extern "C" void _NaP_reg(void);
extern "C" void _bkkca_reg(void);
extern "C" void _cadyn_lt_reg(void);
extern "C" void _cadyn_nqr_reg(void);
extern "C" void _skkca_reg(void);

extern "C" void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"imp_files/AMPA.mod\"");
    fprintf(stderr, " \"imp_files/CaL12.mod\"");
    fprintf(stderr, " \"imp_files/CaL13.mod\"");
    fprintf(stderr, " \"imp_files/CaN.mod\"");
    fprintf(stderr, " \"imp_files/CaQ.mod\"");
    fprintf(stderr, " \"imp_files/CaR.mod\"");
    fprintf(stderr, " \"imp_files/CaT.mod\"");
    fprintf(stderr, " \"imp_files/GABA.mod\"");
    fprintf(stderr, " \"imp_files/KAf.mod\"");
    fprintf(stderr, " \"imp_files/KAs.mod\"");
    fprintf(stderr, " \"imp_files/Kir.mod\"");
    fprintf(stderr, " \"imp_files/Krp.mod\"");
    fprintf(stderr, " \"imp_files/NMDA.mod\"");
    fprintf(stderr, " \"imp_files/NaF.mod\"");
    fprintf(stderr, " \"imp_files/NaP.mod\"");
    fprintf(stderr, " \"imp_files/bkkca.mod\"");
    fprintf(stderr, " \"imp_files/cadyn_lt.mod\"");
    fprintf(stderr, " \"imp_files/cadyn_nqr.mod\"");
    fprintf(stderr, " \"imp_files/skkca.mod\"");
    fprintf(stderr, "\n");
  }
  _AMPA_reg();
  _CaL12_reg();
  _CaL13_reg();
  _CaN_reg();
  _CaQ_reg();
  _CaR_reg();
  _CaT_reg();
  _GABA_reg();
  _KAf_reg();
  _KAs_reg();
  _Kir_reg();
  _Krp_reg();
  _NMDA_reg();
  _NaF_reg();
  _NaP_reg();
  _bkkca_reg();
  _cadyn_lt_reg();
  _cadyn_nqr_reg();
  _skkca_reg();
}
