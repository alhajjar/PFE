#include "cs.h"
/* add 2 vectors retourne valeur dans b */
csi cs_add_vec ( double *a,double *b,double *d,double val)
{
	

	for (int i=0;i<38024;i++)
	a[i] = b[i]+d[i]*val;
       
    
	
    return (1) ;
}
