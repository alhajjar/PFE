/** 
 * \file Controleur_Simulation.hpp
 * \brief Fichier d'entête de la bibliotheque gérant une simulation 
*/

#ifndef __CONTROLEUR_SIMULATION__
#define __CONTROLEUR_SIMULATION__

#include "allincludes.hpp"
#include "Lecture_Ecriture.hpp"
#include "Calcul_Lois.hpp"
#include "Calcul_Matrice.hpp"
#include "Voronoi.hpp"
#include <stdexcept>

#define NB_LIGNES 197
#define NB_COLONNES 194

/** \class Controleur_Simulation
 *  \brief Classe gérant une simulation
 */
class Controleur_Simulation
{

public :
	__declspec(dllexport) Controleur_Simulation();
	__declspec(dllexport) ~Controleur_Simulation();

	__declspec(dllexport) void initialisation(double k, double h, string CSV_mat_C, string CSV_mat_A, string CSV_p, string CSV_eta, string CSV_coord_stades,
						int nbligneCSV_coord_s, int nbcolonneCSV_coord_s, string CSV_data_stades, int nbligneCSV_data_s, int nbcolonneCSV_data_s,
						string CSV_coord_temp, int nbligneCSV_coord_t, int nbcolonneCSV_coord_t, string CSV_data_temp, int nbligneCSV_data_t,
						int nbcolonneCSV_data_t, string CSV_mat_D, string CSV_mat_vitesse_h, string CSV_mat_vitesse_v, int meteo, int pression);
	__declspec(dllexport) void iteration(int jour);
	__declspec(dllexport) void affiche();
	__declspec(dllexport) void affiche_bloc(int abscisse_point,int coordonnee_point,int nbligne,int nbcolonne); 
	
	static __declspec(dllexport) double **taux_accroissement(double stade, double sm, double b, double k, double a1, double a2);
	static __declspec(dllexport) double **coeff_envol(int stade, double a, double a0, double a1, double a2);
	
	__declspec(dllexport) Matrice get_mat_D();
	__declspec(dllexport) Matrice get_mat_vitesse_h();
	__declspec(dllexport) Matrice get_mat_vitesse_v();
	__declspec(dllexport) Matrice get_mat_C();
	__declspec(dllexport) Matrice get_mat_A();
	__declspec(dllexport) Matrice get_mat_A_retourne();
	__declspec(dllexport) Matrice get_mat_C_retourne();
	
	__declspec(dllexport) void set_mat_A(Matrice mat);
	__declspec(dllexport) void set_mat_C(Matrice mat);

	__declspec(dllexport) void  set_constantes_taux_accroissement(double sm, double b, double k, double a1, double a2);
	__declspec(dllexport) void  set_constantes_coeffdepot1( double a, double a1, double a2, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot2(double a1, double a2, double a3, double a4, double a5, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot3(double a1, double a2, double a3, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot4( double a1, double a2, double a3, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot5_inf(double a1, double a2, double a3, double k);
	__declspec(dllexport) void  set_constantes_coeffdepot5_sup(double a1, double a2, double a3, double k);
	__declspec(dllexport) void  set_constantes_coeff_envol( double a, double a0, double a1, double a2);

private :
	Matrice mat_A;
	Matrice mat_C;
	Matrice mat_A_demi;
	Matrice mat_C_demi;
	Matrice m_p;
	Matrice m_eta;
	Matrice m_vitesse_v;
	Matrice m_vitesse_h;
	Matrice m_D;
	
	double k;
	double h;
	int choix_meteo;
	int choix_pression;
	Voronoi voronoistades;
	Voronoi voronoitheta;
	
	Calcul_Lois calcul_lois;
	Lecture_Ecriture lect;
    Calcul_Matrice calculmatrice;


};

#endif
