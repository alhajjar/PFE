#ifndef MATRICEU_H
#define MATRICEU_H
#include "MatriceN.h"
#include <iostream>
using std::ostream;

class MatriceU{
private:
  //1 tableau de valeurs ck*:
  float * Cketoile; 
  int taille;

public:
  MatriceU(MatriceN);

  ~MatriceU();

  void afficheU() const;

  void setUValue(int,float);
  float getUValue(int) const;

  void matriceSuperieure_Cketoile(const MatriceN &) const ;
float * * matriceInverseU(const MatriceN & ) const; 
};

#endif
