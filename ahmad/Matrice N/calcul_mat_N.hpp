#ifndef __projet_pfe__Calcul_mat_N__
#define __projet_pfe__Calcul_mat_N__

#include <iostream>
#include "/usr/include/eigen2/Eigen/Core"
//#include <Map.h>

    using namespace std;
    using namespace Eigen;

    typedef Matrix<float, 196,194> Matrice;
    typedef Matrix<float, 1 ,196*194 > Vecteur;
    //typedef Matrix<float, 1 ,196 > Vecteur1;
    typedef Matrix<float,Dynamic,Dynamic> MatriceN;
    //typedef Map<Vecteur> MapType;
    //typedef Matrix<float, 194,194> MatriceM;

    MatriceN calculmatriceN1N3(int h , int k ,  Matrice d , Matrice alpha1 , Matrice vitesse);
    Matrice calculmatriceN2N4 (int h , Matrice r , Matrice alpha2 );

#endif
