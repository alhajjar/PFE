////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    calcul_mat_N.cpp                            //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include "Includes/calcul_mat_N.hpp"
/** \calcul des matrices N1, N3, N22 et N44
 *  \return retourne les matrices N1, N22, N3 et N44 
 */
cs* matriceN1N3 (int h , int k ,  Matrice d , Matrice alpha1 , Matrice v){
/** \ cette fonction nous cree la matrice creuse tridiagonale N1
*/
/** \on declare deux matrices creuse A et T
*/
    cs *A;
    cs *T;
    int n = d.rows()*d.cols();
    int i = 0;
    double vec3[38024];
    double vec2[38024];

/** \Allocation en memoire de la matrice tridiagonale temporaire 
*/
     T = cs_spalloc (0, 0, 1, 1, 1) ;
     int f = 0;

/** \on cree la matrice tridiagonal
*/
	 for(int i=0;i!=d.rows();i++){
		 for(int j=0;j!=d.cols();j++){

		    cs_entry (T, f, f, (1+h*alpha1(i,j)+(2*h*d(i,j))/(k*k))) ;//diag
		    vec2[f]  = -(h/(k*k))*d(i,j)+(h/(2*k)) *  v(i,j);//diag inf
		    vec3[f]  =  -(h/(k*k))*d(i,j)+(h/(2*k))*  v(i,j);//diag sup

		    	f++;
		    }
	   }

	for( i = 0; i!=n-1;i++){
/** \ on stocke dans T les valeurs de vec2 et vec3
*/
		cs_entry (T, i+1, i,vec2[i]);//diaginf
		cs_entry (T,  i, i+1,vec3[i]);//diagsup
	}

/* Compression en memoire et remplissage de la matrice creuse */
	A = cs_compress(T);

/* Liberation de l'espace memoire T */
	cs_spfree(T);

 return A;
}


Vecteur calculmatriceN22N44 (int h , Matrice r , Matrice alpha2 ){
/** \cette fonction cree la matrice N2 et l'inverse
*/
       Vecteur  N22(38024);
       N22 = Vecteur::Zero(38024);

   int f = 0;

   for(int i=0;i!=r.rows();i++){
        for(int j=0;j!=r.cols();j++){
            N22(f) = 1/(1 + h * (r(i,j))*(1-alpha2(i,j)));
            f++;
        }
    }

 return N22;
}

