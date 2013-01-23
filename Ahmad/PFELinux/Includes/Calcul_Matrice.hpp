/** 
 *  \file Calcul_Matrice.hpp
 *  \brief Fichier d'entête de la bibliothèque des calculs de la matrice tridiagonale et les matrices finales des aptères et des ailés
*/

#ifndef __CALCUL_MATRICE__
#define __CALCUL_MATRICE__

#include "allincludes.hpp"

/** \class Calcul_Matrice
 *  \brief Classe effectuant les calculs de la matrice tridiagonale et les matrices finales des aptères et des ailés
 */
class Calcul_Matrice
{
public :
	Calcul_Matrice();
	~Calcul_Matrice();
	
	void matriceN1 (double h , double k ,  Matrice p , Matrice alpha1 , Matrice vitesse_h);
	void matriceN3 (double h , double k ,  Matrice p , Matrice alpha1 , Matrice vitesse_v);
	void inverseN2N4 (double h , Matrice r , Matrice alpha2 );
	void Resolution_ailes(double h , Matrice mat_A , Matrice mat_C , Matrice alpha2, cs* N1);
	void Resolution_apteres (double h , Matrice mat_A , Matrice mat_C , Matrice alpha1, Vecteur N22);
	
	void set_N1(cs* mat);
	void set_N3(cs* mat);
	void set_inverse_N2(Vecteur vec);
	void set_mat_A(Matrice mat);
	void set_mat_C(Matrice mat);
	void set_h(int val);
	void set_k(int val);
	
	cs*  get_N1();
	cs*  get_N3();
	Vecteur get_inverse_N2();
	Matrice get_mat_A();
	Matrice get_mat_C();
	int get_h();
	int get_k();

private :
	cs* N1;
	cs* N3;
	Vecteur N22;
	Matrice mat_A;
	Matrice mat_C;
	double h;
	double k;
};

#endif
		
		
		
