/**
 * \file Courbe.h
 * \brief fichier d'entête de la bibliothèque dessinant des courbes
 */

#ifndef COURBE_H
#define COURBE_H

#include <iostream>
#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

/** \class Courbe
 *  \brief Classe gérant l'affichage d'un graphe et de plusieurs courbes
 */
class Courbe : public Gtk::DrawingArea
{
public:
	
	Courbe();
	virtual ~Courbe();
  
	void set_echelle(double x_mi, double x_ma, double y_mi, double y_ma);
	void set_axe_x(string axe_x);
	void set_axe_y(string axe_y);
	void ajouter_courbe(double **points, int size);
	void modifier_courbe(double **points, int size, int num);
	void tracer();

/* Surcharge de la méthode par défaut du call-back du signal d'exposition */
    virtual bool on_expose_event(GdkEventExpose* event);
 
private:
	Cairo::RefPtr<Cairo::Context> cr;
	int height, width;
	string x_min_lettre, x_max_lettre, y_min_lettre, y_max_lettre;
	double x_min, x_max;
	double y_min, y_max;
	string titre_abcsisse,titre_ordonnee;
	vector< vector<double> > abscisse;
	vector< vector<double> > ordonnee;
	double couleurs[15][3];
 };
 
#endif