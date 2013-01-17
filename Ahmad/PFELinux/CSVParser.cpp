////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    CSVParser.cpp                               //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "Includes/CSVParser.hpp"

/** \Stockage des données dans une matrice
 *  \brief Stock dans une matrice les valeurs contenu dans un fichier 
 *  \param[in] fichierCSV : contient les données a stocker
 *  \return matrice: matrice contenant seulement les valeurs du fichier
 */

Matrice CSVParser(int m,int n, string filePath){

/** \declaration d'une matrice qui est de meme dimension du fichier CSV
*/
    Matrice mfinal(m,n);
    mfinal = Matrice::Zero(m,n);

/** \declaration d'une matrice de sortie dont le nombre de lignes 
*   \est egale au nombre de lignes du fichier CSV -1 et de meme nombre de colonnes 
*/
    Matrice mfin(m-1,n);
    mfin = Matrice::Zero(m-1,n);
/** \ouverture du fichier CSV
*/
    string data(filePath);
    ifstream in(data.c_str());
/** \s'il ne s'ouvre pas on aura une message d'erreur
*/
    if (in.fail()){
        cout <<filePath <<" "<<"not found" <<endl;
    }
/** \sinon il extrait son contenu et il le met dans une matrice
*/
    else{
/** \declaration trois vecteurs deux de type string et un de type double 
    \dans le premier on stocke une ligne du fichier CSV telquelle est.
    \exemple: a;d;c mais ce vecteur est former d'une seule case
    \on parcourt le premier vecteur et on le decoupe quand on trouve un ";"
    \puis on  stock les valeurs obtenues dans le deuxieme vecteur   
*/ 
        vector< string > vec;
        vector<string> splitArray;
        vector<double> splitArrayd;
        string line;
        int nbligne=0;
        /* ************************************************************* */
        while (getline(in,line))
        {
/** \on declare un jeton sur la ligne du CSV son debut est le debut de la ligne 
    \et sa fin est la fin du ligne
*/
            Tokenizer tok(line);
            vec.assign(tok.begin(),tok.end());
        /*// decomposition du vecteur obtenu et on le met dans un autre vecteur//*/
            split(splitArray, vec.at(0), is_any_of(";"));
            int nbcolonne=splitArray.size();
/** \on stocke le vecteur dans une matrice
*/
            for (int a=0;a!=nbcolonne;a++){
                try{
                    splitArrayd[a]= boost::lexical_cast<double>(splitArray[a]);
                    mfinal(nbligne,a)= splitArrayd.at(a);
                 }
                 catch(bad_lexical_cast &){
                    splitArrayd.push_back(0);
                   }
             }
          nbligne++;
          }
/** \on efface la premiere ligne de la matrice qui est la ligne d'entete du CSV
*/ 
mfin = mfinal.block(1,0,m-1,n);
    }
 return mfin;
}

