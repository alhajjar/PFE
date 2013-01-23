////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    main.cpp                                    //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include "../Includes/Lecture_Ecriture.hpp"
#include "../Includes/Calcul_Lois.hpp"
#include "../Includes/Calcul_Matrice.hpp"
#include "../Includes/Voronoi.hpp"
#include "../Includes/Simulation.hpp"

int main(int argc, char **argv)
{
Lecture_Ecriture lect;
Matrice mat(196,194);
for(int i =0;i<196;i++)
for(int j = 0;j<194;j++){
mat(i,j)=0.5;
}
lect.EcritureCSV(mat,"m_C.csv");


 return 0;
 }

