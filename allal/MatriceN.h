#ifndef MATRICEN_H
#define MATRICEN_H
#include "Matrice.h"

#include <iostream>
using std::ostream;

class MatriceN {
private:
  // 3 tableaux de valeurs:
  float * tabC; 
  float * tabB;
  float * tabA;
  int taille;
 

public:

  MatriceN(int);

  ~MatriceN();

  void setAValue(int,float);
  void setBValue(int,float);
  void setCValue(int,float);
  float getAValue(int) const;
  float getBValue(int) const;
  float getCValue(int) const;
  int getTaille() const;
  

  void afficheA() const;
  void afficheB() const;
  void afficheC() const;

  void Matrice_en_tabA(const Matrice &);
  void Matrice_en_tabB(const Matrice &);
  void Matrice_en_tabC(const Matrice &);

   Matrice matriceInverseN(float ** &,float ** &) const;
   
};

#endif



