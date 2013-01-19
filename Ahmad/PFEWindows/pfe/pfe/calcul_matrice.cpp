/** 
 *\file calcul_matrice.cpp
 *\brief ce fichier permet de calculer la matrice tridiagonale et les matrices finales de pucerons apteres et pucerons ailes
 */

#include "Includes/calcul_matrice.hpp"


calcul_matrice::calcul_matrice(){
	 N22=new Vecteur(38024);
	 *N22=Vecteur::Zero(38024);
	 mat_A=new Matrice(196,194);
	 *mat_A=Matrice::Zero(196,194);
	 mat_C=new Matrice(196,194);
	 *mat_C=Matrice::Zero(196,194);
	 h=5;
	 k=1;
	 N1=cs_spalloc (0, 0, 1, 1, 1) ;
}

/** 
 *\brief     calcul des matrices N1, N3, N22 et N44
 *\details   cette fonction nous cree la matrice creuse tridiagonale N1
 *\return retourne les matrices N1, N22, N3 et N44 
 */
void calcul_matrice:: matriceN1N3 (int h , int k ,  Matrice p , Matrice alpha1 , Matrice v){
/** \on declare deux matrices creuse A et T
*/
    cs *A;
    cs *T;
    int n = p.rows()*p.cols();
    int i = 0;
    double vec1[38024]={0};
    double vec3[38024]={0};
    double vec2[38024]={0};

/** \Allocation en memoire de la matrice tridiagonale temporaire 
*/
     T = cs_spalloc (0, 0, 1, 1, 1) ;
     int f = 0;

/** \on cree la matrice tridiagonale
*/
	 for(int i=0;i!=p.rows();i++){
		 for(int j=0;j!=p.cols();j++){

			vec1[f]  = (1+h*alpha1(i,j)+(2*h*p(i,j))/(k*k)) ;//diag
		    vec2[f]  = -(h/(k*k))*p(i,j)+(h/(2*k)) *  v(i,j);//diag inf
		    vec3[f]  =  -(h/(k*k))*p(i,j)+(h/(2*k))*  v(i,j);//diag sup

		    	f++;
		    }
	   }

	for( i = 0; i!=n-1;i++){
/** \ on stocke dans T les valeurs de vec2 et vec3
*/		 cs_entry (T, i, i,vec1[i]);
		 cs_entry (T, i+1, i,vec2[i]);//diaginf
		 cs_entry (T,  i, i+1,vec3[i]);//diagsup
	}

/* Compression en memoire et remplissage de la matrice creuse */
	A = cs_compress(T);
	set_N1(A);

/* Liberation de l'espace memoire T */
	cs_spfree(T);
}



/** 
 *\brief     fonction cree la matrice N2 et l'inverse
 *\param  h  constante h
 *\param   r  Matrice r
 *\param  alpha2  Matrice alpha2
 *\return    N22  la matrice inverse de N2
 */
