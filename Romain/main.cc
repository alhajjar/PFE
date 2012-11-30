#include "Matrice.h"
#include "simulation.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#define TAILLE_LIGNE 196
#define TAILLE_COLONNE 194

using namespace std;


int main(int argc, char *argv[]){
  Matrice eta(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice theta(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice stades(TAILLE_LIGNE,TAILLE_COLONNE);
  for(int i=0;i<TAILLE_LIGNE;i++)
          for(int j=0;j<TAILLE_COLONNE;j++)
           stades.setValue(i,j,rand()%100);
  Matrice result(TAILLE_LIGNE,TAILLE_COLONNE);
  for(int i=0;i<TAILLE_LIGNE;i++)
          for(int j=0;j<TAILLE_COLONNE;j++)
           eta.setValue(i,j,(rand()%2)*2-1);

  /*
  result=taux_accroissement(theta,stades);
  std::cout << result ;
  cout<<"\n";
  
  result=coeff_depot1(0.5,eta);
  std::cout << result ;
  cout<<"\n";
  
  result=coeff_depot2(0.6,eta);
  std::cout << result ;
  cout<<"\n";
  
  result=coeff_depot3(0.6,eta);
  std::cout << result ;
  cout<<"\n";
  
  result=coeff_depot4(0.4,eta);
  std::cout << result ;
  cout<<"\n";
  
  result=coeff_depot5(0.4,eta);
  std::cout << result ;
  cout<<"\n";
  
  result=coeff_envol(50,theta,eta);
  std::cout << result ;
  cout<<"\n";*/
  /*
  cout<<taux_accroissement(m,n);
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

  
  Matrice U(4,4);
  U = m.matriceSuperieure();
  cout<<"matrice supérieure U\n";
  U.affiche();
  cout<<"\n";

  Matrice L(4,4);
  L = m.matriceInferieure();
  cout<<"matrice inférieure L\n";
  L.affiche();
  cout<<"\n";


  Matrice Uinv(4,4);
  Uinv= U.matriceInverseU();
  cout<<"matrice inverse U \n";
  Uinv.affiche();
  cout<<"\n";


  Matrice Linv(4,4);
  Linv= L.matriceInverseL();
  cout<<"matrice inverse L \n";
  Linv.affiche();
  cout<<"\n";

  Matrice N1(4,4);
  N1.multiplier(L,U);
  //N1 = L*U;
  cout<<"matrice N1 \n";
  N1.affiche();
  cout<<"\n";

  Matrice N1inv(4,4);
  N1inv.multiplier(Uinv,Linv);
  cout<<"matrice N1inv \n";
  N1inv.affiche();
  cout<<"\n";

  Matrice Identite(4,4);
  Identite.multiplier(N1,N1inv);
  cout<<"matrice Identite \n";
  Identite.affiche();
  cout<<"\n";
*/

  system("PAUSE");
  return EXIT_SUCCESS;
  
}

