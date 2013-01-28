/** 
 *  \file Calcul_Matrice.cpp
 *  \brief Ce fichier permet de calculer la matrice tridiagonale et les matrices finales des aptères et des ailés
 */

#include "Includes/Calcul_Matrice.hpp"
#include <iomanip>
/** \fn Calcul_Matrice::Calcul_Matrice()
 *  \brief Constructeur de la classe Calcul_Matrice
 */
Calcul_Matrice::Calcul_Matrice(){
	N22 =  Vecteur(38024);
	N22 = Vecteur::Zero(38024);
	mat_A =  Matrice(196,194);
	mat_A = Matrice::Zero(196,194);
	mat_C =  Matrice(196,194);
	mat_C = Matrice::Zero(196,194);
	N1 = cs_spalloc (0, 0, 1, 1, 1) ;
	N3 = cs_spalloc (0, 0, 1, 1, 1) ;
	h = 1;
	k = 5;
	 
}

/** \fn Calcul_Matrice::Calcul_Matrice()
 *  \brief Destructeur de la classe Calcul_Matrice
 */
Calcul_Matrice::~Calcul_Matrice(){
	cs_spfree(N1);
	cs_spfree(N3);
}

/** \fn void matriceN1 (double h , double k ,  Matrice D , Matrice alpha , Matrice vitesse_h)
 *  \brief Calcul de la matrice tridiagonale N1
 *  \param h Pas de temps
 *  \param k Pas d'espace
 *  \param D Donnees liees a la diffusion
 *  \param alpha Coefficient de dépôt pour la loi sélectionnée
 *  \param vitesse_h Données de vent disponibles sur l'axe horizontal
 *  \return Rien
 */

void Calcul_Matrice:: matriceN1 (double h , double k ,  Matrice D , Matrice alpha , Matrice vitesse_h){
/* Déclaration de deux matrices creuse A et T */
    cs *A;
    cs *T;
    int i = 0;
    int f = 0;
    double vec1[38024]={0};
    double vec3[38024]={0};
    double vec2[38024]={0};

/* Allocation en mémoire de la matrice tridiagonale temporaire */
	T = cs_spalloc (0, 0, 1, 1, 1) ;
	//A = cs_spalloc (0, 0, 1, 1, 1) ;
/* Création de la matrice tridiagonale */
	for(int i=0;i<D.rows();i++){
		for(int j=0;j<D.cols();j++){
/* Remplissage de la diagonale centrale */
		    vec1[f]  = (1+h*alpha(i,j)+(2*h*D(i,j))/(k*k));
/* Remplissage de la diagonale inférieure */
		    vec2[f]  = -(h/(k*k))*D(i,j)-(h/(2*k)) *  vitesse_h(i,j);
/* Remplissage de la diagonale supérieure */
		    vec3[f]  =  -(h/(k*k))*D(i,j)+(h/(2*k))*  vitesse_h(i,j);
		    f++;
		}
	}

	for( i = 0; i<38024;i++){
/* Stockage dans la matrice tridiagonale temporaire de la diagonale centrale */
		cs_entry (T, i, i,vec1[i]);
	}
	for( i = 0; i<38023;i++){
/* Stockage dans la matrice tridiagonale temporaire de la diagonale inférieure */
		cs_entry (T, i+1, i,vec2[i]);
/* Stockage dans la matrice tridiagonale temporaire de la diagonale supérieure */
		cs_entry (T,  i, i+1,vec3[i]);
	}

/* Compression en mémoire et remplissage de la matrice creuse tridiagonale */
	A = cs_compress(T);
	set_N1(A);

/* Suppression en mémoire de la matrice tridiagonale temporaire */
	cs_spfree(T);
 	//cs_spfree(A);
}

/** \fn void matriceN3 (double h , double k ,  Matrice D , Matrice alpha , Matrice vitesse_v)
 *  \brief Calcul de la matrice tridiagonale N3
 *  \param h Pas de temps
 *  \param k Pas d'espace
 *  \param D Donnees liees a la diffusion
 *  \param alpha Coefficient de dépôt pour la loi sélectionnée
 *  \param vitesse_h Données de vent disponibles sur l'axe vertical
 *  \return Rien
 */

