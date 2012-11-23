#include "Matrice.h"
#include <assert.h>
#include <vector>


/** \fonction indice
 *  \brief Retourne l'indice de la position dans un tableau 1D a partir d'indice de tableau 2D
 *  \param [in] i et j position dans un tableau 2D 
 *  \return l'indice position dans un tableau 1D 
 *  \note il est plus facile de travailler avec une simple allocation dynamique
 */
int Matrice::indice(int i, int j) const {
  return (j*nbLigne) + i;
}


/** \Constructeur matrice
 *  \brief Constructeur et initialisation de la matrice
 *  \param [in] i et j longueur de la matrice
 *  \return une matrire remplie de zero
 *  \note nbLigne et nbColonne permet de recuperer le nombre de ligne et de colonne d'une matrice
 *  on cree un tableau possedant le meme nombre de valeur que la matrice
 *  on initialise le tableau avec des zeros
 */
Matrice::Matrice(int i, int j){
  nbLigne = i;
  nbColonne = j;
  mat = new float[i*j];
  for(int k=0; k<i; k++)
    for(int l=0; l<j; l++)
      mat[indice(k,l)] = 0;
}

/** \copie de constructeur
 *  \brief Copie une matrice dans une nouvelle matrice
 *  \param [in] m matrice a copier
 *  \return une matrire ailllant les meme valeur que la premiere
 *  \note on construit une nouvelle matrice de meme dimension et possedant les meme valeurs
 *  const permet a m de ne pas etre modifier lors de l'appelle de la fonction
 */
Matrice::Matrice(const Matrice &m){
  nbLigne = m.nbLigne;
  nbColonne = m.nbColonne;
  mat = new float[nbLigne*nbColonne];
  for(int k=0; k<nbLigne; k++)
    for(int l=0; l<nbColonne; l++)
      mat[indice(k,l)] = m.mat[indice(k,l)];
}

/** \Destructeur matrice
 *  \brief Destructeur
 */
Matrice::~Matrice(){
  delete(mat);
}
/** \Fonction setValue
 *  \brief modifie une valeur qui se trouve dans la matrice a la position i,j
 *  \param [in] i et j position dans un tableau 2D, v la valeur a placer dans la matrice
 *  \return la matrice avec une nouvelle valeur(v) a la position i ,j
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
void Matrice::setValue(int i, int j, float v){
  assert((0<=i) && (i<nbLigne));
  assert((0<=j) && (j<nbColonne));
  mat[indice(i,j)] = v;
}
/** \Fonction getValue
 *  \brief renvoie la valeur se trouvant a la position i,j
 *  \param [in] i et j position dans un tableau 2D
 *  \return la valeur a la position i,j
 *  \note assert permet de verifier les condition ne non debordement de la matrice
 */
float Matrice::getValue(int i, int j) const{
  assert((0<=i) && (i<nbLigne));
  assert((0<=j) && (j<nbColonne));
  return mat[indice(i,j)];
}
/** \Fonction affiche
 *  \brief affiche la matrice
 */
void Matrice::affiche() const {
  for(int k=0; k<nbLigne; k++){
    std::cout << "[";
    for(int l=0; l<nbColonne-1; l++){
      std::cout << mat[indice(k,l)] << ",";
    }
    std::cout << mat[indice(k,nbColonne-1)]<< "]" << std::endl;
  }
}


/** \Fonction operator<<
 *  \brief affichage par <<
 *  \param [in] la matrice a afficher
 *  \return ostream qqch
 *  \note la surcharge d'op�rateur(modifie le comportement du << )afin d'afficher une matrice directement a l'appelle de <<
 */
ostream& operator<<(ostream& out, const Matrice& m){
  for(int k=0; k<m.nbLigne; k++){
    out << "[";
    for(int l=0; l<m.nbColonne-1; l++){
      out << m.mat[m.indice(k,l)] << ",";
    }
    out << m.mat[m.indice(k,m.nbColonne-1)]<< "]" << std::endl;
  }
}

/** \Fonction operator=
 *  \brief permet de remplacer une matrice par une autre 
 *  \param [in] m matrice a copier
 *  \return une matrire ailllant les memes valeurs que la premiere
 */
Matrice& Matrice::operator=(const Matrice&m){
  delete(mat);
  nbLigne = m.nbLigne;
  nbColonne = m.nbColonne;
  mat = new float[nbLigne*nbColonne];
  for(int k=0; k<nbLigne; k++)
    for(int l=0; l<nbColonne; l++)
      mat[indice(k,l)] = m.mat[indice(k,l)];
}

/** \Fonction operator*
 *  \brief permet de multiplier une matrice par une autre 
 */
Matrice Matrice::operator*(const Matrice& m) {
  assert((m.nbLigne==nbLigne) && (m.nbColonne==nbColonne));
  Matrice result(nbLigne, nbColonne);
  for(int k=0; k<nbLigne; k++){
    for(int l=0; l<nbColonne; l++){
      for(int p=0; p<nbColonne; p++){
	result.mat[indice(k,l)] = result.mat[indice(k,l)]+ 
	  m.mat[indice(k,p)]*mat[indice(p,l)];
      }
    }
   } 
  return result;
}


/** \multiplie deux matrice entre elle 
 *  \brief multiplie deux matrice en elle
 *  \param [in] m et n les matrices a multiplier
 *  \return mat une matrice resultat du produit de deux matrices 
 *  \note 
 */

