#include <iostream>
#include <cmath>
#include "shapefil.h"

using namespace std;

/** \fn double ** lecture_SHP(string fichiergeomatique)
 *  \brief Lecture d'un fichier au format SHP dont on précise le chemin en entrée de la fonction
 *  \param fichiergeomatique Nom du fichier à lire
 *  \return points Coordonnées des points + Numéro des différents polygones présents dans le fichier. Est également présent les coordonnées du rectangle
 *  de contour de la carte de France ainsi que l'ordonnée du point le plus haut de la carte.
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
	
	
/* Récuperation des infos et des données du fichier */
	h = SHPOpen(fichiergeomatique.c_str(),"rb+");
	
/* Gestion d'ouverture de fichier */
	if(h == 0){
		points = new double*[4];
		
		for(int i=0; i<4; i++)
		points[i] = new double[1];
		
		points[3][0] = 0;
		return points;
	}

/* Récupération des données de la carte */
	objet = SHPReadObject( h, 0 );
	
/* Récupération d'infos du fichier SHP */
	SHPGetInfo(h, NULL, NULL, coord_min, coord_max);

/* Fermeture du fichier SHP */
	SHPClose(h);

/* Nombre de polygones dans la carte */	
	nb_polygone = objet->nParts;
/* Nombre de points dans la carte */
	nb_point = objet->nVertices;
	
/* Tableau des numéros de plygone */
	tab_poly = new int[nb_polygone];
	
/* Récupération des numéros des points de début de chaque polygone */
	for(int i=0; i<nb_polygone; i++)
		tab_poly[i] = objet->panPartStart[i];
		
/* Initialisation du tableau des coordonnées des points de la carte */	
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
/* Ordonnée minimale de la carte */
	points[3][3] = coord_min[1];
/* Ordonnée maximale de la carte */
	points[3][4] = coord_max[1];
	
	for(int j=0; j < nb_point; j++){
/* Récupération de chaque abscisse des points des polygones de la carte */
		points[0][j] = objet->padfX[j];
/* Récupération de chaque ordonnées des points des polygones de la carte */
		points[1][j] = objet->padfY[j];
		if(objet->padfY[j] < mini)
			mini = objet->padfY[j];
/* Identification du numéro de polygone auquel appartient chaque point de la carte */		
		for(int i=(nb_polygone-1); i>=0; i--){
			if(j<tab_poly[i]){
				points[2][j] = i;
			}
		}
	}
/* Récupération de l'ordonnée du point le plus haut de la carte de France */
	points[3][5] = mini;

	return points;
}
