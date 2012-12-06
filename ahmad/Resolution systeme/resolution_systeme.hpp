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
    typedef Matrix<float, 1 ,10000> VecteurX;
    typedef Matrix<float, 194,194> Matrice_carre;
    typedef Matrix<float,196,196> Matrice_carre_plus;
    typedef Matrix<float,Dynamic,Dynamic> MatriceN;

    Matrice Resolution_apteres(int h , Matrice A , Matrice C , Matrice alpha2, MatriceN N1);
    Matrice Resolution_ailees (int h , Matrice A , Matrice C , Matrice alpha1,Matrice_carre N22,int iteration );

#endif

/*
 convertir C + h* alpha2* A en vecteur de taille (196 x 194)
 convertir h* alpha1* C + A en vecteur de taille (196 x 194)
 calculer la matrice tridiagonale N1 de taille (196 x 194) x (196 x 194) avec :
. sur la diagonale principale : 1.000+h*alpha1+(2*h*d)/(k^2) converti en vecteur
. sur la diagonale supérieure : -(h/(k^2))*d+(h/(2*k))*vitesseh converti en vecteur
. sur la diagonale inférieure : -(h/(k^2))*d-(h/(2*k))*vitesseh converti en vecteur
 calculer l'inverse de N1 : N11= inverse de N1
 convertir N2=1+h*r*(1-alpha2) en vecteur de taille (196 x 194). Poser N22= 1/N2
 calculer les nouvelles valeurs de A et C
 C= N11 * (C + h* alpha2* A)
 A= N2 * (h* alpha1* C + A )*/
