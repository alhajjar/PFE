////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    calcul_mat_N.cpp                            //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include "calcul_mat_N.hpp"
#include "pseudoinverse.hpp"

MatriceN matricen (int h , int k ,  Matrice d , Matrice alpha1 , Matrice v){

    Matrice alpha1ij=Matrice::Zero();
    Matrice alpha2ij=Matrice::Zero();
    Matrice alpha3ij=Matrice::Zero();
    Vecteur vec3=Vecteur::Zero();
    Vecteur vec2=Vecteur::Zero();
    Vecteur vec1=Vecteur::Zero();
    int f = 0;

   for(int i=0;i<alpha1ij.rows();i++){
            for(int j=0;j<alpha1ij.cols();j++){

                alpha1ij(i,j)= ((1 - h + h*alpha1(i,j)) + (2 * h /(k*k) *d(i,j))) ;
                vec1(f) = alpha1ij(i,j);
                alpha2ij(i,j)  = ((-h/k)*(d(i,j)/k + v(i,j)/2) ) ;
                vec2(f) = alpha2ij(i,j);
                alpha3ij(i,j)  = ((-h/k)*(d(i,j)/k - v(i,j)/2) ) ;
                vec3(f) = alpha3ij(i,j);

            f++;
            }
    }

     MatriceN matn;
     matn = MatriceN::Zero(194*196,3);

    for(int i=0;i<matn.cols();i++){
          matn(i,0)  = vec2(i);
          matn(i,1) =  vec1(i);
          matn(i,2)  = vec3(i);
       }

//N11 =pseudoinv(matn);

 return matn ;
}


Matriceinv calculmatriceN2N4 (int h , Matrice r , Matrice alpha2 ){

   Matrice m=Matrice::Zero();

   for(int i=0;i<r.rows();i++){
        for(int j=0;j<r.cols();j++){
            m(i,j) = (1 - h *(r(i,j) - alpha2(i,j)));
        }
    }

    Matriceinv m2 = Matriceinv::Zero();
    m2 = pseudoinv(m);

 return m2;
}

