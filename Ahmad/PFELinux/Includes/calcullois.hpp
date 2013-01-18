
#ifndef __projet_pfe__calcullois__
#define __projet_pfe__calcullois__

#include "allincludes.hpp"

class calcullois
{
	public :
		calcullois();
		~calcullois();
		//
		void calcul_taux_accroissement(Matrice theta, Matrice stades);
		void calcul_coeffdepot1(Matrice p, Matrice eta);
		void calcul_coeffdepot2(Matrice p, Matrice eta);
		void calcul_coeffdepot3(Matrice p, Matrice eta);
		void calcul_coeffdepot4(Matrice p, Matrice eta);
		void calcul_coeffdepot5(Matrice p, Matrice eta);
		void calcul_coeff_envol(Matrice A,Matrice stades,Matrice theta);
		//
		void  set_taux_accroissement(Matrice taux_accroissement);
		void  set_coeffdepot1(Matrice coeff_depot1);
		void  set_coeffdepot2(Matrice coeff_depot2);
		void  set_coeffdepot3(Matrice coeff_depot3);
		void  set_coeffdepot4(Matrice coeff_depot4);
		void  set_coeffdepot5(Matrice coeff_depot5);
		void  set_coeff_envol(Matrice coeff_envol);
		//
		Matrice  get_taux_accroissement();
		Matrice  get_coeffdepot1();
		Matrice  get_coeffdepot2();
		Matrice  get_coeffdepot3();
		Matrice  get_coeffdepot4();
		Matrice  get_coeffdepot5();
		Matrice  get_coeff_envol();
	
	private :
		Matrice taux_accroissement;
		Matrice coeff_depot1;
		Matrice coeff_depot2;
		Matrice coeff_depot3;
		Matrice coeff_depot4;
		Matrice coeff_depot5;
		Matrice coeff_envol;
};

#endif /* defined(__projet_pfe__simulation__) */
		
		
		
		
		
	
