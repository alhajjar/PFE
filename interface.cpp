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

	// Gtk::FileChooserDialog* pFileChoose = 0;

	//builder->get_widget("filechooserdialog1", pFileChoose);
	//builder->get_widget("button5", pButton);
	

	/*pMenuOuvrir->signal_activate().connect(sigc::ptr_fun (&on_menu_ouvrir));
	pButton->signal_clicked().connect(sigc::ptr_fun (&on_menu_clic));*/
	
	ControleurAffichage ca("gui.glade");
	
	ca.connecter_signaux();

   	Gtk::Main::run(*(ca.get_fenetre()));
	
}


