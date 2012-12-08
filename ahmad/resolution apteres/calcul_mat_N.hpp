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
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>


    using namespace std;
    using namespace Eigen;
    using namespace boost::numeric::ublas;

    typedef Matrix<float, 196,194> Matrice;
    typedef Matrix<float, 1 ,196*194> Vecteur;


    typedef Matrix<float, 196,196> Matrice_carre;
    typedef Matrix<float,Dynamic,Dynamic> MatriceN;
    typedef Matrix<float,194,196> Matriceinv;

    Matriceinv calculmatriceN2N4 (int h , Matrice r , Matrice alpha2 );
    MatriceN matricen (int h , int k ,  Matrice d , Matrice alpha1 , Matrice v);






#endif
