/** 
 *  \file Calcul_Matrice.cpp
 *  \brief Ce fichier permet de calculer la matrice tridiagonale et les matrices finales des aptères et des ailés
 */

#include "Includes/Calcul_Matrice.hpp"

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

/** \fn void Calcul_Matrice::matriceN1(double h , double k ,  Matrice D , Matrice alpha , Matrice vitesse_h)
 *  \brief Calcul de la matrice tridiagonale N1
 *  \param h Pas de temps
 *  \param k Pas d'espace
 *  \param D Donnees liées à la diffusion
 *  \param alpha Coefficient de dépôt pour la loi sélectionnée
 *  \param vitesse_h Données de vent disponibles sur l'axe horizontal
 *  \return Rien
 */
void Calcul_Matrice::matriceN1(double h , double k ,  Matrice D , Matrice alpha , Matrice vitesse_h){
/* Déclaration de deux matrices creuse A et T */
    cs *A;
    cs *T;
    int i = 0;
    int f = 0;
    double vec1[38024] = {0};
    double vec3[38024] = {0};
    double vec2[38024] = {0};

/* Allocation en mémoire de la matrice tridiagonale temporaire */
	T = cs_spalloc (0, 0, 1, 1, 1) ;
	//A = cs_spalloc (0, 0, 1, 1, 1) ;
/* Création de la matrice tridiagonale */
	for(int i=0; i<D.rows(); i++){
		for(int j=0; j<D.cols(); j++){
/* Remplissage de la diagonale centrale */
		    vec1[f]  = (1+h*alpha(i, j)+(2*h*D(i, j))/(k*k));
/* Remplissage de la diagonale inférieure */
		    vec2[f]  = -(h/(k*k))*D(i, j)-(h/(2*k)) * vitesse_h(i, j);
/* Remplissage de la diagonale supérieure */ 
		    vec3[f]  =  -(h/(k*k))*D(i, j)+(h/(2*k)) * vitesse_h(i, j);
		    f++;
		}
	}

	for( i = 0; i<38024; i++){
/* Stockage dans la matrice tridiagonale temporaire de la diagonale centrale */
		cs_entry (T, i, i, vec1[i]);
	}
	for( i = 0; i<38023; i++){
/* Stockage dans la matrice tridiagonale temporaire de la diagonale inférieure */
		cs_entry (T, i+1, i, vec2[i]);
/* Stockage dans la matrice tridiagonale temporaire de la diagonale supérieure */
		cs_entry (T,  i, i+1, vec3[i]);
	}

/* Compression en mémoire et remplissage de la matrice creuse tridiagonale */
	A = cs_compress(T);
	set_N1(A);

/* Suppression en mémoire de la matrice tridiagonale temporaire */
	cs_spfree(T);
}

/** \fn void Calcul_Matrice::matriceN3(double h, double k, Matrice D, Matrice alpha, Matrice vitesse_v)
 *  \brief Calcul de la matrice tridiagonale N3
 *  \param h Pas de temps
 *  \param k Pas d'espace
 *  \param D Données liées à la diffusion
 *  \param alpha Coefficient de dépôt pour la loi sélectionnée
 *  \param vitesse_h Données de vent disponibles sur l'axe vertical
 *  \return Rien
 */
void Calcul_Matrice::matriceN3(double h, double k, Matrice D, Matrice alpha, Matrice vitesse_v){
/* Déclaration de deux matrices creuse A et T */
    cs *A;
    cs *T;
    int i = 0;
    int f = 0;
    double vec1[38024] = {0};
    double vec3[38024] = {0};
    double vec2[38024] = {0};

/* Allocation en mémoire de la matrice tridiagonale temporaire */
	T = cs_spalloc (0, 0, 1, 1, 1) ;

/* Création de la matrice tridiagonale */
	for(int i=0; i<D.rows(); i++){
		for(int j=0; j<D.cols(); j++){
/* Remplissage de la diagonale centrale */
		    vec1[f]  = (1 + h*alpha(i, j) + (2*h*D(i, j))/(k*k));
/* Remplissage de la diagonale inférieure */
		    vec2[f]  = -(h/(k*k))*D(i, j) - (h/(2*k)) * vitesse_v(i, j);
/* Remplissage de la diagonale supérieure */
		    vec3[f]  =  -(h/(k*k))*D(i, j) + (h/(2*k)) * vitesse_v(i, j);
		    f++;
		}
	}

	for( i = 0; i<38024; i++){
/* Stockage dans la matrice tridiagonale temporaire de la diagonale centrale */
		cs_entry (T, i, i, vec1[i]);
	}
	for( i = 0; i<38023; i++){
/* Stockage dans la matrice tridiagonale temporaire de la diagonale inférieure */
		cs_entry (T, i+1, i, vec2[i]);
/* Stockage dans la matrice tridiagonale temporaire de la diagonale supérieure */
		cs_entry (T,  i, i+1, vec3[i]);
	}

/* Compression en mémoire et remplissage de la matrice creuse tridiagonale */
	A = cs_compress(T);
	set_N3(A);

/* Suppression en mémoire de la matrice tridiagonale temporaire */
	cs_spfree(T);
}


