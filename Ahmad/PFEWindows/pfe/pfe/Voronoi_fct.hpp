////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    voronoi_fct.hpp                             //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#ifndef Voronoi_fct_H
#define Voronoi_fct_H

#include "allincludes.hpp"
#include "CSVParser.hpp"

/* Fonction de lecture du fichier de coordonn�es des villes qui prend en entr�e le nom du fichier,
   le nombre de lignes et le nombre de colonnes de ce dernier et renvoie la matrice des coordonn�es */
Matrice voronoi_lecture_coord(string file_name_coord, int nb_row_coord, int nb_col_coord); // param�tres des fichiers .csv

/* Fonction de lecture du fichier de donn�es de temp�rature ou stade ph�nologique qui prend en entr�e le nom du fichier,
   le nombre de lignes et le nombre de colonnes de ce dernier et renvoie la matrice des donn�es */
Matrice voronoi_lecture_data(string file_name_data, int nb_row_data, int nb_col_data);

/* Fonction de construction de la matrice des indices qui prend en entr�e la matrice des coordonn�es
   et le nombre de lignes et colonnes des fichiers de coordonn�es et de donn�es. Celle-ci contient, 
   pour chaque position, l'indice de la ville la plus proche */
Matrice voronoi_build_index(Matrice mat_coord, int nb_row_coord, int nb_col_coord,int nb_row_data, int nb_col_data);

/* Fonction d'affichage des matrices de taille 194*196 */
void affiche_matrice_194_196(Matrice matrice);

/* Fonction qui calcule la matrice finale en fonction du jour et des matrices de donn�es et d'index */
Matrice voronoi_iteration(int jour, Matrice mat_data, Matrice mat_index);

#endif