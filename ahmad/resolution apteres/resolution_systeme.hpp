////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    Resolution_systeme.hpp                      //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#ifndef __projet_pfe__Resolution_systeme__
#define __projet_pfe__Resolution_systeme__


#include <iostream>
#include "/usr/include/eigen2/Eigen/Array"
#include "/usr/include/eigen2/Eigen/Core"
#include "/usr/include/eigen2/Eigen/LU"
#include "/usr/include/eigen2/Eigen/Dense"

    using namespace std;
    using namespace Eigen;

    typedef Matrix<float, 196,194> Matrice;
    typedef Matrix<float, 1 ,196*194> Vecteur;
    typedef Matrix<float, 196,196> Matrice_carre;
    typedef Matrix<float,196,196> Matrice_carre_plus;
    typedef Matrix<float,Dynamic,Dynamic> MatriceN;
    typedef Matrix<float, 194 ,196> Matriceinv;

    Matrice Resolution_apteres(int h , Matrice A , Matrice C , Matrice alpha2, MatriceN N1);
    Matrice Resolution_ailees (int h , Matrice A , Matrice C , Matrice alpha1,Matriceinv N22,int iteration );

#endif