/** \fn void Calcul_Matrice::inverseN2N4 (double h, Matrice r, Matrice alpha )
 *  \brief Calcul l'inverse de la matrice N2 (N4 = N2)
 *  \param h Pas de temps
 *  \param r Taux d'accroissement
 *  \param alpha2 Coefficient d'envol
 *  \return Rien
 */
void  Calcul_Matrice::inverseN2N4 (double h, Matrice r, Matrice alpha2 ){
	Vecteur N2(38024);
	N2 = Vecteur::Zero(38024);
	int f = 0;

	for(int i=0; i<r.rows(); i++){
		for(int j=0; j<r.cols(); j++){
			N2(f) = 1/(1 + h * r(i, j) * (1 - alpha2(i, j)));
            f++;
        }
    }
	set_inverse_N2(N2);
}

/** \fn void Calcul_Matrice::Resolution_ailes_demi_pas(double h , Matrice A , Matrice C , Matrice alpha, cs* N)
 *  \brief Résolution du système pour calculer la matrice du nombre d'ailés pour le demi pas. \n
 *  Cette méthode utilise la décomposition LU <A HREF="www.math-info.univ-paris5.fr/~pastre/meth-num/MN/3-lu/cours-lu.pdf">Cours Décomposition LU</A>
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
	
	x = (double*)cs_malloc (N->n, sizeof (double)) ;
/* Première colonne de la matrice Identité */
	I1[0] = 1;

/* Création du vecteur C + (A*h*alpha2) */
	for(int i = 0; i < C.rows(); i++){
		for(int j = 0; j < C.cols(); j++){
			vec1(f) = C(i, j) + h * alpha2(i, j) * A(i, j);
			f++;
		}
	}
	
/* Les deux fonctions cs_lusol_init et cs_lusol_boucle retournent la ième colonne de l'inverse de N1 dans le vecteur I1 */
/* La focntion cs_lusol_init se différencie de la fonction cs_lusol_boucle du fait que cs_lusol_init calcule la décomposition LU */
/* alors que la fonction cs_lusol_boucle utilise la décomposition LU qui est retournée par la fonction cs_lusol_init. */

	R = cs_lusol_init (1, N, I1, 1e-14, x);

	for(int i = 1; i < 38025; i++){
		double val = vec1(i-1);

		cs_add_vec (I3, I3, I1, val);

		if(i !=38024){
			I[i-1] = 0;
			I[i] = 1;
			cs_lusol_inverse (N, I, I1, R, x);
		}
	}
/* Suppression en mémoire de R, variable contenant la décomposition LU, */
/* et de x, la variable temporaire servant à construire l'inverse de la ième colonne de l'inverse de N1*/
	cs_nfree (R) ;
	cs_free(x);

	f = 0;
	for(int i = 0; i < C.rows(); i++){
		for(int j = 0; j < C.cols(); j++){
			C(i,j) = I3[f];
			f++;
		}
	}
	mat_C_demi = C;
}

/** \fn void Calcul_Matrice::Resolution_ailes_pas_entier(double h , Matrice A , Matrice C , Matrice alpha, cs* N)
 *  \brief Résolution du système pour calculer la matrice du nombre d'ailés pour le pas entier. \n 
 *  Cette méthode utilise la décomposition LU <A HREF="www.math-info.univ-paris5.fr/~pastre/meth-num/MN/3-lu/cours-lu.pdf">Cours Décomposition LU</A>
 *  \param h  Le pas de temps
 *  \param A  Matrice nombre d'aptères
 *  \param C  Matrice nombre d'ailés
 *  \param alpha2 Coefficient d'envol
 *  \param N Matrice tridiagonale N3
 *  \return Rien
 */
