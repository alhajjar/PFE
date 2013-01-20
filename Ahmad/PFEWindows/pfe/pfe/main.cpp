////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    main.cpp                                    //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include "Includes/lecture_ecriture.hpp"
#include "Includes/calcullois.hpp"
#include "Includes/calcul_matrice.hpp"
#include "Includes/Voronoi.hpp"

int main(int argc, char **argv)
{
    Vecteur N22(38024);
    N22=Vecteur::Zero(38024);
    int m,n,num ;
    string numtmp,nameC,nameA,str,tmp;
    cs* N1;
    calcullois calcul_lois;
    lecture_ecriture lect;

/****************************************************************************************************************************/
			/********************Choisir les dimensions des CSV**********************/
/****************************************************************************************************************************/

    m = 197;
    n = 194;

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
	Voronoi voronoi("coord_s.csv",22,3,"data_s.csv",367,23);
	Voronoi voronoitemp("coord_t.csv",67,3,"data_t.csv",4384,68);
	for (int i=1; i<91; i++){
	voronoi.iteration(i);
	stades = voronoi.getfinalMatrix();
	voronoitemp.iteration(i);
	theta =voronoitemp.getfinalMatrix();
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
          lect.LectureCSV(m,n,str );
	m_eta = lect.get_CSV();

/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice P [default :mat_p.csv]:";
    const string defaultText1 = "mat_p.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        str = tmp;
    else
        str = defaultText1;
          lect.LectureCSV(m,n,str );
	m_p = lect.get_CSV();

cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice A  [default :mat_A.csv]:";
 const string defaultText4 = "mat_A.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        str = tmp;
    else
        str = defaultText4;
          lect.LectureCSV(m,n,str );
	mat_A = lect.get_CSV();

/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice C  [default :mat_C.csv]:";
 const string defaultText5 = "mat_C.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        str = tmp;
    else
        str = defaultText5;
          lect.LectureCSV(m,n,str );
	mat_C = lect.get_CSV();

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

	 calcul_lois.calcul_taux_accroissement(theta,stades);
	 tauxaccroissement = calcul_lois.get_taux_accroissement();

         calcul_lois.calcul_coeffdepot1(m_p,m_eta)         ;
	     coeffdepot1 = calcul_lois.get_coeffdepot1();
         calcul_lois.calcul_coeffdepot2(m_p,m_eta)         ;
         coeffdepot2 = calcul_lois.get_coeffdepot2();
       /* //Matrice coeffdepot3       = coeff_depot3(m_p,m_eta)         ;
        //Matrice coeffdepot4       = coeff_depot4(m_p,m_eta)         ;
        //Matrice coeffdepot5       = coeff_depot5(m_p,m_eta)         ;*/

	calcul_matrice calculmatrice;
         calculmatrice.matriceN1N3(num2 , num3 ,  m_p, coeffdepot1 , m_eta);
	N1 = calculmatrice.get_N1();
//cout<<N1;
       for(int i = 0; i!= num;i++){

  	calcul_lois.calcul_coeff_envol(mat_A,theta,m_eta)     ;
	coeffenvol = calcul_lois.get_coeff_envol();
//cout<<coeffenvol;
 	calculmatrice.calculmatriceN22N44 ( num2,  tauxaccroissement , coeffenvol );
	N22 =calculmatrice.get_N22();
       //cout<< N22<<"\n===========\n";

	calculmatrice.Resolution_apteres(num2 , mat_A, mat_C , coeffdepot2, N1);
        mat_C =calculmatrice.get_mat_C();
	//cout<<mat_C;
	calculmatrice.Resolution_ailees (num2, mat_A, mat_C, coeffenvol,N22);
        mat_A =calculmatrice.get_mat_A();
	//cout<<"\n=============================\n"<<mat_A<<"\n=============================\n";
	calculmatrice.Resolution_apteres(num2 , mat_A, mat_C , coeffdepot2, N1);
        mat_C =calculmatrice.get_mat_C();
	calculmatrice.Resolution_ailees (num2, mat_A, mat_C, coeffenvol,N22);
       mat_A =calculmatrice.get_mat_A();

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
lect.EcritureCSV( mat_A,nameA);
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
 lect.EcritureCSV( mat_C,nameC);
}

   lect.EcritureCSV(m_eta,"mat.csv");

    MatriceResultat=lect.LectureGeotiff("erd.tif");
    lect.EcritureGeotiff(MatriceResultat ,"test.tif");

    MatriceResultat=lect.LectureAscii("MNT500_L93_FRANCE.ASC");
    lect.EcritureAscii(MatriceResultat ,"test.ASC"); 
   }

 return 0;
 }

