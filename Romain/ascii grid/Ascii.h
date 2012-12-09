#ifndef ASCII_H
#define ASCII_H

#include <cstdlib>
#include <fstream>
#include "../modele/Matrice.h"
#include <iostream>
#include <string>


Matrice Lecture(std::string fichierAscii);
void Ecriture(int ,int ,int ,int ,int ,int ,Matrice ,std::string fichierAscii);

#endif
