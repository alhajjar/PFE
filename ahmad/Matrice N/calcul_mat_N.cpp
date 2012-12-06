#include "calcul_mat_N.hpp"

MatriceN calculmatriceN1N3(int h , int k ,  Matrice d , Matrice alpha1 , Matrice v){
    MatriceN mat;
    mat = MatriceN::Zero(50, 50);
    Matrice alpha1ij;
    Matrice alpha2ij;
    Matrice alpha3ij;
    Matrice matrice;
    Vecteur vec1;
    Vecteur vec2;
    Vecteur vec3;

   for(int i=0;i<alpha1ij.rows();i++){
            for(int j=0;j<alpha1ij.cols();j++){
                alpha1ij(i,j)= ((1 - h + h*alpha1(i,j)) + (2 * h /(k*k) *d(i,j))) ;
                alpha2ij(i,j)  = ((-h/k)*(d(i,j)/k + v(i,j)/2) ) ;
                alpha3ij(i,j)  = ((-h/k)*(d(i,j)/k - v(i,j)/2) ) ;
            }
    }
   // cout <<alpha1ij;

   for(int i=0;i<alpha1ij.rows();i++){

            for(int j=0,k;j<alpha1ij.cols();j++){
                //cout<<k;
              vec1(k) = alpha1ij(i,j);
              vec2(k) = alpha2ij(i,j);
              vec3(k) = alpha3ij(i,j);

              k++;
            }
    }

    //cout<<vec1.rows()<<vec1.cols();
//cout <<vec1;

//cout<< vec1.block <1,100>(0,0);
    for(int i=0;i<mat.cols();i++){
        mat(i,i) = vec1(i);
        //cout<<mat(i,i);
        //cout<< vec1(i);
       }

//cout<< mat.cols()<<"\n";
   for(int i=0;i<mat.cols()-1;i++){
          mat(i,i+1)  = vec2(i);
          mat(i+1,i)  = vec3(i);
       }
return mat;
}


 Matrice calculmatriceN2N4 (int h , Matrice r , Matrice alpha2 ){

   Matrice mat;
   for(int i=0;i<mat.rows();i++){
        for(int j=0;j<mat.cols();j++){
            mat(i,j) = (1 - h * (r(i,j) - alpha2(i,j)));

        }
    }
 return mat;
 }
