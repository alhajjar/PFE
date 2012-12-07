#include "Matrice.h"
#include "simulation.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <ctime>
#include "boostcsvfinal.h"
#define TAILLE_LIGNE 196
#define TAILLE_COLONNE 194

using namespace std;


int main(int argc, char *argv[]){
  time_t depart, arrivee;
  time(&depart);
  Matrice p(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice eta(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice theta(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice stades(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice coeffdepot1(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice coeffdepot2(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice coeffdepot3(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice coeffdepot4(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice coeffdepot5(TAILLE_LIGNE,TAILLE_COLONNE);
  Matrice coeffenvol(TAILLE_LIGNE,TAILLE_COLONNE);

  Matrice tauxaccroissement(TAILLE_LIGNE,TAILLE_COLONNE);
  p=importation("mat_p.csv");
  eta=importation("mat_eta.csv");
  stades = eta;
  theta = eta;

 /* for(int i=0;i<TAILLE_LIGNE;i++)
          for(int j=0;j<TAILLE_COLONNE;j++)
           theta.setValue(i,j,7);

    for(int i=0;i<TAILLE_LIGNE;i++)
          for(int j=0;j<TAILLE_COLONNE;j++)
           stades.setValue(i,j,rand()%100);*/

  tauxaccroissement=taux_accroissement(theta,stades);
  //std::cout << tauxaccroissement ;
  //cout<<"\n";


  coeffdepot1=coeff_depot1(p,eta);
  //std::cout << coeffdepot1 ;
  //cout<<"\n";

  coeffdepot2=coeff_depot2(p,eta);
  //std::cout << coeffdepot2 ;
  //cout<<"\n";

  coeffdepot3=coeff_depot3(p,eta);
  //std::cout << coeffdepot3 ;
  //cout<<"\n";

  coeffdepot4=coeff_depot4(p,eta);
  //std::cout << coeffdepot4 ;
  //cout<<"\n";

  coeffdepot5=coeff_depot5(p,eta);
  //std::cout << coeffdepot5 ;
  //cout<<"\n";

  coeffenvol=coeff_envol(50,theta,eta);
     cout<<"tauxaccroissement(1,1)  = "<<tauxaccroissement.getValue(1,1)
         <<"\n"<<"coeff_depot1(1,1) = "<<coeffdepot1.getValue(1,1)
         <<"\n"<<"coeff_depot2(1,1) = "<<coeffdepot2.getValue(1,1)
         <<"\n"<<"coeff_depot3(1,1) = "<<coeffdepot3.getValue(1,1)
         <<"\n"<<"coeff_depot4(1,1) = "<<coeffdepot4.getValue(1,1)
         <<"\n"<<"coeff_depot5(1,1) = "<<coeffdepot5.getValue(1,1)
         <<"\n"<<"coeff_envol(1,1)  = "<<coeffenvol.getValue(1,1);


  //std::cout << coeffenvol ;
  //cout<<"\n";
  //time(&arrivee);
  //cout<< "temps:" <<(((float)arrivee-(float)depart)/1000000.0F)*1000<<"\n";
 /* for (int i=0;i<196;i++){
      for (int j=0;j<194;j++){
          cout << theta.getValue(i,j) << "\t" << stades.getValue(i,j) << "\t" << tauxaccroissement.getValue(i,j)<<"\n";
          }
}*/

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
  //system("PAUSE");
  return EXIT_SUCCESS;

}

