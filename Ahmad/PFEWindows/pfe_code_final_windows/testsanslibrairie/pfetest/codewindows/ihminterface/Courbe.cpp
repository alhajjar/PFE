#include "Courbe.h"

Courbe ::Courbe(){
	x_min_lettre.clear();
	x_max_lettre.clear();
	y_min_lettre.clear();
	y_max_lettre.clear();
	
/* Remplissage du tableau des couleurs statiquement pour une meilleure répartition des couleurs */
	couleurs[0][0] = 1;
	couleurs[0][1] = 0;
	couleurs[0][2] = 0;
	couleurs[1][0] = 0;
	couleurs[1][1] = 1;
	couleurs[1][2] = 0;
	couleurs[2][0] = 0;
	couleurs[2][1] = 0;
	couleurs[2][2] = 1;
	couleurs[3][0] = 1;
	couleurs[3][1] = 1;
	couleurs[3][2] = 0;
	couleurs[4][0] = 1;
	couleurs[4][1] = 0;
	couleurs[4][2] = 1;
	couleurs[5][0] = 0;
	couleurs[5][1] = 1;
	couleurs[5][2] = 1;
	couleurs[6][0] = 0.25;
	couleurs[6][1] = 0;
	couleurs[6][2] = 0;
	couleurs[7][0] = 0;
	couleurs[7][1] = 0.25;
	couleurs[7][2] = 0;
	couleurs[8][0] = 0;
	couleurs[8][1] = 0;
	couleurs[8][2] = 0.25;
	couleurs[9][0] = 1;
	couleurs[9][1] = 0.25;
	couleurs[9][2] = 0;
	couleurs[10][0] = 1;
	couleurs[10][1] = 0;
	couleurs[10][2] = 0.25;
	couleurs[11][0] = 0;
	couleurs[11][1] = 1;
	couleurs[11][2] = 0.25; 
	couleurs[12][0] = 0.25;
	couleurs[12][1] = 1;
	couleurs[12][2] = 0;
	couleurs[13][0] = 0.25;
	couleurs[13][1] = 0;
	couleurs[13][2] = 1;
	couleurs[14][0] = 0;
	couleurs[14][1] = 0.25;
	couleurs[14][2] = 1;
}
	
Courbe ::~Courbe(){}
 
 bool Courbe ::on_expose_event(GdkEventExpose* event)
{
	width= this->get_width() ;
	height= this->get_height() ;
	tracer();
}

void Courbe::set_echelle(double x_min, double x_max, double y_min, double y_max){
    stringstream sstr;
	
    sstr << x_min;
	x_min_lettre = sstr.str();
	sstr.str(string());
	
	sstr << x_max;
	x_max_lettre = sstr.str();
	sstr.str(string());
	
	sstr << y_min;
	y_min_lettre = sstr.str();
	sstr.str(string());
	
	sstr << y_max;
	y_max_lettre = sstr.str();
	sstr.str(string());
	
	this->x_min = x_min; 
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;
}

void Courbe::set_axe_x(string axe_x){
	titre_abcsisse = axe_x;
}

void Courbe::set_axe_y(string axe_y){
	titre_ordonnee = axe_y;
}

void Courbe::ajouter_courbe(double **points, int size){
	abscisse.resize(abscisse.size() + 1);
	ordonnee.resize(ordonnee.size() + 1);
	for(int i=0; i<size; i++){
		abscisse[abscisse.size()-1].push_back(points[i][0]);
		ordonnee[ordonnee.size()-1].push_back(points[i][1]);
		if(points[i][1] > y_max)
			y_max = points[i][1] ;
		if(points[i][1] < y_min)
			y_min = points[i][1] ;
	}
	set_echelle(x_min, x_max, y_min, y_max);
}

void Courbe::modifier_courbe(double **points, int size, int num){
	abscisse[num].erase(abscisse[num].begin(),abscisse[num].end());
	ordonnee[num].erase(ordonnee[num].begin(),ordonnee[num].end());
	for(int i=0; i<size;i++){
		abscisse[num].push_back(points[i][0]);
		ordonnee[num].push_back(points[i][1]);
		if(points[i][1] > y_max)
			y_max = points[i][1];
		if(points[i][1] < y_min)
			y_min = points[i][1];
	}
	set_echelle(x_min, x_max, y_min, y_max);
}

void Courbe::tracer(){
	double echelle_x = 410/(x_max-x_min);
	double echelle_y = 460/(y_max-y_min);

	cr = this->get_window()->create_cairo_context();
	
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->rectangle(0, 0, width,height);
	cr->fill();
/* La couleur est noire */
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->set_line_width(1.0);
	
	cr->move_to(50, height - 20);
	cr->line_to(50, 20);
	cr->move_to(50, height - 20);
	cr->line_to(width - 40, height - 20);
	
	cr->stroke();
	
	Cairo::TextExtents extents;
	
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->set_font_size(12);
	cr->select_font_face("Sans",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_BOLD);
	
/* x_min */
	cr->get_text_extents(x_min_lettre.c_str(), extents);
	cr->move_to(50 - (extents.width/2), height - 5);
	cr->show_text(x_min_lettre.c_str());	
	
/* x_max */
	cr->get_text_extents(x_max_lettre.c_str(), extents);
	cr->move_to(width - 40 - (extents.width/2), height - 5);
	cr->show_text(x_max_lettre.c_str());	
	
/* y_min */
	cr->get_text_extents(y_min_lettre.c_str(), extents);
	if(extents.width >= 50)
		cr->move_to(2, height - 20 + (extents.height/2));
	else
		cr->move_to(50 - extents.width - 2, height - 20 + (extents.height/2));
	cr->show_text(y_min_lettre.c_str());
	
/* y_max */
	cr->get_text_extents(y_max_lettre.c_str(), extents);
	if(extents.width >= 50)
		cr->move_to(2, 20 + (extents.height/2));
	else
		cr->move_to(50 - extents.width - 2, 20 + (extents.height/2));
	cr->show_text(y_max_lettre.c_str());

/* titre_abcisse */	
	cr->get_text_extents(titre_abcsisse.c_str(), extents);
	cr->move_to( width - 37 , height - 22 +(extents.height/2));
	cr->show_text(titre_abcsisse.c_str());

/* titre_ordonnee */
	cr->get_text_extents(titre_ordonnee.c_str(), extents);
	if(extents.width >= 50)
		cr->move_to(2, 2 + extents.height);
	else
		cr->move_to(50 - (extents.width/2), 2 + extents.height);
	cr->show_text(titre_ordonnee.c_str());
	
	cr->set_line_width(2.0);
	
	for(int i=0; i<ordonnee.size();i++){
		for(int j=0; j<ordonnee[i].size();j++){
			cr->move_to((abscisse[i].at(j) * echelle_x) + 50, height - 20 - (ordonnee[i].at(j) * echelle_y) + (y_min * echelle_y));
			cr->set_source_rgb(couleurs[i][0], couleurs[i][1], couleurs[i][2]);
			cr->arc ((abscisse[i].at(j) * echelle_x) + 50, height - 20 - (ordonnee[i].at(j) * echelle_y) + (y_min * echelle_y), 3, 0, 2 * M_PI);	
			cr->move_to((abscisse[i].at(j) * echelle_x) + 50, height - 20 - (ordonnee[i].at(j) * echelle_y) + (y_min * echelle_y));
			cr->fill();
		}
	}
	cr->stroke();	
	cr->fill();
}
