#include <ctime>
#include <cmath>
#include <iostream>
#include "Dessin.h"
#include "ControleurAffichage.h"

using namespace std;

/*void on_menu_ouvrir(){
	pFileChoose->set_action(GTK_FILE_CHOOSER_ACTION_OPEN);
	pFileChoose->show();
}

void on_menu_clic(){
	pFileChoose->hide();
	cout << pFileChoose->get_filename() <<endl; 
}*/

int main(int argc, char** argv)
{
/* Initialisation de GTK (obligatoire) */
	Gtk::Main app(argc, argv);
	
	ControleurAffichage ca("gui.glade");
	
	ca.connecter_signaux();

   	Gtk::Main::run(*(ca.get_fenetre()));
	
}


