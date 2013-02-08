/**
 * \file ControleurAffichage.cpp
 * \brief fichier du contenu des méthodes de la bibliothèque du contrôle de l'interface graphique
 */

#include "Includes/ControleurAffichage.h"

/**
 * \fn ControleurAffichage ()
 * \brief Constructeur de la classe ControleurAffichage
 */
 ControleurAffichage ::ControleurAffichage (string gui_file)
{
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(gui_file);
	
	builder->get_widget("window1", pFenetre);
	builder->get_widget("hbox14", pCadre);
	builder->get_widget("imagemenuitem5", pMenuQuitter);
	builder->get_widget("imagemenuitem2", pMenuOuvrir);
	builder->get_widget("imagemenuitem3", pMenuSauvegarder);
	builder->get_widget("imagemenuitem10", pMenuAide);
	builder->get_widget("imagemenuitem9", pMenuImprimer);
	builder->get_widget("filechooserdialog1",pChoixFichierOuvrir);
	builder->get_widget("filechooserdialog2", pChoixFichierSauvegarderAptere);
	builder->get_widget("filechooserdialog3", pChoixFichierSauvegarderAile);
	builder->get_widget("label121",pCheminOuvertureCarte);
	builder->get_widget("label122", pCheminSauvegardeCarteAptere);
	builder->get_widget("label123", pCheminSauvegardeCarteAile);
	builder->get_widget("button6", pBoutonAnnulerOuvrir);
	builder->get_widget("button5", pBoutonAccepterOuvrir);
	builder->get_widget("button8", pBoutonAnnulerSauvegarderAptere);
	builder->get_widget("button7", pBoutonAccepterSauvegarderAptere);
	builder->get_widget("button10", pBoutonAnnulerSauvegarderAile);
	builder->get_widget("button9", pBoutonAccepterSauvegarderAile);
	builder->get_widget("button19", pBoutonLancerSimulation);
	builder->get_widget("button4", pBoutonSimulationSuivante);
	builder->get_widget("button3", pBoutonSimulationPrecedente);
	builder->get_widget("button2", pBoutonAllerNumeroSimulation);
	builder->get_widget("entry27", pNumeroSimulation);
	builder->get_widget("label40", pNombreMaxSimulation);
	builder->get_widget("radiobutton4", pRadioMeteoFavorable);
	builder->get_widget("radiobutton5", pRadioMeteoNormale);
	builder->get_widget("radiobutton6", pRadioMeteoDefavorable);
	builder->get_widget("radiobutton1", pRadioPressionEnnemisNulle);
	builder->get_widget("radiobutton2", pRadioPressionEnnemisNormale);
	builder->get_widget("radiobutton3", pRadioPressionEnnemisForte);
	builder->get_widget("messagedialog1", pAvertissementCheminFichierOuverture);
	builder->get_widget("messagedialog2", pAvertissementCheminFichiersSauvegarde);
	builder->get_widget("messagedialog3", pAvertissementImpression);
	builder->get_widget("messagedialog4", pAvertissementDossierDonnees);
	builder->get_widget("messagedialog5", pAvertissementDossierEnregistrements);
	builder->get_widget("messagedialog6", pAvertissementExistenceFichiers);
	builder->get_widget("button11", pBoutonAvertissementCheminFichierOuverture);
	builder->get_widget("button13", pBoutonAvertissementCheminFichiersSauvegarde);
	builder->get_widget("button12", pBoutonAvertissementImpression);
	builder->get_widget("button30", pBoutonAvertissementDossierDonnees);
	builder->get_widget("button31", pBoutonAvertissementDossierEnregistrements);
	builder->get_widget("button32", pBoutonAvertissementExistenceFichiers);
	builder->get_widget("notebook1", pOnglets);
	builder->get_widget("image11", pImageMeteo);
	builder->get_widget("image12", pImagePressionEnnemis);
	builder->get_widget("button14", pBoutonOuvrir);
	builder->get_widget("button15", pBoutonSauvegarder);
	builder->get_widget("button16", pBoutonImprimer);
	builder->get_widget("button17", pBoutonQuitter);
	builder->get_widget("button18", pBoutonAide);
	builder->get_widget("vbox2", pCadreCoeffEnvol);
	builder->get_widget("vbox8", pCadreTauxAccroissement);
	builder->get_widget("entry39", pNb_jour_simu);
	builder->get_widget("entry44", pTa_sm);
	builder->get_widget("entry45", pTa_b);
	builder->get_widget("entry46", pTa_k);
	builder->get_widget("entry47", pTa_a1);
	builder->get_widget("entry48", pTa_a2);
	builder->get_widget("entry50", pCd1_a1);
	builder->get_widget("entry51", pCd1_a2);
	builder->get_widget("entry49", pCd1_a);
	builder->get_widget("entry52", pCd1_k);
	builder->get_widget("entry53", pCd2_a1);
	builder->get_widget("entry54", pCd2_a2);
	builder->get_widget("entry55", pCd2_a3);
	builder->get_widget("entry56", pCd2_a4);
	builder->get_widget("entry57", pCd2_a5);
	builder->get_widget("entry58", pCd2_k);
	builder->get_widget("entry59", pCd3_a1);
	builder->get_widget("entry60", pCd3_a2);
	builder->get_widget("entry61", pCd3_a3);
	builder->get_widget("entry62", pCd3_k);
	builder->get_widget("entry63", pCd4_a1);
	builder->get_widget("entry64", pCd4_a2);
	builder->get_widget("entry65", pCd4_a3);
	builder->get_widget("entry66", pCd4_k);
	builder->get_widget("entry67", pCd5_inf_a1);
	builder->get_widget("entry68", pCd5_inf_a2);
	builder->get_widget("entry69", pCd5_inf_a3);
	builder->get_widget("entry70", pCd5_inf_k);
	builder->get_widget("entry71", pCd5_sup_a1);
	builder->get_widget("entry72", pCd5_sup_a2);
	builder->get_widget("entry73", pCd5_sup_a3);
	builder->get_widget("entry74", pCd5_sup_k);
	builder->get_widget("entry40", pCe_a);
	builder->get_widget("entry41", pCe_a0);
	builder->get_widget("entry42", pCe_a1);
	builder->get_widget("entry43", pCe_a2);
	builder->get_widget("button54", pRAZ_Ta);
	builder->get_widget("button1", pRAZ_Cd1);
	builder->get_widget("button20", pRAZ_Cd2);
	builder->get_widget("button21", pRAZ_Cd3);
	builder->get_widget("button22", pRAZ_Cd4);
	builder->get_widget("button23", pRAZ_Cd5_inf);
	builder->get_widget("button24", pRAZ_Cd5_sup);
	builder->get_widget("button53", pRAZ_Ce);
	builder->get_widget("button52", pBoutonDossierDonnees);
	builder->get_widget("button25", pBoutonAccepterDossierDonnees);
	builder->get_widget("button26", pBoutonAnnulerDossierDonnees);
	builder->get_widget("label26", pCheminDossierDonnees);
	builder->get_widget("filechooserdialog4", pChoixDossierDonneesOuvrir);
	builder->get_widget("button27", pBoutonDossierEnregistrements);
	builder->get_widget("button28", pBoutonAccepterDossierEnregistrements);
	builder->get_widget("button29", pBoutonAnnulerDossierEnregistrements);
	builder->get_widget("label4", pCheminDossierEnregistrements);
	builder->get_widget("filechooserdialog5", pChoixDossierEnregistrementsOuvrir);
	
	pCadre->add(carte_A);
	pCadre->add(carte_C);
	carte_A.set_titre("Apteres");
	carte_C.set_titre("Ailes");
	carte_A.show();
	carte_C.show();
	
	pCadreCoeffEnvol->add(courbe_coeff_envol);
	pCadreTauxAccroissement->add(courbe_taux_accroissement);
	
	courbe_coeff_envol.set_echelle(0.0, 30.0, 0.0, 0.01);
	courbe_coeff_envol.set_axe_x("T(C)");
	courbe_coeff_envol.set_axe_y("S=20 (Rouge), S=50 (Vert), S=70 (Bleu)");
	courbe_coeff_envol.show();

	coefficient_envol_init();
	
	courbe_taux_accroissement.set_echelle(0.0, 30.0, 0.0, 0.01);
	courbe_taux_accroissement.set_axe_x("T(C)");
	courbe_taux_accroissement.set_axe_y("S=20 (Rouge), S=50 (Vert), S=70 (Bleu)");
	courbe_taux_accroissement.show();
	
	taux_accroissement_init();
	
	meteo = 1;
	pression_ennemis = 1;
	
	cheminOuvertureCarte.clear();
	cheminSauvegardeAptere.clear();
	cheminSauvegardeAile.clear();
	cheminDossierEnregistrements = "enregistrements";
	cheminDossierDonnees = "donnees";
}

