/** 
 * \file Calcul_Lois.cpp
 * \brief Ce fichier permet de calculer les Matrices de valeurs des différentes lois de diffusion/multiplication
 */
#include "Includes/Calcul_Lois.hpp"

/** \fn Calcul_Lois::Calcul_Lois()
 *  \brief Constructeur de la classe Calcul_Lois
 */
Calcul_Lois::Calcul_Lois(){
	ta_sm = 15.27211;
    ta_b = 0.04133;
    ta_k = 0.11987;
    ta_a1 = -0.10373;
    ta_a2 = 0.11132;
	cd1_a1 = 1.004855;
    cd1_a2 = 1.652655;
    cd1_a = -0.267819;
    cd1_k = 6.214583;
	cd2_a1 = -0.128715;
    cd2_a2 = 24.589110;
    cd2_a3 = 0.946651;
    cd2_a4 = 0.079787;
    cd2_a5 = 0.906087;
    cd2_k = 7.317821;
	cd3_a1 = 0.23001;
    cd3_a2 = 0.86894;
    cd3_a3 = 1.08105;
    cd3_k = 8.22311;
	cd4_a1 = 0.318941;
    cd4_a2 = 0.983375;
    cd4_a3 = 1.669692;
    cd4_k = -6.572036;
	cd5_a1 = -0.12952;
    cd5_a2 = 0.73519;
    cd5_a3 = 1.92703;
    cd5_k = 38.70085;
	ce_a = 0.034733;
    ce_a0 = 1.417143;
    ce_a1 = 0.048163;
    ce_a2 = -0.543663;

	taux_accroissement =  Matrice(196,194);
	taux_accroissement = Matrice::Zero(196,194);
	coeff_depot1 =  Matrice(196,194);
	coeff_depot1 = Matrice::Zero(196,194);
	coeff_depot2 =  Matrice(196,194);
	coeff_depot2 = Matrice::Zero(196,194);
	coeff_depot3 =  Matrice(196,194);
	coeff_depot3 = Matrice::Zero(196,194);
	coeff_depot4 =  Matrice(196,194);
	coeff_depot4 = Matrice::Zero(196,194);
	coeff_depot5 =  Matrice(196,194);
	coeff_depot5 = Matrice::Zero(196,194);
	coeff_envol =  Matrice(196,194);
	coeff_envol = Matrice::Zero(196,194);
}

/** \fn Calcul_Lois::~Calcul_Lois()
 *  \brief Destructeur de la classe Calcul_Lois
 */
Calcul_Lois::~Calcul_Lois(){
	
}

/** \fn void Calcul_Lois::calcul_taux_accroissement(Matrice theta, Matrice stades)
 *  \brief Calcul la matrice du taux d'accroissement
 *  \param theta Matrice de températures 
 *  \param stade Matrice de stades phénologiques : vieillissement de la plante de 0 a 93
 *  \return Rien
 */
void Calcul_Lois::calcul_taux_accroissement(Matrice theta, Matrice stades){
    double num = 0;
    double den = 0;
	Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i = 0;i != mat.rows();i++){
		for(int j = 0;j != mat.cols();j++){
			if(theta(i,j) >= 30 || stades(i,j) >= 92){
				mat(i, j) = 0;
			}
            else{
				num = ta_a1*log(30-theta(i,j))+ta_a2*log(92-stades(i,j));
				den = 1+exp(-ta_k*(stades(i,j)-ta_sm))+exp(-ta_b*theta(i,j));
				mat(i, j) = num/den;
			}
		}
    }
    taux_accroissement = mat;
}

/** \fn void Calcul_Lois::calcul_coeffdepot1(Matrice p, Matrice eta)
 *  \brief Calcul du coefficient de dépôt 1
 *  \param p Proportion de blé dans la grille en 0 et 1
 *  \param eta Distribution des parcelles de blé entre -1 et 1
 *  \return Rien
 */
