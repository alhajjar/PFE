/**
 * \file ControleurAffichage.h
 * \brief fichier d'entête de la bibliothèque du contrôle de l'interface graphique
 */

#ifndef CONTROLEUR_AFFICHAGE_H
#define CONTROLEUR_AFFICHAGE_H

#include <gtkmm.h>
#include <iostream>
#include <fstream>
#include "Dessin.h"
#include "Courbe.h"
#include "ImpressionOperation.h"
#include "Lecture_Ecriture.hpp"
#include "Controleur_Simulation.hpp"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
namespace fs = boost::filesystem;

/** \class ControleurAffichage
 *  \brief Classe contrôlant l'affichage et le comportement de l'interface graphique
 */
class ControleurAffichage
{
private:
/* Indice des choix (0, 1 ou 2) de la météo et de la pression des ennemis */
	int meteo;
	int pression_ennemis;
	int nb_jour_simulation;

/* Chemins des fichiers à charger ou que l'on sauvegarde */
	string cheminOuvertureCarte;
	string cheminSauvegardeAptere;
	string cheminSauvegardeAile;
	string cheminDossierDonnees;
	string cheminDossierEnregistrements;
	
/* Eléments de l'interface graphique avec lesquels il y a interaction */
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
	Gtk::FileChooserDialog* pChoixDossierDonneesOuvrir;
	Gtk::FileChooserDialog* pChoixDossierEnregistrementsOuvrir;
	Gtk::Label* pCheminOuvertureCarte;
	Gtk::Label* pCheminSauvegardeCarteAptere;
	Gtk::Label* pCheminSauvegardeCarteAile;
	Gtk::Label* pCheminDossierDonnees;
	Gtk::Label* pCheminDossierEnregistrements;
	Gtk::Button* pBoutonAnnulerOuvrir;
	Gtk::Button* pBoutonAccepterOuvrir;
	Gtk::Button* pBoutonAnnulerSauvegarderAptere;
	Gtk::Button* pBoutonAccepterSauvegarderAptere;
	Gtk::Button* pBoutonAnnulerSauvegarderAile;
	Gtk::Button* pBoutonAccepterSauvegarderAile;
	Gtk::Button* pBoutonDossierDonnees;
	Gtk::Button* pBoutonAccepterDossierDonnees;
	Gtk::Button* pBoutonAnnulerDossierDonnees;
	Gtk::Button* pBoutonDossierEnregistrements;
	Gtk::Button* pBoutonAccepterDossierEnregistrements;
	Gtk::Button* pBoutonAnnulerDossierEnregistrements;
	Gtk::Button* pBoutonLancerSimulation;
	Gtk::Button* pBoutonSimulationSuivante;
	Gtk::Button* pBoutonSimulationPrecedente;
	Gtk::Button* pBoutonAllerNumeroSimulation;
	Gtk::Entry* pNumeroSimulation;
	Gtk::Label* pNombreMaxSimulation;
	Gtk::RadioButton* pRadioMeteoFavorable;
	Gtk::RadioButton* pRadioMeteoNormale;
	Gtk::RadioButton* pRadioMeteoDefavorable;
	Gtk::RadioButton* pRadioPressionEnnemisNulle;
	Gtk::RadioButton* pRadioPressionEnnemisNormale;
	Gtk::RadioButton* pRadioPressionEnnemisForte;
	Gtk::MessageDialog* pAvertissementCheminFichierOuverture;
	Gtk::MessageDialog* pAvertissementCheminFichiersSauvegarde;
	Gtk::MessageDialog* pAvertissementImpression;
	Gtk::MessageDialog* pAvertissementDossierDonnees;
	Gtk::MessageDialog* pAvertissementDossierEnregistrements;
	Gtk::MessageDialog* pAvertissementExistenceFichiers;
	Gtk::Button* pBoutonAvertissementCheminFichierOuverture;
	Gtk::Button* pBoutonAvertissementCheminFichiersSauvegarde;
	Gtk::Button* pBoutonAvertissementImpression;
	Gtk::Button* pBoutonAvertissementDossierDonnees;
	Gtk::Button* pBoutonAvertissementDossierEnregistrements;
	Gtk::Button* pBoutonAvertissementExistenceFichiers;
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
	Gtk::Button* pRAZ_Ta;
	Gtk::Button* pRAZ_Cd1;
	Gtk::Button* pRAZ_Cd2;
	Gtk::Button* pRAZ_Cd3;
	Gtk::Button* pRAZ_Cd4;
	Gtk::Button* pRAZ_Cd5_inf;
	Gtk::Button* pRAZ_Cd5_sup;
	Gtk::Button* pRAZ_Ce;
	
	Dessin carte_A;
	Dessin carte_C;
	Courbe courbe_coeff_envol;
	Courbe courbe_taux_accroissement;
	
	double string_to_double(const std::string& s);
	string double_to_string(const double& d);
	
public:
	ControleurAffichage(string);
	virtual ~ControleurAffichage();

/* Méthode qui connecte les signaux à leur call-back */	
	void connecter_signaux();
	
/* Méthode qui permet de récupérer la fenêtre à afficher */
	Gtk::Window* get_fenetre();
	
/* Méthodes appelées lorsqu'il y a appui sur les boutons de l'interface graphique */
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
	void on_raz_taux_accroissement();
	void on_raz_coeff_depot_1();
	void on_raz_coeff_depot_2();
	void on_raz_coeff_depot_3();
	void on_raz_coeff_depot_4();
	void on_raz_coeff_depot_5_inf();
	void on_raz_coeff_depot_5_sup();
	void on_raz_coeff_envol();
	void on_ouvrir_dossier_donnees();
	void on_accepter_dossier_donnees();
	void on_annuler_dossier_donnees();
	void on_ouvrir_dossier_enregistrements();
	void on_accepter_dossier_enregistrements();
	void on_annuler_dossier_enregistrements();
	void on_simulation_suivante();
	void on_simulation_precedente();
	void on_simulation_aller();
	double **taux_accroissement(int stade, double sm, double b, double k, double a1, double a2);
};

#endif
