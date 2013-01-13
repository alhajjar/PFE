////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    calcul_mat_N.cpp                            //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include "../Includes/calcul_mat_N.hpp"

cs* matricen ( int h , int k ,  Matrice &dd , Matrice &alpha1 , Matrice &v){

    cs *A;
    cs *T;
    int n = 38024;
    int i = 0;
    double vec3[38024];
    double vec2[38024];


/* Allocation en m�moire de la matrice tridiagonale temporaire */
     T = cs_spalloc (0, 0, 1, 1, 1) ;
     int f = 0;

//je cree la matrice tridiagonal
	 for(int i=0;i!=dd.rows();i++){
		 for(int j=0;j!=dd.cols();j++){

		    cs_entry (T, f, f,  ((1 - h + h*alpha1(i,j)) + (2 * h /(k*k) *dd(i,j)))) ;//diag
		    vec2[f]  =  ((-h/k)*(dd(i,j)/k + v(i,j)/2) ) ;//diag inf
		    vec3[f]  =  ((-h/k)*(dd(i,j)/k - v(i,j)/2) ) ;//diag sup

		    	f++;
		    }
	   }

	for( i = 0; i!=n-1;i++){

	cs_entry (T, i+1, i,vec2[i]);//diaginf
	cs_entry (T,  i, i+1,vec3[i]);//diagsup

	}

/* Compression en m�moire et remplissage de la matrice creuse */
	A = cs_compress(T);

/* Liberation de l'espace memoire T */
	cs_spfree(T);

 return A;
}


Vecteur calculmatriceN2N4 (int h , Matrice  &rr , Matrice  &alpha2 ){

   Vecteur N2(38024);
   N2=Vecteur::Zero(38024);
   int f = 0;

   for(int i=0;i!=rr.rows();i++){
        for(int j=0;j!=rr.cols();j++){
            N2(f) = 1/(1 - h * (rr(i,j)- alpha2(i,j)));
            f++;
        }
    }

 return N2;

}

