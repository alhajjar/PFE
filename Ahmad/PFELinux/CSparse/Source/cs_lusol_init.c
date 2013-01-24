#include "cs.h"
/* x=A\b where A is unsymmetric; b overwritten with solution */
csn *cs_lusol_init (csi order, const cs *A, double *b, double tol, double *x)
{
	//double *x;
    csi n;
    csn *N;
    css *S;

    n = A->n ;
    S = cs_sqr (order, A, 0) ;              /* ordering and symbolic analysis */
    N = cs_lu (A, S, tol) ;                 /* numeric LU factorization */
   // x = cs_malloc (n, sizeof (double)) ;    /* get workspace */

        cs_ipvec (N->pinv, b, x, n) ;       /* x = b(p) */
        cs_lsolve (N->L, x) ;               /* x = L\x */
        cs_usolve (N->U, x) ;               /* x = U\x */
        cs_ipvec (S->q, x, b, n) ;          /* b(q) = x */
    	//N->q=S->q;
//	cs_free(x);
    return N ;
}