void  calcul_matrice::calculmatriceN22N44 (int h , Matrice r , Matrice alpha2 ){

Vecteur N2(38024);
N2 = Vecteur::Zero(38024);
   int f = 0;

   for(int i=0;i!=r.rows();i++){
        for(int j=0;j!=r.cols();j++){
            N2(f) = 1/(1 + h * (r(i,j))*(1-alpha2(i,j)));
            f++;
        }
    }
   set_N22(N2);
}
/** \fn Resolution_apteres(int h , Matrice A , Matrice C , Matrice alpha2, cs* N)
* \brief Calcul les matrices nombre d'aptéres 
* \param h  Le pas de temps
* \param A  Matrice nombre d'ailés
* \param C  Matrice nombre d'aptères
* \param alpha2 Coefficient de dépôt
* \param N Matrice tridiagonale N1
* \return Rien
*/
void calcul_matrice:: Resolution_apteres(int h , Matrice A , Matrice C , Matrice alpha2, cs* N){

 int n = 38024;
/** \deux vecteurs identite 
*/
 double I[38024] = {0};
 double I1[38024] = {0};
 I1[0] = 1;
 Vecteur vec1(38024);
 vec1 = Vecteur::Zero(38024);
 int f = 0;
 csn *R;
 double *x;
 x = (double*)cs_malloc (N->n , sizeof (double)) ;

 for(int i = 0;i != C.rows();i++){
     for(int j = 0;j != C.cols();j++){
         vec1(f) = C(i,j) + h* alpha2(i,j)* A(i,j);
         f++;
       }
  }
/** \ces deux fonctions cs_lusol_boucle nous retournent la matrice inverse N11 colonne par colonne dans le vecteur
* \identite I1 pour cela on est obliger apres stockage du vecteur qu'on a eu dans le vecteur I 
* \a remetre le vecteur I1 a zero et incremente le place du 1 
*/
  R = cs_lusol_init (0, N, I1, 1e-14,x);
  for(int i = 1;i < 38024;i++){
        double val = vec1(i);
        for(int k = 0;k < n;k++){
            I[k] += I1[k]*val;
            I1[k] = 0;
        }
        I1[i] = 1;
    cs_lusol_boucle (N, I1, R, x);
  }
  cs_nfree (R) ;
  cs_free(x);

 f = 0;
 for(int i = 0;i != C.rows();i++){
     for(int j = 0;j != C.cols();j++){
    	 if(I[f]>0)
    		 //j'arrondi si apres la virgule >5 il sera = a lui meme +1 sinon en enleve les nombre apres la virgule
         C(i,j) = (int)(I[f]+0.5);
    	 	 else
    	 		 C(i,j) =0;
         f++;
       }
  }
set_mat_C(C);
}
/** \fn  Resolution_ailees (int h , Matrice A , Matrice C , Matrice alpha,Vecteur N22  )
* \brief Calcul les matrices nombre d'aptéres 
* \param h  Le pas de temps
* \param A  Matrice nombre d'ailés
* \param C  Matrice nombre d'aptères
* \param coeff_envol Coefficient d'envol
* \param N22 Inverse du vecteur N2
* \return Rien
*/
void calcul_matrice:: Resolution_ailees (int h , Matrice A , Matrice C , Matrice alpha,Vecteur N22  ){

  int f = 0;
  Vecteur vec(38024);
  vec = Vecteur::Zero(38024);
  for (int i = 0;i != A.rows();i++){
       for (int j = 0;j != A.cols();j++){
       vec(f)=N22(f) * (h* alpha(i,j)* C(i,j) + A(i,j));
       if(vec(f)>0)
        A(i,j) = (int)(vec(f)+0.5);
    	   else
    		   (A(i,j)=0);
        f++;
        }
   }
  set_mat_A(A);
}
 /** 
 *  \brief setter matrice N1
 */
void  calcul_matrice::set_N1(cs* N){
N1 = N;
}
 /** 
 *  \brief setter vecteur matrice inverse de N2
 */
void  calcul_matrice::set_N22(Vecteur N){
*N22 = N;
}
 /** 
 *  \brief setter matrice des pucerons ailes
 */
void  calcul_matrice::set_mat_A(Matrice A){
*mat_A = A;
}
 /** 
 *  \brief setter matrice des pucerons apteres
 */
void  calcul_matrice::set_mat_C(Matrice C){
*mat_C = C;
}
 /** 
 *  \brief setter constante h
 */
void  calcul_matrice::set_h(int h){
this->h = h;
}
 /** 
 *  \brief setter constante k
 */
void  calcul_matrice::set_k(int k){
this->k = k;
}
/** 
 *  \brief getter matrice N1
 */
cs* calcul_matrice::get_N1(){
return N1;
 }
 /** 
 *  \brief getter vecteur matrice inverse de N2
 */
Vecteur calcul_matrice::get_N22(){
return *N22;
 }
 /** 
 *  \brief getter matrice des pucerons ailes
 */
Matrice  calcul_matrice::get_mat_A(){
return *mat_A;
 }
  /** 
 *  \brief getter matrice des pucerons apteres
 */
Matrice  calcul_matrice::get_mat_C(){
return *mat_C;
 }
   /** 
 *  \brief getter constante h
 */
int  calcul_matrice::get_h(){
return h;
 }
   /** 
 *  \brief getter constante k
 */
int  calcul_matrice::get_k(){
return k;
 }
calcul_matrice::~calcul_matrice(){
	cs_spfree(N1);
	delete(mat_A);
	delete(mat_C);


}



