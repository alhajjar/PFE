/** 
 *\file calcullois.cpp
 *\brief ce fichier permet de calculer les Matrices de valeurs des differentes lois de diffusion/multiplication
 */
#include "Includes/calcullois.hpp"

/** 
 *  \brief constructeur de la classe calcullois
 *  \details cette classe calculs les différentes voids des lois
 */
calcullois::calcullois(){//Constructeur sans paramètres
}
calcullois::~calcullois(){//Constructeur sans paramètres
}
/** 
 *  \brief calcul la matrice du taux d'accroissement
 *  \param[in] theta matrice de temperature 
 *  \param[in] stade matrice de stades phenologique : viellissement de la plante de 0 a 93
 */
void calcullois::calcul_taux_accroissement(Matrice theta, Matrice stades){
	double sm = 15.27211;
    double b = 0.04133;
    double k = 0.11987;
    double a1 = -0.10373;
    double a2 = 0.11132;
    double num = 0;
    double den = 0;
     taux_accroissement=Matrice(196,194);
    taux_accroissement = Matrice::Zero(196,194);

    for(int i = 0;i != taux_accroissement.rows();i++){
            for(int j = 0;j != taux_accroissement.cols();j++){
                    if(theta(i,j) >= 30 || stades(i,j) >= 92){
                        taux_accroissement(i, j) = 0;}
                    else{
                        num = a1*log(30-theta(i,j))+a2*log(92-stades(i,j));
                        den = 1+exp(-k*(stades(i,j)-sm))+exp(-b*theta(i,j));
                        taux_accroissement(i, j) = num/den;
                    }
            }
    }
}
 /** 
 *  \brief calcul coeff depot1
 *  \details calcul la matrice des coeff depot1
 *  \param p proportion de ble dans la grille en 0 et 1,
 *  \param eta distribution des parcelle de ble entre -1 et 1
 */
void calcullois::calcul_coeffdepot1(Matrice p, Matrice eta){
	double a1 = 1.004855;
    double a2 = 1.652655;
    double a = -0.267819;
    double k = 6.214583;
     coeff_depot1=Matrice(196,194);
    coeff_depot1 = Matrice::Zero(196,194);

    for(int i=0;i!=coeff_depot1.rows();i++){
            for(int j=0;j!=coeff_depot1.cols();j++){
              coeff_depot1(i, j)=log(a1+a*(-(p(i,j)*p(i,j)+p(i,j)) *atan(k*eta(i,j))+a2*p(i,j)));
            }
    }
}
 /** 
 *  \brief calcul coeff depot2
 *  \details calcul la matrice des coeff depot2
 *  \param p proportion de ble dans la grille en 0 et 1,
 *  \param eta distribution des parcelle de ble entre -1 et 1
 */
void calcullois::calcul_coeffdepot2(Matrice p, Matrice eta){
	double a1 = -0.128715;
    double a2 = 24.589110;
    double a3 = 0.946651;
    double a4 = 0.079787;
    double a5 = 0.906087;
    double k = 7.317821;
    double num = 0;
    double den = 0;
     coeff_depot2=Matrice(196,194);
    coeff_depot2 = Matrice::Zero(196,194);

    for(int i=0;i!=coeff_depot2.rows();i++){
            for(int j=0;j!=coeff_depot2.cols();j++){
              num = (a4*exp(p(i,j))+a5*log(1+p(i,j)));
              den = 1-a1*atan(k*eta(i,j))+exp(a2*(p(i,j)-a3));
              coeff_depot2(i, j) = num/den;
            }
    }
}
 /** 
 *  \brief calcul coeff depot3
 *  \details calcul la matrice des coeff depot3
 *  \param p proportion de ble dans la grille en 0 et 1,
 *  \param eta distribution des parcelle de ble entre -1 et 1
 */
void calcullois::calcul_coeffdepot3(Matrice p, Matrice eta){
	double a1 = 0.23001;
    double a2 = 0.86894;
    double a3 = 1.08105;
    double k = 8.22311;
     coeff_depot3=Matrice(196,194);
    coeff_depot3 = Matrice::Zero(196,194);

    for(int i=0;i!=coeff_depot3.rows();i++){
            for(int j=0;j!=coeff_depot3.cols();j++){
                    coeff_depot3(i, j) = log(a2+a1*(p(i,j)-p(i,j)*p(i,j))*atan(k*eta(i,j)))+a3*p(i,j);
            }
    }
}

 /** 
 *  \brief calcul coeff depot4
 *  \details calcul la matrice des coeff depot4
 *  \param p proportion de ble dans la grille en 0 et 1,
 *  \param eta distribution des parcelle de ble entre -1 et 1
 */	
