#include "Includes/Simulation.hpp"
#include "Includes/lecture_ecriture.hpp"
#include "Includes/calcullois.hpp"
#include "Includes/calcul_matrice.hpp"
#include "Includes/Voronoi.hpp"

Simulation::Simulation(){
};
Simulation::~Simulation(){
};
void Simulation::simulation_start (int k,int h,string CSV_mat_C,string CSV_mat_A ,string CSV_p,string CSV_eta,string  CSV_coord_stades , int nbligneCSV_coord_s , int nbcolonneCSV_coord_s , string CSV_data_stades , int nbligneCSV_data_s, int nbcolonneCSV_data_s ,string  CSV_coord_temp, int nbligneCSV_coord_t, int nbcolonneCSV_coord_t, string  CSV_data_temp, int nbligneCSV_data_t, int nbcolonneCSV_data_t,int nbjour,int nbiteration){
int m =197,n=194;
Matrice theta(m-1,n);
Matrice stades(m-1,n);
Matrice matA(m-1,n);
Matrice matC(m-1,n);
 mat_A=Matrice(m-1,n);
 mat_C=Matrice(m-1,n);
Matrice m_eta(m-1,n);
Matrice m_p (m-1,n);
Matrice coeffenvol(m-1,n);
Matrice coeffdepot1(m-1,n);
Matrice coeffdepot2(m-1,n);
Matrice tauxaccroissement(m-1,n);
Matrice mat(n,m-1);
Matrice tt(n,m-1);
cs* N1;
Vecteur N22(38024);
/********************initialisation**********************/
m_p = m_eta = stades = matC = matA = theta = Matrice::Zero(m-1,n);
coeffdepot2 = coeffdepot1 = coeffenvol = tauxaccroissement = Matrice::Zero(m-1,n);
calcullois calcul_lois;
lecture_ecriture lect;
    calcul_matrice calculmatrice;
    
Voronoi voronoistades( CSV_coord_stades ,  nbligneCSV_coord_s ,  nbcolonneCSV_coord_s ,  CSV_data_stades ,  nbligneCSV_data_s,
 nbcolonneCSV_data_s );

Voronoi voronoitheta(  CSV_coord_temp,  nbligneCSV_coord_t,  nbcolonneCSV_coord_t,   CSV_data_temp,  nbligneCSV_data_t
,  nbcolonneCSV_data_t);

   	for (int i=0; i<nbjour; i++){
	voronoistades.iteration(i);
	stades = voronoistades.getfinalMatrix();
	voronoitheta.iteration(i);
	theta =voronoitheta.getfinalMatrix();
	}

   lect.LectureCSV(197,194,CSV_eta );
   m_eta = lect.get_CSV();

   lect.LectureCSV(197,194,CSV_p );
   m_p = lect.get_CSV();

   lect.LectureCSV(197,194,CSV_mat_A );
   //matA = lect.get_CSV();
   calculmatrice.set_mat_A(lect.get_CSV());

   lect.LectureCSV(197,194,CSV_mat_C );
  // matC = lect.get_CSV();
   calculmatrice.set_mat_C(lect.get_CSV());


 	 calcul_lois.calcul_taux_accroissement(theta,stades);
	 tauxaccroissement = calcul_lois.get_taux_accroissement();

     calcul_lois.calcul_coeffdepot1(m_p,m_eta)         ;
	 coeffdepot1 = calcul_lois.get_coeffdepot1();
	
     calcul_lois.calcul_coeffdepot2(m_p,m_eta)         ;
     coeffdepot2 = calcul_lois.get_coeffdepot2();

     calculmatrice.matriceN1N3(k,h ,  m_p, coeffdepot1 , m_eta);

	N1 = calculmatrice.get_N1();
	for(int i = 0; i!= nbiteration;i++){

	matC =calculmatrice.get_mat_C();
	matA =calculmatrice.get_mat_A();

  	calcul_lois.calcul_coeff_envol(matA,theta,m_eta)     ;
	coeffenvol = calcul_lois.get_coeff_envol();

 	calculmatrice.calculmatriceN22N44 ( k,  tauxaccroissement , coeffenvol );
	N22 =calculmatrice.get_N22();
    
	calculmatrice.Resolution_apteres(k , matA, matC , coeffdepot2, N1);
    calculmatrice.set_mat_C(calculmatrice.get_mat_C());
	matC =calculmatrice.get_mat_C();

	calculmatrice.Resolution_ailees (k, matA, matC, coeffenvol,N22);
    calculmatrice.set_mat_A(calculmatrice.get_mat_A());
	matA =calculmatrice.get_mat_A();

	calculmatrice.Resolution_apteres(k , matA, matC , coeffdepot2, N1);
    calculmatrice.set_mat_C(calculmatrice.get_mat_C());
	matC =calculmatrice.get_mat_C();

	calculmatrice.Resolution_ailees (k, matA, matC, coeffenvol,N22);
    calculmatrice.set_mat_A(calculmatrice.get_mat_A());
	matA =calculmatrice.get_mat_A();


	}
	mat_A = calculmatrice.get_mat_A();
	mat_C = calculmatrice.get_mat_C();
	 cout<<"premiere ligne de la matrice c "<<"\n------------------\n"<< mat_C.block<1, 194>(0,0)<<"\n------------------\n"<<
	    	 "premiere ligne de la matrice A "<<"\n------------------\n"<< mat_A.block<1, 194>(0,0)<<"\n------------------\n";

}

void Simulation::simulation_affiche_block (int absc_pt,int coord_pt,int nbligne,int nbcolonne){

cout<<Simulation::get_mat_A().block( absc_pt, coord_pt, nbligne, nbcolonne);
cout<<"\n=========================================================\n";
cout<<Simulation::get_mat_C().block( absc_pt, coord_pt, nbligne, nbcolonne);}

void Simulation::simulation_affiche (){

cout<< Simulation::get_mat_A();
cout<<"\n=========================================================\n";
cout<<Simulation::get_mat_C();}

Matrice  Simulation::get_mat_A(){
return mat_A;
 }
  /**
 *  \brief getter matrice des pucerons apteres
 */
Matrice  Simulation::get_mat_C(){
return mat_C;
 }
void  Simulation::set_mat_A(Matrice mat){
	mat_A = mat;
};
void  Simulation::set_mat_C(Matrice mat){
	mat_A = mat;
};

