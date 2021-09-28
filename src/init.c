
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern SEXP gozer_();

static const R_CallMethodDef CEntries[] = {

  {"gozer_", (DL_FUNC) &gozer_, 1},
  {NULL , NULL, 0}
};


void R_init_gozer(DllInfo *info) {
  R_registerRoutines(
    info,      // DllInfo
    NULL,      // .C
    CEntries,  // .Call
    NULL,      // Fortran
    NULL       // External
  );
  R_useDynamicSymbols(info, FALSE);
}



