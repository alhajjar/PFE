/**
 * \file ControleurAffichage.cpp
 * \brief fichier du contenu des methodes de la bibliotheque du controle de l'interface graphique
 * \author Francois Blouin
 * \date 21 novembre 2012
 */

#include "ControleurAffichage.h"

/**
 * \fn ControleurAffichage ()
 * \brief Constructeur de la classe ControleurAffichage
 *
 * \return vide
 */
 ControleurAffichage ::ControleurAffichage (string gui_file)
{
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(gui_file);
	
	builder->get_widget("window1", pWindow);
	builder->get_widget("vbox4", pCadre);
	builder->get_widget("imagemenuitem5", pMenuQuitter);
	builder->get_widget("imagemenuitem2", pMenuOuvrir);
	builder->get_widget("imagemenuitem3", pMenuSauvegarder);
	builder->get_widget("imagemenuitem10", pMenuAide);
	builder->get_widget("filechooserdialog1",pChoixFichierOuvrir);
	builder->get_widget("filechooserdialog2", pChoixFichierSauvegarderAptere);
	builder->get_widget("filechooserdialog3", pChoixFichierSauvegarderAile);
	builder->get_widget("button6", pBoutonAnnulerOuvrir);
	builder->get_widget("button5", pBoutonAccepterOuvrir);
	builder->get_widget("button8", pBoutonAnnulerSauvegarderAptere);
	builder->get_widget("button7", pBoutonAccepterSauvegarderAptere);
	builder->get_widget("button10", pBoutonAnnulerSauvegarderAile);
	builder->get_widget("button9", pBoutonAccepterSauvegarderAile);
	builder->get_widget("button1", pBoutonLancerSimulation);
	builder->get_widget("button4", pBoutonSimulationSuivante);
	builder->get_widget("button3", pBoutonSimulationPrecedente);
	builder->get_widget("button2", pBoutonAllerNumeroSimulation);
	
	pCadre->add(carte);
	carte.show();
}

/**
 * \fn ~ControleurAffichage ()
 * \brief Destructeur de la classe ControleurAffichage
 *
 * \return vide
 */
ControleurAffichage ::~ControleurAffichage ()
{
}

/**
 * \fn void connecter_signaux ()
 * \brief Methode connectant les signaux des objets de la GUI a leur fonction de call-back
 *
 * \return vide
 */
void ControleurAffichage::connecter_signaux(){
	pMenuQuitter->signal_activate().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_quitter));
	pMenuOuvrir->signal_activate().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_ouvrir));
	pMenuSauvegarder->signal_activate().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder));
	pBoutonAnnulerOuvrir->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_ouvrir_annuler));
	pBoutonAccepterOuvrir->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_ouvrir_accepter));
	pBoutonAnnulerSauvegarderAptere->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder_annuler_aptere));
	pBoutonAccepterSauvegarderAptere->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder_accepter_aptere));
	pBoutonAnnulerSauvegarderAile->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder_annuler_aile));
	pBoutonAccepterSauvegarderAile->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder_accepter_aile));
}

/**
 * \fn Gtk::Window* get_fenetre ()
 * \brief Methode retournant la fenetre de l'interface graphique a afficher
 *
 * \return vide
 */
Gtk::Window* ControleurAffichage::get_fenetre(){
	return pWindow;
}

/**
 * \fn void on_menu_quitter ()
 * \brief Methode quittant le logiciel quand un appui sur le menu Simulation/Quitter a ete effectue
 *
 * \return vide
 */
void ControleurAffichage::on_menu_quitter(){
	Gtk::Main::quit();
}

/**
 * \fn void on_menu_ouvrir ()
 * \brief Methode qui la fenetre de choix de fichier pour ouvrir un fichier contenant une carte de France.
 * Actif quand Appui sur le menu Simulation/Ouvrir
 *
 * \return vide
 */
void ControleurAffichage::on_menu_ouvrir(){
	pChoixFichierOuvrir->show();
}	

/**
 * \fn void on_menu_ouvrir_annuler ()
 * \brief Methode qui annule la fenetre de choix d'ouverture de fichier de carte de France
 *
 * \return vide
 */
void ControleurAffichage::on_menu_ouvrir_annuler(){
	pChoixFichierOuvrir->hide();
}

/**
 * \fn void on_menu_ouvrir_accepter ()
 * \brief Methode recuperant le chemin du fichier qui contient une carte de France et ferme la fenetre de choix.
 *
 * \return vide
 */
void ControleurAffichage::on_menu_ouvrir_accepter(){
	cheminOuvertureCarte = pChoixFichierOuvrir->get_filename();
	pChoixFichierOuvrir->hide();
}

/**
 * \fn void on_menu_sauvegarder ()
 * \brief Methode qui ouvre les fenetres permettant de choisir l'emplacement de sauvegarde des fichiers de Simulation.
 *
 * \return vide
 */
void ControleurAffichage::on_menu_sauvegarder(){
	pChoixFichierSauvegarderAptere->show();
	pChoixFichierSauvegarderAile->show();
}

/**
 * \fn void on_menu_sauvegarder_annuler_aptere ()
 * \brief Methode annulant le choix de sauvegarde pour la carte des Apteres.
 *
 * \return vide
 */
void ControleurAffichage::on_menu_sauvegarder_annuler_aptere(){
	ControleurAffichage::pChoixFichierSauvegarderAptere->hide();
}

/**
 * \fn void on_menu_sauvegarder_accepter_aptere ()
 * \brief Methode recuperant le chemin ou l'on souhaite sauvegarder la carte des Apteres.
 *	Ferme egalement la fenetre de choix d'emplacement de sauvegarde.
 *
 * \return vide
 */
void ControleurAffichage::on_menu_sauvegarder_accepter_aptere(){
	ControleurAffichage::cheminSauvegardeAptere = ControleurAffichage::pChoixFichierSauvegarderAptere->get_filename();
	ControleurAffichage::pChoixFichierSauvegarderAptere->hide();
}

/**
 * \fn void on_menu_sauvegarder_annuler_aile ()
 * \brief Methode annulant le choix de sauvegarde pour la carte des Ailes.
 *
 * \return vide
 */
void ControleurAffichage::on_menu_sauvegarder_annuler_aile(){
	ControleurAffichage::pChoixFichierSauvegarderAile->hide();
}

/**
 * \fn void on_menu_sauvegarder_accepter_aile ()
 * \brief Methode recuperant le chemin ou l'on souhaite sauvegarder la carte des Ailes.
 *	Ferme egalement la fenetre de choix d'emplacement de sauvegarde
 *
 * \return vide
 */
void ControleurAffichage::on_menu_sauvegarder_accepter_aile(){
	ControleurAffichage::cheminSauvegardeAile = ControleurAffichage::pChoixFichierSauvegarderAile->get_filename();
	ControleurAffichage::pChoixFichierSauvegarderAile->hide();
}