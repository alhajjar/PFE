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
   Simulation simulation;

 simulation.initialisation(1, 5, "m_C.csv", "m_A.csv", "mat_p.csv", "mat_eta.csv", "coord_s.csv",22,3, "data_s.csv",367,23,
"coord_t.csv", 67,3,"data_t.csv", 4384,68,"mat_D.csv","vitesse_h.csv","vitesse_v.csv");
for(int i=1;i<=4;i++){
simulation.iteration(i);

simulation.affiche_bloc(0,0,1,194);}

 return 0;
 }

