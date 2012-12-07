#include "Matrice.h"
#include "MatriceN.h"
#include "MatriceU.h"
#include "MatriceL.h"
#include <cstdlib>
#include <iostream>
#include <time.h>

#define TAILLE 4
using namespace std;

int main(int argc, char *argv[]){

/** \Exemple de matrice N1 de TAILLE TAILLE */
 
  Matrice m(TAILLE,TAILLE);
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
/*Matrice inverse de N*/


/*
  Matrice U(TAILLE,TAILLE);
  U = m.matriceSuperieure();
  cout<<"matrice supérieure U\n";
  U.affiche();
  cout<<"\n";

  Matrice L(TAILLE,TAILLE);
  L = m.matriceInferieure();
  cout<<"matrice inférieure L\n";
  L.affiche();
  cout<<"\n";


  Matrice Uinv(TAILLE,TAILLE);
  Uinv= U.matriceInverseU();
  cout<<"matrice inverse U \n";
  Uinv.affiche();
  cout<<"\n";


  Matrice Linv(TAILLE,TAILLE);
  Linv= L.matriceInverseL();
  cout<<"matrice inverse L \n";
  Linv.affiche();
  cout<<"\n";*/

  /*Matrice N1(TAILLE,TAILLE);
  N1.multiplier(L,U);
  //N1 = L*U;
  cout<<"matrice N1 \n";
  N1.affiche();
  cout<<"\n";

  Matrice N1inv(TAILLE,TAILLE);
  N1inv.multiplier(Uinv,Linv);
  cout<<"matrice N1inv \n";
  N1inv.affiche();
  cout<<"\n";

  Matrice Identite(TAILLE,TAILLE);
  Identite.multiplier(N1,N1inv);
  cout<<"matrice Identite \n";
  Identite.affiche();
  cout<<"\n";*/


/*création de trois instances de la matriceN*/

MatriceN Tableaux1(TAILLE);
MatriceN Tableaux2(TAILLE);
MatriceN Tableaux3(TAILLE);

/*extraction des coeffs de la diagonale inférieure tabA*/
cout<<"TabA\n";
Tableaux1.Matrice_en_tabA(m);
Tableaux2.Matrice_en_tabA(m);
Tableaux1.afficheA();

/*extraction des coeffs de la diagonale principale tabB*/
cout<<"TabB\n";
Tableaux1.Matrice_en_tabB(m);
Tableaux2.Matrice_en_tabB(m);
Tableaux1.afficheB();

/*extraction des coeffs de la diagonale supérieure tabC*/
cout<<"TabC\n";
Tableaux1.Matrice_en_tabC(m);
Tableaux2.Matrice_en_tabC(m);
Tableaux1.afficheC();

/*Affichage des coeffs ck* de la matrice U*/
cout<<"Ck*\n";
MatriceU Cketoil(Tableaux1);
Cketoil.afficheU();

/*Affichage des coeffs bk* de la matrice L*/
cout<<"Bk*\n";
MatriceL Bketoil(Tableaux2);
Bketoil.afficheL();

/*Affichage des différentes diagonales non nulles de la matrice Linv*/
cout<<"Linv\n";
float * * ResLinv;
 ResLinv=Bketoil.matriceInverseL(Tableaux2);

 for(int i=0;i< TAILLE;i++){
	std::cout << "[";
         for(int j=0;j<TAILLE-i-1;j++){
            cout<<ResLinv[i][j]<<",";
            }
	    cout<<ResLinv[i][TAILLE-i-1];
            cout<<"]\n";
 }        
cout<<"\n";


/*Affichage des différentes diagonales non nulles de la matrice Uinv*/
cout<<"Uinv\n";
float * * ResUinv;

 ResUinv=Cketoil.matriceInverseU(Tableaux1);

for(int i=0;i< TAILLE;i++){
	cout << "[";
         for(int j=0;j<TAILLE-i-1;j++){
            cout<<ResUinv[i][j]<<",";
            }
	    cout<<ResUinv[i][TAILLE-i-1];
            cout<<"]\n";
 } 
cout<<"\n";


/*Affichage de la Ninv*/
cout<<"Ninv\n";
Matrice Ninv(TAILLE,TAILLE);
Ninv = Tableaux3.matriceInverseN(ResUinv,ResLinv);
Ninv.affiche();
cout<<"\n";
  //  system("PAUSE");
 // return EXIT_SUCCESS;
  
}

