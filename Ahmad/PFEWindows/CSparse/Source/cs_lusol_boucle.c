#include "cs.h"
/* x=A\b where A is unsymmetric; b overwritten with solution */
csi cs_lusol_boucle (const cs *A, double *b, csn *N, double *x)
{
	
    csi n;

    n = A->n ;
        /* get workspace */
   
        cs_ipvec (N->pinv, b, x, n) ;       /* x = b(p) */
        cs_lsolve (N->L, x) ;               /* x = L\x */
        cs_usolve (N->U, x) ;               /* x = U\x */
        cs_ipvec (N->q, x, b, n) ;          /* b(q) = x */
    
	
    return (1) ;
}
