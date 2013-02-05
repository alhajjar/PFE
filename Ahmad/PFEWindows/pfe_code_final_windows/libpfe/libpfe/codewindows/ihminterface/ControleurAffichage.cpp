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
 * \return Rien
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
	builder->get_widget("radiobutton4", pRadioMeteoFavorable);
	builder->get_widget("radiobutton5", pRadioMeteoNormale);
	builder->get_widget("radiobutton6", pRadioMeteoDefavorable);
	builder->get_widget("radiobutton1", pRadioPressionEnnemisNulle);
	builder->get_widget("radiobutton2", pRadioPressionEnnemisNormale);
	builder->get_widget("radiobutton3", pRadioPressionEnnemisForte);
	builder->get_widget("messagedialog1", pAvertissementCheminFichierOuverture);
	builder->get_widget("messagedialog2", pAvertissementCheminFichiersSauvegarde);
	builder->get_widget("messagedialog3", pAvertissementImpression);
	builder->get_widget("button11", pBoutonAvertissementCheminFichierOuverture);
	builder->get_widget("button13", pBoutonAvertissementCheminFichiersSauvegarde);
	builder->get_widget("button12", pBoutonAvertissementImpression);
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
	
	pCadre->add(carte_A);
	pCadre->add(carte_C);
	carte_A.set_titre("Carte Aptères");
	carte_C.set_titre("Carte Ailés");
	carte_A.show();
	carte_C.show();
	
	pCadreCoeffEnvol->add(courbe_coeff_envol);
	pCadreTauxAccroissement->add(courbe_taux_accroissement);
	
	courbe_coeff_envol.set_echelle(0,30.0,0,0.01);
	courbe_coeff_envol.set_axe_x("Θ(°C)");
	courbe_coeff_envol.set_axe_y("S=20 (Rouge), S=50 (Vert), S=70 (Bleu)");
	courbe_coeff_envol.show();

	coefficient_envol_init();
	
	
	courbe_taux_accroissement.set_echelle(0,30.0,0,0.01);
	courbe_taux_accroissement.set_axe_x("Θ(°C)");
	courbe_taux_accroissement.set_axe_y("S=20 (Rouge), S=50 (Vert), S=70 (Bleu)");
	courbe_taux_accroissement.show();
	
	taux_accroissement_init();
	
	
	
	meteo = 1;
	pression_ennemis = 1;
	
	cheminOuvertureCarte.clear();
	cheminSauvegardeAptere.clear();
	cheminSauvegardeAile.clear();
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
   std::istringstream i(s);
   double x;
   if (!(i >> x))
     return 0;
   return x;
} 

/**
 * \fn void connecter_signaux ()
 * \brief Méthode connectant les signaux des objets de la GUI à leur fonction de call-back
 *
 * \return Rien
 */
void ControleurAffichage::connecter_signaux(){
	pMenuQuitter->signal_activate().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_quitter));
	pMenuOuvrir->signal_activate().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_ouvrir));
	pMenuSauvegarder->signal_activate().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder));
	pMenuImprimer->signal_activate().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_imprimer));
	pMenuAide->signal_activate().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_aide));
	pBoutonAnnulerOuvrir->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_ouvrir_annuler));
	pBoutonAccepterOuvrir->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_ouvrir_accepter));
	pBoutonAnnulerSauvegarderAptere->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder_annuler_aptere));
	pBoutonAccepterSauvegarderAptere->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder_accepter_aptere));
	pBoutonAnnulerSauvegarderAile->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder_annuler_aile));
	pBoutonAccepterSauvegarderAile->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder_accepter_aile));
	pRadioMeteoFavorable->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_choix_meteo));
	pRadioMeteoNormale->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_choix_meteo));
	pRadioMeteoDefavorable->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_choix_meteo));
	pRadioPressionEnnemisNulle->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_choix_pression_ennemis));
	pRadioPressionEnnemisNormale->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_choix_pression_ennemis));
	pRadioPressionEnnemisForte->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_choix_pression_ennemis));
	pBoutonLancerSimulation->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_lancement_simulation));
	pBoutonAvertissementCheminFichierOuverture->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_valider_avertissement));
	pBoutonAvertissementCheminFichiersSauvegarde->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_valider_avertissement));
	pBoutonAvertissementImpression->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_valider_avertissement));
	pBoutonOuvrir->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_ouvrir));
	pBoutonSauvegarder->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_sauvegarder));
	pBoutonImprimer->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_imprimer));
	pBoutonQuitter->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_quitter));
	pBoutonAide->signal_clicked().connect(sigc::mem_fun (this,&ControleurAffichage::on_menu_aide));
	pTa_sm->signal_changed().connect(sigc::mem_fun (this,&ControleurAffichage::on_taux_accroissement_change));
	pTa_b->signal_changed().connect(sigc::mem_fun (this,&ControleurAffichage::on_taux_accroissement_change));
	pTa_a1->signal_changed().connect(sigc::mem_fun (this,&ControleurAffichage::on_taux_accroissement_change));
	pTa_a2->signal_changed().connect(sigc::mem_fun (this,&ControleurAffichage::on_taux_accroissement_change));
	pTa_k->signal_changed().connect(sigc::mem_fun (this,&ControleurAffichage::on_taux_accroissement_change));
	pCe_a->signal_changed().connect(sigc::mem_fun (this,&ControleurAffichage::on_coefficient_envol_change));
	pCe_a0->signal_changed().connect(sigc::mem_fun (this,&ControleurAffichage::on_coefficient_envol_change));
	pCe_a1->signal_changed().connect(sigc::mem_fun (this,&ControleurAffichage::on_coefficient_envol_change));
	pCe_a2->signal_changed().connect(sigc::mem_fun (this,&ControleurAffichage::on_coefficient_envol_change));
	
}

