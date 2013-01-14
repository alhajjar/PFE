#include "csparseinv.hpp"

double* calcul_N(cs* A,double I[38024]){


 cs_lusol(0,A,I,1e-14);

return I;

}









