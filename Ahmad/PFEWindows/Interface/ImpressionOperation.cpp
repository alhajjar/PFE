/**
 * \file ImpressionOperation.cpp
 * \brief fichier du contenu des méthodes de la bibliothèque gérant l'impression d'un rapport de résultats
 */

#include "Includes/ImpressionOperation.h"

/** \fn ImpressionOperation::ImpressionOperation()
 *  \brief Constructeur de la classe ImpressionOperation
 *  \return Rien
 */
ImpressionOperation::ImpressionOperation(){
}

/** \fn ImpressionOperation::~ImpressionOperation()
 *  \brief Destructeur de la classe ImpressionOperation
 *  \return Rien
 */
ImpressionOperation::~ImpressionOperation(){
}

/** \fn Glib::RefPtr<ImpressionOperation> ImpressionOperation::create()
 *  \brief Méthode créant une opération d'impression
 *  \return Glib::RefPtr<ImpressionOperation> Pointeur sur l'opération d'impression créée
 */
Glib::RefPtr<ImpressionOperation> ImpressionOperation::create(){
  return Glib::RefPtr<ImpressionOperation>(new ImpressionOperation());
}

/** \fn void ImpressionOperation::set_gdk_pixbuf(Glib::RefPtr<Gdk::Pixbuf> pix, const int num)
 *  \brief Méthode insérant les zones de dessin à imprimer
 *  \param pix Tableau de zone de dessin à insérer
 *  \param num Nombre de zone de dessins à insérer
 *  \return Rien
 */
void ImpressionOperation::set_gdk_pixbuf(Glib::RefPtr<Gdk::Pixbuf> pix, const int num){
	pixbuf[num] = pix;
}

/** \fn void ImpressionOperation::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& print_context)
 *  \brief Méthode surchargeant la même méthode de la classe héritée PrintOperation
 *  \param print_context Contexte d'impression
 *  \return Rien
 */
void ImpressionOperation::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& print_context){
/* Nombre de pages dans le document */
	set_n_pages(1);
}

/** \fn void ImpressionOperation::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr)
 *  \brief Méthode surchargeant la même méthode de la classe héritée PrintOperation
 *  \param print_context Contexte de l'impression
 *  \int page_nr Numéro de la page à imprimer
 *  \return Rien
 */
void ImpressionOperation::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr){
	time_t temps_act; 
	
	string phrase_date;
	ostringstream phrase;

/* Récupération du contexte graphique cairo */
	Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();
  
/* Récupération de la largeur de la page a imprimer */
	int largeur_page = print_context->get_width();
/* Récupération de la hauteur de la page a imprimer */
	int hauteur_page = print_context->get_height();
	
/* La marge = 2.5 cm qu'il faut convertir en pixels */
	int marge = ((largeur_page * 5)/21)/2;
/* La largeur utile sert à redimesionner la carte de France avec le bon facteur et la centrer pour l'impression */	
	int largeur_utile = largeur_page - (4 * marge);
	double facteur_agrandissement = largeur_utile/largeur_carte;
  
/* Redimensionnement du pixbuf car trop petit par rapport à la page d'impression */
	pixbuf[0] = pixbuf[0]->scale_simple(facteur_agrandissement * largeur_carte, facteur_agrandissement * hauteur_carte, Gdk::INTERP_HYPER);
	pixbuf[1] = pixbuf[1]->scale_simple(facteur_agrandissement * largeur_carte, facteur_agrandissement * hauteur_carte, Gdk::INTERP_HYPER);
	
/* pixbuf va dans le contexte_cairo servant à l'impression */
	Gdk::Cairo::set_source_pixbuf(cairo_ctx, pixbuf[0], 2 * marge, 400 + marge);
	
/* Affichage du contexte cairo (pour mettre à jour l'insertion du pixbuf */
	cairo_ctx->paint();
	
/* pixbuf va dans le contexte_cairo servant à l'impression */
	Gdk::Cairo::set_source_pixbuf(cairo_ctx, pixbuf[1], 2 * marge, 400 + marge + facteur_agrandissement * hauteur_carte + 300);
	
/* Affichage du contexte cairo (pour mettre à jour l'insertion du pixbuf */
	cairo_ctx->paint();
	
/* Insertion de texte pour présenter les résultats de la simulation */
	Cairo::TextExtents extents;
	
/* Insertion du titre */
	cairo_ctx->set_source_rgb(0, 0, 0);
	cairo_ctx->set_font_size(250);
	cairo_ctx->select_font_face("Sans",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_BOLD);
	cairo_ctx->get_text_extents("Resultats", extents);
	cairo_ctx->move_to((largeur_page/2) - (extents.width/2), marge + (extents.height/2));  
	cairo_ctx->show_text("Resultats");  
	
/* Insertion de la date et de l'heure au moment de l'impression */
	cairo_ctx->set_font_size(90);
	cairo_ctx->move_to(marge, marge + 300);
	
/* Récupération de la date et du temps */
	time(&temps_act);
	struct tm * tm = localtime(&temps_act);

	phrase <<"La simulation a ete realisee le " << tm->tm_mday << "/" << (tm->tm_mon + 1) << "/" << (1900 + tm->tm_year) << " a " << tm->tm_hour << "h" << tm->tm_min << "." ;
	
	cairo_ctx->show_text(phrase.str());
	
/* Insertion du minimum et du maximum pour la carte des aptères */
	cairo_ctx->move_to(marge, 400 + marge + facteur_agrandissement * hauteur_carte + 80);  
	cairo_ctx->show_text((valeur_min_A + valeur_max_A).c_str()); 
	
/* /* Insertion du minimum et du maximum pour la carte des ailés */
	cairo_ctx->move_to(marge, 400 + marge + 2 * facteur_agrandissement * hauteur_carte + 380);  
	cairo_ctx->show_text((valeur_min_C + valeur_max_C).c_str()); 
	
	cairo_ctx->fill();
}

/** \fn void ImpressionOperation::set_taille_carte(int h_carte, int l_carte)
 *  \brief Méthode définissant la taille des cartes pour les redimensionner à l'affichage de l'impression
 *  \param h_carte Hauteur de la carte
 *  \param l_carte Largeur de la carte
 *  \return Rien
 */
void ImpressionOperation::set_taille_carte(int h_carte, int l_carte){
	hauteur_carte = h_carte;
	largeur_carte = l_carte;
}

/** \fn void ImpressionOperation::set_valeur_min(int val, int num)
 *  \brief Méthode permettant l'affichage du minimum de toutes les matrices pour la simulation
 *  \param val Valeur minimale à afficher
 *  \param num Numéro de la carte pour laquelle doit être afficher le minimum
 *  \return Rien
 */
void ImpressionOperation::set_valeur_min(int val, int num){
	stringstream *sstr = new stringstream();
	
	if(num == 0){
		*sstr << "Le minimum pour la matrice des Apteres est " << val;
		valeur_min_A = sstr->str();
	}
	else{
		*sstr << "Le minimum pour la matrice des Ailes est " << val;
		valeur_min_C = sstr->str();
	}
}

/** \fn void ImpressionOperation::set_valeur_max(int val, int num)
 *  \brief Méthode permettant l'affichage du maximum de toutes les matrices pour la simulation
 *  \param val Valeur maximale à afficher
 *  \param num Numéro de la carte pour laquelle doit être afficher le maximum
 *  \return Rien
 */
void ImpressionOperation::set_valeur_max(int val, int num){
	stringstream *sstr = new stringstream();
	
	*sstr << " et le maximum est " << val << ".";
	if(num == 0)
		valeur_max_A = sstr->str();
	else
		valeur_max_C = sstr->str();
}
