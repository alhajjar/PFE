/** 
 * \file Lecture_Ecriture.hpp
 * \brief Fichier d'ent�te de la biblioth�que de la lecture et �criture dans les formats CSV, ASCII Grid, Geotiff, SHP et ENVI header
 */

#ifndef __LECTURE_ECRITURE__
#define __LECTURE_ECRITURE__

#include "allincludes.hpp"
#include "shapefil.h"
#include "Rgbe.h"
#include <stdexcept>

/** \class Lecture_Ecriture
 *  \brief Classe de lecture et d'�criture pour les fichiers CSV, ASCII Grid, Geotiff, SHP et ENVI header
 */
class Lecture_Ecriture
{
public :
	__declspec(dllexport) Lecture_Ecriture();
	__declspec(dllexport) ~Lecture_Ecriture();

	__declspec(dllexport) int getRows();
	__declspec(dllexport) int getCols();
	__declspec(dllexport) int getXllcorner();
	__declspec(dllexport) int getYllcorner();
	__declspec(dllexport) int getCellsize();
	__declspec(dllexport) int getNODATA_value();
	__declspec(dllexport) Matrice get_CSV();

	__declspec(dllexport) void setRows(int val);
	__declspec(dllexport) void setCols(int val);
	__declspec(dllexport) void setXllcorner(int val);
	__declspec(dllexport) void setYllcorner(int val);
	__declspec(dllexport) void setCellsize(int val);
	__declspec(dllexport) void setNODATA_value(int val);

	__declspec(dllexport) void LectureCSV(int m, int n, string cheminFichier);
	__declspec(dllexport) void EcritureCSV(Matrice mat, string cheminFichier);
	
	__declspec(dllexport) Matrice LectureAscii(string fichiergeomatique);
	__declspec(dllexport) void EcritureAscii(Matrice, string fichiergeomatique);

	__declspec(dllexport) void LectureGeotiff(string fichiergeomatique);
	__declspec(dllexport) void EcritureGeotiff(Matrice, string fichiergeomatique);

	__declspec(dllexport) double **lecture_SHP(string fichiergeomatique);

	__declspec(dllexport) Matrice LectureEnvi(string fichiergeomatique);
	__declspec(dllexport) void EcritureEnvi(Matrice matrice, string fichiergeomatique);

private :
	Matrice sortie;
	string cheminFichier;
	int ncols , nrows, xllcorner, yllcorner, cellsize, NODATA_value;
};

#endif
		
		
		
		
		
	
