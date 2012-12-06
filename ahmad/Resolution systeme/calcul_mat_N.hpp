////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    calcul_mat_N.hpp                            //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#ifndef __projet_pfe__Calcul_mat_N__
#define __projet_pfe__Calcul_mat_N__


#include <iostream>
#include "/usr/include/eigen2/Eigen/Array"
#include "/usr/include/eigen2/Eigen/Core"
#include "/usr/include/eigen2/Eigen/LU"
#include "/usr/include/eigen2/Eigen/Dense"

    using namespace std;
    using namespace Eigen;

    typedef Matrix<float, 196,194> Matrice;
    typedef Matrix<float, 1 ,196*194> Vecteur;
    typedef Matrix<float, 1 ,10000> VecteurX;

    typedef Matrix<float, 194,194> Matrice_carre;
    typedef Matrix<float,Dynamic,Dynamic> MatriceN;


    Vecteur MatriceNdiag(int h , int k ,  Matrice d , Matrice alpha1 , Matrice vitesse);
    Vecteur MatriceNdiaginf(int h , int k ,  Matrice d , Matrice vitesse);
    Vecteur MatriceNdiagsup(int h , int k ,  Matrice d , Matrice vitesse);
    Matrice_carre calculmatriceN2N4 (int h , Matrice r , Matrice alpha2 );
    MatriceN matricen (Vecteur v1, Vecteur v2, Vecteur v3);

#endif
