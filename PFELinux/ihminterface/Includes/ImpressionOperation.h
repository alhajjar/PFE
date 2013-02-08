/**
 * \file ImpressionOperation.h
 * \brief fichier d'entête de la bibliothèque permettant l'impression d'un rapport de résultat
 */

#ifndef GTKMM_IMPRESSION_OPERATION_H
#define GTKMM_IMPRESSION_OPERATION_H

#include <pangomm.h>
#include <gtkmm.h>
#include <ctime>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

/** \class ImpressionOperation
  * \brief Classe gérant l'impression de rapports de résultats
  * Cette classe hérite de la classe PrintOperation de Gtk.
  */
class ImpressionOperation : public Gtk::PrintOperation
{
public:
	ImpressionOperation();
	virtual ~ImpressionOperation();

	static Glib::RefPtr<ImpressionOperation> create();
	void set_gdk_pixbuf(Glib::RefPtr<Gdk::Pixbuf> pix, const int num);
	void set_taille_carte(int h_carte, int l_carte);
	void set_valeur_min(int val, int num);
	void set_valeur_max(int val, int num);

protected:
/* Surcharge des gestionnaires de signaux par défaut */
	virtual void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context);
	virtual void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context, int page_nr);

private:
/* Contexte graphique pour la bibliothèque qui permet de faire l'impression de la zone de dessin */
	Glib::RefPtr<Gdk::Pixbuf> pixbuf[2];
	
	int hauteur_carte, largeur_carte;
	string valeur_min_A, valeur_max_A, valeur_min_C, valeur_max_C;
};

#endif