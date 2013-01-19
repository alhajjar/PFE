#include "allincludes.hpp"

class Simulation
{
	public :
		Simulation();
		~Simulation();
		void simulation_start (int a,int z, string c,string b,string d,string t,string v,int k,int l,string m,int n,int e,string f,int g,int y,string u,int p,int o,int w,int r);
		void simulation_affiche ();
		void simulation_affiche_block(int , int , int , int); 
		Matrice  get_mat_A();
		Matrice  get_mat_C();
		void  set_mat_A(Matrice);
		void  set_mat_C(Matrice);

		
		
private :

		Matrice mat_A;
		Matrice mat_C;

};