/**
 * \fn Gtk::Window* get_fenetre ()
 * \brief Méthode retournant la fenêtre de l'interface graphique à afficher
 *
 * \return Rien
 */
Gtk::Window* ControleurAffichage::get_fenetre(){
	return pFenetre;
}

/**
 * \fn void on_menu_quitter ()
 * \brief Méthode quittant le logiciel quand un appui sur le menu Simulation/Quitter a été effectué
 *
 * \return Rien
 */
void ControleurAffichage::on_menu_quitter(){
	Gtk::Main::quit();
}

/**
 * \fn void on_menu_ouvrir ()
 * \brief Méthode qui la fenêtre de choix de fichier pour ouvrir un fichier contenant une carte de France.
 * Actif quand Appui sur le menu Simulation/Ouvrir
 *
 * \return Rien
 */
void ControleurAffichage::on_menu_ouvrir(){
	pChoixFichierOuvrir->show();
}	

/**
 * \fn void on_menu_ouvrir_annuler ()
 * \brief Méthode qui annule la fenêtre de choix d'ouverture de fichier de carte de France
 *
 * \return Rien
 */
void ControleurAffichage::on_menu_ouvrir_annuler(){
	pChoixFichierOuvrir->hide();
}

/**
 * \fn void on_menu_ouvrir_accepter ()
 * \brief Méthode récupérant le chemin du fichier qui contient une carte de France et ferme la fenêtre de choix.
 *
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
 * \fn void on_menu_sauvegarder ()
 * \brief Méthode qui ouvre les fenêtres permettant de choisir l'emplacement de sauvegarde des fichiers de Simulation.
 *
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder(){
	pChoixFichierSauvegarderAptere->show();
	pChoixFichierSauvegarderAile->show();
}

/**
 * \fn void on_menu_sauvegarder_annuler_aptere ()
 * \brief Méthode annulant le choix de sauvegarde pour la carte des Aptères.
 *
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder_annuler_aptere(){
	pChoixFichierSauvegarderAptere->hide();
}

/**
 * \fn void on_menu_sauvegarder_accepter_aptere ()
 * \brief Methode récuperant le chemin souhaité pour la sauvegarde de la carte des Aptères.
 *	Ferme également la fenêtre de choix d'emplacement de sauvegarde.
 *Images\\\\coef_depot
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder_accepter_aptere(){
	cheminSauvegardeAptere = pChoixFichierSauvegarderAptere->get_filename();
	pCheminSauvegardeCarteAptere->set_text(cheminSauvegardeAptere);
	pChoixFichierSauvegarderAptere->hide();
}

/**
 * \fn void on_menu_sauvegarder_annuler_aile ()
 * \brief Méthode annulant le choix de sauvegarde pour la carte des Ailés.
 *
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder_annuler_aile(){
	pChoixFichierSauvegarderAile->hide();
}

/**
 * \fn void on_menu_sauvegarder_accepter_aile ()
 * \brief Méthode récupérant le chemin souhaité pour la sauvegarde de la carte des Ailés.
 *	Ferme également la fenêtre de choix d'emplacement de sauvegarde.
 *
 * \return Rien
 */
void ControleurAffichage::on_menu_sauvegarder_accepter_aile(){
	cheminSauvegardeAile = pChoixFichierSauvegarderAile->get_filename();
	pCheminSauvegardeCarteAile->set_text(cheminSauvegardeAile);
	pChoixFichierSauvegarderAile->hide();
}

