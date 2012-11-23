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


  friend ostream& operator<<(ostream&, const Matrice&);
  Matrice& operator=(const Matrice&);
  Matrice operator*(const Matrice&);

  Matrice matriceSuperieure() const;
  Matrice matriceInferieure() const;
  Matrice matriceInverseU() const;
  Matrice matriceInverseL() const;
  Matrice matriceN1(const Matrice &,const Matrice &);


};

#endif
