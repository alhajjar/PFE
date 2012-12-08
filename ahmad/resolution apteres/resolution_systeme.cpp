////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    Resolution_systeme.cpp                      //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include"resolution_systeme.hpp"


/*
Matrice Resolution_apteres(int h , Matrice A , Matrice C , Matrice alpha2, MatriceN N){
  MatriceN N11 = MatriceN::Zero(194*196, 194*196);
Vecteur vec1;

    int f =0;
  for(int i=0;i<C.rows();i++){

            for(int j=0;j<C.cols();j++){
               // cout<<C.cols();
               // cout<<k<<"\n";
             vec1(f) = C(i,j) + h* alpha2(i,j)* A(i,j);
                 f++;
            }
    }

  //N11 = N.inverse();

   for(int i=0;i<N.rows();i++){

            for(int j=0;j<N.cols();j++){
    //(196*194)X(196*194) * (196*194)X(196*194)
    C(i,j)=  vec1(j) * N11(i,j);

            }
   }

return C;

}
*/


Matrice Resolution_ailees (int h , Matrice A , Matrice C , Matrice alpha1,Matriceinv N22 ,int iter ){

    Matrice_carre_plus matricealpha1 = Matrice_carre_plus::Zero();
    Vecteur vec2=Vecteur::Zero();
    Matrice matr = Matrice::Zero() ;

            A = h* (alpha1*N22* C) + A;

return A;

}