void Calcul_Matrice:: matriceN3 (double h , double k ,  Matrice D , Matrice alpha , Matrice vitesse_v){
/* Déclaration de deux matrices creuse A et T */
    cs *A;
    cs *T;
    int i = 0;
    int f = 0;
    double vec1[38024]={0};
    double vec3[38024]={0};
    double vec2[38024]={0};

/* Allocation en mémoire de la matrice tridiagonale temporaire */
	T = cs_spalloc (0, 0, 1, 1, 1) ;
	//A = cs_spalloc (0, 0, 1, 1, 1) ;

/* Création de la matrice tridiagonale */
	for(int i=0;i<D.rows();i++){
		for(int j=0;j<D.cols();j++){
/* Remplissage de la diagonale centrale */
		    vec1[f]  = (1+h*alpha(i,j)+(2*h*D(i,j))/(k*k));
/* Remplissage de la diagonale inférieure */
		    vec2[f]  = -(h/(k*k))*D(i,j)-(h/(2*k)) *  vitesse_v(i,j);
/* Remplissage de la diagonale supérieure */
		    vec3[f]  =  -(h/(k*k))*D(i,j)+(h/(2*k))*  vitesse_v(i,j);
		    f++;
		}
	}

	for( i = 0; i<38024;i++){
/* Stockage dans la matrice tridiagonale temporaire de la diagonale centrale */
		cs_entry (T, i, i,vec1[i]);
	}
	for( i = 0; i<38023;i++){
/* Stockage dans la matrice tridiagonale temporaire de la diagonale inférieure */
		cs_entry (T, i+1, i,vec2[i]);
/* Stockage dans la matrice tridiagonale temporaire de la diagonale supérieure */
		cs_entry (T,  i, i+1,vec3[i]);
	}

/* Compression en mémoire et remplissage de la matrice creuse tridiagonale */
	A = cs_compress(T);
	set_N3(A);

/* Suppression en mémoire de la matrice tridiagonale temporaire */
	cs_spfree(T);
	//cs_spfree(A);
 
}


/** \fn void inverseN2N4 (double h , Matrice r , Matrice alpha )
 *  \brief Calcul l'inverse de la matrice N2 (N4 = N2)
 *  \param h Pas de temps
 *  \param r Taux d'accroissement
 *  \param alpha2 Coefficient d'envol
 *  \return Rien
 */
void  Calcul_Matrice::inverseN2N4 (double h , Matrice r , Matrice alpha2 ){
	Vecteur N2(38024);
	N2 = Vecteur::Zero(38024);
	int f = 0;

	for(int i=0;i<r.rows();i++){
		for(int j=0;j<r.cols();j++){
			N2(f) = 1/(1 + h * r(i,j)*(1-alpha2(i,j)));
            f++;
        }
    }
	set_inverse_N2(N2);
  
}

/** \fn void Resolution_ailes_demi_pas(double h , Matrice A , Matrice C , Matrice alpha, cs* N)
 *  \brief Calcul des matrices du nombre d'aptères 
 *  \param h  Le pas de temps
 *  \param A  Matrice nombre d'aptères
 *  \param C  Matrice nombre d'ailés
 *  \param alpha2 Coefficient d'envol
 *  \param N Matrice tridiagonale N1
 *  \return Rien
 */
void Calcul_Matrice::Resolution_ailes_demi_pas(double h , Matrice A , Matrice C , Matrice alpha2, cs* N){

	int f = 0;
	double I[38024] = {0};
	double I1[38024] = {0};
	double I3[38024] = {0};
	Vecteur vec1(38024);
	vec1 = Vecteur::Zero(38024);
	csn *R;
	double *x;
	
	x = (double*)cs_malloc (N->n , sizeof (double)) ;
/* Première colonne de la matrice Identité */
	I1[0] = 1;

/* Création du vecteur C + (A*h*alpha2) */
	for(int i = 0;i < C.rows();i++){
		for(int j = 0;j < C.cols();j++){
			vec1(f) = C(i,j) + h* alpha2(i,j)* A(i,j);
/*if (f == 2230){


cout<<A(i,j)<<"\n"<<C(i,j)<<"\n"<<alpha2(i,j)<<"\n"<<h<<"\n"<<vec1(f);}*/
			f++;
		}
	}
	
/* Les deux fonctions cs_lusol_init et cs_lusol_boucle retournent la ième colonne de l'inverse de N1 dans le vecteur I1 */
/* La focntion cs_lusol_init se différencie de la fonction cs_lusol_boucle du fait que cs_lusol_init calcule la décomposition LU */
/* alors que la fonction cs_lusol_boucle utilise la décomposition LU qui est retournée par la fonction cs_lusol_init. */

	R = cs_lusol_init (1, N, I1, 1e-14, x);

	for(int i = 1;i < 38025;i++){
	//pour arrondir 

		double val = vec1(i-1);

	//I3 =I3+I1*val	
	cs_add_vec ( I3,I3,I1,val);


	//memset(I1, 0, sizeof I1);
	if(i !=38024){
	I[i-1] = 0;
        I[i] = 1;
		cs_lusol_inverse (N, I,I1, R, x);
	}
	}
/* Suppression en mémoire de R, variable contenant la décomposition LU, */
/* et de x, la variable temporaire servant à construire l'inverse de la ième colonne de l'inverse de N1*/
	cs_nfree (R) ;
	cs_free(x);

	f = 0;
	for(int i = 0;i < C.rows();i++){
		for(int j = 0;j < C.cols();j++){

				C(i,j) = I3[f];
//cout << I3[f]<<endl;
			f++;
		}
	}
	mat_C_demi = C;

}