void Calcul_Lois::calcul_coeffdepot1(Matrice p, Matrice eta){
    Matrice mat(196,194);
	mat = Matrice::Zero(196,194);

    for(int i=0; i!=mat.rows(); i++){
		for(int j=0; j!=mat.cols(); j++){
			mat(i, j) = log(cd1_a1+cd1_a*(-(p(i,j)*p(i,j)+p(i,j))) *atan(cd1_k*eta(i,j))+cd1_a2*p(i,j));


		}
    }
    coeff_depot1 = mat;


}

/** \fn void Calcul_Lois::calcul_coeffdepot2(Matrice p, Matrice eta)
 *  \brief Calcul du coefficient de dépôt 2
 *  \param p Proportion de blé dans la grille en 0 et 1,
 *  \param eta Distribution des parcelles de blé entre -1 et 1
 *  \return Rien
 */
void Calcul_Lois::calcul_coeffdepot2(Matrice p, Matrice eta){
    double num = 0;
    double den = 0;
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);
	
    for(int i=0; i!=mat.rows(); i++){
		for(int j=0; j!=mat.cols(); j++){
			num = cd2_a4*exp(p(i,j))+cd2_a5*log(1+p(i,j));
			den = 1-cd2_a1*atan(cd2_k*eta(i,j))+exp(cd2_a2*(p(i,j)-cd2_a3));
			mat(i, j) = num/den;
		}
    }
    coeff_depot2 = mat;
}

/** \fn void Calcul_Lois::calcul_coeffdepot3(Matrice p, Matrice eta)
 *  \brief Calcul du coefficient de dépôt 3
 *  \param p Proportion de blé dans la grille en 0 et 1,
 *  \param eta Distribution des parcelles de blé entre -1 et 1
 *  \return Rien
 */
void Calcul_Lois::calcul_coeffdepot3(Matrice p, Matrice eta){
    Matrice mat(196,194);
	mat = Matrice::Zero(196,194);

    for(int i=0; i != mat.rows(); i++){
		for(int j=0; j != mat.cols(); j++){
			mat(i, j) = log(cd3_a2+cd3_a1*(p(i,j)-p(i,j)*p(i,j))*atan(cd3_k*eta(i,j)))+cd3_a3*p(i,j);
		}
    }
    coeff_depot3 = mat;
}

/** \fn void Calcul_Lois::calcul_coeffdepot4(Matrice p, Matrice eta)
 *  \brief Calcul du coefficient de dépôt 4
 *  \param p Proportion de blé dans la grille en 0 et 1,
 *  \param eta Distribution des parcelles de blé entre -1 et 1
 *  \return Rien
 */	
void Calcul_Lois::calcul_coeffdepot4(Matrice p, Matrice eta){
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i=0; i != mat.rows(); i++){
		for(int j=0; j != mat.cols(); j++){
			mat(i, j) = log(cd4_a2+cd4_a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(cd4_k*eta(i,j))+cd4_a3*p(i,j));
		}
    }
    coeff_depot4 = mat;
}

/** \fn void Calcul_Lois::calcul_coeffdepot5(Matrice p, Matrice eta)
 *  \brief Calcul du coefficient de dépôt 5
 *  \details Calcul la matrice des coeff depot5
 *  \param p Proportion de blé dans la grille en 0 et 1,
 *  \param eta Distribution des parcelles de blé entre -1 et 1
 *  \return Rien
 */
void Calcul_Lois::calcul_coeffdepot5(Matrice p, Matrice eta){
	
    Matrice mat(196,194);
    mat = Matrice::Zero(196,194);

    for(int i=0; i != mat.rows(); i++){
		for(int j=0; j != mat.cols(); j++){
			if (p(i,j)<0.5)
				mat(i, j) =  log(cd5_a2+cd5_a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(-cd5_k*eta(i,j))+cd5_a3*p(i,j)) ;
			else mat(i, j) = log(cd5_a2+cd5_a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(cd5_k*eta(i,j))+cd5_a3*p(i,j));
		}
    }
    coeff_depot5 = mat;
}

