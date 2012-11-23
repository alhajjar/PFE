/**
 * \file ControleurAffichage.h
 * \brief fichier d'entete de la bibliotheque du controle de l'interface graphique
 * \author Francois Blouin
 * \date 21 novembre 2012
 */

#ifndef CONTROLEUR_AFFICHAGE_H
#define CONTROLEUR_AFFICHAGE_H

#include <gtkmm.h>
#include "Dessin.h"

using namespace std;

class ControleurAffichage
{
private:
	string cheminOuvertureCarte;
	string cheminSauvegardeAptere;
	string cheminSauvegardeAile;
	
/* Elements de l'interface graphique avec lesquels il y a interaction */
	Gtk::Window* pWindow;
	Gtk::VBox* pCadre;
	Gtk::ImageMenuItem* pMenuQuitter;
	Gtk::ImageMenuItem* pMenuOuvrir;
	Gtk::ImageMenuItem* pMenuSauvegarder;
	Gtk::ImageMenuItem* pMenuAide;
	Gtk::FileChooserDialog* pChoixFichierOuvrir;
	Gtk::FileChooserDialog* pChoixFichierSauvegarderAptere;
	Gtk::FileChooserDialog* pChoixFichierSauvegarderAile;
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
	Dessin carte;
	
public:
	ControleurAffichage(string);
	virtual ~ControleurAffichage();

/* Methode qui connecte les signaux a leur call-back */	
	void connecter_signaux();
	
/* Methode qui permet de recuperer la fenetre a afficher */
	Gtk::Window* get_fenetre();
	
/* Methodes appelees lorsqu'il y a appui sur les boutons de l'interface graphique */
	void on_menu_quitter();
	void on_menu_ouvrir();
	void on_menu_ouvrir_annuler();
	void on_menu_ouvrir_accepter();
	void on_menu_sauvegarder();
	void on_menu_sauvegarder_annuler_aptere();
	void on_menu_sauvegarder_accepter_aptere();
	void on_menu_sauvegarder_annuler_aile();
	void on_menu_sauvegarder_accepter_aile();
};

#endif