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

/* Fonction de lecture du fichier de coordonnées des villes qui prend en entrée le nom du fichier,
   le nombre de lignes et le nombre de colonnes de ce dernier et renvoie la matrice des coordonnées */
Matrice voronoi_lecture_coord(string file_name_coord, int nb_row_coord, int nb_col_coord); // paramètres des fichiers .csv

/* Fonction de lecture du fichier de données de température ou stade phénologique qui prend en entrée le nom du fichier,
   le nombre de lignes et le nombre de colonnes de ce dernier et renvoie la matrice des données */
Matrice voronoi_lecture_data(string file_name_data, int nb_row_data, int nb_col_data);

/* Fonction de construction de la matrice des indices qui prend en entrée la matrice des coordonnées
   et le nombre de lignes et colonnes des fichiers de coordonnées et de données. Celle-ci contient, 
   pour chaque position, l'indice de la ville la plus proche */
Matrice voronoi_build_index(Matrice mat_coord, int nb_row_coord, int nb_col_coord,int nb_row_data, int nb_col_data);

/* Fonction d'affichage des matrices de taille 194*196 */
void affiche_matrice_194_196(Matrice matrice);

/* Fonction qui calcule la matrice finale en fonction du jour et des matrices de données et d'index */
Matrice voronoi_iteration(int jour, Matrice mat_data, Matrice mat_index);

#endif