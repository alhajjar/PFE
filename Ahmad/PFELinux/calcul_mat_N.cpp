////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    calcul_mat_N.cpp                            //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include "Includes/calcul_mat_N.hpp"

cs* matricen (int h , int k ,  Matrice d , Matrice alpha1 , Matrice v){

    cs *A;
    cs *T;
    int n = d.rows()*d.cols();
    int i = 0;
    double vec3[n];
    double vec2[n];


/* Allocation en memoire de la matrice tridiagonale temporaire */
     T = cs_spalloc (0, 0, 1, 1, 1) ;
     int f = 0;

//je cree la matrice tridiagonal
	 for(int i=0;i!=d.rows();i++){
		 for(int j=0;j!=d.cols();j++){

		    cs_entry (T, f, f,  ((1 - h + h*alpha1(i,j)) + (2 * h /(k*k) *d(i,j)))) ;//diag
		    vec2[f]  =  ((-h/k)*(d(i,j)/k + v(i,j)/2) ) ;//diag inf
		    vec3[f]  =  ((-h/k)*(d(i,j)/k - v(i,j)/2) ) ;//diag sup

		    	f++;
		    }
	   }

	for( i = 0; i!=n-1;i++){

		cs_entry (T, i+1, i,vec2[i]);//diaginf
		cs_entry (T,  i, i+1,vec3[i]);//diagsup
	}

/* Compression en memoire et remplissage de la matrice creuse */
	A = cs_compress(T);

/* Liberation de l'espace memoire T */
	cs_spfree(T);

 return A;
}


Vecteur calculmatriceN2N4 (int h , Matrice r , Matrice alpha2 ){
       Vecteur  N2(38024);
       N2 = Vecteur::Zero(38024);

   int f = 0;

   for(int i=0;i!=r.rows();i++){
        for(int j=0;j!=r.cols();j++){
            N2(f) = 1/(1 - h * (r(i,j)- alpha2(i,j)));
            f++;
        }
    }

 return N2;
}