/**
 * \fn ~ControleurAffichage ()
 * \brief Destructeur de la classe ControleurAffichage
 *
 * \return Rien
 */
ControleurAffichage ::~ControleurAffichage ()
{
}

/**
 * \fn double ControleurAffichage::string_to_double(const std::string& s)
 * \brief Méthode transformant une variable de type string en une variable de type double
 *
 * \return x Transformation en double d'un string
 */
double ControleurAffichage::string_to_double(const std::string& s){
   istringstream *i = new istringstream(s);
   double x;
   if (!(*i >> x))
     return 0;
   return x;
} 

/**
 * \fn string ControleurAffichage::double_to_string(const double& d)
 * \brief Méthode transformant une variable de type double en une variable de type string
 *
 * \return s Transformation en string d'un double
 */
string ControleurAffichage::double_to_string(const double& d){
	stringstream *sstr = new stringstream();
	*sstr << d;
	return sstr->str();
}

/**
 * \fn void ControleurAffichage::connecter_signaux ()
 * \brief Méthode connectant les signaux des objets de la GUI à leur fonction de call-back
 *
 * \return Rien
 */
void ControleurAffichage::connecter_signaux(){
	pMenuQuitter->signal_activate().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_quitter));
	pMenuOuvrir->signal_activate().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_ouvrir));
	pMenuSauvegarder->signal_activate().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_sauvegarder));
	pMenuImprimer->signal_activate().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_imprimer));
	pMenuAide->signal_activate().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_aide));
	pBoutonAnnulerOuvrir->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_ouvrir_annuler));
	pBoutonAccepterOuvrir->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_ouvrir_accepter));
	pBoutonAnnulerSauvegarderAptere->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_sauvegarder_annuler_aptere));
	pBoutonAccepterSauvegarderAptere->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_sauvegarder_accepter_aptere));
	pBoutonAnnulerSauvegarderAile->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_sauvegarder_annuler_aile));
	pBoutonAccepterSauvegarderAile->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_sauvegarder_accepter_aile));
	pBoutonDossierDonnees->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_ouvrir_dossier_donnees));
	pBoutonAccepterDossierDonnees->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_accepter_dossier_donnees));
	pBoutonAnnulerDossierDonnees->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_annuler_dossier_donnees));
	pBoutonDossierEnregistrements->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_ouvrir_dossier_enregistrements));
	pBoutonAccepterDossierEnregistrements->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_accepter_dossier_enregistrements));
	pBoutonAnnulerDossierEnregistrements->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_annuler_dossier_enregistrements));
	pRadioMeteoFavorable->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_choix_meteo));
	pRadioMeteoNormale->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_choix_meteo));
	pRadioMeteoDefavorable->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_choix_meteo));
	pRadioPressionEnnemisNulle->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_choix_pression_ennemis));
	pRadioPressionEnnemisNormale->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_choix_pression_ennemis));
	pRadioPressionEnnemisForte->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_choix_pression_ennemis));
	pBoutonLancerSimulation->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_lancement_simulation));
	pBoutonAvertissementCheminFichierOuverture->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_valider_avertissement));
	pBoutonAvertissementCheminFichiersSauvegarde->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_valider_avertissement));
	pBoutonAvertissementImpression->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_valider_avertissement));
	pBoutonAvertissementDossierDonnees->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_valider_avertissement));
	pBoutonAvertissementDossierEnregistrements->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_valider_avertissement));
	pBoutonAvertissementExistenceFichiers->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_valider_avertissement));
	pBoutonOuvrir->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_ouvrir));
	pBoutonSauvegarder->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_sauvegarder));
	pBoutonImprimer->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_imprimer));
	pBoutonQuitter->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_quitter));
	pBoutonAide->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_menu_aide));
	pTa_sm->signal_changed().connect(sigc::mem_fun (this, &ControleurAffichage::on_taux_accroissement_change));
	pTa_b->signal_changed().connect(sigc::mem_fun (this, &ControleurAffichage::on_taux_accroissement_change));
	pTa_a1->signal_changed().connect(sigc::mem_fun (this, &ControleurAffichage::on_taux_accroissement_change));
	pTa_a2->signal_changed().connect(sigc::mem_fun (this, &ControleurAffichage::on_taux_accroissement_change));
	pTa_k->signal_changed().connect(sigc::mem_fun (this, &ControleurAffichage::on_taux_accroissement_change));
	pCe_a->signal_changed().connect(sigc::mem_fun (this, &ControleurAffichage::on_coefficient_envol_change));
	pCe_a0->signal_changed().connect(sigc::mem_fun (this, &ControleurAffichage::on_coefficient_envol_change));
	pCe_a1->signal_changed().connect(sigc::mem_fun (this, &ControleurAffichage::on_coefficient_envol_change));
	pCe_a2->signal_changed().connect(sigc::mem_fun (this, &ControleurAffichage::on_coefficient_envol_change));
	pRAZ_Ta->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_raz_taux_accroissement));
	pRAZ_Cd1->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_raz_coeff_depot_1));
	pRAZ_Cd2->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_raz_coeff_depot_2));
	pRAZ_Cd3->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_raz_coeff_depot_3));
	pRAZ_Cd4->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_raz_coeff_depot_4));
	pRAZ_Cd5_inf->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_raz_coeff_depot_5_inf));
	pRAZ_Cd5_sup->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_raz_coeff_depot_5_sup));
	pRAZ_Ce->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_raz_coeff_envol));
	pBoutonSimulationSuivante->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_simulation_suivante));
	pBoutonSimulationPrecedente->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_simulation_precedente));
	pBoutonAllerNumeroSimulation->signal_clicked().connect(sigc::mem_fun (this, &ControleurAffichage::on_simulation_aller));
}

