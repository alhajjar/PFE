#ifndef ASCII_H
#define ASCII_H

#include <cstdlib>
#include <fstream>
#include "Matrice.h"
#include <iostream>
#include <string>

class Ascii{
private:
int ncols , nrows,xllcorner,yllcorner,cellsize,NODATA_value;
Matrice *matrice;
public:

Ascii();
~Ascii();
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

Matrice Lecture(std::string fichierAscii);
void Ecriture(Matrice ,std::string fichierAscii);
};

#endif
