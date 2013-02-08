/** 
 * \file Voronoi.hpp
 * \brief Fichier d'entête de la bibliothèque de la création et de l'utilisation du diagramme de Voronoï
*/

#ifndef __VORONOI__
#define __VORONOI__

#include "allincludes.hpp"
#include "Lecture_Ecriture.hpp"

/** \class Voronoi
 *  \brief Classe de création et d'utilisation du diagramme de Voronoï <A HREF="fr.wikipedia.org/wiki/Diagramme_de_Voronoï">Cours Voronoï</A>
 */
class Voronoi {
public:
	__declspec(dllexport) Voronoi();
	__declspec(dllexport) Voronoi(string coord_file_name, int nb_row_coord, int nb_col_coord, string data_file_name, int nb_row_data, int nb_col_data);
	__declspec(dllexport) ~Voronoi();
	
	__declspec(dllexport) void lecture_coordonnees(string file_name_coord, int nb_row_coord, int nb_col_coord);
	__declspec(dllexport) void lecture_donnees(string file_name_data, int nb_row_data, int nb_col_data);
	__declspec(dllexport) void construction_index(Matrice mat_coord, int nb_row_coord, int nb_col_coord, int nb_row_data, int nb_col_data);
	__declspec(dllexport) void voronoi_iteration(int jour, Matrice mat_data, Matrice mat_index);
	__declspec(dllexport) void iteration(int jour);
	
	__declspec(dllexport) Matrice get_Matrice_Coordonnees();  
	__declspec(dllexport) Matrice get_Matrice_Donnees();  
	__declspec(dllexport) Matrice get_Matrice_Index();
	__declspec(dllexport) Matrice get_Matrice_Finale();

	__declspec(dllexport) void set_Matrice_Coordonnees(Matrice mat);
	__declspec(dllexport) void set_Matrice_Donnees(Matrice mat);
	__declspec(dllexport) void set_Matrice_Index(Matrice mat);
	__declspec(dllexport) void set_Matrice_Finale(Matrice mat);
  
private:  
	Matrice mat_coord;
	Matrice mat_data;
	Matrice mat_index;
	Matrice mat_finale;
};

#endif
