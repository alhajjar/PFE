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
	__declspec(dllexport) Calcul_Matrice();
	__declspec(dllexport) ~Calcul_Matrice();
	
	__declspec(dllexport) void matriceN1 (double h , double k ,  Matrice p , Matrice alpha1 , Matrice v);
	__declspec(dllexport) void matriceN3 (double h , double k ,  Matrice p , Matrice alpha1 , Matrice vitesse_v);
	__declspec(dllexport) void inverseN2N4 (double h , Matrice r , Matrice alpha2 );
	__declspec(dllexport) void Resolution_ailes_demi_pas(double h , Matrice mat_A , Matrice mat_C , Matrice alpha2, cs* N1);
	__declspec(dllexport) void Resolution_apteres_demi_pas (double h , Matrice mat_A , Matrice mat_C , Matrice alpha1, Vecteur N22);
	__declspec(dllexport) void Resolution_ailes_pas_entier(double h , Matrice mat_A , Matrice mat_C , Matrice alpha2, cs* N1);
	__declspec(dllexport) void Resolution_apteres_pas_entier (double h , Matrice mat_A , Matrice mat_C , Matrice alpha1, Vecteur N22);
	
	__declspec(dllexport) void set_N1(cs* mat);
	__declspec(dllexport) void set_N3(cs* mat);
	__declspec(dllexport) void set_inverse_N2(Vecteur vec);
	__declspec(dllexport) void set_mat_A(Matrice mat);
	__declspec(dllexport) void set_mat_C(Matrice mat);
	__declspec(dllexport) void set_mat_A_demi(Matrice mat);
	__declspec(dllexport) void set_mat_C_demi(Matrice mat);
	__declspec(dllexport) void set_h(int val);
	__declspec(dllexport) void set_k(int val);
	
	__declspec(dllexport) cs*  get_N1();
	__declspec(dllexport) cs*  get_N3();
	__declspec(dllexport) Vecteur get_inverse_N2();
	__declspec(dllexport) Matrice get_mat_A();
	__declspec(dllexport) Matrice get_mat_C();
	__declspec(dllexport) Matrice get_mat_A_demi();
	__declspec(dllexport) Matrice get_mat_C_demi();
	__declspec(dllexport) int get_h();
	__declspec(dllexport) int get_k();

private :
	cs* N1;
	cs* N3;
	Vecteur N22;
	Matrice mat_A;
	Matrice mat_C;
	Matrice mat_A_demi;
	Matrice mat_C_demi;
	double h;
	double k;
};

#endif
		
		
		