/**
 * \fn Gtk::Window* ControleurAffichage::get_fenetre ()
 * \brief Méthode retournant la fenêtre de l'interface graphique à afficher
 * \return Rien
 */
Gtk::Window* ControleurAffichage::get_fenetre(){
	return pFenetre;
}

/**
 * \fn ControleurAffichage::void on_menu_quitter ()
 * \brief Méthode quittant le logiciel quand un appui sur le menu Simulation/Quitter a été effectué
 * \return Rien
 */
void ControleurAffichage::on_menu_quitter(){
	Gtk::Main::quit();
}

/**
 * \fn ControleurAffichage::void on_menu_ouvrir ()
 * \brief Méthode qui la fenêtre de choix de fichier pour ouvrir un fichier contenant une carte de France.
 * Actif quand Appui sur le menu Simulation/Ouvrir
 * \return Rien
 */
void ControleurAffichage::on_menu_ouvrir(){
	pChoixFichierOuvrir->show();
}	

/**
 * \fn ControleurAffichage::void on_menu_ouvrir_annuler ()
 * \brief Méthode qui annule la fenêtre de choix d'ouverture de fichier de carte de France
 * \return Rien
 */
void ControleurAffichage::on_menu_ouvrir_annuler(){
	pChoixFichierOuvrir->hide();
}

/**
 * \fn void ControleurAffichage::on_menu_ouvrir_accepter ()
 * \brief Méthode récupérant le chemin du fichier qui contient une carte de France et ferme la fenêtre de choix.
 * \return Rien
 */
void ControleurAffichage::on_menu_ouvrir_accepter(){
	cheminOuvertureCarte = pChoixFichierOuvrir->get_filename();
	pCheminOuvertureCarte->set_text(cheminOuvertureCarte);
	carte_A.set_chemin_carte(cheminOuvertureCarte);
	carte_C.set_chemin_carte(cheminOuvertureCarte);
	pChoixFichierOuvrir->hide();
}

/**
 * \fn void ControleurAffichage::on_menu_sauvegarder ()
 * \brief Méthode qui ouvre les fenêtres permettant de choisir l'emplacement de sauvegarde des fichiers de Simulation.
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder(){
	pChoixFichierSauvegarderAptere->show();
	pChoixFichierSauvegarderAile->show();
}

/**
 * \fn void ControleurAffichage::on_menu_sauvegarder_annuler_aptere ()
 * \brief Méthode annulant le choix de sauvegarde pour la carte des Aptères.
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder_annuler_aptere(){
	pChoixFichierSauvegarderAptere->hide();
}

/**
 * \fn void ControleurAffichage::on_menu_sauvegarder_accepter_aptere ()
 * \brief Methode récuperant le chemin souhaité pour la sauvegarde de la carte des Aptères.
 * Ferme également la fenêtre de choix d'emplacement de sauvegarde.
 * Images//coef_depot
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder_accepter_aptere(){
	cheminSauvegardeAptere = pChoixFichierSauvegarderAptere->get_filename();
	pCheminSauvegardeCarteAptere->set_text(cheminSauvegardeAptere);
	pChoixFichierSauvegarderAptere->hide();
}

/**
 * \fn ControleurAffichage::void on_menu_sauvegarder_annuler_aile ()
 * \brief Méthode annulant le choix de sauvegarde pour la carte des Ailés.
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder_annuler_aile(){
	pChoixFichierSauvegarderAile->hide();
}

/**
 * \fn void ControleurAffichage::on_menu_sauvegarder_accepter_aile()
 * \brief Méthode récupérant le chemin souhaité pour la sauvegarde de la carte des Ailés.
 *	Ferme également la fenêtre de choix d'emplacement de sauvegarde.
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder_accepter_aile(){
	cheminSauvegardeAile = pChoixFichierSauvegarderAile->get_filename();
	pCheminSauvegardeCarteAile->set_text(cheminSauvegardeAile);
	pChoixFichierSauvegarderAile->hide();
}

/**
 * \fn void ControleurAffichage::on_annuler_dossier_donnees()
 * \brief Méthode annulant le choix de chemin du dossier des données
 *	Ferme également la fenêtre de choix d'emplacement de dossier de données.
 * \return Rien
 */
