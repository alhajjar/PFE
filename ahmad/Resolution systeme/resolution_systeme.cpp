////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    Resolution_systeme.cpp                      //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include"resolution_systeme.hpp"

Matrice Resolution_apteres(int h , Matrice A , Matrice C , Matrice alpha2, cs* N){
int n = A.rows()*A.cols();
 double I[n];
 Vecteur vec1;
 for(int i = 0;i!=n;i++){
        double I1[38024] = {0};
        I1[i]=1;
        calcul_N(N,I1);

    for(int k = 0;k!=n;k++){
        I[k]+=I1[k];
     }
 }

 int f = 0;
 for(int i=0;i!=C.rows();i++){

     for(int j=0;j!=C.cols();j++){
         vec1(f) = C(i,j) + h* alpha2(i,j)* A(i,j);
         C(i,j) =(float)I[f]*vec1(f);
           f++;
       }
  }
return C;
}

Matrice Resolution_ailees (int h , Matrice A , Matrice C , Matrice alpha1,Vecteur N22  ){

  int f = 0;
  for (int i = 0;i!=A.rows();i++){
       for (int j = 0;j!=A.cols();j++){

        A(i,j) = N22(f) * (h* alpha1(i,j)* C(i,j) + A(i,j));

        f++;
        }
   }

return A;

}
