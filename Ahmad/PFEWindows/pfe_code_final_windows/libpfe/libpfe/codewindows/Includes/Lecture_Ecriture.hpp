/** 
 * \file Lecture_Ecriture.hpp
 * \brief Fichier d'entête de la bibliotheque de la lecture et écriture dans les formats CSV, ASCII Grid, Geotiff et SHP
*/

#ifndef __LECTURE_ECRITURE__
#define __LECTURE_ECRITURE__

#include "allincludes.hpp"

/** \class Lecture_Ecriture
 *  \brief Classe de lecture et d'écriture pour les fichiers CSV, ASCII Grid, Geotiff et SHP
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

	__declspec(dllexport) void LectureCSV(int m,int n, string cheminFichier);
	__declspec(dllexport) void EcritureCSV(Matrice mat, string cheminFichier);
	
	__declspec(dllexport) Matrice LectureAscii(string fichiergeomatique);
	__declspec(dllexport) void EcritureAscii(Matrice ,string fichiergeomatique);

	__declspec(dllexport) void LectureGeotiff(std::string fichiergeomatique);
	__declspec(dllexport) void EcritureGeotiff(Matrice ,string fichiergeomatique);

private :
	Matrice sortie;
	string cheminFichier;
	int ncols , nrows, xllcorner, yllcorner, cellsize, NODATA_value;
};

#endif
		
		
		
		
		
	
