////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    main.cpp                                    //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "CSVParser.hpp"


 int main(int argc, char *argv[]){

     string filePath  = "mat_eta.csv" ;
     string filePath2 = "mat_p.csv"   ;


     Matrice mat   ;
     Matrice m_eta ;
     Matrice m_p   ;

     m_eta = CSVParser(filePath,mat );
     m_p   = CSVParser(filePath2,mat);

      //cout<<m_eta;
      //cout<<m_p;
     cout<<m_eta.block<1,194>(1,0)<<"\n";
     cout<<"---------------------------"<<"\n";
     cout<<m_p.block<1,194>(1,0)<<"\n";
     cout<<"---------------------------"<<"\n";


  //system("PAUSE");
  return EXIT_SUCCESS;
 }
