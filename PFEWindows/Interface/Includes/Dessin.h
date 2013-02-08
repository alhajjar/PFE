/**
 * \file Dessin.h
 * \brief fichier d'entête de la bibliothèque de la zone de dessin
 */

#ifndef DESSIN_H
#define DESSIN_H

/* Hauteur et largeur par défaut pour la zone de dessin */
#define H_MAP 570
#define L_MAP 570

#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <iostream>
#include <cstdlib>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Lecture_Ecriture.hpp"

using namespace std;

/** \class Dessin
  * \brief Classe représentant la zone de dessin sur laquelle est affichée la carte avec laquelle l'utilisateur peut interagir
  * Cette classe hérite de la classe DrawingArea de Gtk.
  */
class Dessin : public Gtk::DrawingArea
{
public:
	Dessin ();
	virtual ~Dessin ();

	Glib::RefPtr<Gdk::Pixbuf> get_gdk_pixbuf();
	void set_chemin_carte(string path);
	void set_titre(string untitre);
	string get_titre();
	int get_hauteur();
	int get_largeur();
	double get_valeur_min();
	double get_valeur_max();
	void set_matrice(Matrice mat);
	Matrice get_matrice();
	void dessiner_carte(int hauteur, int largeur, int decalage_y, int decalage_x);
  	string enregistrement(int num, string chemin);
	void lecture_coordonnees_points();
	bool get_activation();
	void init();
  
protected:
/* Contexte graphique pour la bibliothèque qui permet de faire les dessins Cairo */
	Cairo::RefPtr<Cairo::Context> cr;
/* Surface du dessin au sens de GDK */
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;

/* Surcharge des méthodes par défaut des call-back de signaux d'évènements */
   virtual bool on_expose_event(GdkEventExpose* event);
   virtual bool on_event_happend(GdkEvent* event);
   
private:
/* Attributs de coordonnées de la souris et du type de bouton de souris utilisé */
	int x, y, type_bouton;
/* Indicateur de zoom déjà activé ou non */
	bool zoom_actif;
	bool cadre_actif;
/* Attributs servant pour le zoom */
	int hauteur_zoom, largeur_zoom;
	double decalage_x_zoom, decalage_y_zoom;
/* Chemin de la carte */
	string chemin_carte;
/* Titre de la carte */	
	string titre;
	Matrice matrice;
	int valeur_min;
	int valeur_max;

	double *abscisse_points;
	double *ordonnee_points;

/* Valeur servant à savoir si la zone de dessin a déjà été dessiné */
	bool actif;

/* Valeur déterminant si c'est la première carte de la simulation pour déterminer le min et max du gradient */
	bool initialisation;
	
/* Méthodes pour interagir avec la zone de dessin */
	void zoom(int abscisse, int ordonnee);
	void dezoom();
	void dessiner_cadre_selection_zoom(int abscisse, int ordonnee);
	
	double **lire_carte(int hauteur, int largeur, string chemin);
	double **points_dans_polygone(int ordonnees[194], string chemin);
	
	double gradient_couleur(double min, double max, double val, char composante);
};

#endif