void ControleurAffichage::on_annuler_dossier_donnees(){
	pChoixDossierDonneesOuvrir->hide();
}

/**
 * \fn ControleurAffichage::on_ouvrir_dossier_donnees()
 * \brief Méthode ouvrant la fenêtre de choix de chemin de dossier de données
 * \return Rien
 */
void ControleurAffichage::on_ouvrir_dossier_donnees(){
	pChoixDossierDonneesOuvrir->show();
}
	
/**
 * \fn ControleurAffichage::on_accepter_dossier_donnees()
 * \brief Méthode récupérant le chemin souhaité pour le dossier des données
 *	Ferme également la fenêtre de choix d'emplacement de dossier de données.
 * \return Rien
 */
void ControleurAffichage::on_accepter_dossier_donnees(){
	cheminDossierDonnees = pChoixDossierDonneesOuvrir->get_filename();
	pCheminDossierDonnees->set_text(cheminDossierDonnees);
	pChoixDossierDonneesOuvrir->hide();
}

/**
 * \fn ControleurAffichage::on_ouvrir_dossier_enregistrements()
 * \brief Méthode ouvrant la fenêtre de choix de chemin de dossier des enregistrements
 * \return Rien
 */
void ControleurAffichage::on_ouvrir_dossier_enregistrements(){
	pChoixDossierEnregistrementsOuvrir->show();
}

/**
 * \fn ControleurAffichage::on_accepter_dossier_enregistrements()
 * \brief Méthode récupérant le chemin souhaité pour le dossier des enregistrements
 *	Ferme également la fenêtre de choix d'emplacement de dossier des enregistrments.
 * \return Rien
 */
void ControleurAffichage::on_accepter_dossier_enregistrements(){
	cheminDossierEnregistrements = pChoixDossierEnregistrementsOuvrir->get_filename();
	pCheminDossierEnregistrements->set_text(cheminDossierEnregistrements);
	pChoixDossierEnregistrementsOuvrir->hide();
}

/**
 * \fn void ControleurAffichage::on_annuler_dossier_enregistrements()
 * \brief Méthode annulant le choix de chemin du dossier des enregistrements
 *	Ferme également la fenêtre de choix d'emplacement de dossier de enregistrements.
 * \return Rien
 */
void ControleurAffichage::on_annuler_dossier_enregistrements(){
	pChoixDossierEnregistrementsOuvrir->hide();
}

/** \fn void ControleurAffichage::on_menu_imprimer()
 *  \brief Méthode lancant une impression de résultat
 *  \return Rien
 */
void ControleurAffichage::on_menu_imprimer(){
	if(!cheminOuvertureCarte.empty() && carte_A.get_activation() == 1 && carte_C.get_activation() == 1){
/* Objets en relation avec l'impression (configuration d'impression) */
		Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
		Glib::RefPtr<Gtk::PrintSettings> m_refSettings;

/* Création d'une Operation d'impression */
		Glib::RefPtr<ImpressionOperation> impression = ImpressionOperation::create();
		
/* Insertion de la carte des aptères dans la page d'impression */
		impression->set_gdk_pixbuf(carte_A.get_gdk_pixbuf(), 0);
/* La taille de la carte est renseignée dans l'opération d'impression pour redimmensionner à l'échelle de la page d'impression */
		impression->set_taille_carte(carte_A.get_hauteur(),carte_A.get_largeur());
/* Les valeurs min et max sont renseignées dans l'opération d'impression pour les afficher dans la page d'impression */
		impression->set_valeur_min(carte_A.get_valeur_min(), 0);
		impression->set_valeur_max(carte_A.get_valeur_max(), 0);
		
/* Insertion de la carte des ailés dans la page d'impression */
		impression->set_gdk_pixbuf(carte_C.get_gdk_pixbuf(), 1);
/* Les valeurs min et max sont renseignées dans l'opération d'impression pour les afficher dans la page d'impression */
		impression->set_valeur_min(carte_C.get_valeur_min(), 1);
		impression->set_valeur_max(carte_C.get_valeur_max(), 1);
		
/* Affichage de la page de configuration de mise en page */
		m_refPageSetup = Gtk::run_page_setup_dialog(*pFenetre, m_refPageSetup, m_refSettings);
			
		impression->set_default_page_setup(m_refPageSetup);
		impression->set_print_settings(m_refSettings);
		
/* Lancement de configuration de l'impression + lancement impression */
		impression->run(Gtk::PRINT_OPERATION_ACTION_PRINT_DIALOG, *pFenetre);
	}
	else{
		pAvertissementImpression->show();
	}
}

/** \fn void ControleurAffichage::on_choix_meteo()
 *  \brief Mise à jour du choix de la météo
 *  \return Rien
 */
void ControleurAffichage::on_choix_meteo(){
	bool meteoFavorable = pRadioMeteoFavorable->get_active();
	bool meteoNormale = pRadioMeteoNormale->get_active();
	bool meteoDefavorable = pRadioMeteoDefavorable->get_active();
	
	if(meteoFavorable){
		meteo = 0;
		pImageMeteo->set("Images/meteo_favorable.png");
	}
	if(meteoNormale){
		meteo = 1;
		pImageMeteo->set("Images/meteo_normale.png");
	}
	if(meteoDefavorable){
		meteo = 2;
		pImageMeteo->set("Images/meteo_defavorable.png");
	}
}

/** \fn void ControleurAffichage::on_choix_pression_ennemis()
 *  \brief Mise à jour du choix de la pression des ennemis
 *  \return Rien
 */
