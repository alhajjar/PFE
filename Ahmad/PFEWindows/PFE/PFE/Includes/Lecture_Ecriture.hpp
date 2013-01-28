/** 
 * \file Lecture_Ecriture.hpp
 * \brief Fichier d'entête de la bibliotheque de la lecture et écriture dans les formats CSV, ASCII Grid, Geotiff et SHP
*/

#ifndef __LECTURE_ECRITURE__
#define __LECTURE_ECRITURE__

#include "allincludes.hpp"
#include "hdrloader.h"

/** \class Lecture_Ecriture
 *  \brief Classe de lecture et d'écriture pour les fichiers CSV, ASCII Grid, Geotiff et SHP
 */
class Lecture_Ecriture
{
public :
	Lecture_Ecriture();
	~Lecture_Ecriture();

	int getRows();
	int getCols();
	int getXllcorner();
	int getYllcorner();
	int getCellsize();
	int getNODATA_value();
	Matrice get_CSV();

	void setRows(int val);
	void setCols(int val);
	void setXllcorner(int val);
	void setYllcorner(int val);
	void setCellsize(int val);
	void setNODATA_value(int val);

	void LectureCSV(int m,int n, string cheminFichier);
	void EcritureCSV(Matrice mat, string cheminFichier);
	
	Matrice LectureAscii(string fichiergeomatique);
	void EcritureAscii(Matrice ,string fichiergeomatique);

	void LectureGeotiff(std::string fichiergeomatique);
	void EcritureGeotiff(Matrice ,string fichiergeomatique);

	//lecture du envi
	Matrice LectureEnvi(string fichiergeomatique);
	void EcritureEnvi(Matrice ,string fichiergeomatique);  


private :
	Matrice sortie;
	string cheminFichier;
	int ncols , nrows, xllcorner, yllcorner, cellsize, NODATA_value;
};

#endif
		
		
		
		
		
	
