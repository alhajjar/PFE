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

/**************************************************************************************************************************************************/
/* initialisation( k,  h, CSV_mat_C, CSV_mat_A, CSV_p, CSV_eta, CSV_coord_stades, nbligneCSV_coord_s, nbcolonneCSV_coord_s, CSV_data_stades,      */
/*																	          */
/* 		  nbligneCSV_data_s, nbcolonneCSV_data_s,CSV_coord_temp, nbligneCSV_coord_t, nbcolonneCSV_coord_t, CSV_data_temp,                 */
/*                                         													  */
/*		  nbligneCSV_data_t, nbcolonneCSV_data_t, CSV_mat_D, CSV_mat_vitesse_h, CSV_mat_vitesse_v );                                      */
/**************************************************************************************************************************************************/
Lecture_Ecriture lect;
//cout<<sizeof(int)<<"\n"<<sizeof(float)<<"\n"<<sizeof(double);
 simulation.initialisation(5, 1, "mat_C.csv", "mat_A.csv", "mat_p.csv", "mat_eta.csv", "coord_s.csv",22,3, "data_s.csv",367,23,
 "coord_t.csv", 67,3,"data_t.csv", 4384,68,"mat_D.csv","vitesse_h.csv","vitesse_v.csv");

for ( int i=1;i<=90;i++){
simulation.iteration(i);
simulation.affiche_bloc(0,0,1,194);
}
//lect.EcritureCSV(simulation.get_mat_A(),"mat_A_save.csv");
//lect.EcritureCSV(simulation.get_mat_C(),"mat_C_save.csv");
 return 0;
 }

