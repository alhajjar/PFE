/** 
 * \file Calcul_Lois.hpp
 * \brief Fichier d'entête de la bibliothèque des calculs des différentes lois de diffusion/multiplication
*/

#ifndef __CALCUL_LOIS__
#define __CALCUL_LOIS__


#include "allincludes.hpp"

/** \class Calcul_Lois
  * \brief Classe effectuant les calculs des différentes lois de diffusion/multiplication
  */
class Calcul_Lois
{
public :
	__declspec(dllexport)  Calcul_Lois();
	__declspec(dllexport) ~Calcul_Lois();

	__declspec(dllexport) void calcul_taux_accroissement(Matrice theta, Matrice stades, int choix_meteo, int choix_pression);
	__declspec(dllexport) void calcul_coeffdepot1(Matrice p, Matrice eta);
	__declspec(dllexport) void calcul_coeffdepot2(Matrice p, Matrice eta);
	__declspec(dllexport) void calcul_coeffdepot3(Matrice p, Matrice eta);
	__declspec(dllexport) void calcul_coeffdepot4(Matrice p, Matrice eta);
	__declspec(dllexport) void calcul_coeffdepot5(Matrice p, Matrice eta);
	__declspec(dllexport) void calcul_coeff_envol(Matrice A,Matrice stades,Matrice theta);
		
	__declspec(dllexport) void  set_constantes_taux_accroissement(double sm, double b, double k, double a1, double a2);
	__declspec(dllexport) void  set_constantes_coeffdepot1( double a, double a1, double a2, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot2(double a1, double a2, double a3, double a4, double a5, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot3(double a1, double a2, double a3, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot4( double a1, double a2, double a3, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot5_inf(double a1, double a2, double a3, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot5_sup(double a1, double a2, double a3, double k);
	__declspec(dllexport) void  set_constantes_coeff_envol( double a, double a0, double a1, double a2);
		
	__declspec(dllexport) Matrice  get_taux_accroissement();
	__declspec(dllexport) Matrice  get_coeffdepot1();
	__declspec(dllexport) Matrice  get_coeffdepot2();
	__declspec(dllexport) Matrice  get_coeffdepot3();
	__declspec(dllexport) Matrice  get_coeffdepot4();
	__declspec(dllexport) Matrice  get_coeffdepot5();
	__declspec(dllexport) Matrice  get_coeff_envol();
	
private :
	Matrice taux_accroissement;
	Matrice coeff_depot1;
	Matrice coeff_depot2;
	Matrice coeff_depot3;
	Matrice coeff_depot4;
	Matrice coeff_depot5;
	Matrice coeff_envol;

/* Constantes taux d'accroissement */	
	double ta_sm;
    double ta_b;
    double ta_k;
    double ta_a1;
    double ta_a2;
/* Constantes coefficient dépôt 1 */
	double cd1_a1;
    double cd1_a2;
    double cd1_a;
    double cd1_k;
/* Constantes coefficient dépôt 2 */	
	double cd2_a1;
    double cd2_a2;
    double cd2_a3;
    double cd2_a4;
    double cd2_a5;
    double cd2_k;
/* Constantes coefficient dépôt 3 */	
	double cd3_a1;
    double cd3_a2;
    double cd3_a3;
    double cd3_k;
/* Constantes coefficient dépôt 4 */	
	double cd4_a1;
    double cd4_a2;
    double cd4_a3;
    double cd4_k;
/* Constantes coefficient dépôt 5 avec p < 0.5 */	
	double cd5_inf_a1;
    double cd5_inf_a2;
    double cd5_inf_a3;
    double cd5_inf_k;
/* Constantes coefficient dépôt 5 avec p >= 0.5 */	
	double cd5_sup_a1;
    double cd5_sup_a2;
    double cd5_sup_a3;
    double cd5_sup_k;
/* Constantes coefficient d'envol */	
	double ce_a;
    double ce_a0;
    double ce_a1;
    double ce_a2;
};

#endif
		
		
		
		
		
	
