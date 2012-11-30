#include "MatriceL.h"
#include <assert.h>

using namespace std;


/** \Constructeur matrice L
 *  \brief Constructeur et initialisation du tableau L des bk*
 *  \param [in] i la taille du tableau
 *  \return un tableau
 *  \note:on initialise le tableau avec des zeros
 */
MatriceL::MatriceL(MatriceN N){
	taille = N.getTaille();
	Bketoile=new float[taille];
	matriceSuperieure_Bketoile(N);
//        matriceInverseL(N);

    
}



/** \Destructeur tableau L
 *  \brief Destructeur
 */
MatriceL::~MatriceL(){
  delete(Bketoile);
}

/** \Fonction setLValue
 *  \brief modifie une valeur qui se trouve dans le tableau des bk* à la position i
 *  \param [in] i position dans un tableau, v la valeur a placer dans la matrice
 *  \return le tableau avec une nouvelle valeur(v) a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
void MatriceL::setLValue(int i, float v){
  assert((0<=i) && (i<taille));

  Bketoile[i]= v;
}

/** \Fonction getLValue
 *  \brief renvoie la valeur se trouvant a la position i du tableau des bk*
 *  \param [in] i position dans un tableau 
 *  \return la valeur a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
float MatriceL::getLValue(int i) const{
  assert((0<=i) && (i<taille));
  return Bketoile[i];
}


/** \Fonction afficheL
 *  \brief affiche le tableau des bk*
 */
void MatriceL::afficheL() const {
 

   std::cout << "[";
  for(int i=0; i<taille-1; i++)
         std::cout << Bketoile[i] << ",";
  
	 std::cout << Bketoile[taille-1];
    	 std::cout << "] \n" << std::endl;

}

/*les méthodes et constructeurs pour construire le tableau des bk*


/

/** \Fonction Calcul de la matrice supérieure des bk*<<
 *  \brief permet de calculer le tableau des bk*
 *  \param [in] matrice ou se trouve les données
 *  \return L_bk*
*/

void MatriceL::matriceSuperieure_Bketoile(const MatriceN &N) const {
  

// calcul de B1*:
  Bketoile[0]= N.getBValue(0);

// calcul de bk*

  for(int i=1;i<taille;i++){
   Bketoile[i]= N.getBValue(i)- N.getAValue(i)* (N.getCValue(i-1)/Bketoile[i-1]);

   }

}


/** \Fonction Calcul Inverse de la matrice Linv<<
 *  \brief permet de calculer la matrice inverse de L
 *  \param [in] matrice L 
 *  \return Linverse*/

float * * MatriceL::matriceInverseL(const MatriceN &N) const {
    
   
    float * * Linv = 0;
    Linv = new float* [taille];
    for(int i=0; i<taille;i++)
            Linv[i]=new float[taille-i];
            
    for(int i=0;i< taille;i++){
            Linv[0][i]=1/Bketoile[i];
    }

   for(int j=0;j< taille-1;j++){
    for(int i=1;i< taille-j;i++){
	    Linv[i][j] = - N.getAValue(i+j) *  Linv[i-1][j] / Bketoile[i+j];

}


}
    return Linv;
}




