


#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Generate C function finalizer which prints the string stored in the
// protected field
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void gozer_finalizer(SEXP ptr_) {
  SEXP str_ = R_ExternalPtrProtected(ptr_);
  const char *txt = CHAR(asChar(str_));
  Rprintf("%s\n", txt);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Return a NULL external pointer with a finalizer
// @param destructor_ string or function call only
//
// @return external pointer with a finalizer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP gozer_(SEXP destructor_) {

  SEXP ptr_;
  if (isFunction(destructor_)) {
    ptr_ = PROTECT(R_MakeExternalPtr(NULL, R_NilValue, R_NilValue));
    R_RegisterFinalizer(ptr_, destructor_);
  } else if (isString(destructor_)) {
    ptr_ = PROTECT(R_MakeExternalPtr(NULL, R_NilValue, destructor_));
    R_RegisterCFinalizer(ptr_, gozer_finalizer);
  } else {
    error("Only strings and functions are acceptable as destructors");
  }

  SET_CLASS(ptr_, mkString("gozer"));

  UNPROTECT(1);
  return ptr_;
}
