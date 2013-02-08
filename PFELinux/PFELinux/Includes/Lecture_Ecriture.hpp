/** 
 * \file Lecture_Ecriture.hpp
 * \brief Fichier d'entête de la bibliothèque de la lecture et écriture dans les formats CSV, ASCII Grid, Geotiff, SHP et ENVI header
 */

#ifndef __LECTURE_ECRITURE__
#define __LECTURE_ECRITURE__

#include "allincludes.hpp"
#include "shapefil.h"
#include "Rgbe.h"
#include <stdexcept>

/** \class Lecture_Ecriture
 *  \brief Classe de lecture et d'écriture pour les fichiers CSV, ASCII Grid, Geotiff, SHP et ENVI header
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

	 void LectureCSV(int m, int n, string cheminFichier);
	 void EcritureCSV(Matrice mat, string cheminFichier);
	
	 Matrice LectureAscii(string fichiergeomatique);
	 void EcritureAscii(Matrice, string fichiergeomatique);

	 void LectureGeotiff(string fichiergeomatique);
	 void EcritureGeotiff(Matrice, string fichiergeomatique);

	 double **lecture_SHP(string fichiergeomatique);

	 Matrice LectureEnvi(string fichiergeomatique);
	 void EcritureEnvi(Matrice matrice, string fichiergeomatique);

private :
	Matrice sortie;
	string cheminFichier;
	int ncols , nrows, xllcorner, yllcorner, cellsize, NODATA_value;
};

#endif
		
		
		
		
		
	
