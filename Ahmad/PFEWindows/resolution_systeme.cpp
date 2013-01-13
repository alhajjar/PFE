////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    Resolution_systeme.cpp                      //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include"../Includes/resolution_systeme.hpp"

Matrice Resolution_apteres(int h , Matrice &A , Matrice &C , Matrice &alpha2, cs* N){
int n = 38024;
 double I[38024]={0};
 double I1[38024] = {0};
 I1[0]=1;
 Vecteur vec1(38024);
  int f = 0;
  csn *R;
 

  double *x;
  x = (double*)cs_malloc (N->n , sizeof (double)) ;

 for(int i=0;i!=C.rows();i++){

     for(int j=0;j!=C.cols();j++){
         vec1(f) = C(i,j) + h* alpha2(i,j)* A(i,j);
           f++;

       }
  }

 R=cs_lusol_init (0, N, I1, 1e-14,x);
  for(int i = 1;i<38024;i++){

       double val = vec1(i);
        for(int k = 0;k<n;k++){
            I[k]+=I1[k]*val;
            I1[k]=0;
        }
        I1[i]=1;
    cs_lusol_boucle (N, I1, R, x);


 }
  cs_nfree (R) ;
  cs_free(x);

  f = 0;
 for(int i=0;i!=C.rows();i++){

     for(int j=0;j!=C.cols();j++){

         C(i,j) =I[f];
           f++;
       }
  }

return C;
}

Matrice Resolution_ailees (int h , Matrice &A , Matrice &C , Matrice &alpha1,Vecteur &N22  ){

  int f = 0;
  for (int i = 0;i!=A.rows();i++){
       for (int j = 0;j!=A.cols();j++){

        A(i,j) = N22(f) * (h* alpha1(i,j)* C(i,j) + A(i,j));

        f++;
        }
   }

return A;

}
