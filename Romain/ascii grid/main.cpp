#include <cstdlib>
#include <iostream>
#include <fstream>
#include "../modele/Matrice.h"
#include "Ascii.h"
#define TAILLE_DEFAUT 10

using namespace std;

int main(int argc, char *argv[])
{
    Matrice MatriceResultat(TAILLE_DEFAUT,TAILLE_DEFAUT);     
    MatriceResultat=Lecture("MNT500_L93_FRANCE.ASC");
    //MatriceResultat.affiche();
    Ecriture(2321 ,2161 ,89750 ,6039750 ,500 ,-9999 ,MatriceResultat ,"test.ASC");
    system("PAUSE");
    return EXIT_SUCCESS;
}
