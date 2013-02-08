/** 
  * \file Controleur_Simulation.cpp
  * \brief Fichier permettant la gestion d'une simulation
  */

#include "Includes/Controleur_Simulation.hpp"

/** \fn Controleur_Simulation::Controleur_Simulation()
 *  \brief Constructeur de la classe Controleur_Simulation
 */
Controleur_Simulation::Controleur_Simulation(){
	int  m = 197;
	int n = 194;
	mat_A = Matrice(m-1,n);
	mat_A = Matrice::Zero(196,194);
	mat_C = Matrice(m-1,n);
	mat_C = Matrice::Zero(196,194);
	mat_A_demi = Matrice(m-1,n);
	mat_A_demi = Matrice::Zero(196,194);
	mat_C_demi = Matrice(m-1,n);
	mat_C_demi = Matrice::Zero(196,194);
};

/** \fn Controleur_Simulation::~Controleur_Simulation()
 *  \brief Destructeur de la classe Controleur_Simulation
 */
Controleur_Simulation::~Controleur_Simulation(){
};


/** \fn void Controleur_Simulation::initialisation(double k, double h, string CSV_mat_C, string CSV_mat_A, string CSV_p, string CSV_eta, string CSV_coord_stades,
		int nbligneCSV_coord_s, int nbcolonneCSV_coord_s, string CSV_data_stades, int nbligneCSV_data_s, int nbcolonneCSV_data_s,
		string CSV_coord_temp, int nbligneCSV_coord_t, int nbcolonneCSV_coord_t, string CSV_data_temp, int nbligneCSV_data_t, int nbcolonneCSV_data_t)
 *  \brief Initialisation de la Controleur_Simulation
 *  \param k Pas d'espace
 *  \param h Pas de temps
 *  \param CSV_mat_C Chemin du fichier d'initialisation de la matrice des ailés \c mat_C
 *  \param CSV_mat_A Chemin du fichier d'initialisation de la matrice des aptères \c mat_A
 *  \param CSV_p Chemin du fichier de la matrice de proportion de blé \c mat_p
 *  \param CSV_eta Chemin du fichier de la matrice des données de proportion de blé \c eta
 *  \param CSV_coord_stades Chemin du fichier des coordonnées de la matrice des stades phénologiques \c coord_s
 *  \param nbligneCSV_coord_s Nombre de lignes à récupérer dans le fichier CSV des coordonnées de la matrice des stades phénologiques \c coord_s
 *  \param nbcolonneCSV_coord_s Nombre de colonnes à récupérer dans le fichier CSV  des coordonnées de la matrice des stades phénologiques \c coord_s
 *  \param CSV_data_stades Chemin du fichier des données de la matrice des stades phénologiques \c data_s
 *  \param nbligneCSV_data_s Nombre de lignes à récupérer dans le fichier CSV des données de la matrice des stades phénologiques \c data_s
 *  \param nbcolonneCSV_data_s Nombre de colonnes à récupérer dans le fichier CSV des données de la matrice des stades phénologiques \c data_s
 *  \param CSV_coord_temp Chemin du fichier des coordonnées de la matrice des températures theta
 *  \param nbligneCSV_coord_t Nombre de lignes à récupérer dans le fichier CSV des coordonnées de la matrice des températures theta
 *  \param nbcolonneCSV_coord_t Nombre de colonnes à récupérer dans le fichier CSV des coordonnées de la matrice des températures theta
 *  \param CSV_data_temp Chemin du fichier des données de la matrice des températures theta
 *  \param nbligneCSV_data_t Nombre de lignes à récupérer dans le fichier CSV des données de la matrice des températures theta
 *  \param nbcolonneCSV_data_t Nombre de colonnes à récupérer dans le fichier CSV des données de la matrice des températures theta
 *  \param meteo Indice du choix de la météo qui influe sur le taux d'accroissement
 *  \param pression Indice du choix de la pression des ennemis qui influe sur le taux d'accroissement
 *  \return Rien
 */
