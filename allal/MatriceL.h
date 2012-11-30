#ifndef MATRICEL_H
#define MATRICEL_H
#include "MatriceN.h"
#include <iostream>

using std::ostream;

class MatriceL {
private:
  //tableaux des bk*
   float * Bketoile;
 //  float *p;

   int taille;

public:
  MatriceL(MatriceN);

  ~MatriceL();

  void afficheL() const;

  void setLValue(int,float);
  float getLValue(int) const;

  void matriceSuperieure_Bketoile(const MatriceN&) const ;
  float * * matriceInverseL(const MatriceN &N) const;

};

#endif
