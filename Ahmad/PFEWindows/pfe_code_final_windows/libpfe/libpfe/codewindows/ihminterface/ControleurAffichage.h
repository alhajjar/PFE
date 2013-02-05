/**
 * \file ControleurAffichage.h
 * \brief fichier d'entete de la bibliotheque du controle de l'interface graphique
 */

#ifndef CONTROLEUR_AFFICHAGE_H
#define CONTROLEUR_AFFICHAGE_H

#include <gtkmm.h>
#include <iostream>
#include "Dessin.h"
#include "Courbe.h"
#include "ImpressionOperation.h"
#include "Includes/Lecture_Ecriture.hpp"
#include "Includes/Simulation.hpp"

using namespace std;

class ControleurAffichage
{
private:
/* Indice des choix (0, 1 ou 2) de la meteo et de la pression des ennemis */
	int meteo;
	int pression_ennemis;
	int nb_jour_simulation;

/* Chemins des fichiers à charger ou que l'on sauvegarde */
	string cheminOuvertureCarte;
	string cheminSauvegardeAptere;
	string cheminSauvegardeAile;
	
/* Elements de l'interface graphique avec lesquels il y a interaction */
	Gtk::Window* pFenetre;
	Gtk::HBox* pCadre;
	Gtk::ImageMenuItem* pMenuQuitter;
	Gtk::ImageMenuItem* pMenuOuvrir;
	Gtk::ImageMenuItem* pMenuSauvegarder;
	Gtk::ImageMenuItem* pMenuAide;
	Gtk::ImageMenuItem* pMenuImprimer;
	Gtk::FileChooserDialog* pChoixFichierOuvrir;
	Gtk::FileChooserDialog* pChoixFichierSauvegarderAptere;
	Gtk::FileChooserDialog* pChoixFichierSauvegarderAile;
	Gtk::Label* pCheminOuvertureCarte;
	Gtk::Label* pCheminSauvegardeCarteAptere;
	Gtk::Label* pCheminSauvegardeCarteAile;
	Gtk::Button* pBoutonAnnulerOuvrir;
	Gtk::Button* pBoutonAccepterOuvrir;
	Gtk::Button* pBoutonAnnulerSauvegarderAptere;
	Gtk::Button* pBoutonAccepterSauvegarderAptere;
	Gtk::Button* pBoutonAnnulerSauvegarderAile;
	Gtk::Button* pBoutonAccepterSauvegarderAile;
	Gtk::Button* pBoutonLancerSimulation;
	Gtk::Button* pBoutonSimulationSuivante;
	Gtk::Button* pBoutonSimulationPrecedente;
	Gtk::Button* pBoutonAllerNumeroSimulation;
	Gtk::RadioButton* pRadioMeteoFavorable;
	Gtk::RadioButton* pRadioMeteoNormale;
	Gtk::RadioButton* pRadioMeteoDefavorable;
	Gtk::RadioButton* pRadioPressionEnnemisNulle;
	Gtk::RadioButton* pRadioPressionEnnemisNormale;
	Gtk::RadioButton* pRadioPressionEnnemisForte;
	Gtk::MessageDialog* pAvertissementCheminFichierOuverture;
	Gtk::MessageDialog* pAvertissementCheminFichiersSauvegarde;
	Gtk::MessageDialog* pAvertissementImpression;
	Gtk::Button* pBoutonAvertissementCheminFichierOuverture;
	Gtk::Button* pBoutonAvertissementCheminFichiersSauvegarde;
	Gtk::Button* pBoutonAvertissementImpression;
	Gtk::Notebook* pOnglets;
	Gtk::Image* pImageMeteo;
	Gtk::Image* pImagePressionEnnemis;
	Gtk::Button* pBoutonOuvrir;
	Gtk::Button* pBoutonSauvegarder;
	Gtk::Button* pBoutonImprimer;
	Gtk::Button* pBoutonQuitter;
	Gtk::Button* pBoutonAide;
	Gtk::VBox* pCadreCoeffEnvol;
	Gtk::VBox* pCadreTauxAccroissement;
	Gtk::Entry* pNb_jour_simu;
	Gtk::Entry* pTa_sm;
	Gtk::Entry* pTa_b;
	Gtk::Entry* pTa_k;
	Gtk::Entry* pTa_a1;
	Gtk::Entry* pTa_a2;
	Gtk::Entry* pCd1_a1;
	Gtk::Entry* pCd1_a2;
	Gtk::Entry* pCd1_a;
	Gtk::Entry* pCd1_k;
	Gtk::Entry* pCd2_a1;
	Gtk::Entry* pCd2_a2;
	Gtk::Entry* pCd2_a3;
	Gtk::Entry* pCd2_a4;
	Gtk::Entry* pCd2_a5;
	Gtk::Entry* pCd2_k;
	Gtk::Entry* pCd3_a1;
	Gtk::Entry* pCd3_a2;
	Gtk::Entry* pCd3_a3;
	Gtk::Entry* pCd3_k;
	Gtk::Entry* pCd4_a1;
	Gtk::Entry* pCd4_a2;
	Gtk::Entry* pCd4_a3;
	Gtk::Entry* pCd4_k;
	Gtk::Entry* pCd5_inf_a1;
	Gtk::Entry* pCd5_inf_a2;
	Gtk::Entry* pCd5_inf_a3;
	Gtk::Entry* pCd5_inf_k;
	Gtk::Entry* pCd5_sup_a1;
	Gtk::Entry* pCd5_sup_a2;
	Gtk::Entry* pCd5_sup_a3;
	Gtk::Entry* pCd5_sup_k;
	Gtk::Entry* pCe_a;
	Gtk::Entry* pCe_a0;
	Gtk::Entry* pCe_a1;
	Gtk::Entry* pCe_a2;
	Dessin carte_A;
	Dessin carte_C;
	Courbe courbe_coeff_envol;
	Courbe courbe_taux_accroissement;
	
	double string_to_double(const std::string& s);
	
public:
	ControleurAffichage(string);
	virtual ~ControleurAffichage();

/* Methode qui connecte les signaux a leur call-back */	
	void connecter_signaux();
	
/* Methode qui permet de recuperer la fenetre a afficher */
	Gtk::Window* get_fenetre();
	
/* Methodes appelées lorsqu'il y a appui sur les boutons de l'interface graphique */
	void on_menu_quitter();
	void on_menu_ouvrir();
	void on_menu_ouvrir_annuler();
	void on_menu_ouvrir_accepter();
	void on_menu_sauvegarder();
	void on_menu_sauvegarder_annuler_aptere();
	void on_menu_sauvegarder_accepter_aptere();
	void on_menu_sauvegarder_annuler_aile();
	void on_menu_sauvegarder_accepter_aile();
	void on_menu_imprimer();
	void on_menu_aide();
	void on_choix_meteo();
	void on_choix_pression_ennemis();
	void on_lancement_simulation();
	void on_valider_avertissement();
	void taux_accroissement_init();
	void coefficient_envol_init();
	void on_coefficient_envol_change();
	void on_taux_accroissement_change();
	double **taux_accroissement(int stade, double sm, double b, double k, double a1, double a2);
};

#endif