void Controleur_Simulation::initialisation(double k1, double h1, string CSV_mat_C, string CSV_mat_A, string CSV_p, string CSV_eta, string CSV_coord_stades,
								int nbligneCSV_coord_s, int nbcolonneCSV_coord_s, string CSV_data_stades, int nbligneCSV_data_s, int nbcolonneCSV_data_s,
								string CSV_coord_temp, int nbligneCSV_coord_t, int nbcolonneCSV_coord_t, string CSV_data_temp, int nbligneCSV_data_t,
								int nbcolonneCSV_data_t, string CSV_mat_D, string CSV_vitesse_h, string CSV_vitesse_v, int meteo, int pression){
	m_eta = Matrice(NB_LIGNES-1, NB_COLONNES);
	m_eta = Matrice::Zero(196,194);
	m_p = Matrice(NB_LIGNES-1, NB_COLONNES);
	m_p = Matrice::Zero(196,194);
	m_D = Matrice(NB_LIGNES-1, NB_COLONNES);
	m_D = Matrice::Zero(196,194);
	m_vitesse_h = Matrice(NB_LIGNES-1, NB_COLONNES);
	m_vitesse_h = Matrice::Zero(196,194);
	m_vitesse_v = Matrice(NB_LIGNES-1, NB_COLONNES);
	m_vitesse_v = Matrice::Zero(196,194);

	cout << "\n"
	<< "\t"
	<< "===================\n"
	<< "\t"
	<< "= " << "Initialisation "
	<< " ="
	<< "\n"
	<< "\t" << "===================\n";
  
	voronoistades = Voronoi(CSV_coord_stades, nbligneCSV_coord_s, nbcolonneCSV_coord_s, CSV_data_stades, nbligneCSV_data_s, nbcolonneCSV_data_s);

	voronoitheta = Voronoi(CSV_coord_temp, nbligneCSV_coord_t, nbcolonneCSV_coord_t, CSV_data_temp, nbligneCSV_data_t, nbcolonneCSV_data_t);

	lect.LectureCSV(NB_LIGNES, NB_COLONNES, CSV_eta);
	m_eta = lect.get_CSV();

	lect.LectureCSV(NB_LIGNES, NB_COLONNES, CSV_p);
	m_p = lect.get_CSV();

	lect.LectureCSV(NB_LIGNES, NB_COLONNES, CSV_mat_A);
	calculmatrice.set_mat_A(lect.get_CSV());
	mat_A = lect.get_CSV();
	lect.LectureCSV(NB_LIGNES, NB_COLONNES, CSV_mat_C);
	calculmatrice.set_mat_C(lect.get_CSV());
	mat_C = lect.get_CSV();

	lect.LectureCSV(NB_LIGNES, NB_COLONNES, CSV_mat_D);
	m_D = lect.get_CSV();

	lect.LectureCSV(NB_LIGNES, NB_COLONNES, CSV_vitesse_h);
	m_vitesse_h = lect.get_CSV();

	lect.LectureCSV(NB_LIGNES, NB_COLONNES, CSV_vitesse_v);
	 m_vitesse_v = lect.get_CSV();

    calcul_lois.calcul_coeffdepot1(m_p, m_eta);
    calcul_lois.calcul_coeffdepot2(m_p, m_eta);

    calculmatrice.matriceN1(h1, k1, m_D, calcul_lois.get_coeffdepot1(), m_vitesse_h);
    cout << "\nFin du calcul de la matrice tridiagonale N1\n";
    calculmatrice.matriceN3(h1, k1, m_D, calcul_lois.get_coeffdepot1(), m_vitesse_v);
    cout << "\nFin du calcul de la matrice tridiagonale N3\n";

	k = k1;
	h = h1;

	choix_meteo = meteo;
	choix_pression = pression;
}

/** \fn void Controleur_Simulation::iteration(int jour)
 *  \brief Effectue un jour de Controleur_Simulation
 *  \param jour Jour d'une itération de la Controleur_Simulation. Ex: 60ème jour de simulation
 *  \return Rien
 */