void Calcul_Matrice::Resolution_ailes_pas_entier(double h, Matrice A, Matrice C, Matrice alpha2, cs* N){
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
	for(int i = 0; i < C.rows(); i++){
		for(int j = 0; j < C.cols(); j++){
			vec1(f) = C(i, j) + h * alpha2(i,j) * A(i,j);
			f++;
		}
	}
	
/* Les deux fonctions cs_lusol_init et cs_lusol_boucle retournent la ième colonne de l'inverse de N1 dans le vecteur I1 */
/* La focntion cs_lusol_init se différencie de la fonction cs_lusol_boucle du fait que cs_lusol_init calcule la décomposition LU */
/* alors que la fonction cs_lusol_boucle utilise la décomposition LU qui est retournée par la fonction cs_lusol_init. */

	R = cs_lusol_init (0, N, I1, 1e-14, x);
	for(int i = 1; i < 38025; i++){
		double val = vec1(i - 1);

		cs_add_vec (I3, I3, I1, val);

		if(i !=38024){
			I[i-1] = 0;
			I[i] = 1;
			cs_lusol_inverse (N, I, I1, R, x);
		}
	}
/* Suppression en mémoire de R, variable contenant la décomposition LU, */
/* et de x, la variable temporaire servant à construire l'inverse de la ième colonne de l'inverse de N1*/
	cs_nfree (R) ;
	cs_free(x);

	f = 0;
	for(int i = 0; i < C.rows(); i++){
		for(int j = 0; j < C.cols(); j++){
			C(i,j) = I3[f];
			f++;
		}
	}
	mat_C = C;
}

/** \fn void Calcul_Matrice::Resolution_apteres_demi_pas(double h, Matrice A, Matrice C, Matrice alpha, Vecteur N22)
 *  \brief Résolution du système pour calculer la matrice du nombre d'aptères pour le demi pas
 *  \param h  Le pas de temps
 *  \param A  Matrice nombre d'aptères
 *  \param C  Matrice nombre d'ailés
 *  \param alpha Coefficient de dépôt pour la loi sélectionnée
 *  \param N22 Inverse du vecteur N2
 *  \return Rien
 */
void Calcul_Matrice::Resolution_apteres_demi_pas(double h, Matrice A, Matrice C, Matrice alpha, Vecteur N22){
	int f = 0;
	Vecteur vec(38024);
	vec = Vecteur::Zero(38024);
  
	for (int i = 0; i < A.rows(); i++){
		for (int j = 0;j < A.cols();j++){
			vec(f) = N22(f) * (h* alpha(i,j)* C(i,j) + A(i,j));
			A(i,j) = vec(f);
			f++;
        }
	}
	 mat_A_demi = A;
}

/** \fn void Calcul_Matrice::Resolution_apteres_pas_entier(double h, Matrice A, Matrice C, Matrice alpha, Vecteur N22)
 *  \brief Résolution du système pour calculer la matrice du nombre d'aptères pour le pas entier
 *  \param h  Le pas de temps
 *  \param A  Matrice des aptères
 *  \param C  Matrice des ailés
 *  \param alpha Coefficient de dépôt pour la loi sélectionnée
 *  \param N22 Inverse du vecteur N4
 *  \return Rien
 */
void Calcul_Matrice::Resolution_apteres_pas_entier(double h, Matrice A, Matrice C, Matrice alpha, Vecteur N22){
	int f = 0;
	Vecteur vec(38024);
	vec = Vecteur::Zero(38024);
  
	for (int i = 0; i < A.rows(); i++){
		for (int j = 0;j < A.cols();j++){
			vec(f) = N22(f) * (h * alpha(i,j) * C(i,j) + A(i,j));
			A(i,j) = vec(f);
			f++;
        }
	}
	 mat_A = A;
}

/** \fn void Calcul_Matrice::set_N1(cs* mat)
 *  \brief Mise à jour de la matrice N1
 *  \param mat Matrice tridiagonale N1
 *  \return Rien
 */
void Calcul_Matrice::set_N1(cs* mat){
	*N1 = *mat;
}

/** \fn void Calcul_Matrice::set_N3(cs* mat)
 *  \brief Mise à jour de la matrice N3
 *  \param mat Matrice tridiagonale N3
 *  \return Rien
 */
void Calcul_Matrice::set_N3(cs* mat){
	*N3 = *mat;
}

/** \fn void Calcul_Matrice::set_N22(Vecteur vec)
 *  \brief Mise à jour du vecteur \c N22 inverse de N2
 *  \param vec Vecteur inverse de N2
 *  \return Rien
 */
