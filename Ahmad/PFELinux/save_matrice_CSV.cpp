#include "Includes/save_matrice_CSV.hpp"
/** \Création d'un fichier CSV
 *  \brief Construit un fichier  de type CSV
 *  \param[in] n le nombre de colonne de la matrice, m le nombre de ligne de la matrice
 *  \mat la matrice a sauvgarder, str le nom du fichier CSV de sortie
 */
void save_matrice_CSV(int m , int n ,Matrice mat,string str)
{
   ofstream outdata; // outdata is like cin
   int i=0,j=0; // loop index

  outdata.open(str.c_str()); // opens the file
   if( !outdata ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }

  	for (j=0; j<n-1; j++){

  	    outdata << "V" <<";" ;
 	 }
  outdata  << "V"<<endl ;
  for (i=0; i<m-1; i++){

  	for (j=0; j<n-1; j++){
  	    outdata << mat(i,j)<<";" ;
 	 }
	outdata <<mat(i,j)<<endl ;
   }
   outdata.close();

}
