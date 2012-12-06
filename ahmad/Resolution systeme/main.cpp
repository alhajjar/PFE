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

 int main(int argc, char *argv[]){

     Matrice matr_A,matr_C,mat_A,mat_C;

     string filePath1  = "mat_eta.csv" ;
     string filePath2  = "mat_p.csv"   ;
     string filePath3  = "mat_theta.csv" ;
     string filePath4  = "mat_eta.csv" ;

    Matrice m_eta  = CSVParser(filePath1 );
    Matrice m_p    = CSVParser(filePath2 );
    Matrice theta  = m_eta ;//CSVParser(filePath3 );
    Matrice stades = m_eta ;//CSVParser(filePath4 );
    mat_A = Matrice::Zero();
    mat_C = mat_A;

     Matrice tauxaccroissement = taux_accroissement(theta,stades);
     Matrice coeffdepot1       = coeff_depot1(m_p,m_eta)         ;
     Matrice coeffdepot2       = coeff_depot2(m_p,m_eta)         ;
     Matrice coeffdepot3       = coeff_depot3(m_p,m_eta)         ;
     Matrice coeffdepot4       = coeff_depot4(m_p,m_eta)         ;
     Matrice coeffdepot5       = coeff_depot5(m_p,m_eta)         ;
     Matrice coeffenvol        = coeff_envol(50,theta,m_eta)     ;

     Vecteur vec1 = MatriceNdiag(5 , 5,  m_p , coeffdepot1 ,  m_eta);
     Vecteur vec2 = MatriceNdiaginf(5 , 5,  m_p  ,  m_eta);
     Vecteur vec3 = MatriceNdiagsup(5 , 5,  m_p  ,  m_eta);
      //cout <<vec3;
      MatriceN matin;
     // matin =  matricen (vec2, vec1, vec3);
     // Matrice_carre mat = calculmatriceN2N4 ( 20000,  tauxaccroissement , coeffdepot2 );

      //MatriceN matr_A = Resolution_apteres(5 , mat_A, mat_C , coeffdepot2, matricen);
    //cout<<matr_A;
     // matr_C =Resolution_ailees (100, m_p ,m_eta , coeffdepot1,mat,1 );
     //cout<<matr_C;

  return EXIT_SUCCESS;
 }
