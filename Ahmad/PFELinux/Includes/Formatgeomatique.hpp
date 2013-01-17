#ifndef FORMATGEOMATIQUE_H
#define FORMATGEOMATIQUE_H

#include "allincludes.hpp"
#include <tiffio.h> 

class Formatgeomatique{
private:
int ncols , nrows,xllcorner,yllcorner,cellsize,NODATA_value;
public:

Formatgeomatique();
~Formatgeomatique();
int getRows();
int getCols();
int getXllcorner();
int getYllcorner();
int getCellsize();
int getNODATA_value();

void setRows(int);
void setCols(int);
void setXllcorner(int);
void setYllcorner(int);
void setCellsize(int);
void setNODATA_value(int);

Matrice Lecture(std::string fichiergeomatique);
void Ecriture(Matrice ,std::string fichiergeomatique);

//lecture et ecriture de l'ascii grid
Matrice LectureAscii(std::string fichiergeomatique);
void EcritureAscii(Matrice ,std::string fichiergeomatique);

//lecture et ecriture du geotiff
Matrice LectureGeotiff(std::string fichiergeomatique);
void EcritureGeotiff(Matrice ,std::string fichiergeomatique);

};

#endif
