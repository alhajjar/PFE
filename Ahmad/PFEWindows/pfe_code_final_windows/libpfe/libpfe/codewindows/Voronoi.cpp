/** 
  * \file Voronoi.cpp
  * \brief Fichier permettant la création et de l'utilisation du diagramme de Voronoï
  */

#include "Includes/Voronoi.hpp"
#include <stdexcept>
Voronoi::Voronoi(){
}

/** \fn Voronoi::Voronoi()
 *  \brief Constructeur de la classe Voronoi
 *  \param coord_file_name Nom du fichier où se trouvent les coordonnées
 *  \param nb_row_coord Nombre de lignes de la matrice des coordonnées
 *  \param nb_col_coord Nombre de colonnes de la matrice des coordonnées
 *  \param data_file_name Nom du fichier où se trouvent les données
 *  \param nb_row_data Nombre de lignes de la matrice des données
 *  \param nb_col_data Nombre de colonnes de la matrice des données
 */
Voronoi::Voronoi(string coord_file_name, int nb_row_coord, int nb_col_coord, string data_file_name, int nb_row_data, int nb_col_data){
	mat_index =  Matrice (194,196);
	mat_index = Matrice::Zero(194,196);
	mat_coord =  Matrice (nb_row_coord, nb_col_coord);
	mat_coord = Matrice::Zero(nb_row_coord, nb_col_coord);
	mat_data =  Matrice (nb_row_data, nb_col_data-1);
	mat_data = Matrice::Zero(nb_row_data, nb_col_data-1);
	mat_finale =  Matrice (196,194);
    	mat_finale = Matrice::Zero(196,194);

	Matrice matcoord(nb_row_coord, nb_col_coord);
	matcoord = Matrice::Zero(nb_row_coord, nb_col_coord);
	
	lecture_coordonnees(coord_file_name, nb_row_coord, nb_col_coord);
	matcoord = get_Matrice_Coordonnees();

	Matrice matdata(nb_row_data, nb_col_data);
	matdata = Matrice::Zero(nb_row_data, nb_col_data);
	
	lecture_donnees(data_file_name, nb_row_data, nb_col_data);
	matdata = get_Matrice_Donnees();
	construction_index(matcoord, nb_row_coord, nb_col_coord, nb_row_data, nb_col_data);
}

/** \fn Voronoi::Voronoi()
 *  \brief Destructeur de la classe Voronoi
 */
Voronoi::~Voronoi(){
 /* delete(mat_coord);
  delete(mat_data);
  delete(mat_index);
  delete(mat_finale);*/
}

/** \fn void Voronoi::lecture_coordonnees(string file_name_coord, int nb_row_coord, int nb_col_coord)
 *  \brief Lecture du fichier permettant de remplir la matrice des coordonnées 
 *  \param file_name_coord Nom du fichier où se trouvent les coordonnées
 *  \param nb_row_coord Nombre de lignes de la matrice des coordonnées
 *  \param nb_col_coord Nombre de colonnes de la matrice des coordonnées
 *  \return Rien
 */
void Voronoi::lecture_coordonnees(string file_name_coord, int nb_row_coord, int nb_col_coord){
	Lecture_Ecriture lect;

	Matrice matcoord(nb_row_coord,nb_col_coord);
	matcoord = Matrice::Zero(nb_row_coord,nb_col_coord);
	
	lect.LectureCSV(nb_row_coord,nb_col_coord,file_name_coord);
	matcoord = lect.get_CSV();

	for(int i=0; i < nb_row_coord - 1 ;i++){
/* Indices des villes */
		matcoord(i,0) = i;
/* Coordonnées des abcisses de 0 à 193 */
		matcoord(i,1) = (int)(matcoord(i,1)-47700)/5000;
/* Coordonnées des ordonnées de 0 à 195 */
		matcoord(i,2) = (int)(matcoord(i,2)-1703600)/5000;
	}
	set_Matrice_Coordonnees(matcoord);
}

/** \fn void Voronoi::lecture_donnees(string file_name_data, int nb_row_data, int nb_col_data)
 *  \brief Lecture du fichier permettant de remplir la matrice des données 
 *  \param file_name_data Nom du fichier où se trouvent les données
 *  \param nb_row_data Nombre de lignes de la matrice des données
 *  \param nb_col_data Nombre de lignes de la matrice des données
 *  \return Rien
 */
void Voronoi::lecture_donnees(string file_name_data, int nb_row_data, int nb_col_data){
	Lecture_Ecriture lect;
	
	Matrice mat_data_temp(nb_row_data, nb_col_data);
	mat_data_temp = Matrice::Zero(nb_row_data, nb_col_data);

	Matrice matdata(nb_row_data, nb_col_data-1);
	matdata = Matrice::Zero(nb_row_data, nb_col_data-1);

	lect.LectureCSV(nb_row_data, nb_col_data, file_name_data);
	mat_data_temp = lect.get_CSV();

	for(int j = 0; j<nb_row_data-1; j++){
		for(int k = 0; k<nb_col_data-1; k++)
			matdata(j + 1, k) = mat_data_temp(j, k + 1);
	}

	for(int m = 0; m < nb_row_data; m++){
		matdata(m, 0) = m ;
	}

	for(int n=0; n < nb_col_data-2; n++){
		matdata(0, n+1) = n ;
	}

	set_Matrice_Donnees(matdata);
}

/** \fn void Voronoi::construction_index(Matrice mat_coord, int nb_row_coord, int nb_col_coord, int nb_row_data, int nb_col_data)
 *  \brief Création de la matrice des indices. Ces indices déterminent quelle est la ville la plus proche par rapport à un point courant
 *  \param mat_coord Matrice des coordonnées
 *  \param nb_row_coord Nombre de lignes de la matrice des coordonnées
 *  \param nb_col_coord Nombre de colonnes de la matrice des coordonnées
 *  \param nb_row_data Nombre de lignes de la matrice des données
 *  \param nb_col_data Nombre de colonnes de la matrice des coordonnées
 *  \return Rien
 */
