////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    main.cpp                                    //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include  <tiffio.h>
#include "../Includes/CSVParser.hpp"
#include "../Includes/simulation.hpp"
#include "../Includes/calcul_mat_N.hpp"
#include "../Includes/resolution_systeme.hpp"
#include "../Includes/save_matrice_CSV.hpp"
#include "../Includes/Formatgeomatique.hpp"
#include "../Includes/Voronoi.hpp"


int main(int argc, char **argv)
{
    Vecteur N22(38024);
    N22=Vecteur::Zero(38024);
    int m,n,num ;
    string numtmp,nameC,nameA,str,tmp;
    cs* N1;
/****************************************************************************************************************************/
			/********************Choisir les dimensions des CSV**********************/
/****************************************************************************************************************************/
cout << "veuillez entrer le nombre de lignes du CSV[default :197]:";
    getline(cin, numtmp);
    if (numtmp== "")
    m = 197;
  else
    m = atoi(numtmp.c_str());

cout << "veuillez entrer le nombre de colonnes du CSV[default :194]:";
    getline(cin, numtmp);
    if (numtmp== "")
    n = 194;
  else
    n = atoi(numtmp.c_str());
/***************************************************************************************************/
        	Matrice theta(m-1,n);
        	Matrice stades(m-1,n); 
        	Matrice mat_A(m-1,n);
    		Matrice MatriceResultat(10,10); 
		Matrice MatriceResultat1(10,10); 
		Matrice mat_C(m-1,n);
		Matrice m_eta(m-1,n);
		Matrice m_p (m-1,n); 
		Matrice coeffenvol(m-1,n);
		Matrice coeffdepot1(m-1,n); 
		Matrice coeffdepot2(m-1,n); 
		Matrice tauxaccroissement(m-1,n);
		Matrice mat(n,m-1);
		Matrice tt(n,m-1);
		/********************initialisation**********************/
        	m_p = m_eta = stades = mat_C = mat_A = theta = Matrice::Zero(m-1,n);
		coeffdepot2 = coeffdepot1 = coeffenvol = tauxaccroissement = Matrice::Zero(m-1,n);
/****************************************************************************************************************************/
			/********************voronoy**********************/
/****************************************************************************************************************************/
	Voronoi voronoi("coord.csv",23,3,"data.csv",367,23);
	Voronoi voronoitemp("coord.csv",23,3,"data.csv",367,23);
	for (int i=1; i<91; i++){
	stades = voronoi.iteration(i);
	theta = voronoitemp.iteration(i);
	}

/****************************************************************************************************************************/
			/********************input**********************/
/****************************************************************************************************************************/
cout << "veuillez entrer le nombre d'iteration [default : 1 ]:";
    getline(cin, numtmp);
    if (numtmp== "")
    num = 1;
  else
    num = atoi(numtmp.c_str());

/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice eta [default : mat_eta.csv ]:";
    const string defaultText = "mat_eta.csv";
    getline(cin, tmp);
    if (!tmp.empty()) 
        str = tmp;
    else 
        str = defaultText;
          m_eta  = CSVParser(m,n,str );
          m_p    = CSVParser(m,n,str );

/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice P [default :mat_p.csv]:";
    const string defaultText1 = "mat_p.csv";
    getline(cin, tmp);
    if (!tmp.empty()) 
        str = tmp;
    else 
        str = defaultText1;
        m_p    = CSVParser(m,n,str );

cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice A  [default :mat_A.csv]:";
 const string defaultText4 = "mat_A.csv";
    getline(cin, tmp);
    if (!tmp.empty()) 
        str = tmp;
    else 
        str = defaultText4;
	mat_A = CSVParser(m,n,str );
 
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice C  [default :mat_C.csv]:";
 const string defaultText5 = "mat_C.csv";
    getline(cin, tmp);
    if (!tmp.empty()) 
        str = tmp;
    else 
        str = defaultText5;
        mat_C = CSVParser(m,n,str );

/******************************************/
cout << "veuillez entrer la valeur de k [default : 5]:";
    int num2 ;
    getline(cin, numtmp);
    if (numtmp== "") 
        num2 = 5;
    else 
        num2 = atoi(numtmp.c_str());
/******************************************/
cout << "veuillez entrer la valeur de h [default : 1]:";
    int num3 ;
    getline(cin, numtmp);
    if (numtmp== "") 
     num3 = 1;
    else 
     num3 = atoi(numtmp.c_str());
/****************************************************************************************************************************/
			/********************Simulation**********************/
/****************************************************************************************************************************/
         tauxaccroissement   = taux_accroissement(theta,stades);
         coeffdepot1         = coeff_depot1(m_p,m_eta)         ;
         coeffdepot2         = coeff_depot2(m_p,m_eta)         ;
        //Matrice coeffdepot3       = coeff_depot3(m_p,m_eta)         ;
        //Matrice coeffdepot4       = coeff_depot4(m_p,m_eta)         ;
        //Matrice coeffdepot5       = coeff_depot5(m_p,m_eta)         ;

        //Ascii_lecture = Lecture_ASCII("MNT500_L93_FRANCE.ASC");
     	//cout<<Ascii_lecture.block<1,2321>(1891,0);
     	//Ecriture_ASCII(2161 ,1891 ,89750 ,6039750 ,500 ,-9999 ,Ascii_lecture ,"test.ASC");

        N1=matriceN1N3 (num2 , num3 ,  m_p, coeffdepot1 , m_eta);

       for(int i = 0; i!= num;i++){

  	coeffenvol = coeff_envol(mat_A,theta,m_eta)     ;
        N22 = calculmatriceN22N44 ( num2,  tauxaccroissement , coeffenvol );
        mat_C = Resolution_apteres(num2 , mat_A, mat_C , coeffdepot2, N1);
        mat_A =Resolution_ailees (num2, mat_A, mat_C, coeffenvol,N22);
        mat_C = Resolution_apteres(num2 , mat_A, mat_C , coeffdepot2, N1);
        mat_A =Resolution_ailees (num2, mat_A, mat_C, coeffenvol,N22);

	 cout<<"premiere ligne de la matrice c "<<"\n------------------\n"<< mat_C.block<1, 194>(0,0)<<"\n------------------\n"<<
	 "premiere ligne de la matrice A "<<"\n------------------\n"<< mat_A.block<1, 194>(0,0)<<"\n------------------\n";
/****************************************************************************************************************************/
			/********************Sauvegarde**********************/
/****************************************************************************************************************************/
const string defaultTextee = "oui";
cout << "Voulez vous enregistrez le resultat de mat_A [default :oui]:";
    getline(cin, tmp);
    if (!tmp.empty()) 
        str = tmp;
    else 
        str = defaultTextee;

if (str == "oui"){
cout << "choisissez le nom de fichier destination [mat_A_save.csv]:";
string defaultnameA = "mat_A_save.csv";
    getline(cin, tmp);
    if (!tmp.empty()){ 
        nameA = tmp;
	}
    else {nameA = defaultnameA;
	}
 save_matrice_CSV( m , n, mat_A,nameA);
}

cout << "Voulez vous enregistrez le resultat de mat_C[default :oui]:";
    getline(cin, tmp);
    if (!tmp.empty()) 
        str = tmp;
    else 
        str = defaultTextee;

if (str == "oui"){
cout << "choisissez le nom de fichier destination [mat_C_save.csv]:";
string defaultnameC = "mat_C_save.csv";
    getline(cin, tmp);
    if (!tmp.empty()){ 
        nameC = tmp;
	}
    else{nameC = defaultnameC;
	}
 save_matrice_CSV( m , n, mat_C,nameC);
} 
 
  /*  Formatgeomatique geo;
    MatriceResultat=geo.Lecture("erd.tif");
    
    geo.Ecriture(MatriceResultat ,"test.tif"); 
MatriceResultat1=geo.Lecture("MNT500_L93_FRANCE.ASC");
    
    geo.Ecriture(MatriceResultat1 ,"test.ASC");   */ 
   }

 return 0;
 }


