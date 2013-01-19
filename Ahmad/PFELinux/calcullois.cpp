/** 
 *\file calcullois.cpp
 *\brief ce fichier permet de calculer les Matrices de valeurs des differentes lois de diffusion/multiplication
 */
#include "Includes/calcullois.hpp"

/** 
 *  \brief constructeur de la classe calcullois
 *  \details cette classe calculs les différentes voids des lois
 */
calcullois::calcullois(){
	 taux_accroissement= new Matrice(196,194);
	 *taux_accroissement=Matrice::Zero(196,194);
	 coeff_depot1=new Matrice(196,194);
	 *coeff_depot1=Matrice::Zero(196,194);
	 coeff_depot2=new Matrice(196,194);
	 *coeff_depot2=Matrice::Zero(196,194);
	 coeff_depot3=new Matrice(196,194);
	 *coeff_depot3=Matrice::Zero(196,194);
	 coeff_depot4=new Matrice(196,194);
	 *coeff_depot4=Matrice::Zero(196,194);
	 coeff_depot5=new Matrice(196,194);
	 *coeff_depot5=Matrice::Zero(196,194);
	 coeff_envol=new Matrice(196,194);
	 *coeff_envol=Matrice::Zero(196,194);
}
calcullois::~calcullois(){
	delete(taux_accroissement);
	delete(coeff_depot1);
	delete(coeff_depot2);
	delete(coeff_depot3);
	delete(coeff_depot4);
	delete(coeff_depot5);
	delete(coeff_envol);
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
    *taux_accroissement = mat;
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
    Matrice mat(196,194);
     mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
              mat(i, j)=log(a1+a*(-(p(i,j)*p(i,j)+p(i,j)) *atan(k*eta(i,j))+a2*p(i,j)));
            }
    }
    *coeff_depot1 = mat;
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
    Matrice mat(196,194);
     mat = Matrice::Zero(196,194);
    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
              num = (a4*exp(p(i,j))+a5*log(1+p(i,j)));
              den = 1-a1*atan(k*eta(i,j))+exp(a2*(p(i,j)-a3));
              mat(i, j) = num/den;
            }
    }
    *coeff_depot2=mat;
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
    Matrice mat(196,194);
     mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
            	mat(i, j) = log(a2+a1*(p(i,j)-p(i,j)*p(i,j))*atan(k*eta(i,j)))+a3*p(i,j);
            }
    }
    *coeff_depot3=mat;
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
    Matrice mat(196,194);
     mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
            	mat(i, j) = log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(k*eta(i,j))+a3*p(i,j));
            }
    }
    *coeff_depot4=mat;
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
    Matrice mat(196,194);
     mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
                    if (p(i,j)<0.5)
                    	mat(i, j) =  log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(-k*eta(i,j))+a3*p(i,j)) ;
                    else mat(i, j) = log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(k*eta(i,j))+a3*p(i,j));
            }
    }
    *coeff_depot5=mat;
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
    Matrice mat(196,194);
     mat = Matrice::Zero(196,194);

    for(int i=0;i!=mat.rows();i++){
            for(int j=0;j!=mat.cols();j++){
            logN4=exp(a*stades(i,j))/(1+exp(a0+a1*stades(i,j)+a2*log(1+A(i,j))));
            phi_alpha2=2/( 1 + exp( - 0.1 * theta(i,j)))- 1;
            mat(i, j) = exp(logN4)*phi_alpha2;
            }
    }
    *coeff_envol=mat;
}

 /** 
 *  \brief setter matrice des taux d'accroissement
 */
void  calcullois::set_taux_accroissement(Matrice tauxaccroissement){
*taux_accroissement = tauxaccroissement;
}
 /** 
 *  \brief setter matrice coeff_depot1
 */
void  calcullois::set_coeffdepot1(Matrice coeffdepot1){
*coeff_depot1=coeffdepot1;
}
 /** 
 *  \brief setter matrice coeff_depot2
 */
void  calcullois::set_coeffdepot2(Matrice coeffdepot2){
*coeff_depot2=coeffdepot2;
}
 /** 
 *  \brief setter matrice coeff_depot3
 */
void  calcullois::set_coeffdepot3(Matrice coeffdepot3){
*coeff_depot3=coeffdepot3;
}
 /** 
 *  \brief setter matrice coeff_depot4
 */
void  calcullois::set_coeffdepot4(Matrice coeffdepot4){
*coeff_depot4=coeffdepot4;
}
 /** 
 *  \brief setter matrice coeff_depot5
 */
void  calcullois::set_coeffdepot5(Matrice coeffdepot5){
*coeff_depot5=coeffdepot5;
}
 /** 
 *  \brief setter matrice coeff_envol
 */
void  calcullois::set_coeff_envol(Matrice coeffenvol){
*coeff_envol=coeffenvol;
}
 /** 
 *  \brief getter matrice des taux d'accroissement
 */
Matrice  calcullois::get_taux_accroissement(){
return *taux_accroissement;
 }
  /** 
 *  \brief getter matrice coeff_depot1
 */
Matrice  calcullois::get_coeffdepot1(){
return *coeff_depot1;
 }
  /** 
 *  \brief getter matrice coeff_depot2
 */
Matrice  calcullois::get_coeffdepot2(){
return *coeff_depot2;
}
 /** 
 *  \brief getter matrice coeff_depot3
 */
Matrice  calcullois::get_coeffdepot3(){
return *coeff_depot3;
}
 /** 
 *  \brief getter matrice coeff_depot4
 */
Matrice  calcullois::get_coeffdepot4(){
return *coeff_depot4;
}
 /** 
 *  \brief getter matrice coeff_depot5
 */
Matrice  calcullois::get_coeffdepot5(){
return *coeff_depot5;
}
 /** 
 *  \brief getter matrice coeff_envol
 */
Matrice  calcullois::get_coeff_envol(){
return *coeff_envol;
}