/** \fn void Calcul_Lois::calcul_coeff_envol(Matrice A, Matrice stades, Matrice theta, double a, double a0, double a1, double a2)
 *  \brief Calcul du coefficient d'envol
 *  \param A Matrice des pucerons ailés
 *  \param stades Matrice de stades phénologiques : vieillissement de la plante de 0 a 93
 *  \param theta Matrice de températures 
 *  \return Rien
 */
void Calcul_Lois::calcul_coeff_envol(Matrice A, Matrice stades, Matrice theta){
//cout<<theta;
int f = 0;
    double logN4 = 0;
    double phi_alpha2 = 0;
    Matrice mat(196,194);
	mat = Matrice::Zero(196,194);
double val =0;
    for(int i=0; i!=mat.rows(); i++){
		for(int j=0; j!=mat.cols(); j++){
	if (1+ A(i,j)<=0)
	A(i,j)=0;
	val = log(1+A(i,j));
            logN4=exp(ce_a*stades(i,j))/(1+exp(ce_a0+ce_a1*stades(i,j)+ce_a2*val));
/*if (f == 2230)
cout<<ce_a0+ce_a1*stades(i,j)<<"\n"<<ce_a2*log(1+A(i,j))<<"\n"<<1+A(i,j)<<"\n";*/
            phi_alpha2=2/( 1 + exp( - 0.1 * theta(i,j)))- 1;
            mat(i, j) = exp(logN4)*phi_alpha2;
/*if (f == 2230)
cout<<mat(i, j)<<"\n"<<logN4<<"\n"<<exp(logN4)<<"\n"<<phi_alpha2<<"\n";*/
f++;
		}
    }
    coeff_envol = mat;
//cout<< mat;
}

/** \fn void Calcul_Lois::set_constantes_taux_accroissement(double sm, double b, double k, double a1, double a2)
 *  \brief Mise à jour des constantes pour le calcul du taux d'accroissement
 *  \param double sm Coefficient constant pour calculer le taux d'accroissement
 *  \param double b Coefficient constant pour calculer le taux d'accroissement
 *  \param double k Coefficient constant pour calculer le taux d'accroissement
 *  \param double a1 Coefficient constant pour calculer le taux d'accroissement
 *  \param double a2 Coefficient constant pour calculer le taux d'accroissement
 *  \return Rien
 */
void Calcul_Lois::set_constantes_taux_accroissement(double sm, double b, double k, double a1, double a2){
	ta_sm = sm;
    ta_b = b;
    ta_k = k;
    ta_a1 = a1;
    ta_a2 = a2;
}

/** \fn void Calcul_Lois::set_constantes_coeffdepot1(double a, double a1, double a2, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 1
 *  \param a Coefficient constant pour calculer le coefficient de dépôt pour la loi 1
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 1
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 1
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 1
 *  \return Rien
 */
void Calcul_Lois::set_constantes_coeffdepot1(double a, double a1, double a2, double k){
	cd1_a1 = a1;
    cd1_a2 = a2;
    cd1_a = a;
    cd1_k = k;
}

/** \fn void Calcul_Lois::set_constantes_coeffdepot2(double a1, double a2, double a3, double a4, double a5, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 2
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param a3 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param a4 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param a5 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \return Rien
 */
void Calcul_Lois::set_constantes_coeffdepot2(double a1, double a2, double a3, double a4, double a5, double k){
	cd2_a1 = a1;
    cd2_a2 = a2;
    cd2_a3 = a3;
    cd2_a4 = a4;
    cd2_a5 = a5;
    cd2_k = k;
}

/** \fn void Calcul_Lois::set_constantes_coeffdepot3(double a1, double a2, double a3, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 3
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 3
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 3
 *  \param a3 Coefficient constant pour calculer le coefficient de dépôt pour la loi 3
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 3
 *  \return Rien
 */
void Calcul_Lois::set_constantes_coeffdepot3(double a1, double a2, double a3, double k){
	cd3_a1 = a1;
    cd3_a2 = a2;
    cd3_a3 = a3;
    cd3_k = k;
}

