#include "Matrice.h"
#include <cstdlib>
#include <iostream>
#include <time.h>

#define taille 4
using namespace std;

int main(int argc, char *argv[]){


  Matrice m(taille,taille);
  m.setValue(0,0,1);
  m.setValue(0,1,4);
  m.setValue(0,2,0);
  m.setValue(0,3,0);

  m.setValue(1,0,3);
  m.setValue(1,1,4);
  m.setValue(1,2,1);
  m.setValue(1,3,0);

  m.setValue(2,0,0);
  m.setValue(2,1,2);
  m.setValue(2,2,3);
  m.setValue(2,3,4);

  m.setValue(3,0,0);
  m.setValue(3,1,0);
  m.setValue(3,2,1);
  m.setValue(3,3,3);





  cout<<"m matrice 4 4\n";
  std::cout << m ;
  cout<<"\n";

/*
  Matrice U(taille,taille);
  U = m.matriceSuperieure();
  cout<<"matrice supérieure U\n";
  U.affiche();
  cout<<"\n";

  Matrice L(taille,taille);
  L = m.matriceInferieure();
  cout<<"matrice inférieure L\n";
  L.affiche();
  cout<<"\n";


  Matrice Uinv(taille,taille);
  Uinv= U.matriceInverseU();
  cout<<"matrice inverse U \n";
  Uinv.affiche();
  cout<<"\n";


  Matrice Linv(taille,taille);
  Linv= L.matriceInverseL();
  cout<<"matrice inverse L \n";
  Linv.affiche();
  cout<<"\n";

  Matrice N1(taille,taille);
  N1.multiplier(L,U);
  //N1 = L*U;
  cout<<"matrice N1 \n";
  N1.affiche();
  cout<<"\n";

  Matrice N1inv(taille,taille);
  N1inv.multiplier(Uinv,Linv);
  cout<<"matrice N1inv \n";
  N1inv.affiche();
  cout<<"\n";

  Matrice Identite(taille,taille);
  Identite.multiplier(N1,N1inv);
  cout<<"matrice Identite \n";
  Identite.affiche();
  cout<<"\n";


*/


float* vectorA=new float[taille];

  vectorA = Matrice_en_VecteurA(m);

  cout<<"Vecteur A\n";


  std::cout << "[";
  for(int l=0; l<taille-1; l++)

         std::cout << vectorA[l] << ",";
	 std::cout << vectorA[taille-1];
    	 std::cout << "] \n" << std::endl;


float* vectorB=new float[taille];

  vectorB = Matrice_en_VecteurB(m);

  cout<<"Vecteur B\n";


  std::cout << "[";
  for(int l=0; l<taille-1; l++)

         std::cout << vectorB[l] << ",";
	 std::cout << vectorB[taille-1];
    	 std::cout << "] \n" << std::endl;

float* vectorC=new float[taille];

  vectorC = Matrice_en_VecteurC(m);

  cout<<"Vecteur C\n";


  std::cout << "[";
  for(int l=0; l<taille-1; l++)

         std::cout << vectorC[l] << ",";
	 std::cout << vectorC[taille-1];
    	 std::cout << "] \n" << std::endl;


  //  system("PAUSE");
  return EXIT_SUCCESS;
  
}

