#include "MatriceU.h"
#include <assert.h>

using namespace std;


/** \Constructeur matrice U
 *  \brief Constructeur et initialisation du tableau U des ck*
 *  \param [in] i la taille du tableau
 *  \return un tableau
 *  \note:on initialise le tableau avec des zeros
 */
MatriceU::MatriceU(MatriceN N){
	taille = N.getTaille();
	Cketoile=new float[taille];
	matriceSuperieure_Cketoile(N);
    
}



/** \Destructeur tableau U
 *  \brief Destructeur
 */
MatriceU::~MatriceU(){
  delete(Cketoile);
}

/** \Fonction setUValue
 *  \brief modifie une valeur qui se trouve dans le tableau des Ck* à la position i
 *  \param [in] i position dans un tableau, v la valeur a placer dans la matrice
 *  \return le tableau avec une nouvelle valeur(v) a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
void MatriceU::setUValue(int i, float v){
  assert((0<=i) && (i<taille));

  Cketoile[i]= v;
}

/** \Fonction getUValue
 *  \brief renvoie la valeur se trouvant a la position i du tableau des ck*
 *  \param [in] i position dans un tableau 
 *  \return la valeur a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
float MatriceU::getUValue(int i) const{
  assert((0<=i) && (i<taille));
  return Cketoile[i];
}


/** \Fonction afficheU
 *  \brief affiche le tableau des ck*
 */
void MatriceU::afficheU() const {
 

   std::cout << "[";
  for(int i=0; i<taille-1; i++)
         std::cout << Cketoile[i] << ",";
  
	 std::cout << Cketoile[taille-1];
    	 std::cout << "] \n" << std::endl;

}

/*les méthodes et constructeurs pour construire le tableau des Ck*


/

/** \Fonction Calcul de la matrice supérieure des Ck*<<
 *  \brief permet de calculer le tableau des ck*
 *  \param [in] matrice ou se trouve les données
 *  \return U_ck*
*/

void MatriceU::matriceSuperieure_Cketoile(const MatriceN &N) const {
  

  // calcul de C1*:
  Cketoile[0]= N.getCValue(0)/N.getBValue(0);

  // calcul des Ck*:
  for(int i=1;i<taille;i++)
	 Cketoile[i]= N.getCValue(i)/(N.getBValue(i)-(N.getAValue(i)*Cketoile[i-1]));



}

//** \Fonction Calcul Inverse de la matrice Uinv<<
 /*  \brief permet de calculer la matrice inverse de U
 *  \param [in] matrice U 
 *  \return Uinverse*/

float * * MatriceU::matriceInverseU(const MatriceN &N) const {
    
   
    float * * Uinv;
    Uinv = new float* [taille];
    for(int i=0; i<taille;i++)
            Uinv[i]=new float[taille-i];
            
    for(int j=0;j< taille;j++){
            Uinv[0][j]=1;
    }

   for(int j=1;j< taille;j++){
    for(int i=0;i<taille-j;i++){
      Uinv[j][i] = -Cketoile[i]*Uinv[j-1][i+1];
    
      

}

}
    return Uinv;
}