void Controleur_Simulation::iteration(int jour){
	cout << "\n"
	<< "\t"
	<< "=======================\n"
	<< "\t"
	<< "= "<< "Iteration numero :"
	<< jour
	<< " ="
	<< "\n"
	<< "\t" << "=======================\n";

	voronoistades.iteration(jour);
	voronoitheta.iteration(jour);
	calcul_lois.calcul_taux_accroissement(voronoitheta.get_Matrice_Finale(), voronoistades.get_Matrice_Finale(), choix_meteo, choix_pression);

	calcul_lois.calcul_coeff_envol(mat_A, voronoitheta.get_Matrice_Finale(), m_eta);
	calculmatrice.inverseN2N4(k, calcul_lois.get_taux_accroissement(), calcul_lois.get_coeff_envol());
	cout << "\nFin du calcul de la matrice inverse de N2 et de N4\n";

	cout << "\nCalcul de la matrice des ailes pour un demi_pas\n";	
	calculmatrice.Resolution_ailes_demi_pas(h, mat_A, mat_C, calcul_lois.get_coeffdepot2(), calculmatrice.get_N1());
	cout << "\nFin du calcul de la matrice des ailes pour un demi_pas\n";
	cout << "\nCalcul de la matrice des apteres pour un demi_pas\n";
	calculmatrice.Resolution_apteres_demi_pas (h, mat_A, mat_C, calcul_lois.get_coeff_envol(), calculmatrice.get_inverse_N2());
	cout << "\nFin du calcul de la matrice des apteres pour un demi_pas\n";
	mat_C_demi = calculmatrice.get_mat_C_demi();
	mat_A_demi = calculmatrice.get_mat_A_demi();

	cout << "\nCalcul de la matrice des ailes pour un pas_entier\n";
	calculmatrice.Resolution_ailes_pas_entier(k, mat_A_demi, mat_C_demi, calcul_lois.get_coeffdepot2(), calculmatrice.get_N3());
	cout << "\nFin du calcul de la matrice des ailes pour un pas_entier\n";
	cout << "\nCalcul de la matrice des apteres pour un pas_entier\n";
	calculmatrice.Resolution_apteres_pas_entier(k, mat_A_demi, mat_C_demi, calcul_lois.get_coeff_envol(), calculmatrice.get_inverse_N2());
	cout << "\nFin du calcul de la matrice des apteres pour pas_entier\n";
	mat_C = calculmatrice.get_mat_C();
	mat_A = calculmatrice.get_mat_A();
}

/** \fn static double **Controleur_Simulation::taux_accroissement(int stade, double sm, double b, double k, double a1, double a2)
 *  \brief Calcul du taux d'accroissement pour en visualiser la forme sur 30 valeurs de theta
 *  \param int stade Stade phénologique pour calculer la forme du taux d'accroissement
 *  \param double sm Coefficient constant pour calculer la forme du taux d'accroissement
 *  \param double b Coefficient constant pour calculer la forme du taux d'accroissement
 *  \param double k Coefficient constant pour calculer la forme du taux d'accroissement
 *  \param double a1 Coefficient constant pour calculer la forme du taux d'accroissement
 *  \param double a2 Coefficient constant pour calculer la forme du taux d'accroissement
 *  \return Rien
 */
 double **Controleur_Simulation::taux_accroissement(double stade, double sm, double b, double k, double a1, double a2){
	double **mat = new double*[30];
	for(int i=0; i < 30; i++){
        mat[i] = new double [2];
	}

    double num = 0;
    double den = 0;

    for(int i = 0; i<30; i++){
		mat[i][0] = i;
		num = a1 * log(30 - mat[i][0]) + a2 * log(92 - stade);
		den = 1 + exp(-k * (stade - sm)) + exp(-b * mat[i][0]);
		mat[i][1] = num/den;
    }
    return mat;
}

/** \fn static double **Controleur_Simulation::coeff_envol(int stade, double a, double a0, double a1, double a2)
 *  \brief Calcul du coefficient d'envol pour en visualiser la forme sur 30 valeurs de theta
 *  \param int stade Stade phénologique pour calculer la forme du coefficient d'envol
 *  \param double a Coefficient constant pour calculer la forme du coefficient d'envol
 *  \param double a0 Coefficient constant pour calculer la forme du coefficient d'envol
 *  \param double a1 Coefficient constant pour calculer la forme du coefficient d'envol
 *  \param double a2 Coefficient constant pour calculer la forme du coefficient d'envol
 *  \return Rien
 */
 double **Controleur_Simulation::coeff_envol(int stade, double a, double a0, double a1, double a2){
	double **mat = new double*[30];
	for(int i=0; i<30; i++){
        mat[i] = new double [2];
	}

    double logN4 = 0;
    double phi_alpha2 = 0;
    double A = 10000;

    for(int i=0; i<30; i++){
		mat[i][0] = i + 1;
		logN4 = exp(a * stade)/(1 + exp(a0 + a1 * stade + a2 * log(1 + A)));
		phi_alpha2 = 2/( 1 + exp( - 0.1 * mat[i][0])) - 1;
		mat[i][1] = exp(logN4) * phi_alpha2;
    }
    return mat;
}

/** \fn void Controleur_Simulation::affiche_bloc()
 *  \brief Affiche un bloc des matrices d'aptères et d'ailés
 *  \param abscisse_point Abscisse de la coordonnée du début des éléments à afficher
 *  \param coordonnee_point Ordonnée de la coordonnée du début des éléments à afficher
 *  \param nbligne Nombre de lignes qui doit être affiché
 *  \param nbcolonne Nombre de colonnes qui doit être affiché
 *  \return Rien
 */
