////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    calcul_mat_N.cpp                            //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include "calcul_mat_N.hpp"

Vecteur MatriceNdiag(int h , int k ,  Matrice d , Matrice alpha1 , Matrice v){

    Matrice alpha1ij;
    Vecteur vec1;
    int f = 0;

   for(int i=0;i<alpha1ij.rows();i++){
            for(int j=0;j<alpha1ij.cols();j++){
                alpha1ij(i,j)= ((1 - h + h*alpha1(i,j)) + (2 * h /(k*k) *d(i,j))) ;

            }
    }
   // cout <<alpha1ij;

   for(int i=0;i<alpha1ij.rows();i++){

            for(int j=0;j<alpha1ij.cols();j++){

              vec1(f) = alpha1ij(i,j);
              f++;
            }
    }

    //cout<<vec1.rows()<<vec1.cols();
//cout <<vec1;

//cout<< vec1.block <1,100>(0,0);

return vec1;
}
Vecteur MatriceNdiaginf(int h , int k ,  Matrice d  , Matrice v){

    Matrice alpha2ij;
    Vecteur vec2;
    int f = 0;

   for(int i=0;i<alpha2ij.rows();i++){
            for(int j=0;j<alpha2ij.cols();j++){

                alpha2ij(i,j)  = ((-h/k)*(d(i,j)/k + v(i,j)/2) ) ;

            }
    }


   for(int i=0;i<alpha2ij.rows();i++){

            for(int j=0;j<alpha2ij.cols();j++){

              vec2(f) = alpha2ij(i,j);
              f++;
            }
    }

return vec2;

}
    Vecteur MatriceNdiagsup(int h , int k ,  Matrice d , Matrice v){

    Matrice alpha3ij;
    Vecteur vec3;
    int f = 0;

   for(int i=0;i<alpha3ij.rows();i++){
            for(int j=0;j<alpha3ij.cols();j++){

                alpha3ij(i,j)  = ((-h/k)*(d(i,j)/k - v(i,j)/2) ) ;
            }
    }

   for(int i=0;i<alpha3ij.rows();i++){

            for(int j=0;j<alpha3ij.cols();j++){

              vec3(f) = alpha3ij(i,j);

              f++;
            }
    }

return vec3;

    }

    MatriceN matricen (Vecteur VECINF, Vecteur DIAG, Vecteur VECSUP){
        MatriceN matn;
        matn = MatriceN::Zero(194*196, 194*196);
      for(int i=0;i<matn.cols();i++){
        matn(i,i) = DIAG(i);
        //cout<<mat(i,i);
        //cout<< vec1(i);
       }

//cout<< mat.cols()<<"\n";
   for(int i=0;i<matn.cols()-1;i++){
          matn(i,i+1)  = VECSUP(i);
          matn(i+1,i)  = VECINF(i);
       }
    return matn;
    }

 Matrice_carre calculmatriceN2N4 (int h , Matrice r , Matrice alpha2 ){

   Matrice mat;
   for(int i=0;i<mat.rows();i++){
        for(int j=0;j<mat.cols();j++){
            mat(i,j) = (1 - h *(r(i,j) - alpha2(i,j)));

        }
    }
        Matrice_carre m = Matrice_carre::Ones();
       for(int i=0;i<m.rows();i++){
                for(int j=0;j<m.cols();j++){
                    m(i,j)= mat(i,j);
                }
       }
Eigen::LU<Matrice_carre> lu(m);
 Matrice_carre m2 =lu.inverse();
 //cout<<m2;
 // Matrice_carre m2 = m.inverse();
   // cout<<mat;
 return m2;
 }
