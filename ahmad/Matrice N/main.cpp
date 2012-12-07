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

 int main(int argc, char *argv[]){

     Matrice m_eta ;
     Matrice mat ;
     Matrice m_p   ;
     Matrice theta;
     Matrice stades;
     MatriceN matricen;

     string filePath1  = "mat_eta.csv" ;
     string filePath2  = "mat_p.csv"   ;
     string filePath3  = "mat_theta.csv" ;
     string filePath4  = "mat_eta.csv" ;

     m_eta  = CSVParser(filePath1 );
     m_p    = CSVParser(filePath2 );
     theta  = m_eta ;//CSVParser(filePath3 );
     stades = m_eta ;//CSVParser(filePath4 );

     Matrice tauxaccroissement = taux_accroissement(theta,stades);
     Matrice coeffdepot1       = coeff_depot1(m_p,m_eta)         ;
     Matrice coeffdepot2       = coeff_depot2(m_p,m_eta)         ;
     Matrice coeffdepot3       = coeff_depot3(m_p,m_eta)         ;
     Matrice coeffdepot4       = coeff_depot4(m_p,m_eta)         ;
     Matrice coeffdepot5       = coeff_depot5(m_p,m_eta)         ;
     Matrice coeffenvol        = coeff_envol(50,theta,m_eta)     ;
     matricen = calculmatriceN1N3(100  , 58,  m_p , coeffdepot1 ,  m_eta);
     cout<< matricen;
     mat = calculmatriceN2N4 ( 100,  tauxaccroissement ,  coeffdepot2 );
     //cout << mat;
     //cout<< matricen.diagonal();
    /* cout<<"tauxaccroissement(1,1)  = "<<tauxaccroissement(1,1)
         <<"\n"<<"coeff_depot1(1,1) = "<<coeffdepot1(1,1)
         <<"\n"<<"coeff_depot2(1,1) = "<<coeffdepot2(1,1)
         <<"\n"<<"coeff_depot3(1,1) = "<<coeffdepot3(1,1)
         <<"\n"<<"coeff_depot4(1,1) = "<<coeffdepot4(1,1)
         <<"\n"<<"coeff_depot5(1,1) = "<<coeffdepot5(1,1)
         <<"\n"<<"coeff_envol(1,1)  = "<<coeffenvol (1,1);*/

  //system("PAUSE");
  return EXIT_SUCCESS;
 }