void ControleurAffichage::on_menu_imprimer(){
	if(!cheminOuvertureCarte.empty()){
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

void ControleurAffichage::on_lancement_simulation(){
Simulation simu;
Lecture_Ecriture lect;
	if (cheminOuvertureCarte.empty())
		pAvertissementCheminFichierOuverture->show();
	else{
		if(cheminSauvegardeAptere.empty() || cheminSauvegardeAile.empty())
			pAvertissementCheminFichiersSauvegarde->show();
		else{
			nb_jour_simulation = (int) string_to_double(pNb_jour_simu->get_text());
			pOnglets->set_current_page(2);
 simu.initialisation(5, 1, "donnees/vitesse_h.csv", "donnees/mat_p.csv", "donnees/mat_p.csv", "donnees/mat_eta.csv", "donnees/coord_s.csv",22,3, "donnees/data_s.csv",367,23,
 "donnees/coord_t.csv", 67,3,"donnees/data_t.csv", 4384,68,"donnees/mat_D.csv","donnees/vitesse_h.csv","donnees/vitesse_v.csv");
			for(int i=1; i < nb_jour_simulation+1;i++){

				simu.iteration(i); 

				carte_A.set_matrice(simu.get_mat_A_retourne());
				carte_C.set_matrice(simu.get_mat_C_retourne());
				carte_A.dessiner_carte(H_MAP,L_MAP,0,0);
				carte_C.dessiner_carte(H_MAP,L_MAP,0,0);
				
			}
				 lect.EcritureCSV(simu.get_mat_A(), cheminSauvegardeAptere); 
				 lect.EcritureCSV(simu.get_mat_C(), cheminSauvegardeAile);
		}
		
	}
}

void ControleurAffichage::on_valider_avertissement(){
	pAvertissementCheminFichierOuverture->hide();
	pAvertissementCheminFichiersSauvegarde->hide();
	pAvertissementImpression->hide();
}

void ControleurAffichage::on_menu_aide(){
	//system("b.html");
}

void ControleurAffichage::coefficient_envol_init(){
	string s_a, s_a0, s_a1, s_a2;
	double d_a, d_a0, d_a1, d_a2;
	
	s_a = pCe_a->get_text();
	s_a0 = pCe_a0->get_text();
	s_a1 = pCe_a1->get_text();
	s_a2 = pCe_a2->get_text();
	
	d_a = string_to_double(s_a);
	d_a0 = string_to_double(s_a0);
	d_a1 = string_to_double(s_a1);
	d_a2 = string_to_double(s_a2);
	
	double **points;

	points = Simulation::coeff_envol(20, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.ajouter_courbe(points, 30);
	points = Simulation::coeff_envol(50, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.ajouter_courbe(points, 30);
	points = Simulation::coeff_envol(70, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.ajouter_courbe(points, 30);
}

void ControleurAffichage::taux_accroissement_init(){
	string s_sm, s_b, s_a1, s_a2, s_k;
	double d_sm, d_b, d_a1, d_a2, d_k;
	
	s_sm = pTa_sm->get_text();
	s_b = pTa_b->get_text();
	s_a1 = pTa_a1->get_text();
	s_a2 = pTa_a2->get_text();
	s_k = pTa_k->get_text();
	
	d_sm = string_to_double(s_sm);
	d_b = string_to_double(s_b);
	d_a1 = string_to_double(s_a1);
	d_a2 = string_to_double(s_a2);
	d_k = string_to_double(s_k);
	
	double **points;
	points = Simulation::taux_accroissement(20, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.ajouter_courbe(points, 30);
	points = Simulation::taux_accroissement(50, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.ajouter_courbe(points, 30);
	points = Simulation::taux_accroissement(70, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.ajouter_courbe(points, 30);
}

void ControleurAffichage::on_coefficient_envol_change(){
	string s_a, s_a0, s_a1, s_a2;
	double d_a, d_a0, d_a1, d_a2;
	
	s_a = pCe_a->get_text();
	s_a0 = pCe_a0->get_text();
	s_a1 = pCe_a1->get_text();
	s_a2 = pCe_a2->get_text();
	
	d_a = string_to_double(s_a);
	d_a0 = string_to_double(s_a0);
	d_a1 = string_to_double(s_a1);
	d_a2 = string_to_double(s_a2);
	
	double **points;

	points = Simulation::coeff_envol(20, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.modifier_courbe(points, 30,0);
	points = Simulation::coeff_envol(50, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.modifier_courbe(points, 30,0);
	points = Simulation::coeff_envol(70, d_a, d_a0, d_a1, d_a2);
	courbe_coeff_envol.modifier_courbe(points, 30,0);

	courbe_coeff_envol.tracer();
}

void ControleurAffichage::on_taux_accroissement_change(){
Simulation simu;
	string s_sm, s_b, s_a1, s_a2, s_k;
	double d_sm, d_b, d_a1, d_a2, d_k;
	
	s_sm = pTa_sm->get_text();
	s_b = pTa_b->get_text();
	s_a1 = pTa_a1->get_text();
	s_a2 = pTa_a2->get_text();
	s_k = pTa_k->get_text();
	
	d_sm = string_to_double(s_sm);
	d_b = string_to_double(s_b);
	d_a1 = string_to_double(s_a1);
	d_a2 = string_to_double(s_a2);
	d_k = string_to_double(s_k);
	
	double **points;
	
	points = Simulation::taux_accroissement(20, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.modifier_courbe(points, 30, 0);
	points = Simulation::taux_accroissement(50, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.modifier_courbe(points, 30, 1);
	points = Simulation::taux_accroissement(70, d_sm, d_b, d_k, d_a1, d_a2);
	courbe_taux_accroissement.modifier_courbe(points, 30, 2);
	
	courbe_taux_accroissement.tracer();
}


