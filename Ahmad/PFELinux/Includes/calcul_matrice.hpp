#ifndef __projet_pfe__calcul_matrice__
#define __projet_pfe__calcul_matrice__

#include "allincludes.hpp"

class calcul_matrice
{
	public :
		calcul_matrice();
		~calcul_matrice();
		//
		void matriceN1N3 (int h , int k ,  Matrice p , Matrice alpha1 , Matrice v);
		void calculmatriceN22N44 (int h , Matrice r , Matrice alpha2 );
		void Resolution_apteres(int h , Matrice mat_A , Matrice mat_C , Matrice alpha2, cs* N1);
		void Resolution_ailees (int h , Matrice mat_A , Matrice mat_C , Matrice alpha1,Vecteur N22);
		//
		void  set_N1(cs* N1);
		void  set_N22(Vecteur N22);
		void  set_mat_A(Matrice mat_A);
		void  set_mat_C(Matrice mat_C);
		void  set_h(int h);
		void  set_k(int k);
		//
		cs*  get_N1();
		Vecteur  get_N22();
		Matrice  get_mat_A();
		Matrice  get_mat_C();
		int  get_h();
		int  get_k();
	
	private :
		cs* N1;
		Vecteur N22;
		Matrice mat_A;
		Matrice mat_C;
		int h;
		int k;
};

#endif /* defined(__projet_pfe__calcul_matrice__) */
		
		
		
