/** \mainpage
 *
 */
 
/**
 * \file interface.cpp
 * \brief Programme principal qui appelle l'interface graphique ainsi que la biliothèque de simulation
 */
 
#include <ctime>
#include <cmath>
#include <iostream>
#include "ControleurAffichage.h"

using namespace std;

int main(int argc, char** argv)
{
/* Initialisation de GTK (obligatoire) */
	Gtk::Main app(argc, argv);
	
	ControleurAffichage ca("gui.glade");
	
	ca.connecter_signaux();
   
   	Gtk::Main::run(*(ca.get_fenetre()));
	
}