void calcullois::calcul_coeffdepot4(Matrice p, Matrice eta){
	double a1=0.318941;
    double a2=0.983375;
    double a3=1.669692;
    double k =-6.572036;
     coeff_depot4=Matrice(196,194);
    coeff_depot4 = Matrice::Zero(196,194);

    for(int i=0;i!=coeff_depot4.rows();i++){
            for(int j=0;j!=coeff_depot4.cols();j++){
                coeff_depot4(i, j) = log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(k*eta(i,j))+a3*p(i,j));
            }
    }
}
 /** 
 *  \brief calcul coeff depot5
 *  \details calcul la matrice des coeff depot5
 *  \param p proportion de ble dans la grille en 0 et 1,
 *  \param eta distribution des parcelle de ble entre -1 et 1
 */
void calcullois::calcul_coeffdepot5(Matrice p, Matrice eta){
	double a1=-0.12952;
    double a2 = 0.73519;
    double a3 =1.92703;
    double k =38.70085;
     coeff_depot5=Matrice(196,194);
    coeff_depot5 = Matrice::Zero(196,194);

    for(int i=0;i!=coeff_depot5.rows();i++){
            for(int j=0;j!=coeff_depot5.cols();j++){
                    if (p(i,j)<0.5)
                       coeff_depot5(i, j) =  log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(-k*eta(i,j))+a3*p(i,j)) ;
                    else coeff_depot5(i, j) = log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(k*eta(i,j))+a3*p(i,j));
            }
    }
}
  /** 
 *  \brief calcul la matrice des coeff_envol
 *  \details calcul la matrice des coeff depot1
 *  \param p proportion de ble dans la grille en 0 et 1
 *  \param stades matrice de stades phenologique : viellissement de la plante de 0 a 93
 *  \param A Matrice des pucerons ailes
 */
void calcullois::calcul_coeff_envol(Matrice A,Matrice stades,Matrice theta){
 double a=0.034733;
    double a0=1.417143;
    double a1=0.048163;
    double a2=-0.543663;
    double logN4 = 0;
    double phi_alpha2 = 0;
     coeff_envol=Matrice(196,194);
    coeff_envol = Matrice::Zero(196,194);

    for(int i=0;i!=coeff_envol.rows();i++){
            for(int j=0;j!=coeff_envol.cols();j++){
            logN4=exp(a*stades(i,j))/(1+exp(a0+a1*stades(i,j)+a2*log(1+A(i,j))));
            phi_alpha2=2/( 1 + exp( - 0.1 * theta(i,j)))- 1;
            coeff_envol(i, j) = exp(logN4)*phi_alpha2;
            }
    }
}

 /** 
 *  \brief setter matrice des taux d'accroissement
 */
void  calcullois::set_taux_accroissement(Matrice taux_accroissement){
this->taux_accroissement = taux_accroissement;
}
 /** 
 *  \brief setter matrice coeff_depot1
 */
void  calcullois::set_coeffdepot1(Matrice coeff_depot1){
this->coeff_depot1=coeff_depot1;
}
 /** 
 *  \brief setter matrice coeff_depot2
 */
void  calcullois::set_coeffdepot2(Matrice coeff_depot2){
this->coeff_depot2=coeff_depot2;
}
 /** 
 *  \brief setter matrice coeff_depot3
 */
void  calcullois::set_coeffdepot3(Matrice coeff_depot3){
this->coeff_depot3=coeff_depot3;
}
 /** 
 *  \brief setter matrice coeff_depot4
 */
void  calcullois::set_coeffdepot4(Matrice coeff_depot4){
this->coeff_depot4=coeff_depot4;
}
 /** 
 *  \brief setter matrice coeff_depot5
 */
void  calcullois::set_coeffdepot5(Matrice coeff_depot5){
this->coeff_depot5=coeff_depot5;
}
 /** 
 *  \brief setter matrice coeff_envol
 */
void  calcullois::set_coeff_envol(Matrice coeff_envol){
this->coeff_envol=coeff_envol;
}
 /** 
 *  \brief getter matrice des taux d'accroissement
 */
Matrice  calcullois::get_taux_accroissement(){
return taux_accroissement;
 }
  /** 
 *  \brief getter matrice coeff_depot1
 */
Matrice  calcullois::get_coeffdepot1(){
return coeff_depot1;
 }
  /** 
 *  \brief getter matrice coeff_depot2
 */
Matrice  calcullois::get_coeffdepot2(){
return coeff_depot2;
}
 /** 
 *  \brief getter matrice coeff_depot3
 */
Matrice  calcullois::get_coeffdepot3(){
return coeff_depot3;
}
 /** 
 *  \brief getter matrice coeff_depot4
 */
Matrice  calcullois::get_coeffdepot4(){
return coeff_depot4;
}
 /** 
 *  \brief getter matrice coeff_depot5
 */
Matrice  calcullois::get_coeffdepot5(){
return coeff_depot5;
}
 /** 
 *  \brief getter matrice coeff_envol
 */
Matrice  calcullois::get_coeff_envol(){
return coeff_envol;
}

