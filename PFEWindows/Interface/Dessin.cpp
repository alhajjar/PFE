/**
 * \file Dessin.cpp
 * \brief fichier du contenu des méthodes de la bibliothèque gérant la zone de dessin et l'affichage de la carte
 */

#include "Includes/Dessin.h"

/**
 * \fn Dessin::Dessin ()
 * \brief Constructeur de la classe Dessin
 * \return Rien
 */
Dessin::Dessin ()
{
	lecture_coordonnees_points();

/* Ajout d'évènements non gérés par défaut par DrawingArea */
	this->add_events(Gdk::BUTTON_PRESS_MASK);
	this->add_events(Gdk::BUTTON1_MOTION_MASK);
	this->add_events(Gdk::BUTTON2_MOTION_MASK);
	this->add_events(Gdk::BUTTON3_MOTION_MASK);
	this->add_events(Gdk::BUTTON_RELEASE_MASK);
	this->signal_event().connect(sigc::mem_fun(*this, &Dessin::on_event_happend));

/* Initialisation des valeurs de la taille de la carte avec des valeurs par défaut */

	zoom_actif = 0;
	hauteur_zoom = H_MAP;
	largeur_zoom = H_MAP;
	decalage_x_zoom = 0;
	decalage_y_zoom = 0;
	
	matrice = Matrice(194, 196);
	matrice = Matrice::Zero(194, 196);
	valeur_min =  0;
	valeur_max =  0;

	actif = 0;
	initialisation = 0;
}

/**
 * \fn Dessin::~Dessin ()
 * \brief Destructeur de la classe Dessin
 * \return Rien
 */
Dessin::~Dessin ()
{
}

/**
 * \fn bool Dessin::on_expose_event (GdkEventExpose* event)
 * \brief Méthode gérant l'exposition de la zone de dessin
 * \param event Evénèment d'exposition ayant provoqué l'instanciation de la méthode
 * \return Indicateur de bon déroulement de la méthode
 */
bool Dessin::on_expose_event(GdkEventExpose* event){
	dessiner_carte(H_MAP, L_MAP, 0, 0);

	actif = 1;

	return 1;
}

/**
 * \fn bool Dessin::on_event_happend (GdkEvent* event)
 * \brief Méthode gérant les évènements de la souris
 * \param event Evènement (appui souris, mouvement en restant appuyé ou relâchement de la souris) ayant provoqué l'instanciation de la méthode
 * \return Indicateur de bon deroulement de la méthode
 */