/** \fn void Calcul_Lois::set_constantes_coeffdepot4(double a1, double a2, double a3, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 4
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 4
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 4
 *  \param a3 Coefficient constant pour calculer le coefficient de dépôt pour la loi 4
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 4
 *  \return Rien
 */
void Calcul_Lois::set_constantes_coeffdepot4(double a1, double a2, double a3, double k){
	cd4_a1 = a1;
    cd4_a2 = a2;
    cd4_a3 = a3;
    cd4_k = k;
}

/** \fn void Calcul_Lois::set_constantes_coeffdepot5(double a1, double a2, double a3, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 5
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 5
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 5
 *  \param a3 Coefficient constant pour calculer le coefficient de dépôt pour la loi 5
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 5
 *  \return Rien
 */
void Calcul_Lois::set_constantes_coeffdepot5(double a1, double a2, double a3, double k){
	cd5_a1 = a1;
    cd5_a2 = a2;
    cd5_a3 = a3;
    cd5_k = k;
}

/** \fn void Calcul_Lois::set_constantes_coeff_envol(double a, double a0, double a1, double a2)
 *  \brief Mise à jour des constantes pour le calcul du coefficient d'envol
 *  \param a Coefficient constant pour calculer le coefficient d'envol 
 *  \param a0 Coefficient constant pour calculer le coefficient d'envol
 *  \param a1 Coefficient constant pour calculer le coefficient d'envol
 *  \param a2 Coefficient constant pour calculer le coefficient d'envol
 *  \return Rien
 */
void Calcul_Lois::set_constantes_coeff_envol(double a, double a0, double a1, double a2){
	ce_a = a;
    ce_a0 = a0;
    ce_a1 = a1;
    ce_a2 = a2;
}

/** \fn Matrice Calcul_Lois::get_taux_accroissement()
 *  \brief Retourne la matrice des taux d'accroissement
 *  \return taux_accroissement Matrice des taux d'accroissement
 */
Matrice  Calcul_Lois::get_taux_accroissement(){
	return taux_accroissement;
}

/** \fn Matrice Calcul_Lois::get_coeffdepot1()
 *  \brief Retourne la matrice coeff_depot1
 *  \return coeff_depot1 Matrice des coefficients de dépôt pour la loi 1
 */
Matrice  Calcul_Lois::get_coeffdepot1(){
	return coeff_depot1;
}

/** \fn Matrice Calcul_Lois::get_coeffdepot2()
 *  \brief Retourne la matrice coeff_depot2
 *  \return coeff_depot2 Matrice des coefficients de dépôt pour la loi 2
 */
Matrice  Calcul_Lois::get_coeffdepot2(){
	return coeff_depot2;
}
//////////////////////////////////////////////////////
/** \fn Matrice Calcul_Lois::get_coeffdepot3()
 *  \brief Retourne la matrice coeff_depot3
 *  \return coeff_depot3 Matrice des coefficients de dépôt pour la loi 3
 */
Matrice  Calcul_Lois::get_coeffdepot3(){
	return coeff_depot3;
}

/** \fn Matrice Calcul_Lois::get_coeffdepot4()
 *  \brief Retourne la matrice coeff_depot4
 *  \return coeff_depot4 Matrice des coefficients de dépôt pour la loi 4
 */
Matrice  Calcul_Lois::get_coeffdepot4(){
	return coeff_depot4;
}

/** \fn Matrice Calcul_Lois::get_coeffdepot5() 
 *  \brief Retourne la matrice coeff_depot5
 *  \return coeff_depot5 Matrice des coefficients de dépôt pour la loi 5
 */
Matrice  Calcul_Lois::get_coeffdepot5(){
	return coeff_depot5;
}

/** \fn Matrice Calcul_Lois::get_coeff_envol()
 *  \brief Retourne la matrice coeff_envol
 *  \return coeff_envol Matrice des coefficients d'envol
 */
Matrice  Calcul_Lois::get_coeff_envol(){
	return coeff_envol;
}

