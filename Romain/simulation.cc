#include "simulation.h"
#include <cstdlib>
#include <math.h>
#define TAILLE_LIGNE 196
#define TAILLE_COLONNE 194
using namespace std;

/** \taux d'accroissement
 *  \brief calcul la matrice du taux d'accroissement
 *  \param[in] theta de temperature °C et stade viellissement de la bibitte de 0 a 93
 *  \return matrice avec taux d'accroissement
 */
Matrice taux_accroissement(Matrice theta, Matrice stades){
    float sm = 15.27211;
    float b = 0.04133;
    float k = 0.11987;
    float a1 = -0.10373;
    float a2 = 0.11132;
    float num;
    float den;
    Matrice mat(TAILLE_LIGNE,TAILLE_COLONNE);
    for(int i=0;i<TAILLE_LIGNE;i++){
            for(int j=0;j<TAILLE_COLONNE;j++){
                    if(theta.getValue(i,j)>=30||stades.getValue(i,j)>=92)
                        mat.setValue(i, j, 0);
                    else{
                        num = a1*log(30-theta.getValue(i,j))+a2*log(92-stades.getValue(i,j));
                        den = 1+exp(-k*(stades.getValue(i,j)-sm))+exp(-b*theta.getValue(i,j));
                        mat.setValue(i, j, num/den);
                    }
            }
    }
    return mat;
}

/** \coeff depot1
 *  \brief calcul la matrice des coeff depot1
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de blé entre -1 et 1
 *  \return matrice avec les coeff depot1
 */
Matrice coeff_depot1(Matrice p, Matrice eta){
    float a1 = 1.004855;
    float a2 = 1.652655;
    float a = -0.267819;
    float k = 6.214583;
    Matrice mat(TAILLE_LIGNE,TAILLE_COLONNE);
    for(int i=0;i<TAILLE_LIGNE;i++){
            for(int j=0;j<TAILLE_COLONNE;j++){
              mat.setValue(i, j,log(a1+a*(-(p.getValue(i,j)*p.getValue(i,j))*atan(k*eta.getValue(i,j))+a2*p.getValue(i,j))));
            }
    }
    return mat;
}

/** \coeff depot2
 *  \brief calcul la matrice des coeff depot2
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de blé entre -1 et 1
 *  \return matrice avec les coeff depot2
 */
Matrice coeff_depot2(Matrice p, Matrice eta){
    float a1 = -0.128715;
    float a2 = 24.589110;
    float a3 = 0.946651;
    float a4 = 0.079787;
    float a5 = 0.906087;
    float k = 7.317821;
    float num;
    float den;
    Matrice mat(TAILLE_LIGNE,TAILLE_COLONNE);
    for(int i=0;i<TAILLE_LIGNE;i++){
            for(int j=0;j<TAILLE_COLONNE;j++){
              num = (a4*exp(p.getValue(i,j))+a5*log(1+p.getValue(i,j)));
              den = 1-a1*atan(k*eta.getValue(i,j))+exp(a2*(p.getValue(i,j)-a3)); 
              mat.setValue(i, j, num/den);
            }
    }
    return mat;  
}
/** \coeff depot3
 *  \brief calcul la matrice des coeff depot3
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de blé entre -1 et 1
 *  \return matrice avec les coeff depot3
 */
Matrice coeff_depot3(Matrice p, Matrice eta){
    float a1 = 0.23001;
    float a2 = 0.86894;
    float a3 = 1.08105;
    float k = 8.22311;
    Matrice mat(TAILLE_LIGNE,TAILLE_COLONNE);
    for(int i=0;i<TAILLE_LIGNE;i++){
            for(int j=0;j<TAILLE_COLONNE;j++){
                    mat.setValue(i, j, log(a2+a1*(p.getValue(i,j)-p.getValue(i,j)*p.getValue(i,j))*atan(k*eta.getValue(i,j))+a3*p.getValue(i,j)) );
            }
    }
    return  mat;
}
/** \coeff depot4
 *  \brief calcul la matrice des coeff depot4
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de blé entre -1 et 1
 *  \return matrice avec les coeff depot4
 */
Matrice coeff_depot4(Matrice p, Matrice eta){
    float a1=0.318941;
    float a2=0.983375;
    float a3=1.669692;
    float k =-6.572036;
     Matrice mat(TAILLE_LIGNE,TAILLE_COLONNE);
    for(int i=0;i<TAILLE_LIGNE;i++){
            for(int j=0;j<TAILLE_COLONNE;j++){
                mat.setValue(i, j,log(a2+a1*(p.getValue(i,j)-(p.getValue(i,j)*p.getValue(i,j)))*atan(k*eta.getValue(i,j))+a3*p.getValue(i,j)));
            }
    }
    return  mat;
}
/** \coeff depot5
 *  \brief calcul la matrice des coeff depot5
 *  \param[in] p proportion de ble dans la grille en 0 et 1, eta distribution des parcelle de blé entre -1 et 1
 *  \return matrice avec les coeff depot5
 */
Matrice coeff_depot5(Matrice p, Matrice eta){
    float a1=-0.12952;
    float a2 = 0.73519;
    float a3 =1.92703;
    float k =38.70085;
    Matrice mat(TAILLE_LIGNE,TAILLE_COLONNE);
    for(int i=0;i<TAILLE_LIGNE;i++){
            for(int j=0;j<TAILLE_COLONNE;j++){
                    if (p.getValue(i,j)<0.5)
                       mat.setValue(i, j,log(a2+a1*(p.getValue(i,j)-(p.getValue(i,j)*p.getValue(i,j))*atan(-k*eta.getValue(i,j))+a3*p.getValue(i,j)) ) );
                    else mat.setValue(i, j,log(a2+a1*(p.getValue(i,j)-(p.getValue(i,j)*p.getValue(i,j))*atan(k*eta.getValue(i,j))+a3*p.getValue(i,j))));
            }
    }
    return  mat;
    
}
/** \coeff_envol
 *  \brief calcul la matrice des coeff_envol
 *  \param[in] A nb d'aptere, theta de temperature °C et stade viellissement de la bibitte de 0 a 100
 *  \return matrice avec les coeff_envol
 */
Matrice coeff_envol(int A,Matrice stades,Matrice theta){
    float a=0.034733;
    float a0=1.417143;
    float a1=0.048163;
    float a2=-0.543663;
    float logN4;
    float phi_alpha2;
    Matrice mat(TAILLE_LIGNE,TAILLE_COLONNE);
    for(int i=0;i<TAILLE_LIGNE;i++){
            for(int j=0;j<TAILLE_COLONNE;j++){      
            logN4=exp(a*stades.getValue(i,j))/(1+exp(a0+a1*stades.getValue(i,j)+a2*log(1+A)));
            phi_alpha2=2/( 1 + exp( - 0.1 * theta.getValue(i,j)))- 1;
            mat.setValue(i, j,exp(logN4)*phi_alpha2);
            }
    }  
    return mat;
}
