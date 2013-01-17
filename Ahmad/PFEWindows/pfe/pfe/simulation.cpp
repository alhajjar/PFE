////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    simulation.cpp                              //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "simulation.hpp"

/** \taux d'accroissement
 *  \brief calcul la matrice du taux d'accroissement
 *  \param[in] theta de temperature C et stade viellissement de la bibitte de 0 a 93
 *  \return matrice avec taux d'accroissement
 */
Matrice taux_accroissement(Matrice theta, Matrice stades){
    double sm = 15.27211;
    double b = 0.04133;
    double k = 0.11987;
    double a1 = -0.10373;
    double a2 = 0.11132;
    double num = 0;
    double den = 0;
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i = 0;i != mat.rows();i++){
            for(int j = 0;j != mat.cols();j++){
                    if(theta(i,j) >= 30 || stades(i,j) >= 92){
                        mat(i, j) = 0;}
                    else{
                        num = a1*log(30-theta(i,j))+a2*log(92-stades(i,j));
                        den = 1+exp(-k*(stades(i,j)-sm))+exp(-b*theta(i,j));
                        mat(i, j) = num/den;
                    }
            }
    }
    return mat;
}

/* \coeff depot1
 *  \brief calcul la matrice des coeff depot1
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de bl� entre -1 et 1
 *  \return matrice avec les coeff depot1
 */

Matrice coeff_depot1(Matrice p, Matrice eta){
    double a1 = 1.004855;
    double a2 = 1.652655;
    double a = -0.267819;
    double k = 6.214583;
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
              mat(i, j)=log(a1+a*(-(p(i,j)*p(i,j)+p(i,j))*atan(k*eta(i,j))+a2*p(i,j)));
            }
    }
    return mat;
}


/* coeff depot2
 *  \brief calcul la matrice des coeff depot2
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de bl� entre -1 et 1
 *  \return matrice avec les coeff depot2

 */


Matrice coeff_depot2(Matrice p, Matrice eta){
    double a1 = -0.128715;
    double a2 = 24.589110;
    double a3 = 0.946651;
    double a4 = 0.079787;
    double a5 = 0.906087;
    double k = 7.317821;
    double num = 0;
    double den = 0;
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
              num = (a4*exp(p(i,j))+a5*log(1+p(i,j)));
              den = 1-a1*atan(k*eta(i,j))+exp(a2*(p(i,j)-a3));
              mat(i, j) = num/den;
            }
    }
    return mat;
}

/** \coeff depot3
 *  \brief calcul la matrice des coeff depot3
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de bl� entre -1 et 1
 *  \return matrice avec les coeff depot3
 */

Matrice coeff_depot3(Matrice p, Matrice eta){
    double a1 = 0.23001;
    double a2 = 0.86894;
    double a3 = 1.08105;
    double k = 8.22311;
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
                    mat(i, j) = log(a2+a1*(p(i,j)-p(i,j)*p(i,j))*atan(k*eta(i,j)))+a3*p(i,j);
            }
    }
    return  mat;
}

/** \coeff depot4
 *  \brief calcul la matrice des coeff depot4
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de bl� entre -1 et 1
 *  \return matrice avec les coeff depot4
 */
Matrice coeff_depot4(Matrice p, Matrice eta){
    double a1=0.318941;
    double a2=0.983375;
    double a3=1.669692;
    double k =-6.572036;
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
                mat(i, j) = log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(k*eta(i,j))+a3*p(i,j));
            }
    }
    return  mat;
}

/** \coeff depot5
 *  \brief calcul la matrice des coeff depot5
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de bl� entre -1 et 1
 *  \return matrice avec les coeff depot5
 */
Matrice coeff_depot5(Matrice p, Matrice eta){
    double a1=-0.12952;
    double a2 = 0.73519;
    double a3 =1.92703;
    double k =38.70085;
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
                    if (p(i,j)<0.5)
                       mat(i, j) =  log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(-k*eta(i,j))+a3*p(i,j)) ;
                    else mat(i, j) = log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(k*eta(i,j))+a3*p(i,j));
            }
    }
    return  mat;

}

/** \coeff_envol
 *  \brief calcul la matrice des coeff_envol
 *  \param[in] A nb d'aptere, theta de temperature �C et stade viellissement de la bibitte de 0 a 100
 *  \return matrice avec les coeff_envol
 */

Matrice coeff_envol(Matrice A,Matrice stades,Matrice theta){
    double a=0.034733;
    double a0=1.417143;
    double a1=0.048163;
    double a2=-0.543663;
    double logN4 = 0;
    double phi_alpha2 = 0;
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
            logN4=exp(a*stades(i,j))/(1+exp(a0+a1*stades(i,j)+a2*log(1+A(i,j))));
            phi_alpha2=2/( 1 + exp( - 0.1 * theta(i,j)))- 1;
            mat(i, j) = exp(logN4)*phi_alpha2;
            }
    }
    return mat;
}

