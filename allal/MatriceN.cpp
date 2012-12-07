#include "MatriceN.h"

#include <assert.h>

/** \Constructeur matrice
 *  \brief Constructeur et initialisation des 3 tableaux
 *  \param [in] i la taille des tableaux
 *  \return trois tableaux
 *  \note:on initialise les tableaux avec des zeros
 */
MatriceN::MatriceN(int i){
  taille =i;
  tabA = new float[i];
  tabB = new float[i];
  tabC = new float[i];

}


/** \Destructeur matrice
 *  \brief Destructeur
 */
MatriceN::~MatriceN(){
  delete(tabA);
  delete(tabB);
  delete(tabC);
}
/** \Fonction setAValue
 *  \brief modifie une valeur qui se trouve dans le ytableau A de la matrice Nà la position i
 *  \param [in] i position dans un tableau, v la valeur a placer dans la matrice
 *  \return le tableau avec une nouvelle valeur(v) a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
void MatriceN::setAValue(int i, float v){
  assert((0<=i) && (i<taille));

  tabA[i]= v;
}
/** \Fonction getAValue
 *  \brief renvoie la valeur se trouvant a la position i du tableau A
 *  \param [in] i position dans un tableau 
 *  \return la valeur a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
float MatriceN::getAValue(int i) const{
  assert((0<=i) && (i<taille));
  return tabA[i];
}



/** \Fonction setBValue
 *  \brief modifie une valeur qui se trouve dans le tableau B de la matrice N à la position i
 *  \param [in] i position dans un tableau, v la valeur a placer dans la matrice
 *  \return le tableau avec une nouvelle valeur(v) a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
void MatriceN::setBValue(int i, float v){
  assert((0<=i) && (i<taille));

  tabB[i]= v;
}
/** \Fonction getBValue
 *  \brief renvoie la valeur se trouvant a la position i du tableau B
 *  \param [in] i position dans un tableau 
 *  \return la valeur a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
float MatriceN::getBValue(int i) const{
  assert((0<=i) && (i<taille));
  return tabB[i];
}

/** \Fonction setCValue
 *  \brief modifie une valeur qui se trouve dans le tableau C de la matrice N à la position i
 *  \param [in] i position dans un tableau, v la valeur a placer dans la matrice
 *  \return le tableau avec une nouvelle valeur(v) a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
void MatriceN::setCValue(int i, float v){
  assert((0<=i) && (i<taille));

  tabC[i]= v;
}
/** \Fonction getCValue
 *  \brief renvoie la valeur se trouvant a la position i du tableau C
 *  \param [in] i position dans un tableau 
 *  \return la valeur a la position i
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
float MatriceN::getCValue(int i) const{
  assert((0<=i) && (i<taille));
  return tabC[i];
}
/** \Fonction afficheA
 *  \brief affiche le tableau A
 */
void MatriceN::afficheA() const {
 
  std::cout << "[";
  for(int i=0; i<taille-1; i++)
    std::cout << tabA[i] << ",";
    std::cout << tabA[taille-1];
    std::cout << "] \n" << std::endl;
}

/** \Fonction afficheB
 *  \brief affiche le tableau B
 */
void MatriceN::afficheB() const {

  std::cout << "[";
  for(int i=0; i<taille-1; i++)
   std::cout << tabB[i] << ",";
   std::cout << tabB[taille-1];
   std::cout << "] \n" << std::endl;
}

/** \Fonction afficheC
 *  \brief affiche le tableau C
 */
void MatriceN::afficheC() const {

  std::cout << "[";
  for(int i=0; i<taille-1; i++)
   std::cout << tabC[i] << ",";
   std::cout << tabC[taille-1];
   std::cout << "] \n" << std::endl;
}


/** \Fonction Matrice N en tableau A <<
 *  \brief permet d'extraire la diagonale inférieure d'une matrice
 *  \param [in] matrice ou se trouve les données 
 *  \return la diagonale inférieure 
 */
void MatriceN::Matrice_en_tabA(const Matrice &m){

      for(int l=2; l<taille+1; l++){
	setAValue(l-1,m.getValue(l-1,l-2));
      }	
}


/** \Fonction Matrice N en tableau B <<
 *  \brief permet d'extraire la diagonale principale d'une matrice
 *  \param [in] matrice ou se trouve les données 
 *  \return la diagonale principale
 */
void MatriceN::Matrice_en_tabB(const Matrice &m){

      for(int l=0; l<taille; l++){
	setBValue(l,m.getValue(l,l));
      }	
}


/** \Fonction Matrice N en tableau C <<
 *  \brief permet d'extraire la diagonale supérieure d'une matrice
 *  \param [in] matrice ou se trouve les données 
 *  \return la diagonale supérieure 
 */

void MatriceN::Matrice_en_tabC(const Matrice &m){

      for(int l=1; l<taille; l++){
	setCValue(l-1,m.getValue(l-1,l));
      }	
}

/** \Fonction Retourne la taille de la matrice <<
 *  \brief permet de renvoyer le taille d'une matrice 
 */
int MatriceN::getTaille() const{
     return taille;
}


/** \Fonction calcul de la matrice inverse de N <<
 *  \brief permet de calculer Ninv à partir de Linv et Uinv
 *  \param [in] tableau à 2D Uinv et Linv 
 *  \return la matrice Ninv
/*expliquer le principe de ce calcul matriciel qui n'est pas conventionnel*/

Matrice MatriceN:: matriceInverseN(float ** &Uinv,float ** &Linv) const{

int l;
Matrice Ninv(taille,taille);

	for(int i=0; i<taille; i++){

		for(int j=0;j<taille;j++){
	         if((i-j)>0) 
	          l=i;
	         else l=j;


        Ninv.setValue(j,i,0);
			   for(int k=0;k<taille-l;k++){
				Ninv.setValue(j,i,Ninv.getValue(j,i)+ Uinv[taille-k-1-j][j] * Linv[taille-k-i-1][i]);
	            	    }
                 }

	}	

return Ninv;
}