void Voronoi::construction_index(Matrice mat_coord, int nb_row_coord, int nb_col_coord, int nb_row_data, int nb_col_data){
/* Initialisation de la matrice des indices */
	Matrice mat_dist(nb_row_coord-1,2);
	mat_dist = Matrice::Zero(nb_row_coord-1,2); 
	Matrice matindex(194,196);
	matindex = Matrice::Zero(194,196);

	for(int a = 0; a < 194; a++){
		for(int b = 0; b < 196; b++){
			for(int p = 0; p < nb_row_coord-1; p++){
				mat_dist(p, 0) = p;
/* Calcul de la distance de chaque ville au point courant */
				mat_dist(p, 1) = pow((mat_coord(p,1) - a), 2) + pow((mat_coord(p, 2) - b), 2);
			}

/* Recherche de l'indice du minimum de distance */

/* Initialisation de l'indice temporaire (1ère ville) */
			int itemp = 0;
/* Initialisation valeur temporaire de distance minimale */
			int temp = 0;
/* Parcours de toutes les villes */
			for(int q=1 ; q < nb_row_coord-1 ; q++){
/* Comparaison des villes deux à deux */
				 temp = min(mat_dist(itemp,1),mat_dist(q,1));
/* Conservation de l'indice de la ville dont la valeur est la plus faible pour la prochaine itération */
				 if (temp == mat_dist(q,1)){             
					 itemp = q;  
				 }
			}
/* Une fois l'indice de la ville la plus proche trouvé, il est stocké dans la matrice des indices */
			matindex(a,b) = itemp;
		}

	}

	set_Matrice_Index(matindex);
}

/** \fn void Voronoi::voronoi_iteration(int jour, Matrice mat_data, Matrice mat_index)
 *  \brief Création du diagramme de Voronoï pour le ième jour
 *  \param jour Jour pour lequel le diagramme de Voronoï est créé
 *  \param mat_data Matrice des données
 *  \param mat_index Matrice des indices
 *  \return Rien
 */
void Voronoi::voronoi_iteration(int jour, Matrice mat_data, Matrice mat_index){

	Matrice mat_final(194,196);
	mat_final = Matrice::Zero(194,196);
	
	Matrice matfinale(196,194);
	matfinale = Matrice::Zero(196,194);

	for(int u=0; u < 194; u++){
		for(int v=0; v < 196; v++){
			mat_final(u, v) = mat_data(jour, mat_index(u, v) + 1);
			matfinale(195 -v, u) = mat_final(u,v);
		}


	}
/*cout<<" \n "<<"\n";
for(int u=195; u >=0; u--)
cout<<matfinale(u,0)<<" ";
cout<<" \n "<<"\n";
	cout<<mat_final.block<1,196> (0,0);
cout<<" \n "<<"\n";*/
	set_Matrice_Finale(matfinale);
//cout<<matfinale;

}

/** \fn void Voronoi::iteration(int jour)
 *  \brief Création du diagramme de Voronoï pour le ième jour
 *  \param jour 
 *  \return Rien
 */
void Voronoi::iteration(int jour){
	voronoi_iteration(jour, get_Matrice_Donnees(),get_Matrice_Index());
}

/** \fn Matrice Voronoi::get_Matrice_Coordonnees()
 *  \brief Retourne la matrice de coordonnées
 *  \return *mat_coord 
 */
Matrice Voronoi::get_Matrice_Coordonnees(){
	return mat_coord;
}

/** \fn Matrice Voronoi::get_Matrice_Donnees()
 *  \brief Retourne la matrice des données
 *  \return *mat_data 
 */
Matrice Voronoi::get_Matrice_Donnees(){
	return mat_data;
}

/** \fn  Matrice Voronoi::get_Matrice_Index()
 *  \brief Retourne la matrice des indices
 *  \return *mat_index
 */
Matrice Voronoi::get_Matrice_Index(){
	return mat_index;
}

/** \fn  Matrice Voronoi::get_Matrice_Finale()
 *  \brief Retourne la matrice finale de Voronoï
 *  \return *mat_finale
 */
Matrice Voronoi::get_Matrice_Finale(){
	return mat_finale;
}

/** \fn void Voronoi::set_Matrice_Coordonnees(Matrice mat)
 *  \brief Mise à jour de la matrice des coordonnées
 *  \param mat Matrice des coordonnées
 *  \return Rien
 */
void Voronoi::set_Matrice_Coordonnees(Matrice mat){
	mat_coord = mat;
}

/** \fn void Voronoi::set_Matrice_Donnees(Matrice mat)
 *  \brief Mise à jour de la matrice des données
 *  \param mat Matrice des données
 *  \return Rien
 */
void Voronoi::set_Matrice_Donnees(Matrice mat){
	mat_data = mat;
}

/** \fn void Voronoi::set_Matrice_Index(Matrice mat)
 *  \brief Mise à jour de la matrice des indices
 *  \param mat Matrice des indices
 *  \return Rien
 */
void Voronoi::set_Matrice_Index(Matrice mat){
	mat_index = mat;
}

/** \fn void Voronoi::set_Matrice_Finale(Matrice mat)
 *  \brief Mise à jour de la matrice finale de Voronoï
 *  \param mat Matrice finale de Voronoï
 *  \return Rien
 */
void Voronoi::set_Matrice_Finale(Matrice mat){
	mat_finale = mat;
}