/** \fn void Resolution_ailes(double h , Matrice A , Matrice C , Matrice alpha, cs* N)
 *  \brief Calcul des matrices du nombre d'aptères 

 *  \param h  Le pas de temps
 *  \param A  Matrice nombre d'aptères
 *  \param C  Matrice nombre d'ailés
 *  \param alpha2 Coefficient d'envol
 *  \param N Matrice tridiagonale N1

 *  \return Rien
 */


void Calcul_Matrice::Resolution_ailes_pas_entier(double h , Matrice A , Matrice C , Matrice alpha2, cs* N){
//cout<<"boucle"<<"\n==========================================\n";
	int f = 0;
	double I[38024] = {0};
	double I1[38024] = {0};
	double I3[38024] = {0};
	Vecteur vec1(38024);
	vec1 = Vecteur::Zero(38024);
	csn *R;
	double *x;
	
	x = (double*)cs_malloc (N->n , sizeof (double)) ;
/* Première colonne de la matrice Identité */
	I1[0] = 1;

/* Création du vecteur C + (A*h*alpha2) */
	for(int i = 0;i < C.rows();i++){
		for(int j = 0;j < C.cols();j++){
			vec1(f) = C(i,j) + h* alpha2(i,j)* A(i,j);

			f++;
		}
	}
	
/* Les deux fonctions cs_lusol_init et cs_lusol_boucle retournent la ième colonne de l'inverse de N1 dans le vecteur I1 */
/* La focntion cs_lusol_init se différencie de la fonction cs_lusol_boucle du fait que cs_lusol_init calcule la décomposition LU */
/* alors que la fonction cs_lusol_boucle utilise la décomposition LU qui est retournée par la fonction cs_lusol_init. */

	R = cs_lusol_init (0, N, I1, 1e-14, x);
	for(int i = 1;i < 38025;i++){
		double val = vec1(i-1);

//cout <<val<< endl;
	//I3 =I3+I1*val	
	cs_add_vec ( I3,I3,I1,val);

	//memset(I1, 0, sizeof I1);
	if(i !=38024){
	I[i-1] = 0;
        I[i] = 1;
		cs_lusol_inverse (N, I,I1, R, x);
	}
	}
/* Suppression en mémoire de R, variable contenant la décomposition LU, */
/* et de x, la variable temporaire servant à construire l'inverse de la ième colonne de l'inverse de N1*/
	cs_nfree (R) ;
	cs_free(x);

	f = 0;
	for(int i = 0;i < C.rows();i++){
		for(int j = 0;j < C.cols();j++){

				C(i,j) = I3[f];

			f++;
		}
	}
	mat_C = C;

}

/** \fn  Resolution_apteres (double h , Matrice A , Matrice C , Matrice alpha,Vecteur N22  )
 *  \brief Calcul des matrices du nombre d'ailés
 *  \param h  Le pas de temps
 *  \param A  Matrice nombre d'aptères
 *  \param C  Matrice nombre d'ailés
 *  \param alpha Coefficient de dépôt pour la loi sélectionnée
 *  \param N22 Inverse du vecteur N2
 *  \return Rien
 */
void Calcul_Matrice::Resolution_apteres_demi_pas(double h , Matrice A , Matrice C , Matrice alpha ,Vecteur N22){

	int f = 0;
	Vecteur vec(38024);
	vec = Vecteur::Zero(38024);
  
	for (int i = 0;i < A.rows();i++){
		for (int j = 0;j < A.cols();j++){
			vec(f) = N22(f) * (h* alpha(i,j)* C(i,j) + A(i,j));
if (f == 2230)
//cout<<A(i,j)<<"\n"<<C(i,j)<<"\n"<<alpha(i,j)<<"\n"<<h<<"\n"<<vec(f)<<"\n";
				A(i,j) = vec(f);
if(f==2230)
//cout<<A(i,j);
			f++;
        }
	}
	 mat_A_demi=A;


}

