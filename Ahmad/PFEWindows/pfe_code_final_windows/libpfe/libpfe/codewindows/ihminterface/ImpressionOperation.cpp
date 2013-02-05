#include "ImpressionOperation.h"

ImpressionOperation::ImpressionOperation(){
}

ImpressionOperation::~ImpressionOperation(){
}

Glib::RefPtr<ImpressionOperation> ImpressionOperation::create(){
  return Glib::RefPtr<ImpressionOperation>(new ImpressionOperation());
}

void ImpressionOperation::set_gdk_pixbuf(Glib::RefPtr<Gdk::Pixbuf> pix, const int num){
	pixbuf[num] = pix;
}

void ImpressionOperation::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& print_context){
/* Nombre de pages dans le document */
	set_n_pages(1);
}

void ImpressionOperation::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr){
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
	cairo_ctx->get_text_extents("Résultats", extents);
	cairo_ctx->move_to((largeur_page/2) - (extents.width/2), marge + (extents.height/2));  
	cairo_ctx->show_text("Résultats");  
	
/* Insertion de la date et de l'heure au moment de l'impression */
	cairo_ctx->set_font_size(90);
	cairo_ctx->move_to(marge, marge + 300);
	
	time_t temps_act; 
	
	std::string phrase_date;
	std::ostringstream phrase;
	
	time(&temps_act);
	struct tm * tm = localtime(&temps_act);
	phrase <<"La simulation a été realisée le " << tm->tm_mday << "/" << (tm->tm_mon + 1) << "/" << (1900 + tm->tm_year) << " à " << tm->tm_hour << "h" << tm->tm_min << "." ;
	
	cairo_ctx->show_text(phrase.str());
	
	cairo_ctx->move_to(marge, 400 + marge + facteur_agrandissement * hauteur_carte + 80);  
	cairo_ctx->show_text((valeur_min_A + valeur_max_A).c_str()); 
	
	cairo_ctx->move_to(marge, 400 + marge + 2 * facteur_agrandissement * hauteur_carte + 380);  
	cairo_ctx->show_text((valeur_min_C + valeur_max_C).c_str()); 
	
	cairo_ctx->fill();
}

void ImpressionOperation::set_taille_carte(int h_carte, int l_carte){
	hauteur_carte = h_carte;
	largeur_carte = l_carte;
}

void ImpressionOperation::set_valeur_min(int val, int num){
	stringstream sstr;
	
	if(num == 0){
		sstr << "Le minimum pour la matrice des Aptères est " << val;
		valeur_min_A = sstr.str();
	}
	else{
		sstr << "Le minimum pour la matrice des Ailés est " << val;
		valeur_min_C = sstr.str();
	}
}

void ImpressionOperation::set_valeur_max(int val, int num){
	stringstream sstr;
	
	sstr << " et le maximum est " << val << ".";
	if(num == 0)
		valeur_max_A = sstr.str();
	else
		valeur_max_C = sstr.str();
}
