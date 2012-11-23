/**
 * \file Dessin.cpp
 * \brief fichier du contenu des methodes de la bibliotheque de la zone de dessin
 * \author Francois Blouin
 * \date 20 novembre 2012
 */

#include "Dessin.h"

/**
 * \fn Dessin ()
 * \brief Constructeur de la classe Dessin
 *
 * \return vide
 */
Dessin ::Dessin ()
{
	this->add_events(Gdk::BUTTON_PRESS_MASK);
	this->add_events(Gdk::BUTTON1_MOTION_MASK);
	this->add_events(Gdk::BUTTON2_MOTION_MASK);
	this->add_events(Gdk::BUTTON3_MOTION_MASK);
	this->add_events(Gdk::BUTTON_RELEASE_MASK);
	this->signal_event().connect(sigc::mem_fun(*this,
	&Dessin::on_event_happend) );
}

/**
 * \fn ~Dessin ()
 * \brief Destructeur de la classe Dessin
 *
 * \return vide
 */
Dessin ::~Dessin ()
{
}

/**
 * \fn bool on_expose_event (GdkEventExpose* event)
 * \brief Methode gerant l'exposition de la zone de dessin
 *
 * \param event Evenement d'exposition ayant provoque l'instanciation de la methode
 * \return Indicateur de bon déroulement de la méthode
 */
bool Dessin ::on_expose_event(GdkEventExpose* event)
{
	
/* Fond d'ecran */

	dessiner_carte();
	
}

/**
 * \fn bool on_event_happend (GdkEvent* event)
 * \brief Methode gerant les evenements de la souris
 *
 * \param event Evenement (appui souris, mouvement en restant appuye ou relachement de la souris) ayant provoque l'instanciation de la methode
 * \return Indicateur de bon déroulement de la méthode
 */
bool Dessin ::on_event_happend(GdkEvent* event){
	if (event->type == GDK_BUTTON_PRESS) {
		x = event->button.x;
		y = event->button.y;
		type_bouton = event->button.button;
	}
	if (event->type == GDK_MOTION_NOTIFY) {
		dessiner_cadre_selection_zoom(event->button.x, event->button.y);
	}
	if (event->type == GDK_BUTTON_RELEASE) {
		switch (type_bouton){
			case 1:
				zoom(event->button.x, event->button.y);
				break;
			case 2:
				dezoom();
				break;
			case 3:
				dezoom();
				break;
			default: 
				break;
		}
		type_bouton = 0;
	}
	return false;
}

/**
 * \fn void zoom (int abs, int ord)
 * \brief Methode gerant le zoom sur une zone de dessin
 *
 * \param abs Abscisse du point de relachement de la souris. Permet de definir la zone de zoom
 * \param ord Ordonnee du point de relachement de la souris. Permet de definir la zone de zoom
 * \return vide
 */
void Dessin::zoom(int abs, int ord){
/* On efface le cadre de sélection */
	
	dessiner_carte();
	
/* Si un clic ou juste un zoom sur une ligne a ete fait, le programme ne zoome pas */

	if(abs == x || ord == y){
	
	}
	else{
		
	}
}

/**
 * \fn void dezoom ()
 * \brief Methode gerant le dezoom sur une zone de dessin
 *
 * \return vide
 */
void Dessin::dezoom(){

}

/**
 * \fn void dessiner_cadre_selection_zoom (int abs, int ord)
 * \brief Methode gerant le dessin et la mise à jour du cadre de selection de la zone de zoom
 *
 * \param abs Abscisse du point ou se trouve la souris. Permet de definir la zone du cadre a dessiner
 * \param ord Ordonnee du point ou se trouve la souris. Permet de definir la zone du cadre a dessiner
 * \return vide
 */
void Dessin::dessiner_cadre_selection_zoom(int abs, int ord){
/* Si clic gauche */
	if(type_bouton == 1){
		dessiner_carte();
		
		cr->set_source_rgb(0.0, 0.0, 0.0);
		cr->rectangle(x, y, abs - x, ord - y);
		cr->stroke();
	}
}

/**
 * \fn void dessiner_carte ()
 * \brief Methode gerant le dessin de la carte de base. Elle est utilisee a chaque fois qu'il y a un evenement sur la zone de dessin
 *
 * \return vide
 */
void Dessin::dessiner_carte(){
/* Fond d'ecran */

	cr = this->get_window()->create_cairo_context();
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->rectangle(0, 0, 1000, 650);
	cr->fill();
}