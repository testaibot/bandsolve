#include <Rcpp.h>
using namespace Rcpp;

//' @title Fast solver for linears systems involving symmetric band matrix.
//' @param D0data Diagonal as a vector of length n.
//' @param D1Data First subdiagonal and superdiagonal as a vector of length n-1.
//' @param D2Data Second subdiagonal and superdiagonal as a vector of length n-2.
//' @param bdata Right hand side of the linear system
//' @return Solution of the linear system.
//' @examples n=2000;
//' D0=runif(n);
//' D1=-0.2*runif(n-1);
//' D2=0.4*runif(n-2);
//' b=runif(n)
//' ref=bandsolve2(D0,D1,D2,b)
//'  @export
// [[Rcpp::export]]
NumericVector bandsolve2(NumericVector D0data, NumericVector D1data, NumericVector D2data, NumericVector bdata) {
    if (D0data.size()!=(D2data.size()+2))
    Rcpp::stop("we must have length(D0)=length(D2)+2");
    if (D0data.size()!=(D1data.size()+1))
    Rcpp::stop("we must have length(D0)=length(D1)+1");
    if (D0data.size()!=bdata.size())
    Rcpp::stop("we must have length(D0)=length(b)");
    
    Rcpp::NumericVector D0(D0data);
    Rcpp::NumericVector D1(D1data);
    Rcpp::NumericVector D2(D2data);
    Rcpp::NumericVector b(bdata);
    int n = D0.size();
    Rcpp::NumericVector L1(n-1);
    Rcpp::NumericVector L2(n-2);
    Rcpp::NumericVector U0(n);
    Rcpp::NumericVector U1(n-1);
    Rcpp::NumericVector x(n);
    Rcpp::NumericVector y(n);
    // initialization
    for (int i=0; i<n; i++) U0[i]=D0[i];
    for (int i=0; i<(n-1); i++) U1[i]=D1[i];
    for (int i=0; i<(n-1); i++) L1[i]=D1[i];
    for (int i=0; i<(n-2); i++) L2[i]=D2[i];
    
    // LU decomposition
    for (int i=1; i<n; i++) {
  // process row i
      L1[i-1]=L1[i-1]/U0[i-1];
      U0[i]=U0[i]-L1[i-1]*U1[i-1];
      if (i<n-1) {
        // process row i+1
        L2[i-1]=L2[i-1]/U0[i-1];
        L1[i]=L1[i]-L2[i-1]*U1[i-1];
        U0[i+1]=U0[i+1]-L2[i-1]*D2[i-1];
        U1[i]=U1[i]-L1[i-1]*D2[i-1];
      }
    }

    // solve y=inv(L)b
    y[0]=b[0];
    y[1]=b[1]-L1[0]*y[0];
    
    for (int i=2; i<n; i++) 
      y[i]=b[i]-L1[i-1]*y[i-1]-L2[i-2]*y[i-2];
      
    // solve x=inv(U)y=inv(LU)b
    x[n-1]=y[n-1]/U0[n-1];
    x[n-2]=(y[n-2]-U1[n-2]*x[n-1])/U0[n-2];
    for (int i=(n-3); i>=0; i--)
      x[i]=(y[i]-U1[i]*x[i+1]-D2[i]*x[i+2])/U0[i];
    return(x);
}