/**
 * \file Dessin.h
 * \brief fichier d'entete de la bibliotheque de la zone de dessin
 * \author Francois Blouin
 * \date 20 novembre 2012
 */

#ifndef DESSIN_H
#define DESSIN_H

#include <gtkmm.h>
#include <cairomm/cairomm.h>

using namespace std;

/** \class Dessin
  * \brief Classe representant la zone de dessin sur laquelle on affiche la carte et avec laquelle on peut interagir
  * 	   Surcharge la classe DrawingArea
  *
  */
class Dessin : public Gtk::DrawingArea
{
public:
  Dessin ();
  virtual ~Dessin ();

protected:
/* Contexte graphique pour la bibliothèque qui permet de faire les dessins Cairo */
	Cairo::RefPtr<Cairo::Context> cr;	

/* Surcharger les méthodes par défaut des call-back de signaux d'evenements */
   virtual bool on_expose_event(GdkEventExpose* event);
   virtual bool on_event_happend(GdkEvent* event);
   
private:
/* attributs de coordonnées de la souris et du type de bouton de souris utilisé */
	int x,y,type_bouton;
	
/* Methodes pour intergir avec la zone de dessin */
	void zoom(int abs, int ord);
	void dezoom();
	void dessiner_cadre_selection_zoom(int abs, int ord);
	void dessiner_carte();
};

#endif