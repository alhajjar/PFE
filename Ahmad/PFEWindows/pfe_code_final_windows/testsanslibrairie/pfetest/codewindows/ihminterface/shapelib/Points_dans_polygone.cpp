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
double **points_dans_polygone(int ordonnees[194], string chemin){
	SHPHandle h;
	SHPObject* objet;
	int nb_polygone;
	int nb_point;
	double coord_min[4];
	double coord_max[4];
	double **points;
	int *tab_poly;
	int mini=3000000;
	int polygone=-1;
	int x_prec,y_prec;
	double coef_dir;
	double **abscisse_croisement;
	
	int indice[194]={0};
	int num_points[194][100];
	
	abscisse_croisement= new double*[194];

	for(int i=0;i<194;i++)
	abscisse_croisement[i]=new double[100];
	
	for(int i=0;i<194;i++){
		for(int j=0;j<100;j++){
			abscisse_croisement[i][j]=0;
			num_points[i][j]=0;
		}
	}

/* Recuperation des infos et des donnees du fichier */
	// h=SHPOpen("france.shp","rb+");
	h=SHPOpen(chemin.c_str(),"rb+");
	
/* Gestion d'ouverture de fichier */
	if(h==0){
		return abscisse_croisement;
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
	points= new double*[3];

	for(int i=0;i<3;i++)
	points[i]=new double[nb_point];

	
/* Transformation des coordonnees (x,y) des points de la carte en coordonnees (x,y) adaptees a l'interface graphique*/	
/* Points[0] : abcisse des points */
/* Points[1] : ordonnee des points */
/* Points[2] : numero des points */
/* Points[3] : nombre de points */
	for(int j=0; j < nb_point;j++){
		points[0][j]=objet->padfX[j]-coord_min[0];
		points[1][j]=coord_max[1]-(objet->padfY[j]-coord_min[1]);
		if(objet->padfY[j]<mini)
			mini=objet->padfY[j];
		
		for(int i=(nb_polygone-1);i>=0;i--){
			if(j<tab_poly[i]){
				points[2][j]=i;
			}
		}
	}

/* Apres avoir recupere les points on calcule les abscisses des points d'intersection entre les lignes de la matrice et la carte de France. */
/* N'est calcule que les abscisses car les ordonnées sont connues car elles proviennent de la matrice */
	for(int i=0;i<nb_point;i++){
		if(polygone !=points[2][i]){
			polygone=points[2][i];
			x_prec=points[0][i];
			y_prec=points[1][i]-coord_min[1];
		}
		else{
			for(int k=0;k<194;k++){
/* Selection des points juste au dessus et juste au dessous de l'ordonnee */
				if((ordonnees[k]>=y_prec && ordonnees[k]<=(points[1][i]-coord_min[1])) || (ordonnees[k]<=y_prec && ordonnees[k]>=(points[1][i]-coord_min[1]))){ 
/* Calcul du coefficient directeur de la droite qui relie les deux points autour de l'ordonnee. */
/* Il y a 2 calculs de coefficients directeur car la droite peut etre orientee du haut a gauche vers le bas a droite ou */
/* du bas gauche vers le haut a droite*/
					if(ordonnees[k]>=y_prec)
						coef_dir = (points[1][i]-coord_min[1]- y_prec)/(points[0][i] - x_prec);
					else
						coef_dir = (y_prec-points[1][i]-coord_min[1])/(x_prec-points[0][i] );
					
					if(coef_dir !=0){
						if((ordonnees[k]==y_prec) || (ordonnees[k] == points[1][i]-coord_min[1])){
							if (ordonnees[k] == points[1][i]-coord_min[1]){
								abscisse_croisement[k][indice[k]]=points[0][i];
								num_points[k][indice[k]]=i;
								indice[k]++;
							}
						}
						else{
							if(ordonnees[k]>=y_prec)
								abscisse_croisement[k][indice[k]]=((double)(ordonnees[k]-y_prec)/coef_dir)+x_prec;
							else
								abscisse_croisement[k][indice[k]]=((double)(ordonnees[k]-points[1][i])/coef_dir)+points[0][i];
							
							num_points[k][indice[k]]=i;	
							indice[k]++;
						}
					}
				}
			}
			
			x_prec=points[0][i];
			y_prec=points[1][i]-coord_min[1];
		}	
	}
/* Gestion des cas particuliers (plusieurs points sur la meme ordonnee provoquent une imparité de croisement du polygone) */
	for(int k=0;k<194;k++){
		/* Si le nombre d'intersection avec le polygone est impair, il y a erreur car la carte de France se termine par des blancs */
		if(indice[k]%2 !=0){
			int trouve=1;
			/* Suppression des points contigus */
			for(int i=0;i<indice[k];i++){
				if((num_points[k][i]+1==num_points[k][i+1]) || (num_points[k][i]+2==num_points[k][i+1]) || (num_points[k][i]+3==num_points[k][i+1])){
					for(int l=i;l<indice[k];l++)
						abscisse_croisement[k][l]=abscisse_croisement[k][l+1];
					i=indice[k];
				}
				/* Si pas de points contigus */
				if(i==(indice[k]-1))
					trouve=0;
			}
			/* Pas de points contigus donc recherche de points les plus proches entre eux */
			if(trouve==0){
				int difference=200;
				int ind_tmp=0;
				for(int l=0;l<indice[k];l++){
					if((num_points[k][l+1]-num_points[k][l]) <= difference){
						difference=(num_points[k][l+1]-num_points[k][l]);
						ind_tmp=l;
					}
				}
				for(int m=ind_tmp;m<indice[k];m++)
					abscisse_croisement[k][m]=abscisse_croisement[k][m+1];
			}
		}
		
		if(abscisse_croisement[k][1]==0)
			abscisse_croisement[k][0]=0;
	}

	return abscisse_croisement;
}