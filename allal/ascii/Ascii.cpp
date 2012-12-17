#include "Ascii.h"
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


/** \Constructeur Ascii
 *  \brief Constructeur et initialisation des attributs
 */
Ascii:: Ascii(){

ncols = 0;
nrows = 0 ;
xllcorner =0;
yllcorner = 0;
cellsize = 0;
NODATA_value =0;
}



/** \Destructeur Ascii
 *  \brief Destructeur
 */
Ascii::~Ascii(){

 //delete (matrice);

}

/** \méthode de renvoi du nombre de ligne
 *  \brief 
 */
int Ascii::getRows() {
 return nrows;
	
}

/** \méthode de renvoi du nombre de colonne
 *  \brief 
 */
int Ascii::getCols() {
 return ncols;
	
}

/** \méthode de renvoi de l'abscisse de l'origine
 *  \brief 
 */
int Ascii::getXllcorner() {
 return xllcorner;
	
}

/** \méthode de renvoi de l'ordonné de l'origine
 *  \brief 
 */
int Ascii::getYllcorner() {
 return yllcorner;
	
}

/** \méthode de renvoi de la taille de la cellule
 *  \brief 
 */
int Ascii::getCellsize() {
 return cellsize;
	
}

/** \méthode de renvoi du no value
 *  \brief 
 */
int Ascii::getNODATA_value() {
 return NODATA_value;
	
}

/** \méthode de modification du nombre de ligne
 *  \brief 
 */
void Ascii::setRows(int rows) {
 nrows = rows;
	
}

/** \méthode de modification du nombre de colonne
 *  \brief 
 */
void Ascii::setCols(int cols) {
 ncols = cols;
	
}

/** \méthode de modification de l'abscisse d'origine
 *  \brief 
 */
void Ascii::setXllcorner(int xcorner) {
 xllcorner = xcorner;
	
}

/** \méthode de modification de l'ordonné d'origine
 *  \brief 
 */
void Ascii::setYllcorner(int ycorner) {
 yllcorner = ycorner;
	
}

/** \méthode de modification de la taille de la cellule
 *  \brief 
 */
void Ascii::setCellsize(int sizecell) {
 cellsize = sizecell;
	
}

/** \méthode de modification du no value
 *  \brief 
 */
void Ascii::setNODATA_value(int novalue) {
 NODATA_value = novalue;
	
}

/** \Stockage des données dans une matrice
 *  \brief Stock dans une matrice les valeurs contenu dans un fichier
 *  \param[in] fichierAscii : contient les données a stocker
 *  \return matrice: matrice contenant seulement les valeurs du fichier
 */
Matrice Ascii:: Lecture(string fichierAscii){
      ifstream fichier(fichierAscii.c_str(), ios::in);  // on ouvre le fichier en lecture
        if(fichier)  // si l'ouverture a réussi
        {       
           
            int entier;
	    string tamp; 
            
            fichier >> tamp >> ncols >> tamp >> nrows>>tamp>>xllcorner>>tamp>>yllcorner>>tamp>>cellsize>>tamp>>NODATA_value;
            Matrice mat(nrows,ncols);
             
            for(int i=0;i<nrows;i++){
                for(int j=0;j<ncols;j++){
                    fichier >> entier;
                    mat.setValue(i,j,entier);
                }
		
            }  
	   
           return mat;
            fichier.close();  // on ferme le fichier
        }
        else  // sinon
             cerr << "Impossible d'ouvrir le fichier !" << endl;
          

}    

/** \Création d'un fichier ASCII
 *  \brief Construit un fichier  de type ascii grid
 *  \param[in] nclos le nombre de colonne de la matrice, nrows le nombre de ligne de la matrice
 *  \xllcorner position iniale des valeurs en x,yllcornerposition iniale des valeurs en y
 *  \cellsize pas entre chaque valeur, NODATA_value valeur par defaut du manque de donnée
 *  \mat : contient les valeurs a enregistrer dans le fichier, fichierAscii nom qu'aura le fichier 
 */
void Ascii:: Ecriture(Matrice mat,std::string fichierAscii){
        
        ofstream fichier(fichierAscii.c_str(), ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
        if(fichier)
        {
                
                fichier << "ncols         " <<ncols<< endl;
                fichier << "nrows         " <<nrows<< endl;
                fichier << "xllcorner     " <<xllcorner<< endl;
                fichier << "yllcorner     " <<yllcorner<< endl;
                fichier << "cellsize      " <<cellsize<< endl;
                fichier << "NODATA_value  " <<NODATA_value<< endl;
                for(int i=0;i<nrows;i++){
                        for(int j=0;j<ncols;j++){
                                fichier << mat.getValue(i,j)<<" ";
                        }
                        fichier<<endl;
                }   
                
 
                fichier.close();
        }
        else
                cerr << "Impossible d'ouvrir le fichier !" << endl;  
             
}
  
