#include "Includes/Ascii.hpp"


/** \Stockage des données dans une matrice
 *  \brief Stock dans une matrice les valeurs contenu dans un fichier
 *  \param[in] fichierAscii : contient les données a stocker
 *  \return matrice: matrice contenant seulement les valeurs du fichier
 */
Matrice Lecture_ASCII(string fichierAscii){

      ifstream fichier(fichierAscii.c_str(), ios::in);  // on ouvre le fichier en lecture
        if(fichier)  // si l'ouverture a réussi
        {       
            int nclos, nrows,xllcorner,yllcorner,cellsize,NODATA_value,entier;
            string tamp; 
            
            fichier >> tamp >> nclos >> tamp >> nrows>>tamp>>xllcorner>>tamp>>yllcorner>>tamp>>cellsize>>tamp>>NODATA_value;
            Matrice matrice(nrows,nclos);
          
            for(int i=0;i<nrows;i++){
                for(int j=0;j<nclos;j++){
                    fichier >> entier;
                    matrice(i,j)=entier;
                }
            }   
            return matrice;
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
void Ecriture_ASCII(int nrows,int nclos,int xllcorner,int yllcorner,int cellsize,int NODATA_value,Matrice mat,string fichierAscii){
        
        ofstream fichier(fichierAscii.c_str(), ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
        if(fichier)
        {
                
                fichier << "ncols         " <<nclos<< endl;
                fichier << "nrows         " <<nrows<< endl;
                fichier << "xllcorner     " <<xllcorner<< endl;
                fichier << "yllcorner     " <<yllcorner<< endl;
                fichier << "cellsize      " <<cellsize<< endl;
                fichier << "NODATA_value  " <<NODATA_value<< endl;
                for(int i=0;i<nrows;i++){
                        for(int j=0;j<nclos;j++){
                                fichier << mat(i,j)<<" ";
                        }
                        fichier<<endl;
                }   
                
 
                fichier.close();
        }
        else
                cerr << "Impossible d'ouvrir le fichier !" << endl;  
             
}
  