void Matrice::multiplier(const Matrice &m,const Matrice &n){
  assert((m.nbLigne==n.nbLigne) && (m.nbColonne==n.nbColonne));
  nbLigne = m.nbLigne;
  nbColonne = m.nbColonne;
  mat = new float[nbLigne*nbColonne];
  for(int k=0; k<nbLigne; k++){
    for(int l=0; l<nbColonne; l++){
       mat[indice(k,l)] = 0;
       for(int p=0; p<nbColonne; p++){
          mat[indice(k,l)] = mat[indice(k,l)]+ m.mat[indice(k,p)]*n.mat[indice(p,l)];
       }
    }
  }    
}


/** \Fonction Calcul de la matrice sup�rieure<<
 *  \brief permet de calculer la matrice U
 *  \param [in] matrice ou se trouve les donn�es
 *  \return U
*/

Matrice Matrice::matriceSuperieure() const {
  Matrice U(nbLigne,nbColonne);
  int c;
  
  // Mettre 1 sur la diagonale:
  for(c=0; c<nbColonne; c++)
    U.mat[indice(c,c)] = 1;

  // calcul de C1*:
  U.mat[indice(0,1)] = mat[indice(0,1)] / mat[indice(0,0)];

  // calcul des Ck*:
  for(c=2; c<nbColonne; c++)
    U.mat[indice(c-1,c)] = mat[indice(c-1,c)] / 
      (mat[indice(c-1,c-1)]-(mat[indice(c-1,c-2)]*U.mat[indice(c-2,c-1)]));
  return U;
}

/** \Fonction Calcul de la matrice inf�rieure<<
 *  \brief permet de calculer la matrice L
 *  \param [in] matrice ou se trouve les donn�es
 *  \return L
*/

Matrice Matrice::matriceInferieure() const {
  Matrice L(nbLigne,nbColonne);
  int c;
  
  // calcul de B1*:
  L.mat[indice(0,0)] = mat[indice(0,0)];

  for(c=1; c<nbColonne; c++){
    // calcul des Bk*:
    L.mat[indice(c,c)] = mat[indice(c,c)] -
      (mat[indice(c,c-1)] * (mat[indice(c-1,c)]/L.mat[indice(c-1,c-1)]));
    // calcul des ak:
    L.mat[indice(c,c-1)] = mat[indice(c,c-1)];
  }
  return L;
}


/** \Fonction Calcul Inverse de la matrice Uinv<<
 *  \brief permet de calculer la matrice inverse de U
 *  \param [in] matrice U 
 *  \return Uinverse
*/


Matrice Matrice::matriceInverseU() const {


  Matrice Uinv(nbLigne,nbColonne);
  int l,c;

  // Mettre 1 sur la diagonale:
  for(c=0; c<nbColonne; c++)
     Uinv.mat[indice(c,c)] = 1;
  
  for(c=0; c<nbColonne; c++){ 

	for(l=c;l>0;l--){

 	 Uinv.mat[indice(l-1,c)] = -(mat[indice(l-1,l)]*Uinv.mat[indice(l,c)]/mat[indice(l-1,l-1)]);

 
 	 }
}
  return Uinv;
}

/** \Fonction Calcul Inverse de la matrice Linv<<
 *  \brief permet de calculer la matrice inverse de L
 *  \param [in] matrice L 
 *  \return Linverse
*/


Matrice Matrice::matriceInverseL() const {


  Matrice Linv(nbLigne,nbColonne);
  int l,c;

  // Calcul de la diagonale:
  for(l=0; l<nbLigne; l++)
     Linv.mat[indice(l,l)] = 1/mat[indice(l,l)];
  
  for(c=0; c<nbColonne; c++){ 

	for(l=c;l<nbLigne-1;l++){

 	 Linv.mat[indice(l+1,c)] = -(mat[indice(l+1,l)]*Linv.mat[indice

 (l,c)]/mat[indice(l+1,l+1)]);

 
 	 }
}
  return Linv;
}


/** \Fonction Matrice en Vecteur <<
 *  \brief permet d'extraire la diagonale inf�rieure d'une matrice
 *  \param [in] matrice ou se trouve les donn�es 
 *  \return la diagonale inf�rieure 
 */
float* Matrice_en_VecteurA(const Matrice &m){

    float* matA = new float[m.nbColonne];


     for(int l=2; l<m.nbLigne+1; l++){
	
	matA[l-1] = m.getValue(l-1,l-2);

      }	

return matA;
}

/** \Fonction Matrice en Vecteur <<
 *  \brief permet d'extraire la diagonale principale d'une matrice
 *  \param [in] matrice ou se trouve les donn�es 
 *  \return la diagonale principale 
 */

float* Matrice_en_VecteurB(const Matrice &m){

float *matB = new float[m.nbColonne];
   for(int l=0; l<m.nbLigne; l++)
	
	matB[l] = m.getValue(l,l);

return matB;

}

/** \Fonction Matrice en Vecteur <<
 *  \brief permet d'extraire la diagonale sup�rieure d'une matrice
 *  \param [in] matrice ou se trouve les donn�es 
 *  \return la diagonale sup�rieure 
 */
float* Matrice_en_VecteurC(const Matrice &m){

float *matC = new float[m.nbColonne];
for(int l=1; l<m.nbLigne; l++)
	
	matC[l-1] = m.getValue(l-1,l);
 return matC;
}