/** \fn  Resolution_apteres (double h , Matrice A , Matrice C , Matrice alpha,Vecteur N22  )

 *  \brief Calcul des matrices du nombre d'ailés

 *  \param h  Le pas de temps

 *  \param A  Matrice nombre d'aptères

 *  \param C  Matrice nombre d'ailés

 *  \param alpha Coefficient de dépôt pour la loi sélectionnée
 *  \param N22 Inverse du vecteur N2

 *  \return Rien

 */
void Calcul_Matrice::Resolution_apteres_pas_entier(double h , Matrice A , Matrice C , Matrice alpha ,Vecteur N22){

	int f = 0;
	Vecteur vec(38024);
	vec = Vecteur::Zero(38024);
  
	for (int i = 0;i < A.rows();i++){
		for (int j = 0;j < A.cols();j++){
			vec(f) = N22(f) * (h* alpha(i,j)* C(i,j) + A(i,j));

				A(i,j) = vec(f);

			f++;
        }
	}
	 mat_A = A;

}

/** \fn void  Calcul_Matrice::set_N1(cs* mat)
 *  \brief Mise à jour de la matrice N1
 *  \param mat 
 *  \return Rien
 */
void  Calcul_Matrice::set_N1(cs* mat){
	*N1 = *mat;
}

void  Calcul_Matrice::set_N3(cs* mat){
	*N3 = *mat;
}

/** \fn void  Calcul_Matrice::set_N22(Vecteur vec)
 *  \brief Mise à jour du vecteur N22 inverse de N2
 *  \param vec
 *  \return Rien
 */
void  Calcul_Matrice::set_inverse_N2(Vecteur vec){
	N22 = vec;
}

/** \fn void  Calcul_Matrice::set_mat_A(Matrice C)
 *  \brief Mise à jour de la matrice des ailés
 *  \param val Pas de temps
 *  \return Rien
 */
void  Calcul_Matrice::set_mat_A(Matrice mat){
	mat_A = mat;
}

void  Calcul_Matrice::set_mat_A_demi(Matrice mat){
	mat_A_demi = mat;
}

void  Calcul_Matrice::set_mat_C_demi(Matrice mat){
	mat_C_demi = mat;
}
/** \fn void  Calcul_Matrice::set_mat_C(Matrice C)
 *  \brief Mise à jour de la matrice des aptères
 *  \param val Pas de temps
 *  \return Rien
 */
void  Calcul_Matrice::set_mat_C(Matrice mat){
	mat_C = mat;
}

/** \fn void  Calcul_Matrice::set_k(int val)
 *  \brief Mise à jour du pas d'espace 
 *  \param val Pas d'espace
 *  \return Rien
 */
void  Calcul_Matrice::set_h(int val){
	h = val;
}

/** \fn void  Calcul_Matrice::set_h(int val)
 *  \brief Mise à jour du pas de temps
 *  \param val Pas de temps
 *  \return Rien
 */
void  Calcul_Matrice::set_k(int val){
	k = val;
}

/** \fn cs* Calcul_Matrice::get_N1()
 *  \brief Retourne la matrice tridiagonale N1
 *  \return N1 Matrice tridigaonale
 */
cs* Calcul_Matrice::get_N1(){
	return N1;
}
 
cs* Calcul_Matrice::get_N3(){
	return N3;
}

/** \fn Vecteur Calcul_Matrice::get_inverse_N2()
 *  \brief Retourne la matrice inverse de N2
 *  \return N22 Matrice inverse de N2
 */
Vecteur Calcul_Matrice::get_inverse_N2(){
	return N22;
}
 
/** \fn Matrice Calcul_Matrice::get_mat_A()
 *  \brief Retourne la matrice des ailés
 *  \return mat_A Matrice des ailés
 */
Matrice  Calcul_Matrice::get_mat_A(){
	return mat_A;
}
 
Matrice  Calcul_Matrice::get_mat_A_demi(){
	return mat_A_demi;
}

Matrice  Calcul_Matrice::get_mat_C_demi(){
	return mat_C_demi;
}

/** \fn Matrice Calcul_Matrice::get_mat_C()
 *  \brief Retourne la matrice des aptères
 *  \return mat_C Matrice des aptères
 */
Matrice  Calcul_Matrice::get_mat_C(){
	return mat_C;
}
 
/** \fn int Calcul_Matrice::get_h()
 *  \brief Retourne le pas de temps h
 *  \return h Pas de temps
 */
int  Calcul_Matrice::get_h(){
	return h;
}
 
/** \fn int Calcul_Matrice::get_k()
 *  \brief Retourne le pas d'espace k
 *  \return k Pas d'espace
 */
int  Calcul_Matrice::get_k(){
	return k;
}