void ControleurAffichage::on_choix_pression_ennemis(){
	bool pressionEnnemisNulle = pRadioPressionEnnemisNulle->get_active();
	bool pressionEnnemisNormale = pRadioPressionEnnemisNormale->get_active();
	bool pressionEnnemisForte = pRadioPressionEnnemisForte->get_active();
	
	if(pressionEnnemisNulle){
		pression_ennemis = 0;
		pImagePressionEnnemis->set("Images/puceron_blanc.png");
	}
	if(pressionEnnemisNormale){
		pression_ennemis = 1;
		pImagePressionEnnemis->set("Images/puceron_vert.png");
	}
	if(pressionEnnemisForte){
		pression_ennemis = 2;
		pImagePressionEnnemis->set("Images/puceron_rouge.png");
	}
}

/** \fn void ControleurAffichage::on_lancement_simulation()
 *  \brief Lancement de la simulation. Cette méthode fait égalment une gestion d'erreur sur les différents fichiers/dossiers.
 *  Un enregistrement est égalment automatiquement fait à chaque fin d'itération de simulation.
 *  \return Rien
 */
void ControleurAffichage::on_lancement_simulation(){
	Controleur_Simulation simu;
	Lecture_Ecriture lect;
	if (cheminOuvertureCarte.empty())
		pAvertissementCheminFichierOuverture->show();
	else{
		if(cheminSauvegardeAptere.empty() || cheminSauvegardeAile.empty())
			pAvertissementCheminFichiersSauvegarde->show();
		else{
			fs::path dossier_donnees(cheminDossierDonnees);
			if(!fs::exists(dossier_donnees))
				pAvertissementDossierDonnees->show();
			else{
				fs::path dossier_enregistrements( cheminDossierEnregistrements);
				if(!fs::exists(dossier_enregistrements))
					pAvertissementDossierEnregistrements->show();
				else{
					string erreur_chemins;
					string debut_message("Les fichiers suivants n'existent pas: \n");

					fs::path existence_fichiers( cheminDossierDonnees + "/mat_A.csv");
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/mat_A.csv\n";
					existence_fichiers = cheminDossierDonnees + "/mat_C.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/mat_C.csv\n";
					existence_fichiers = cheminDossierDonnees + "/mat_p.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/mat_p.csv\n";
					existence_fichiers = cheminDossierDonnees + "/mat_eta.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/mat_eta.csv\n";
					existence_fichiers = cheminDossierDonnees + "/coord_s.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/coord_s.csv\n";
					existence_fichiers = cheminDossierDonnees + "/data_s.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/data_s.csv\n";
					existence_fichiers = cheminDossierDonnees + "/coord_t.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/coord_t.csv\n";
					existence_fichiers = cheminDossierDonnees + "/data_t.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/data_t.csv\n";
					existence_fichiers = cheminDossierDonnees + "/mat_D.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/mat_D.csv\n";
					existence_fichiers = cheminDossierDonnees + "/vitesse_h.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/vitesse_h.csv\n";
					existence_fichiers = cheminDossierDonnees + "/vitesse_v.csv";
					if(!fs::exists(existence_fichiers))
							erreur_chemins += cheminDossierDonnees + "/vitesse_v.csv\n";
					if (!erreur_chemins.empty()){
						pAvertissementExistenceFichiers->set_message(debut_message + erreur_chemins, false);
						pAvertissementExistenceFichiers->show();
					}
					else{
/* Mise à 0 du nombre de cartes dans les résultats de la simulation */
						pNumeroSimulation->set_text("0");
						pNombreMaxSimulation->set_text("0");

/* Initialisation du gradient de couleur pour chaque carte */
						carte_A.init();
						carte_C.init();

/* Récupértion du nombre de jours de simulation */
						nb_jour_simulation = (int) string_to_double(pNb_jour_simu->get_text());

/* MAJ des constantes pour les calculs des lois */
						simu.set_constantes_taux_accroissement(string_to_double(pTa_sm->get_text()), string_to_double(pTa_b->get_text()), string_to_double(pTa_k->get_text()), string_to_double(pTa_a1->get_text()), string_to_double(pTa_a2->get_text()));
						simu.set_constantes_coeffdepot1(string_to_double(pCd1_a->get_text()), string_to_double(pCd1_a1->get_text()), string_to_double(pCd1_a2->get_text()), string_to_double(pCd1_k->get_text()));
						simu.set_constantes_coeffdepot2(string_to_double(pCd2_a1->get_text()), string_to_double(pCd2_a2->get_text()), string_to_double(pCd2_a3->get_text()), string_to_double(pCd2_a4->get_text()), string_to_double(pCd2_a5->get_text()), string_to_double(pCd2_k->get_text()));
						simu.set_constantes_coeffdepot3(string_to_double(pCd3_a1->get_text()), string_to_double(pCd3_a2->get_text()), string_to_double(pCd3_a3->get_text()), string_to_double(pCd3_k->get_text()));
						simu.set_constantes_coeffdepot4(string_to_double(pCd4_a1->get_text()), string_to_double(pCd4_a2->get_text()), string_to_double(pCd4_a3->get_text()), string_to_double(pCd4_k->get_text()));
						simu.set_constantes_coeffdepot5_inf(string_to_double(pCd5_inf_a1->get_text()), string_to_double(pCd5_inf_a2->get_text()), string_to_double(pCd5_inf_a3->get_text()), string_to_double(pCd5_inf_k->get_text()));
						simu.set_constantes_coeffdepot5_sup(string_to_double(pCd5_sup_a1->get_text()), string_to_double(pCd5_sup_a2->get_text()), string_to_double(pCd5_sup_a3->get_text()), string_to_double(pCd5_sup_k->get_text()));
						simu.set_constantes_coeff_envol(string_to_double(pCe_a->get_text()), string_to_double(pCe_a0->get_text()), string_to_double(pCe_a1->get_text()), string_to_double(pCe_a2->get_text()));

/* Affichage de l'onglet Résultats */
						pOnglets->set_current_page(2);

/* Initialisation de la simulation (lecture des fichiers + calculs) */
						simu.initialisation(5, 1, cheminDossierDonnees + "/mat_A.csv", cheminDossierDonnees + "/mat_C.csv",
						cheminDossierDonnees + "/mat_p.csv", cheminDossierDonnees + "/mat_eta.csv",
						cheminDossierDonnees + "/coord_s.csv", 22, 3, cheminDossierDonnees + "/data_s.csv", 367, 23,
						cheminDossierDonnees + "/coord_t.csv", 67, 3,cheminDossierDonnees + "/data_t.csv", 4384, 68,
						cheminDossierDonnees + "/mat_D.csv", cheminDossierDonnees + "/vitesse_h.csv", cheminDossierDonnees + "/vitesse_v.csv", meteo, pression_ennemis);

/* Désactivation du bouton de lancement de simulation */
						pBoutonLancerSimulation->set_sensitive(false);

/* Calculs de toutes les itérations de la simulation */
						for(int i=1; i < nb_jour_simulation + 1; i++){
							simu.iteration(i); 
							simu.affiche_bloc(0,0,1,194);

/* MAJ des matrices A et C à afficher */
							carte_A.set_matrice(simu.get_mat_A_retourne());
							carte_C.set_matrice(simu.get_mat_C_retourne());

/* MAJ des dessins des cartes */
							carte_A.dessiner_carte(H_MAP, L_MAP, 0, 0);
							carte_C.dessiner_carte(H_MAP, L_MAP, 0, 0);

/* Sauvegarde dans le dossier des enregistrements des cartes aptères et ailés pour chaque itération */
							lect.EcritureCSV(simu.get_mat_A(), carte_A.enregistrement(i, cheminDossierEnregistrements));
							lect.EcritureCSV(simu.get_mat_C(), carte_C.enregistrement(i, cheminDossierEnregistrements));

/* MAJ du nombre de cartes dans les résultats */
							pNumeroSimulation->set_text(double_to_string(i));
							pNombreMaxSimulation->set_text(double_to_string(i));
						}
/* Enregistrement des matrices des ailés et des aptères finales */
							 lect.EcritureCSV(simu.get_mat_A(), cheminSauvegardeAptere); 
							 lect.EcritureCSV(simu.get_mat_C(), cheminSauvegardeAile);

/* Réactivation du bouton de lancement de simulation */
						pBoutonLancerSimulation->set_sensitive(true);
					}
				}
			}
		}
		
	}
}

