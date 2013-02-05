#include <iostream>
#include <cmath>
#include "shapefil.h"

using namespace std;

/** \fn double ** lecture_SHP(string fichiergeomatique)
 *  \brief Lecture d'un fichier au format SHP dont on pr�cise le chemin en entr�e de la fonction
 *  \param fichiergeomatique Nom du fichier � lire
 *  \return points Coordonn�es des points + Num�ro des diff�rents polygones pr�sents dans le fichier. Est �galement pr�sent les coordonn�es du rectangle
 *  de contour de la carte de France ainsi que l'ordonn�e du point le plus haut de la carte.
 */
double **lecture_SHP(string fichiergeomatique){
	SHPHandle h;
	SHPObject* objet;
	int nb_polygone;
	int nb_point;
	double coord_min[4];
	double coord_max[4];
	double **points;
	int *tab_poly;
	int mini = 3000000;
	
	
/* R�cuperation des infos et des donn�es du fichier */
	h = SHPOpen(fichiergeomatique.c_str(),"rb+");
	
/* Gestion d'ouverture de fichier */
	if(h == 0){
		points = new double*[4];
		
		for(int i=0; i<4; i++)
		points[i] = new double[1];
		
		points[3][0] = 0;
		return points;
	}

/* R�cup�ration des donn�es de la carte */
	objet = SHPReadObject( h, 0 );
	
/* R�cup�ration d'infos du fichier SHP */
	SHPGetInfo(h, NULL, NULL, coord_min, coord_max);

/* Fermeture du fichier SHP */
	SHPClose(h);

/* Nombre de polygones dans la carte */	
	nb_polygone = objet->nParts;
/* Nombre de points dans la carte */
	nb_point = objet->nVertices;
	
/* Tableau des num�ros de plygone */
	tab_poly = new int[nb_polygone];
	
/* R�cup�ration des num�ros des points de d�but de chaque polygone */
	for(int i=0; i<nb_polygone; i++)
		tab_poly[i] = objet->panPartStart[i];
		
/* Initialisation du tableau des coordonn�es des points de la carte */	
	points = new double*[4];

	for(int i=0; i<3; i++)
		points[i] = new double[nb_point];
	
	points[3] = new double[6];
/* Nombre de points dans la carte */
	points[3][0] = nb_point;
/* Abscisse minimale de la carte */
	points[3][1] = coord_min[0];
/* Abscisse maximale de la carte */
	points[3][2] = coord_max[0];
/* Ordonn�e minimale de la carte */
	points[3][3] = coord_min[1];
/* Ordonn�e maximale de la carte */
	points[3][4] = coord_max[1];
	
	for(int j=0; j < nb_point; j++){
/* R�cup�ration de chaque abscisse des points des polygones de la carte */
		points[0][j] = objet->padfX[j];
/* R�cup�ration de chaque ordonn�es des points des polygones de la carte */
		points[1][j] = objet->padfY[j];
		if(objet->padfY[j] < mini)
			mini = objet->padfY[j];
/* Identification du num�ro de polygone auquel appartient chaque point de la carte */		
		for(int i=(nb_polygone-1); i>=0; i--){
			if(j<tab_poly[i]){
				points[2][j] = i;
			}
		}
	}
/* R�cup�ration de l'ordonn�e du point le plus haut de la carte de France */
	points[3][5] = mini;

	return points;
}