void Controleur_Simulation::affiche_bloc (int abscisse_point,int coordonnee_point,int nbligne,int nbcolonne){
	cout << "\nPremiere ligne de la matrice des apteres A est :\n";
	cout << get_mat_A().block( abscisse_point, coordonnee_point, nbligne, nbcolonne);
	cout << "\n=========================================================\n";
	cout << "\nPremiere ligne de la matrice des ailes C est :\n"; 
	cout << get_mat_C().block(abscisse_point, coordonnee_point, nbligne, nbcolonne) << "\n";
}

/** \fn void Controleur_Simulation::affiche()
 *  \brief Affiche les matrices d'aptères et d'ailés
 *  \return Rien
 */
void Controleur_Simulation::affiche(){
	cout << "\nLa matrice des apteres A est :\n";
	cout << get_mat_A()<<"\n";
	cout << "=========================================================\n";
	cout << "\nLa matrice des ailes C est :\n";
	cout << get_mat_C() << "\n";
}

/** \fn Matrice Controleur_Simulation::get_mat_A()
 *  \brief Retourne la matrice des aptères
 *  \return mat_A Matrice des aptères
 */
Matrice Controleur_Simulation::get_mat_A(){
	return mat_A;
}

/** \fn Matrice Controleur_Simulation::get_mat_C()
 *  \brief Retourne la matrice des ailés
 *  \return mat_C Matrice des ailés
 */
Matrice Controleur_Simulation::get_mat_C(){
	return mat_C;
}

/** \fn Matrice Controleur_Simulation::get_mat_D()
 *  \brief Retourne la matrice de diffusion
 *  \return m_D Matrice de diffusion
 */
Matrice Controleur_Simulation::get_mat_D(){
	return m_D;
}

/** \fn Matrice Controleur_Simulation::get_mat_vitesse_h()
 *  \brief Retourne la matrice de vent pour le pas horizontal
 *  \return m_vitesse_h Matrice de vent pour le pas horizontal
 */
Matrice Controleur_Simulation::get_mat_vitesse_h(){
	return m_vitesse_h;
}

/** \fn Matrice Controleur_Simulation::get_mat_vitesse_v()
 *  \brief Retourne la matrice de vent pour le pas vertical
 *  \return m_vitesse_v Matrice de vent pour le pas vertical
 */
Matrice Controleur_Simulation::get_mat_vitesse_v(){
	return m_vitesse_v;
}

/** \fn void Controleur_Simulation::set_mat_A(Matrice mat)
 *  \brief Mise à jour de la matrice des aptères
 *  \param mat Matrice des aptères
 *  \return Rien
 */
void Controleur_Simulation::set_mat_A(Matrice mat){
	mat_A = mat;
};

/** \fn void Controleur_Simulation::set_mat_C(Matrice mat)
 *  \brief Mise à jour de la matrice des ailés
 *  \param mat Matrice des ailés
 *  \return Rien
 */
void Controleur_Simulation::set_mat_C(Matrice mat){
	mat_C = mat;
};

/** \fn Matrice Controleur_Simulation::get_mat_A_retourne()
 *  \brief Retourne la matrice des aptères avec une rotation de 90° en adéquation avec le sens de la carte de France
 *  \return mat_A_retourne Matrice des aptères retournée
 */
Matrice Controleur_Simulation::get_mat_A_retourne(){
	Matrice mat_A_retourne(194, 196);
	for(int u=0; u < 196; u++){
		for(int v=0; v < 194; v++){
			mat_A_retourne(193 -v, u) = mat_A(u,v);
		}
	}
	return mat_A_retourne;
}

/** \fn Matrice Controleur_Simulation::get_mat_C_retourne()
 *  \brief Retourne la matrice des ailés avec une rotation de 90° en adéquation avec le sens de la carte de France
 *  \return mat_C_retourne Matrice des ailés retournée
 */
Matrice Controleur_Simulation::get_mat_C_retourne(){
	Matrice mat_C_retourne(194, 196);
	for(int u=0; u < 196; u++){
		for(int v=0; v < 194; v++){
			mat_C_retourne(193 -v, u) = mat_C(u,v);
		}
	}
	return mat_C_retourne;
}

/** \fn void Controleur_Simulation::set_constantes_taux_accroissement(double sm, double b, double k, double a1, double a2)
 *  \brief Mise à jour des constantes pour le calcul du taux d'accroissement
 *  \param double sm Coefficient constant pour calculer le taux d'accroissement
 *  \param double b Coefficient constant pour calculer le taux d'accroissement
 *  \param double k Coefficient constant pour calculer le taux d'accroissement
 *  \param double a1 Coefficient constant pour calculer le taux d'accroissement
 *  \param double a2 Coefficient constant pour calculer le taux d'accroissement
 *  \return Rien
 */
