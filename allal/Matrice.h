#ifndef MATRICE_H
#define MATRICE_H

#include <iostream>
using std::ostream;

class Matrice {
private:
  float * mat;
  int nbLigne, nbColonne;
  int indice(int i ,int j) const;

public:
  Matrice(int, int);
  Matrice(const Matrice&);
  ~Matrice();

  void multiplier(const Matrice&,const Matrice&);//
  void affiche() const;
  void setValue(int, int, float);
  float getValue(int,int) const;
  void setMatrice(const Matrice&);

/*
 *\note une redéfinition d'un opérateur dans une classe ne peut avoir que zéro ou un 
 *argument.Friend= la fonction ne fait pas partie de la classe mais 
 *elle a connaissance de tous les champs (privés et publics) de la classe
*/

  friend ostream& operator<<(ostream&, const Matrice&);
  Matrice& operator=(const Matrice&);
  Matrice operator*(const Matrice&);

  Matrice matriceSuperieure() const;
  Matrice matriceInferieure() const;
  Matrice matriceInverseU() const;
  Matrice matriceInverseL() const;
  Matrice matriceN1(const Matrice &,const Matrice &);

  friend float* Matrice_en_VecteurA(const Matrice &);
  friend float* Matrice_en_VecteurB(const Matrice &);
  friend float* Matrice_en_VecteurC(const Matrice &);
};



#endif
