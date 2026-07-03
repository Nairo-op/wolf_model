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
extern "C" void _cadyn_reg(void);
extern "C" void _skkca_reg(void);

extern "C" void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"AMPA.mod\"");
    fprintf(stderr, " \"CaL12.mod\"");
    fprintf(stderr, " \"CaL13.mod\"");
    fprintf(stderr, " \"CaN.mod\"");
    fprintf(stderr, " \"CaQ.mod\"");
    fprintf(stderr, " \"CaR.mod\"");
    fprintf(stderr, " \"CaT.mod\"");
    fprintf(stderr, " \"GABA.mod\"");
    fprintf(stderr, " \"KAf.mod\"");
    fprintf(stderr, " \"KAs.mod\"");
    fprintf(stderr, " \"Kir.mod\"");
    fprintf(stderr, " \"Krp.mod\"");
    fprintf(stderr, " \"NMDA.mod\"");
    fprintf(stderr, " \"NaF.mod\"");
    fprintf(stderr, " \"NaP.mod\"");
    fprintf(stderr, " \"bkkca.mod\"");
    fprintf(stderr, " \"cadyn.mod\"");
    fprintf(stderr, " \"skkca.mod\"");
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
  _cadyn_reg();
  _skkca_reg();
}