void Controleur_Simulation::set_constantes_taux_accroissement(double sm, double b, double k, double a1, double a2){
	calcul_lois.set_constantes_taux_accroissement(sm, b, k, a1, a2);
}

/** \fn void Controleur_Simulation::set_constantes_coeffdepot1(double a, double a1, double a2, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 1
 *  \param a Coefficient constant pour calculer le coefficient de dépôt pour la loi 1
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 1
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 1
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 1
 *  \return Rien
 */
void Controleur_Simulation::set_constantes_coeffdepot1(double a, double a1, double a2, double k){
	calcul_lois.set_constantes_coeffdepot1(a, a1, a2, k);
}

/** \fn void Controleur_Simulation::set_constantes_coeffdepot2(double a1, double a2, double a3, double a4, double a5, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 2
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param a3 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param a4 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param a5 Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 2
 *  \return Rien
 */
void Controleur_Simulation::set_constantes_coeffdepot2(double a1, double a2, double a3, double a4, double a5, double k){
	calcul_lois.set_constantes_coeffdepot2(a1, a2, a3, a4, a5, k);
}

/** \fn void Controleur_Simulation::set_constantes_coeffdepot3(double a1, double a2, double a3, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 3
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 3
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 3
 *  \param a3 Coefficient constant pour calculer le coefficient de dépôt pour la loi 3
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 3
 *  \return Rien
 */
void Controleur_Simulation::set_constantes_coeffdepot3(double a1, double a2, double a3, double k){
	calcul_lois.set_constantes_coeffdepot3(a1, a2, a3, k);
}

/** \fn void Controleur_Simulation::set_constantes_coeffdepot4(double a1, double a2, double a3, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 4
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 4
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 4
 *  \param a3 Coefficient constant pour calculer le coefficient de dépôt pour la loi 4
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 4
 *  \return Rien
 */
void Controleur_Simulation::set_constantes_coeffdepot4(double a1, double a2, double a3, double k){
	calcul_lois.set_constantes_coeffdepot4(a1, a2, a3, k);
}

/** \fn void Controleur_Simulation::set_constantes_coeffdepot5_inf(double a1, double a2, double a3, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 5 avec p < 0.5
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 5 avec p < 0.5
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 5 avec p < 0.5
 *  \param a3 Coefficient constant pour calculer le coefficient de dépôt pour la loi 5 avec p < 0.5
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 5 avec p < 0.5
 *  \return Rien
 */
void Controleur_Simulation::set_constantes_coeffdepot5_inf(double a1, double a2, double a3, double k){
	calcul_lois.set_constantes_coeffdepot5_inf(a1, a2, a3, k);
}

/** \fn void Controleur_Simulation::set_constantes_coeffdepot5_sup(double a1, double a2, double a3, double k)
 *  \brief Mise à jour des constantes pour le calcul du coefficient de dépôt pour la loi 5 avec p >= 0.5
 *  \param a1 Coefficient constant pour calculer le coefficient de dépôt pour la loi 5 avec p >= 0.5
 *  \param a2 Coefficient constant pour calculer le coefficient de dépôt pour la loi 5 avec p >= 0.5
 *  \param a3 Coefficient constant pour calculer le coefficient de dépôt pour la loi 5 avec p >= 0.5
 *  \param k Coefficient constant pour calculer le coefficient de dépôt pour la loi 5 avec p >= 0.5
 *  \return Rien
 */
void Controleur_Simulation::set_constantes_coeffdepot5_sup(double a1, double a2, double a3, double k){
	calcul_lois.set_constantes_coeffdepot5_sup(a1, a2, a3, k);
}

/** \fn void Controleur_Simulation::set_constantes_coeff_envol(double a, double a0, double a1, double a2)
 *  \brief Mise à jour des constantes pour le calcul du coefficient d'envol
 *  \param a Coefficient constant pour calculer le coefficient d'envol 
 *  \param a0 Coefficient constant pour calculer le coefficient d'envol
 *  \param a1 Coefficient constant pour calculer le coefficient d'envol
 *  \param a2 Coefficient constant pour calculer le coefficient d'envol
 *  \return Rien
 */
void Controleur_Simulation::set_constantes_coeff_envol(double a, double a0, double a1, double a2){
	calcul_lois.set_constantes_coeff_envol(a, a0, a1, a2);
}