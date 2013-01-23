#include "cs.h"
/* x=A\b where A is unsymmetric; b overwritten with solution */
csi cs_lusol_inverse (const cs *A, double *a, double *c, csn *N, double *x)
{
	
    csi n;

    n = A->n ;
        /* get workspace */
   
        cs_ipvec (N->pinv, a, x, n) ;       /* x = a(p) */
        cs_lsolve (N->L, x) ;               /* x = L\x */
        cs_usolve (N->U, x) ;               /* x = U\x */
        cs_ipvec (N->q, x, c, n) ;          /* c(q) = x */
    
	
    return (1) ;
}