/** \fn void ControleurAffichage::on_valider_avertissement()
 *  \brief Méthode cachant tous les messages d'avertissement générés par l'interface graphique quand ces derniers ont été validés.
 *  \return Rien
 */
void ControleurAffichage::on_valider_avertissement(){
	pAvertissementCheminFichierOuverture->hide();
	pAvertissementCheminFichiersSauvegarde->hide();
	pAvertissementImpression->hide();
	pAvertissementDossierDonnees->hide();
	pAvertissementDossierEnregistrements->hide();
	pAvertissementExistenceFichiers->hide();
}

/** \fn void ControleurAffichage::on_menu_aide()
 *  \brief Affichage de l'aide. Cette méthode fait juste référence au manuel utilisateur sous format HTML.
 *  \return Rien
 */
void ControleurAffichage::on_menu_aide(){
	//system("b.html");
}

/** \fn void ControleurAffichage::coefficient_envol_init()
 *  \brief Initialisation du graphe qui dessine automatiquement les courbes de coefficient d'envol
 *  \return Rien
 */
void ControleurAffichage::coefficient_envol_init(){
	string *s_a, *s_a0, *s_a1, *s_a2;
	double d_a, d_a0, d_a1, d_a2;
	
	s_a = new string(pCe_a->get_text());
	s_a0 = new string(pCe_a0->get_text());
	s_a1 = new string(pCe_a1->get_text());
	s_a2 = new string(pCe_a2->get_text());
	
	d_a = string_to_double(*s_a);
	d_a0 = string_to_double(*s_a0);
	d_a1 = string_to_double(*s_a1);
	d_a2 = string_to_double(*s_a2);
	
	double **points;

	points = Controleur_Simulation::coeff_envol(20, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.ajouter_courbe(points, 30);
	points = Controleur_Simulation::coeff_envol(50, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.ajouter_courbe(points, 30);
	points = Controleur_Simulation::coeff_envol(70, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.ajouter_courbe(points, 30);
}

/** \fn void ControleurAffichage::taux_accroissement_init()
 *  \brief Initialisation du graphe qui dessine automatiquement les courbes du taux d'accroissement
 *  \return Rien
 */
void ControleurAffichage::taux_accroissement_init(){
	string *s_sm, *s_b, *s_a1, *s_a2, *s_k;
	double d_sm, d_b, d_a1, d_a2, d_k;
	
	s_sm = new string(pTa_sm->get_text());
	s_b = new string(pTa_b->get_text());
	s_a1 = new string(pTa_a1->get_text());
	s_a2 = new string(pTa_a2->get_text());
	s_k = new string(pTa_k->get_text());
	
	d_sm = string_to_double(*s_sm);
	d_b = string_to_double(*s_b);
	d_a1 = string_to_double(*s_a1);
	d_a2 = string_to_double(*s_a2);
	d_k = string_to_double(*s_k);
	
	double **points;
	points = Controleur_Simulation::taux_accroissement(20, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.ajouter_courbe(points, 30);
	points = Controleur_Simulation::taux_accroissement(50, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.ajouter_courbe(points, 30);
	points = Controleur_Simulation::taux_accroissement(70, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.ajouter_courbe(points, 30);
}

/** \fn void ControleurAffichage::on_coefficient_envol_change()
 *  \brief Mise à jour du graphes qui dessine automatiquement les courbes de coefficient d'envol losrque l'une
 *  des constantes définissant ce dernier a été modifiée
 *  \return Rien
 */
void ControleurAffichage::on_coefficient_envol_change(){
	string *s_a, *s_a0, *s_a1, *s_a2;
	double d_a, d_a0, d_a1, d_a2;
	
	s_a = new string(pCe_a->get_text());
	s_a0 = new string(pCe_a0->get_text());
	s_a1 = new string(pCe_a1->get_text());
	s_a2 = new string(pCe_a2->get_text());
	
	d_a = string_to_double(*s_a);
	d_a0 = string_to_double(*s_a0);
	d_a1 = string_to_double(*s_a1);
	d_a2 = string_to_double(*s_a2);
	
	double **points;

	courbe_coeff_envol.set_echelle(0, 30, 0, 0.01);

	points = Controleur_Simulation::coeff_envol(20, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.modifier_courbe(points, 30,0);
	points = Controleur_Simulation::coeff_envol(50, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.modifier_courbe(points, 30,0);
	points = Controleur_Simulation::coeff_envol(70, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.modifier_courbe(points, 30,0);

	courbe_coeff_envol.tracer();
}

/** \fn void ControleurAffichage::on_taux_accroissement_change()
 *  \brief Mise à jour du graphes qui dessine automatiquement les courbes du taux d'accroissement losrque l'une
 *  des constantes définissant ce dernier a été modifiée
 *  \return Rien
 */
void ControleurAffichage::on_taux_accroissement_change(){
	string *s_sm, *s_b, *s_a1, *s_a2, *s_k;
	double d_sm, d_b, d_a1, d_a2, d_k;
	
	s_sm = new string(pTa_sm->get_text());
	s_b = new string(pTa_b->get_text());
	s_a1 = new string(pTa_a1->get_text());
	s_a2 = new string(pTa_a2->get_text());
	s_k = new string(pTa_k->get_text());
	
	d_sm = string_to_double(*s_sm);
	d_b = string_to_double(*s_b);
	d_a1 = string_to_double(*s_a1);
	d_a2 = string_to_double(*s_a2);
	d_k = string_to_double(*s_k);
	
	double **points;

	courbe_taux_accroissement.set_echelle(0, 30, 0, 0.01);
	
	points = Controleur_Simulation::taux_accroissement(20, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.modifier_courbe(points, 30, 0);
	points = Controleur_Simulation::taux_accroissement(50, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.modifier_courbe(points, 30, 1);
	points = Controleur_Simulation::taux_accroissement(70, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.modifier_courbe(points, 30, 2);
	
	courbe_taux_accroissement.tracer();
}

/** \fn void ControleurAffichage::on_raz_taux_accroissement()
 *  \brief Réinitialisation des constantes du taux d'accroissement avec leur valeur par défaut 
 *  \return Rien
 */
void ControleurAffichage::on_raz_taux_accroissement(){
	double ta_sm = 15.27211;
	double ta_b = 0.04133;
	double ta_k = 0.11987;
	double ta_a1 = -0.10373;
	double ta_a2 = 0.11132;

	pTa_sm->set_text(double_to_string(ta_sm));
	pTa_b->set_text(double_to_string(ta_b));
	pTa_k->set_text(double_to_string(ta_k));
	pTa_a1->set_text(double_to_string(ta_a1));
	pTa_a2->set_text(double_to_string(ta_a2));
}

/** \fn void ControleurAffichage::on_raz_coeff_depot_1()
 *  \brief Réinitialisation des constantes du coefficient de dépôt 1 avec leur valeur par défaut 
 *  \return Rien
 */
void ControleurAffichage::on_raz_coeff_depot_1(){
	double cd1_a1 = 1.004855;
	double cd1_a2 = 1.652655;
	double cd1_a = -0.267819;
	double cd1_k = 6.214583;

	pCd1_a1->set_text(double_to_string(cd1_a1));
	pCd1_a2->set_text(double_to_string(cd1_a2));
	pCd1_a->set_text(double_to_string(cd1_a));
	pCd1_k->set_text(double_to_string(cd1_k));
}

/** \fn void ControleurAffichage::on_raz_coeff_depot_2()
 *  \brief Réinitialisation des constantes du coefficient de dépôt 2 avec leur valeur par défaut 
 *  \return Rien
 */
void ControleurAffichage::on_raz_coeff_depot_2(){
	double cd2_a1 = -0.128715;
	double cd2_a2 = 24.589110;
	double cd2_a3 = 0.946651;
	double cd2_a4 = 0.079787;
	double cd2_a5 = 0.906087;
	double cd2_k = 7.317821;

	pCd2_a1->set_text(double_to_string(cd2_a1));
	pCd2_a2->set_text(double_to_string(cd2_a2));
	pCd2_a3->set_text(double_to_string(cd2_a3));
	pCd2_a4->set_text(double_to_string(cd2_a4));
	pCd2_a5->set_text(double_to_string(cd2_a5));
	pCd2_k->set_text(double_to_string(cd2_k));
}

/** \fn void ControleurAffichage::on_raz_coeff_depot_3()
 *  \brief Réinitialisation des constantes du coefficient de dépôt 3 avec leur valeur par défaut 
 *  \return Rien
 */
void ControleurAffichage::on_raz_coeff_depot_3(){
	double cd3_a1 = 0.23001;
	double cd3_a2 = 0.86894;
	double cd3_a3 = 1.08105;
	double cd3_k = 8.22311;

	pCd3_a1->set_text(double_to_string(cd3_a1));
	pCd3_a2->set_text(double_to_string(cd3_a2));
	pCd3_a3->set_text(double_to_string(cd3_a3));
	pCd3_k->set_text(double_to_string(cd3_k));
	
}

/** \fn void ControleurAffichage::on_raz_coeff_depot_4()
 *  \brief Réinitialisation des constantes du coefficient de dépôt 4 avec leur valeur par défaut 
 *  \return Rien
 */
void ControleurAffichage::on_raz_coeff_depot_4(){
	double cd4_a1 = 0.318941;
	double cd4_a2 = 0.983375;
	double cd4_a3 = 1.669692;
	double cd4_k = -6.572036;

	pCd4_a1->set_text(double_to_string(cd4_a1));
	pCd4_a2->set_text(double_to_string(cd4_a2));
	pCd4_a3->set_text(double_to_string(cd4_a3));
	pCd4_k->set_text(double_to_string(cd4_k));
	
}

/** \fn void ControleurAffichage::on_raz_coeff_depot_5_inf()
 *  \brief Réinitialisation des constantes du coefficient de dépôt 5 (p < 0.5) avec leur valeur par défaut 
 *  \return Rien
 */
void ControleurAffichage::on_raz_coeff_depot_5_inf(){
	double cd5_inf_a1 = -0.12952;
	double cd5_inf_a2 = 0.73519;
	double cd5_inf_a3 = 1.92703;
	double cd5_inf_k = 38.70085;

	pCd5_inf_a1->set_text(double_to_string(cd5_inf_a1));
	pCd5_inf_a2->set_text(double_to_string(cd5_inf_a2));
	pCd5_inf_a3->set_text(double_to_string(cd5_inf_a3));
	pCd5_inf_k->set_text(double_to_string(cd5_inf_k));
}

/** \fn void ControleurAffichage::on_raz_coeff_depot_5_sup()
 *  \brief Réinitialisation des constantes du coefficient de dépôt 5 (p >= 0.5) avec leur valeur par défaut 
 *  \return Rien
 */
void ControleurAffichage::on_raz_coeff_depot_5_sup(){
	double cd5_sup_a1 = 0.12952;
	double cd5_sup_a2 = 0.73519;
	double cd5_sup_a3 = 1.92703;
	double cd5_sup_k = 38.70066;

	pCd5_sup_a1->set_text(double_to_string(cd5_sup_a1));
	pCd5_sup_a2->set_text(double_to_string(cd5_sup_a2));
	pCd5_sup_a3->set_text(double_to_string(cd5_sup_a3));
	pCd5_sup_k->set_text(double_to_string(cd5_sup_k));
}

/** \fn void ControleurAffichage::on_raz_coeff_envol()
 *  \brief Réinitialisation des constantes du coefficient d'envol avec leur valeur par défaut 
 *  \return Rien
 */
void ControleurAffichage::on_raz_coeff_envol(){
	double ce_a = 0.034733;
	double ce_a0 = 1.417143;
	double ce_a1 = 0.048163;
	double ce_a2 = -0.543663;

	pCe_a->set_text(double_to_string(ce_a));
	pCe_a0->set_text(double_to_string(ce_a0));
	pCe_a1->set_text(double_to_string(ce_a1));
	pCe_a2->set_text(double_to_string(ce_a2));
}

/** \fn void ControleurAffichage::on_simulation_suivante()
 *  \brief Méthode permettant le changement d'affichage de cartes sur l'onglet résultats pour une simulation suivante
 *  \return Rien
 */
void ControleurAffichage::on_simulation_suivante(){
	string num;
	Lecture_Ecriture lect;
	Controleur_Simulation simu;

	if((int)string_to_double(pNumeroSimulation->get_text()) != (int)string_to_double(pNombreMaxSimulation->get_text())){
		num = double_to_string((int)string_to_double(pNumeroSimulation->get_text()) + 1);
		pNumeroSimulation->set_text(num);

		lect.LectureCSV(197, 194, cheminDossierEnregistrements + "/" + carte_A.get_titre() + "_" + num + ".csv");
		simu.set_mat_A(lect.get_CSV());
		carte_A.set_matrice(simu.get_mat_A_retourne());

		lect.LectureCSV(197, 194, cheminDossierEnregistrements + "/" + carte_C.get_titre() + "_" + num + ".csv");
		simu.set_mat_C(lect.get_CSV());
		carte_C.set_matrice(simu.get_mat_C_retourne());

		carte_A.dessiner_carte(H_MAP, L_MAP, 0, 0);
		carte_C.dessiner_carte(H_MAP, L_MAP, 0, 0);
	}
}

/** \fn void ControleurAffichage::on_simulation_precedente()
 *  \brief Méthode permettant le changement d'affichage de cartes sur l'onglet résultats pour une simulation précédente
 *  \return Rien
 */
void ControleurAffichage::on_simulation_precedente(){
	string num;
	Lecture_Ecriture lect;
	Controleur_Simulation simu;

	if((int)string_to_double(pNumeroSimulation->get_text()) - 1 != 0){
		num = double_to_string(((int)string_to_double(pNumeroSimulation->get_text())) - 1 );
		pNumeroSimulation->set_text(num);

		lect.LectureCSV(197, 194, cheminDossierEnregistrements + "/" + carte_A.get_titre() + "_" + num + ".csv");
		simu.set_mat_A(lect.get_CSV());
		carte_A.set_matrice(simu.get_mat_A_retourne());

		lect.LectureCSV(197, 194, cheminDossierEnregistrements + "/" + carte_C.get_titre() + "_" + num + ".csv");
		simu.set_mat_C(lect.get_CSV());
		carte_C.set_matrice(simu.get_mat_C_retourne());

		carte_A.dessiner_carte(H_MAP, L_MAP, 0, 0);
		carte_C.dessiner_carte(H_MAP, L_MAP, 0, 0);
	}
}

/** \fn void ControleurAffichage::on_simulation_aller()
 *  \brief Méthode permettant le changement d'affichage de cartes sur l'onglet résultats pour un numéro de simulation rentré dans l'onglet résultat
 *  \return Rien
 */
void ControleurAffichage::on_simulation_aller(){
	string num;
	Lecture_Ecriture lect;
	Controleur_Simulation simu;

	if((int)string_to_double(pNumeroSimulation->get_text()) <= 0){
		num = double_to_string(1);
		pNumeroSimulation->set_text(num);
	}
	else{
		if((int)string_to_double(pNumeroSimulation->get_text()) > (int)string_to_double(pNombreMaxSimulation->get_text())){
			num = double_to_string((int)string_to_double(pNombreMaxSimulation->get_text()));
			pNumeroSimulation->set_text(num);
		}
		else{
			num = double_to_string(((int)string_to_double(pNumeroSimulation->get_text())));
			pNumeroSimulation->set_text(num);
		}
	}

	lect.LectureCSV(197, 194, cheminDossierEnregistrements + "/" + carte_A.get_titre() + "_" + num + ".csv");
	simu.set_mat_A(lect.get_CSV());
	carte_A.set_matrice(simu.get_mat_A_retourne());

	lect.LectureCSV(197, 194, cheminDossierEnregistrements + "/" + carte_C.get_titre() + "_" + num + ".csv");
	simu.set_mat_C(lect.get_CSV());
	carte_C.set_matrice(simu.get_mat_C_retourne());

	carte_A.dessiner_carte(H_MAP, L_MAP, 0, 0);
	carte_C.dessiner_carte(H_MAP, L_MAP, 0, 0);
}
