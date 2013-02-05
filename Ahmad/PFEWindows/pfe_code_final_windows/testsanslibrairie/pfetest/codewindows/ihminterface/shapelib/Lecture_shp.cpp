/**
 * \file Lecture_shp.cpp
 * \brief fichier de lecture d'un fichier SHP
 * \author Francois Blouin
 * \date 24 decembre 2012
 */

#include <iostream>
#include <cmath>
#include "shapefil.h"

using namespace std;

/**
 * \fn double** lire_carte (int hauteur, int largeur)
 * \brief Methode lisant la carte de france d'un fichier SHP et redimenssionnant cette derniere pour correspondre a la zone de dessin
 *
 * \param hauteur Hauteur que doit faire la carte
 * \param largeur Largeur que doit faire la carte
 * \return points Tableau contenant les coordonnees des points de la carte adaptees a la hauteur et largeur de la zone de dessin
 */
double **lire_carte(int hauteur, int largeur, string chemin){
	SHPHandle h;
	SHPObject* objet;
	int nb_polygone;
	int nb_point;
	double coord_min[4];
	double coord_max[4];
	double **points;
	int *tab_poly;
	int mini=3000000;

/* Recuperation des infos et des donnees du fichier */
	// h=SHPOpen("france.shp","rb+");
	h=SHPOpen(chemin.c_str(),"rb+");
	
/* Gestion d'ouverture de fichier */
	if(h==0){
		points= new double*[4];
		
		for(int i=0;i<4;i++)
		points[i]=new double[1];
		
		points[3][0]=0;
		return points;
	}

/* Recuperation des donnees de la carte */
	objet = SHPReadObject( h, 0 );
	
/* Recuperation d'infos du fichier SHP */
	SHPGetInfo(h, NULL, NULL, coord_min, coord_max);

/* Fermeture du fichier SHP */
	SHPClose(h);
	
	nb_polygone = objet->nParts;
	nb_point = objet->nVertices;
	
	tab_poly= new int[nb_polygone];
	
/* Recuperation des numeros des points de debut de chaque polygone */
	for(int i=0;i<nb_polygone;i++)
		tab_poly[i]=objet->panPartStart[i];
		
/* Initialisation du tableau des coordonnees des points de la carte */	
	points= new double*[4];

	for(int i=0;i<3;i++)
	points[i]=new double[nb_point];
	
	points[3]=new double[6];
	points[3][0]=nb_point;
	points[3][1]=coord_min[0];
	points[3][2]=coord_max[0];
	points[3][3]=coord_min[1];
	points[3][4]=coord_max[1];
	
/* Transformation des coordonnees (x,y) des points de la carte en coordonnees (x,y) adaptees a l'interface graphique*/	
/* Points[0] : abcisse des points */
/* Points[1] : ordonnee des points */
/* Points[2] : numero des points */
/* Points[3] : nombre de points */
	for(int j=0; j < nb_point;j++){
		points[0][j]=round(((objet->padfX[j]-coord_min[0])*hauteur)/(coord_max[0]-coord_min[0]));
		points[1][j]=hauteur-(round(((objet->padfY[j]-coord_min[1])*largeur)/(coord_max[1]-coord_min[1])));
		if(objet->padfY[j]<mini)
			mini=objet->padfY[j];
		
		for(int i=(nb_polygone-1);i>=0;i--){
			if(j<tab_poly[i]){
				points[2][j]=i;
			}
		}
	}
	points[3][5]=mini;
	
	return points;
}