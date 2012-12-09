////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    main.cpp                                    //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "CSVParser.hpp"
#include "simulation.h"
#include "calcul_mat_N.hpp"
#include "resolution_systeme.hpp"
//#include "pseudoinverse.hpp"

 int main(int argc, char *argv[]){

     Matrice matr_A= Matrice::Zero();
     Matrice matr_C = Matrice::Zero();
     //Matrice mat_A= Matrice::Zero();
     //Matrice mat_C = Matrice::Zero();
     //MatriceN  matin =MatriceN::Zero(194*196,3);
     Matrice stades = Matrice::Zero();
     Matrice theta = Matrice::Zero();
     Matriceinv mat = Matriceinv::Zero();

     string filePath1  = "mat_eta.csv" ;
     string filePath2  = "mat_p.csv"   ;
     //string filePath3  = "mat_theta.csv" ;
    // string filePath4  = "mat_eta.csv" ;

     Matrice m_eta  = CSVParser(filePath1 );
     Matrice m_p    = CSVParser(filePath2 );
     theta = m_eta ;//CSVParser(filePath3 );
     stades= m_eta ;//CSVParser(filePath4 );

     Matrice tauxaccroissement = taux_accroissement(theta,stades);
     Matrice coeffdepot1       = coeff_depot1(m_p,m_eta)         ;
     Matrice coeffdepot2       = coeff_depot2(m_p,m_eta)         ;
     /*Matrice coeffdepot3       = coeff_depot3(m_p,m_eta)         ;
     Matrice coeffdepot4       = coeff_depot4(m_p,m_eta)         ;
     Matrice coeffdepot5       = coeff_depot5(m_p,m_eta)         ;
     Matrice coeffenvol        = coeff_envol(50,theta,m_eta)     ;*/
//cout<<coeffdepot2<<"\n";

    /* matin =  matricen (5 , 5,  m_p , coeffdepot1 ,  m_eta);*/

     mat = calculmatriceN2N4 ( 5,  tauxaccroissement , coeffdepot2 );
    //cout<<mat;
    // MatriceN matr_A = Resolution_apteres(5 , mat_A, mat_C , coeffdepot2, matricen);
      //  cout<<matr_A;
     matr_C =Resolution_ailees (5, m_p ,m_p , coeffdepot1,mat,1);
     cout<<matr_C;
   //  cout<<coeffdepot2;//.block<1,194>(195,0)<<endl<<"matr_C-----------------------\n";

  return EXIT_SUCCESS;
 }
// numericals recipes c
