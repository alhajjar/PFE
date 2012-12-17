//#include "Matrice.h"
#include <iostream>
#include "Ascii.h"
#define TAILLE_DEFAUT 10

using namespace std;

int main(){

    
    Matrice MatriceResultat(TAILLE_DEFAUT,TAILLE_DEFAUT);  
    Ascii asci;
  
    MatriceResultat=asci.Lecture("MNT500_L93_FRANCE.ASC");
    
    //MatriceResultat.affiche();

    asci.setRows(2007);
    asci.setCols(2100);
    asci.setXllcorner(89000);
    asci.setYllcorner(6034253);
    asci.setCellsize(400);
    asci.setNODATA_value(-6666);
    asci.Ecriture(MatriceResultat ,"test.ASC");
    //system("PAUSE");
    return EXIT_SUCCESS;
	
}