bool Dessin::on_event_happend(GdkEvent* event){
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
 * \fn void Dessin::zoom (int abscisse, int ordonnee)
 * \brief Méthode gérant le zoom sur une zone de dessin
 * \param abscisse Abscisse du point de relâchement de la souris. Permet de définir la zone de zoom
 * \param ordonnee Ordonnée du point de relâchement de la souris. Permet de définir la zone de zoom
 * \return Rien
 */
void Dessin::zoom(int abscisse, int ordonnee){
/* Si un clic ou juste un zoom sur une ligne a été fait, le programme ne zoome pas */
	if(abscisse == x || ordonnee == y || zoom_actif == 1){
	}
	else{
		hauteur_zoom = H_MAP * ((double) H_MAP / abs(ordonnee - y));
		
		if(y < ordonnee)
			decalage_y_zoom = (double)(y * hauteur_zoom)/H_MAP;
		else
			decalage_y_zoom = (double)(ordonnee * hauteur_zoom)/H_MAP;
		
		if(x < abscisse)
			decalage_x_zoom = ((double)(x * hauteur_zoom)/H_MAP);
		else
			decalage_x_zoom = ((double)(abscisse * hauteur_zoom)/H_MAP);
				
		largeur_zoom = hauteur_zoom;
		
/* Le zoom vient d'être activé */
		zoom_actif = 1;

/* Effacement du cadre de sélection et zoom */
		dessiner_carte(hauteur_zoom, largeur_zoom, decalage_y_zoom, decalage_x_zoom);
		

	}
	cadre_actif = 0;
}

/**
 * \fn void Dessin::dezoom ()
 * \brief Méthode gérant le dézoom sur une zone de dessin
 * \return Rien
 */
void Dessin::dezoom(){
/* Retour aux valeurs par défaut des variables de l'affichage de la carte */
	zoom_actif = 0;
	hauteur_zoom = H_MAP;
	largeur_zoom = L_MAP;
	decalage_x_zoom = 0;
	decalage_y_zoom = 0;
	
	cr = this->get_window()->create_cairo_context();
	Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file("Images/tmp_" + get_titre()  + ".png");
	Gdk::Cairo::set_source_pixbuf(cr, image, 0, 0);
	cr->paint();
}

/**
 * \fn void Dessin::dessiner_cadre_selection_zoom (int abs, int ord)
 * \brief Méthode gérant le dessin et la mise à jour du cadre de sélection de la zone de zoom
 * \param abscisse Abscisse du point où se trouve la souris. Permet de définir la zone du cadre à dessiner
 * \param ordonnee Ordonnée du point où se trouve la souris. Permet de définir la zone du cadre à dessiner
 * \return Rien
 */
void Dessin::dessiner_cadre_selection_zoom(int abscisse, int ordonnee){
/* Si clic gauche */
	if(type_bouton == 1 && zoom_actif == 0){
/* Si le cadre de sélection n'a pas été utilisé */
		if(cadre_actif == 0){
/* Création d'une image temporaire qui est un print_screen de la carte */
			get_gdk_pixbuf();
			cadre_actif = 1;
		}
/* Utilisation de l'image temporaire au lieu de tout redessinner. L'avantage est la vitesse d'exécution (immédiat ici par rapport à quelques secondes pour */
/* tout redessiner */
		cr = this->get_window()->create_cairo_context();
		Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file("Images/tmp_" + get_titre()  + ".png");
		Gdk::Cairo::set_source_pixbuf(cr, image, 0, 0);
/* Ne pas oublier de "peindre" l'image sinon la misa à jour de la zone de dessin n'est pas effectué*/
		cr->paint();
/* Dessin du rectangle de sélection */
		cr->set_source_rgb(0.0, 0.0, 0.0);
		cr->rectangle(x, y, abscisse - x, ordonnee - y);
		cr->stroke();
	}
}

/** \fn void Dessin::lecture_coordonnees_points()
 *  \brief Lecture des coordonnées de chaque points de la matrice à dessiner
 *  \return Rien
 */
void Dessin::lecture_coordonnees_points(){
	Lecture_Ecriture lect;
	Matrice mat_abs(194, 196);
	Matrice mat_ord(194, 196);
/* Ajout des coordonnées des points sur la carte de France */
	lect.LectureCSV(195, 196, "donnees/abscisse.csv");
	mat_abs = lect.get_CSV();

	lect.LectureCSV(195, 196, "donnees/ordonnee.csv");
	mat_ord = lect.get_CSV();
	
	abscisse_points = new double[38024];
	ordonnee_points = new double[38024];

	int f = 0;
	for(int i = 0; i < 194; i++){
		for(int j = 0; j < 196; j++){
			abscisse_points[f] = mat_abs(i,j); 
			ordonnee_points[f] = mat_ord(i,j);
			f++;
		}
	}
}

/**
 * \fn void Dessin::dessiner_carte ()
 * \brief Méthode gérant le dessin de la carte de base. Elle est utilisée à chaque fois qu'il y a un évènement sur la zone de dessin
 * \param hauteur Hauteur sur laquelle la carte doit être dessinnée
 * \param largeur Largeur sur laquelle la carte doit être dessinnée
 * \param decalage_y Décalage en ordonnée quand il y a un zoom. Cela permet d'afficher la zone voulue
 * \param decalage_x Décalage en abscisse quand il y a un zoom. Cela permet d'afficher la zone voulue
 * \return Rien
 */
void Dessin::dessiner_carte(int hauteur, int largeur, int decalage_y, int decalage_x){
/* Cette variable permet la converion de nombres en lettres */
	stringstream *sstr;
	
/* Cette variable permet de connaitre la taille (hauteur, largeur) d'une phrase */
	Cairo::TextExtents extents;
	
	double premier_point = 0;
	double **points;
	double **croisement;

	double abscisse_tmp, ordonnee_tmp;

/* Fond d'écran */	
	cr = this->get_window()->create_cairo_context();
/* La couleur est le blanc */
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->rectangle(0, 0, L_MAP, H_MAP);
	cr->fill();
/* La couleur est le noir */
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->set_line_width(1.0);
	
/* Lecture du fichier contenant la carte */
	
	points = lire_carte(hauteur, largeur, chemin_carte);
	
/* Gestion d'erreur de lecture du fichier SHP */
	if(points[3][0]!=0){
			for(int i=0; i<points[3][0]; i++){
				if(premier_point == points[2][i]){
					cr->line_to(points[0][i] - decalage_x, points[1][i] - decalage_y);
				}
				else{
					premier_point = points[2][i];
				}
				cr->move_to(points[0][i] - decalage_x, points[1][i] - decalage_y);
			}
		cr->stroke();
	}

	int ordonnees[194];

	for(int j=0; j<194; j++){
		ordonnees[j] = (ordonnee_points[196*j] - points[3][5]);
	}
	croisement = points_dans_polygone(ordonnees, chemin_carte);

	if(initialisation == 1){
		valeur_min = matrice.minCoeff();
		valeur_max = matrice.maxCoeff();
		initialisation = 0;
	}
	else{
		if(matrice.minCoeff() < valeur_min)
			valeur_min = matrice.minCoeff();
		if(matrice.maxCoeff() > valeur_max)
			valeur_max = matrice.maxCoeff();
	}

	for(int i=0; i<194; i++){
		for(int j=0; j<196; j++){
			int ecrire = 0;
			for(int k=0; k<100; k++){
				if(croisement[i][k] != 0){
					if((abscisse_points[(i*196)+j] >= croisement[i][k]) ){
						if(ecrire == 0 )
							ecrire = 1;
						else
							ecrire = 0;
					}	
				}
				else{
					k = 100;
				}
			}
			if(ecrire == 1 ){
				cr->set_source_rgb(gradient_couleur(valeur_min, valeur_max, matrice(i,j), 'R'), gradient_couleur(valeur_min, valeur_max, matrice(i,j), 'G'), gradient_couleur(valeur_min, valeur_max, matrice(i,j), 'B'));
				ordonnee_tmp = ordonnee_points[(i*196)+j] - (points[3][5] - points[3][3]);
				abscisse_tmp = ((abscisse_points[(i*196)+j] - points[3][1]) * largeur)/(points[3][2] - points[3][1]);
				ordonnee_tmp = ((ordonnee_tmp - points[3][3]) * hauteur)/(points[3][4] - points[3][3]);
				cr->arc (abscisse_tmp - decalage_x, ordonnee_tmp - decalage_y, 1, 0, 2 * M_PI);
				cr->fill();
			}
		}
	}
	
/* Insertion de texte pour mettre un titre à la carte */
/* Le titre est écrit en noir */
	cr->set_source_rgb(0, 0, 0);
/* Les lettres font 15 pixels de hauteur */
	cr->set_font_size(15);
/* Sélection de la police */
	cr->select_font_face("Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD);
	string deb_titre("Carte ");
	cr->get_text_extents(deb_titre + titre.c_str(), extents);
	/* Positionnement du titre */
	cr->move_to((L_MAP/2) - (extents.width/2), H_MAP - 20);
	/* Ecriture du titre */
	cr->show_text(deb_titre + titre.c_str());	

/* Dessin du gradient de couleur */
/* Création d'un gradient le long de la ligne définie par (L_MAP - 50, 50) et (L_MAP - 50, H_MAP - 100)  */
	Cairo::RefPtr< Cairo::LinearGradient > gradient = Cairo::LinearGradient::create(L_MAP - 50, 50, L_MAP - 50, H_MAP - 100);

/* Couleur de départ pour le gradient */
	gradient->add_color_stop_rgb(0, 0, 1, 0);
/* Couleur de fin pour le gradient */
	if(valeur_min == valeur_max)
		gradient->add_color_stop_rgb(1, 0, 1, 0);
	else
		gradient->add_color_stop_rgb(1, 1, 0, 0);

/* Dessin d'un rectangle */
	cr->rectangle(L_MAP - 50, 50, 10, H_MAP - 100);
/* Colorisation du rectangle avec le gradient */
	cr->set_source(gradient);
/* Remplissage du rectangle (toujours avec le gradient) */
	cr->fill();  
	
/* Conversion du minimum de la matrice en lettres (pour afficher ce que représente la valeur du minimum du gradient)*/
    sstr = new stringstream();
	*sstr << valeur_min;
	
/* Le titre est écrit en noir */
	cr->set_source_rgb(0, 0, 0);
/* Les lettres font 10 pixels de hauteur */
	cr->set_font_size(10);
/* Sélection de la police */
	cr->select_font_face("Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD);
/* Récupération de la taille la valeur min(hauteur et largeur) */
	cr->get_text_extents((sstr->str()).c_str(), extents);
/* Positionnement du texte */
	cr->move_to((L_MAP - 45) - (extents.width/2), 50 - 5);
/* Ecriture du titre */
	cr->show_text((sstr->str()).c_str());	
	
/* Conversion du maximum de la matrice en lettres (pour afficher ce que représente la valeur du maximum du gradient)*/
    sstr = new stringstream();
	*sstr << valeur_max;
	
/* Récupération de la taille la valeur max(hauteur et largeur) */
	cr->get_text_extents((sstr->str()).c_str(), extents);
/* Positionnement du texte */
	cr->move_to((L_MAP - 45) - (extents.width/2), H_MAP - 50 + extents.height + 5);
/* Ecriture du titre */
	cr->show_text((sstr->str()).c_str());
	
/* Vidage du stringstream */
	if(zoom_actif == 0)
		get_gdk_pixbuf();
}

/** \fn double** Dessin::lire_carte (int hauteur, int largeur, string chemin)
 *  \brief Méthode lisant la carte de france d'un fichier SHP et redimenssionant cette dernière pour correspondre à la zone de dessin
 *  \param hauteur Hauteur que doit faire la carte
 *  \param largeur Largeur que doit faire la carte
 *  \return points Tableau contenant les coordonnées des points de la carte adaptées à la hauteur et largeur de la zone de dessin
 */
double **Dessin::lire_carte(int hauteur, int largeur, string chemin){
	Lecture_Ecriture lect;
/* Lecture de tous les points de tous les polygones */
	double **points = lect.lecture_SHP(chemin);

/* Gestion d'erreur de lecture de fichier */
	if(points[3][0] == 0)
		return points;

	for(int j=0; j < points[3][0]; j++){
		points[0][j] = ((double)(points[0][j]-points[3][1]) * largeur)/(points[3][2] - points[3][1]);
		points[1][j] = hauteur-(((double)(points[1][j]-points[3][3]) * hauteur)/(points[3][4] - points[3][3]));
	}
	
	return points;
}

/** \fn double **Dessin::points_dans_polygone(int ordonnees[194], string chemin)
 *  \brief Méthode déterminant quels points sont dans la carte de France pour ne pas dessiner ceux qui sont en dehors.
 *  Ceci correspond à la gestion des conditions aux limites de la carte de France. 
 *  \param ordonnees Ordonnées des points de la matrice. Ces ordonnées sont utiles pour déterminer où les lignes de points de la matrice vont croiser les contours
 *  de la carte de France 
 *  \param chemin Chemin de la carte à partir de laquelle sont calculés les points d'intersection avec les lignes des points de la matrice
 *  \return abscisse_croisement Abscisse des points d'intersection entre la carte de France et les lignes des points de la matrice
 */
double **Dessin::points_dans_polygone(int ordonnees[194], string chemin){
	Lecture_Ecriture lect;
	int polygone = -1;
	int x_prec, y_prec;
	double coef_dir;
	double **abscisse_croisement;
	
	int indice[194] = {0};
	int num_points[194][100];
	
	abscisse_croisement = new double*[194];

	for(int i=0; i<194; i++)
		abscisse_croisement[i] = new double[100];

/* Initialisation de abscisse_croisement à 0 pour gérer les erreurs sur la lecture de fichier. */
/* Initialisation de num_points à 0 pour gérer le fait qu'il n'y a pas de points de croisement au départ */
	for(int i=0; i<194; i++){
		for(int j=0; j<100; j++){
			abscisse_croisement[i][j] = 0;
			num_points[i][j] = 0;
		}
	}

	double **points = lect.lecture_SHP(chemin);
	
/* Gestion d'erreur de lecture de fichier */
	if(points[3][0] == 0)
		return abscisse_croisement;

	for(int j=0; j < points[3][0]; j++){
		points[1][j] = points[3][4] - (points[1][j] - points[3][3]);
	}

/* Après avoir recupéré les points, calcul des abscisses des points d'intersection entre les lignes de la matrice et la carte de France. */
/* N'est calculé que les abscisses puisque les ordonnées sont connues (elles proviennent de la matrice). */
	for(int i=0; i < points[3][0]; i++){
		if(polygone != points[2][i]){
			polygone = points[2][i];
			x_prec = points[0][i];
			y_prec = points[1][i] - points[3][3];
		}
		else{
			for(int k=0; k<194; k++){
/* Sélection des points juste au dessus et juste au dessous de l'ordonnée */
				if((ordonnees[k]>=y_prec && ordonnees[k]<=(points[1][i]-points[3][3])) || (ordonnees[k]<=y_prec && ordonnees[k]>=(points[1][i]-points[3][3]))){ 
/* Calcul du coefficient directeur de la droite qui relie les deux points autour de l'ordonnée. */
/* Il y a 2 calculs de coefficients directeur car la droite peut être orientée du haut à gauche vers le bas à droite ou */
/* du bas à gauche vers le haut à droite*/
					if(ordonnees[k] >= y_prec)
						coef_dir = (points[1][i]-points[3][3] - y_prec)/(points[0][i] - x_prec);
					else
						coef_dir = (y_prec-points[1][i]-points[3][3])/(x_prec-points[0][i]);
					
					if(coef_dir != 0){
						if((ordonnees[k] == y_prec) || (ordonnees[k] == points[1][i]-points[3][3])){
							if (ordonnees[k] == points[1][i]-points[3][3]){
								abscisse_croisement[k][indice[k]] = points[0][i];
								num_points[k][indice[k]] = i;
								indice[k]++;
							}
						}
						else{
							if(ordonnees[k] >= y_prec)
								abscisse_croisement[k][indice[k]] = ((double)(ordonnees[k]-y_prec)/coef_dir) + x_prec;
							else
								abscisse_croisement[k][indice[k]] = ((double)(ordonnees[k]-points[1][i])/coef_dir) + points[0][i];
							
							num_points[k][indice[k]] = i;	
							indice[k]++;
						}
					}
				}
			}
			
			x_prec = points[0][i];
			y_prec = points[1][i] - points[3][3];
		}	
	}
/* Gestion des cas particuliers (plusieurs points sur la même ordonnée provoquent une imparité de croisement du polygone) */
	for(int k=0; k<194; k++){
/* Si le nombre d'intersection avec le polygone est impair, il y a erreur car la carte de France se termine par des blancs */
		if(indice[k]%2 != 0){
			int trouve = 1;
/* Suppression des points contigus */
			for(int i=0; i<indice[k]; i++){
				if((num_points[k][i]+1 == num_points[k][i+1]) || (num_points[k][i]+2 == num_points[k][i+1]) || (num_points[k][i]+3 == num_points[k][i+1])){
					for(int l=i; l<indice[k]; l++)
						abscisse_croisement[k][l] = abscisse_croisement[k][l+1];
					i = indice[k];
				}
/* Si pas de points contigus */
				if(i == (indice[k]-1))
					trouve = 0;
			}
/* Pas de points contigus donc recherche de 2 points les plus proches entre eux */
			if(trouve == 0){
				int difference = 200;
				int ind_tmp = 0;
				for(int l=0; l<indice[k]; l++){
					if((num_points[k][l+1] - num_points[k][l]) <= difference){
						difference = (num_points[k][l+1] - num_points[k][l]);
						ind_tmp = l;
					}
				}
				for(int m=ind_tmp; m<indice[k]; m++)
					abscisse_croisement[k][m] = abscisse_croisement[k][m+1];
			}
		}
		if(abscisse_croisement[k][1] == 0)
			abscisse_croisement[k][0] = 0;
	}

	return abscisse_croisement;
}

/** \fn double Dessin::gradient_couleur(double min, double max, double val, char composante)
 *  \brief Cette fonction détermine en quelle couleur doit être représentée la valeur passée en paramètre. La fonction retourne la composante 
 *  (Rouge, Verte ou Bleue) de la couleur qui a été déterminée. La palette de couleurs choisie pour effectuer cette sélection est constante et a été
 *  déterminée grâce au site : <A HREF="http://www.perbang.dk/rgbgradient/"> Gradient de couleur RGB </A>.\n
 *  Ce site permet, après avoir choisi les couleurs de début et de fin ainsi que le nombre de valeurs souhaité, de générer un gradient de couleurs.
 *  Les couleurs de début et de fin sont le vert (0, 255, 0)(RGB) et le rouge (255, 0, 0)(RGB). Les valeurs ont toutes été converties entre 0 et 1 car
 *  Cairo n'accepte que ces valeurs.
 *  \param min Minimum de l'intervalle pour lequel est effectué la sélection de couleur
 *  \param max Maximum de l'intervalle pour lequel est effectué la sélection de couleur
 *  \param val Valeur dont doit être déterminé la valeur de la composante Rouge, Verte ou Bleue pour la couleur à laquelle \c val appartient
 *  \param composante 
 *  \return couleur Valeur de la composante Rouge, Verte ou Bleue pour la valeur passée en paramètre et pour un intervalle donné
 */
double Dessin::gradient_couleur(double min, double max, double val, char composante){
/* Numéro de la couleur à afficher */
	int indice;
	
/* Tableau des valeurs d'un gradient de couleur allant du vert au rouge (20 valeurs => 5% de valeurs par pas  */
	double couleur[20][3] = {{0,1,0},{0.050980392,0.945098039,0},{0.101960784,0.894117647,0},{0.156862745,0.839215686,0},{0.207843137,0.788235294,0},
	{0.262745098,0.733333333,0},{0.31372549,0.682352941,0},{0.364705882,0.631372549,0},{0.419607843,0.576470588,0},{0.470588235,0.525490196,0},
	{0.525490196,0.470588235,0},{0.576470588,0.419607843,0},{0.631372549,0.364705882,0},{0.682352941,0.31372549,0},{0.733333333,0.262745098,0},
	{0.788235294,0.207843137,0},{0.839215686,0.156862745,0},{0.894117647,0.101960784,0},{0.945098039,0.050980392,0},{1,0,0}};
	
	double pourcent = (max - min) / 100;

/* Test pour vérifier si max est différent de min et ainsi imposer le vert comme valeur par défaut */	
	if(pourcent != 0){
/* Détermination de la couleur à sélectionner */
		for(int i=1; i<=20; i++){
			if(((5 * pourcent * i) + min) >= val){
				indice = i - 1;
				i = 21;
			}
		}
	}
	else
		indice = 0;
	
/* La composante souhaitée pour la couleur calculée est retournée */
	if(composante == 'R' || composante == 'r')
		return couleur[indice][0];
	if(composante == 'G' || composante == 'g' || composante == 'V' || composante == 'v')
		return couleur[indice][1];
	if(composante == 'B' || composante == 'b')
		return couleur[indice][2];
}

/** \fn Glib::RefPtr<Gdk::Pixbuf> Dessin::get_gdk_pixbuf()
 *  \brief Méthode créant et retournant un pixbuf (zone de Dessin au sens de GDK). Cette méthode est utilisée pour l'impression, le cadre de sélection
 *  et le dézoom.
 *  \return pixbuf Pixbuf créé à partir de la zone de dessin
 */
Glib::RefPtr<Gdk::Pixbuf> Dessin::get_gdk_pixbuf(){
	Glib::RefPtr<Gdk::Drawable> drawable = static_cast<Glib::RefPtr<Gdk::Drawable> >(this->get_window());
	
    pixbuf = Gdk::Pixbuf::create(drawable, 0, 0, L_MAP - 10, H_MAP - 15);
	
    pixbuf->save("Images/tmp_" + get_titre()  + ".png", "png"); 
	return pixbuf;
}

/** \fn string Dessin::enregistrement(int num, string chemin)
 *  \brief Méthode effectuant un enregistrement automatique d'une image de la zone de dessin à chaque itération de la simulation.
 *  \param num Numéro de l'enregistrement courant
 *  \return chemin Chemin du dossier d'enregistrement 
 */
string Dessin::enregistrement(int num, string chemin){
	stringstream *sstr = new stringstream();
	Lecture_Ecriture lect;

	*sstr << chemin << "\\" << titre << "_" << num << ".png";
	Glib::RefPtr<Gdk::Drawable> drawable = static_cast<Glib::RefPtr<Gdk::Drawable> >(this->get_window());
	Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create(drawable, 0, 0, L_MAP - 10, H_MAP - 15);
	pixbuf->save((sstr->str()).c_str(), "png"); 
	sstr->str(string());

	*sstr << chemin << "\\" << titre << "_" << num << ".csv";
	return (sstr->str()).c_str();
}

/** \fn void Dessin::init()
 *  \brief Méthode définissant l'initialisation de la simulation. Cette méthode est utile pour définir le minimum et le maximum de l'échelle du gradient de couleur.
 *  \return Rien
 */
void Dessin::init(){
	initialisation = 1;
}

/** \fn void Dessin::set_chemin_carte(string path)
 *  \brief Méthode mettant à jour la variable de chemin de la carte 
 *  \param path Chemin du fichier de la carte
 *  \return Rien
 */
void Dessin::set_chemin_carte(string path){
	chemin_carte = path;
}

/** \fn void Dessin::set_titre(string untitre)
 *  \brief Méthode mettant à jour la variable du titre de la carte 
 *  \param untitre Titre de la carte
 *  \return Rien
 */
void Dessin::set_titre(string untitre){
	titre = untitre;
}

/** \fn int Dessin::get_hauteur()
 *  \brief Méthode retournant la hauteur de la zone de dessin
 *  \return H_MAP Hauteur de la zone de dessin
 */
int Dessin::get_hauteur(){
	return H_MAP;
}

/** \fn int Dessin::get_largeur()
 *  \brief Méthode retournant la largeur de la zone de dessin
 *  \return L_MAP Largeur de la zone de dessin
 */
int Dessin::get_largeur(){
	return L_MAP;
}

/** \fn double Dessin::get_valeur_min()
 *  \brief Méthode retournant la valeur minimum de l'échelle du gradient de couleur
 *  \return valeur_min Valeur minimum de l'échelle du gradient de couleur
 */
double Dessin::get_valeur_min(){
	return valeur_min;
}

/** \fn double Dessin::get_valeur_max()
 *  \brief Méthode retournant la valeur maximum de l'échelle du gradient de couleur
 *  \return valeur_max Valeur maximum de l'échelle du gradient de couleur
 */
double Dessin::get_valeur_max(){
	return valeur_max;
}

/** \fn void Dessin::set_matrice(Matrice mat)
 *  \brief Méthode mettant à jour la matrice à dessiner sur la zone de dessin
 *  \param mat Matrice de mise à jour
 *  \return Rien
 */
void Dessin::set_matrice(Matrice mat){
	matrice = mat;
}

/** \fn Matrice Dessin::get_matrice()
 *  \brief Méthode retournant la matrice à dessiner sur la zone de dessin
 *  \return matrice Matrice à dessiner sur la zone de dessin
 */
Matrice Dessin::get_matrice(){
	return matrice;
}

/** \fn string Dessin::get_titre()
 *  \brief Méthode retournant le titre de la zone de dessin
 *  \return titre Titre de la zone de dessin
 */
string Dessin::get_titre(){
	return titre;
}

/** \fn bool Dessin::get_activation()
 *  \brief Méthode retournant la valeur qui permet de savoir si la zone de dessin a été activée ou non.
 *  \return actif Variable permettant de savoir si la zone de dessin a été activée 
 */
bool Dessin::get_activation(){
	return actif;
}