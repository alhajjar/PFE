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
#include <stdio.h>
#include <dlfcn.h>

//cp libcsparse.so /usr/local/lib
// ldconfig /usr/local/lib

int main(int argc, char **argv)
{

        int iteration = 1;
        Matrice mat_A= Matrice::Zero();
	Matrice mat_C= Matrice::Zero();
        cs* N1;
        Matrice stades = Matrice::Zero();
        Matrice theta = Matrice::Zero();
        Vecteur N22 = Vecteur::Zero();

        string filePath1  = "mat_eta.csv" ;
        string filePath2  = "mat_p.csv"   ;
        //string filePath3  = "stade.csv" ;
        // string filePath4  = "theta.csv" ;

        Matrice m_eta  = CSVParser(filePath1 );
        Matrice m_p    = CSVParser(filePath2 );
         mat_A = m_eta ;//CSVParser(filePath3 );
         mat_C= m_eta ;//CSVParser(filePath4 );
	theta = m_eta;
        stades=m_p;
        Matrice tauxaccroissement   = taux_accroissement(theta,stades);
        Matrice coeffdepot1         = coeff_depot1(m_p,m_eta)         ;
        Matrice coeffdepot2         = coeff_depot2(m_p,m_eta)         ;
        //Matrice coeffdepot3       = coeff_depot3(m_p,m_eta)         ;
        //Matrice coeffdepot4       = coeff_depot4(m_p,m_eta)         ;
        //Matrice coeffdepot5       = coeff_depot5(m_p,m_eta)         ;
        Matrice coeffenvol          = coeff_envol(50,theta,m_eta)     ;
        N22 = calculmatriceN2N4 ( 5,  tauxaccroissement , coeffenvol );
        N1=matricen (5 , 5 ,  m_p, coeffdepot1 , m_eta);

       for(int i = 0; i!= iteration;i++){
        mat_C = Resolution_apteres(5 , mat_A, mat_C , coeffdepot2, N1);
        mat_A =Resolution_ailees (5, mat_A, mat_C, coeffenvol,N22);
        cout<<mat_C.block<1, 194>(0,0)<<"\n------------------\n";//<<mat_A.block<1, 194>(0,0)<<"\n------------------\n";
   }

 return 0;
 }


