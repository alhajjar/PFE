#include "test.h"

double* calcul_N(cs* A,double I[38024]){
 double tol=1e-14;

 cs_lusol(0,A,I,tol);

return I;

}









