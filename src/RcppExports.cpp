// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// bandsolve_cpp
List bandsolve_cpp(NumericMatrix D, NumericMatrix B);
RcppExport SEXP bandsolve_bandsolve_cpp(SEXP DSEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type D(DSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type B(BSEXP);
    rcpp_result_gen = Rcpp::wrap(bandsolve_cpp(D, B));
    return rcpp_result_gen;
END_RCPP
}
// LDL
List LDL(NumericMatrix D);
RcppExport SEXP bandsolve_LDL(SEXP DSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type D(DSEXP);
    rcpp_result_gen = Rcpp::wrap(LDL(D));
    return rcpp_result_gen;
END_RCPP
}