void Calcul_Matrice::set_inverse_N2(Vecteur vec){
	N22 = vec;
}

/** \fn void Calcul_Matrice::set_mat_A(Matrice mat)
 *  \brief Mise à jour de la matrice des aptères pour un pas entier \c mat_A
 *  \param val Matrice des aptères
 *  \return Rien
 */
void Calcul_Matrice::set_mat_A(Matrice mat){
	mat_A = mat;
}

/** \fn void Calcul_Matrice::set_mat_A_demi(Matrice mat)
 *  \brief Mise à jour de la matrice des aptères pour un demi pas \c mat_A_demi 
 *  \param val Matrice des aptères pour le demi pas
 *  \return Rien
 */
void Calcul_Matrice::set_mat_A_demi(Matrice mat){
	mat_A_demi = mat;
}

/** \fn void Calcul_Matrice::set_mat_C_demi(Matrice mat)
 *  \brief Mise à jour de la matrice des ailés pour un demi pas \c mat_C_demi 
 *  \param val Matrice des ailés pour le demi pas
 *  \return Rien
 */
void Calcul_Matrice::set_mat_C_demi(Matrice mat){
	mat_C_demi = mat;
}

/** \fn void Calcul_Matrice::set_mat_C(Matrice mat)
 *  \brief Mise à jour de la matrice des ailés pour un pas entier \c mat_C 
 *  \param val Matrice des ailés
 *  \return Rien
 */
void Calcul_Matrice::set_mat_C(Matrice mat){
	mat_C = mat;
}

/** \fn void  Calcul_Matrice::set_h(int val)
 *  \brief Mise à jour du pas d'espace \c h 
 *  \param val Pas de temps
 *  \return Rien
 */
void Calcul_Matrice::set_h(int val){
	h = val;
}

/** \fn void  Calcul_Matrice::set_k(int val)
 *  \brief Mise à jour du pas de temps \c k 
 *  \param val Pas d'espace
 *  \return Rien
 */
void Calcul_Matrice::set_k(int val){
	k = val;
}

/** \fn cs* Calcul_Matrice::get_N1()
 *  \brief Retourne la matrice tridiagonale \c N1 
 *  \return N1 Matrice tridigaonale
 */
cs* Calcul_Matrice::get_N1(){
	return N1;
}
 
/** \fn cs* Calcul_Matrice::get_N3()
 *  \brief Retourne la matrice tridiagonale \c N3
 *  \return N3 Matrice tridigaonale
 */
cs* Calcul_Matrice::get_N3(){
	return N3;
}

/** \fn Vecteur Calcul_Matrice::get_inverse_N2()
 *  \brief Retourne la matrice inverse de N2, \c N22 
 *  \return N22 Matrice inverse de N2
 */
Vecteur Calcul_Matrice::get_inverse_N2(){
	return N22;
}
 
/** \fn Matrice Calcul_Matrice::get_mat_A()
 *  \brief Retourne la matrice des aptères de pas entier \c mat_A 
 *  \return mat_A Matrice des aptères
 */
Matrice Calcul_Matrice::get_mat_A(){
	return mat_A;
}
 
/** \fn Matrice Calcul_Matrice::get_mat_A_demi()
 *  \brief Retourne la matrice des aptères de demi pas \c mat_A_demi 
 *  \return mat_A Matrice des aptères pour le demi pas
 */
Matrice Calcul_Matrice::get_mat_A_demi(){
	return mat_A_demi;
}

/** \fn Matrice Calcul_Matrice::get_mat_C_demi()
 *  \brief Retourne la matrice des ailés de demi pas \c mat_C_demi 
 *  \return mat_C Matrice des ailés pour le demi pas
 */
Matrice Calcul_Matrice::get_mat_C_demi(){
	return mat_C_demi;
}

/** \fn Matrice Calcul_Matrice::get_mat_C()
 *  \brief Retourne la matrice des ailés de pas entier \c mat_C 
 *  \return mat_C Matrice des ailés
 */
Matrice Calcul_Matrice::get_mat_C(){
	return mat_C;
}
 
/** \fn int Calcul_Matrice::get_h()
 *  \brief Retourne le pas de temps \c h 
 *  \return h Pas de temps
 */
double Calcul_Matrice::get_h(){
	return h;
}
 
/** \fn int Calcul_Matrice::get_k()
 *  \brief Retourne le pas d'espace \c k 
 *  \return k Pas d'espace
 */
double Calcul_Matrice::get_k(){
	return k;
}




