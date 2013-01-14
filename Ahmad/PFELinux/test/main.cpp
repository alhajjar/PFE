////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    main.cpp                                    //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "../Includes/CSVParser.hpp"
#include "../Includes/simulation.hpp"
#include "../Includes/calcul_mat_N.hpp"
#include "../Includes/resolution_systeme.hpp"
#include "../Includes/save_matrice_CSV.hpp"


//cp libpfe.a /usr/local/lib
// ldconfig /usr/local/lib

int main(int argc, char **argv)
{
		Vecteur N22(38024);
		N22=Vecteur::Zero(38024);
int m,n;
string nameC,nameA;
/***************************************************************************************************/
cout << "veuillez entree le nombre de lignes du CSV[default :197]:";

    string numtmpe;
    getline(cin, numtmpe);
    if (numtmpe== "")
    m = 197;
  else
    m = atoi(numtmpe.c_str());
cout << "veuillez entree le nombre de colonnes du CSV[default :194]:";

    string numtmpe1;
    getline(cin, numtmpe1);
    if (numtmpe1== "")
    n = 194;
  else
    n = atoi(numtmpe1.c_str());
/***************************************************************************************************/
        Matrice theta(m-1,n);
        theta = Matrice::Zero(m-1,n);
        Matrice mat_A(m-1,n);
		mat_A = Matrice::Zero(m-1,n);
		Matrice mat_C(m-1,n);
		mat_C = Matrice::Zero(m-1,n);
        cs* N1;
        Matrice stades(m-1,n); 
		stades = Matrice::Zero(m-1,n);
		Matrice m_eta(m-1,n);  
		m_eta = Matrice::Zero(m-1,n);
			Matrice m_p (m-1,n);
		m_p = Matrice::Zero(m-1,n);
		Matrice coeffenvol(m-1,n);
		coeffenvol = Matrice::Zero(m-1,n);
		Matrice tauxaccroissement(m-1,n);
		tauxaccroissement = Matrice::Zero(m-1,n);
		Matrice coeffdepot1(m-1,n); 
		coeffdepot1 = Matrice::Zero(m-1,n);
		Matrice coeffdepot2(m-1,n); 
		coeffdepot2 = Matrice::Zero(m-1,n);
/***************************************************************************************************/
cout << "veuillez entree le nombre d'iteration [default : 1 ]:";
    int num ;
    string numtmp;
    getline(cin, numtmp);
    if (numtmp== "")
    num = 1;
  else
    num = atoi(numtmp.c_str());
/******************************************/
cout << "veuillez entree le nom du fichier CSV contenant les valeurs de la matrice eta [default : mat_eta.csv ]:";
 const string defaultText = "mat_eta.csv";
    string str ;
    string tmp;
    getline(cin, tmp);
    if (!tmp.empty()) //user typed something different than Enter
        str = tmp;
    else //otherwise use default value
        str = defaultText;
/******************************************/
cout << "veuillez entree le nom du fichier CSV contenant les valeurs de la matrice P [default :mat_p.csv]:";
 const string defaultText1 = "mat_p.csv";
    string str1 ;
    string tmp1;
    getline(cin, tmp1);
    if (!tmp1.empty()) //user typed something different than Enter
        str1 = tmp1;
    else //otherwise use default value
        str1 = defaultText1;
/******************************************/
cout << "veuillez entree le nom du fichier CSV contenant les valeurs de la matrice stade  [default :stade.csv]:";
 const string defaultText2 = "stade.csv";
    string str2 ;
    string tmp2;
    getline(cin, tmp2);
    if (!tmp2.empty()) //user typed something different than Enter
        str2 = tmp2;
    else //otherwise use default value
        str2 = defaultText2;
/******************************************/
cout << "veuillez entree le nom du fichier CSV contenant les valeurs de la matrice theta  [default :theta.csv]:";
 const string defaultText3 = "theta.csv";
    string str3 ;
    string tmp3;
    getline(cin, tmp3);
    if (!tmp3.empty()) //user typed something different than Enter
        str3 = tmp3;
    else //otherwise use default value
        str3 = defaultText3;
/******************************************/
cout << "veuillez entree le nom du fichier CSV contenant les valeurs de la matrice A  [default :mat_A.csv]:";
 const string defaultText4 = "mat_A.csv";
    string str4 ;
    string tmp4;
    getline(cin, tmp4);
    if (!tmp4.empty()) //user typed something different than Enter
        str4 = tmp4;
    else //otherwise use default value
        str4 = defaultText4;
/******************************************/
cout << "veuillez entree le nom du fichier CSV contenant les valeurs de la matrice C  [default :mat_C.csv]:";
 const string defaultText5 = "mat_C.csv";
    string str5 ;
    string tmp5;
    getline(cin, tmp5);
    if (!tmp5.empty()) //user typed something different than Enter
        str5 = tmp5;
    else //otherwise use default value
        str5 = defaultText5;
/******************************************/
cout << "veuillez entree la valeur de k [default : 5]:";
    int num2 ;
    string numtmp2;
    getline(cin, numtmp2);
    if (numtmp2== "") //user typed something different than Enter
        num2 = 5;
    else //otherwise use default value
        num2 = atoi(numtmp2.c_str());
/******************************************/
cout << "veuillez entree la valeur de h [default : 1]:";
    int num3 ;
    string numtmp3;
    getline(cin, numtmp3);
    if (numtmp3== "") //user typed something different than Enter
     num3 = 1;
    else //otherwise use default value
     num3 = atoi(numtmp3.c_str());
/***************************************************************************************************/
          m_eta  = CSVParser(m,n,str );
          m_p    = CSVParser(m,n,str1 );
         stades = CSVParser(m,n,str2);
		 theta = CSVParser(m,n,str3);
		 mat_A = CSVParser(m,n,str4 );
         mat_C = CSVParser(m,n,str5 );
//cout<<mat_C.block<1, 194>(0,0)<<"\n";
/***************************************************************************************************/
         tauxaccroissement   = taux_accroissement(theta,stades);
         coeffdepot1         = coeff_depot1(m_p,m_eta)         ;
         coeffdepot2         = coeff_depot2(m_p,m_eta)         ;
        //Matrice coeffdepot3       = coeff_depot3(m_p,m_eta)         ;
        //Matrice coeffdepot4       = coeff_depot4(m_p,m_eta)         ;
        //Matrice coeffdepot5       = coeff_depot5(m_p,m_eta)         ;
	
	
       
        N1=matricen (num2 , num3 ,  m_p, coeffdepot1 , m_eta);
const string defaultTextee = "oui";
const string defaultTexteee = "oui";
    string strt ;
    string tmpt;
    string strin ;
    string tmptt;
       for(int i = 0; i!= num;i++){
  		coeffenvol = coeff_envol(mat_A,theta,m_eta)     ;
        N22 = calculmatriceN2N4 ( num2,  tauxaccroissement , coeffenvol );
        mat_C = Resolution_apteres(num2 , mat_A, mat_C , coeffdepot2, N1);
        mat_A =Resolution_ailees (num2, mat_A, mat_C, coeffenvol,N22);
        mat_C = Resolution_apteres(num2 , mat_A, mat_C , coeffdepot2, N1);
        mat_A =Resolution_ailees (num2, mat_A, mat_C, coeffenvol,N22);
	//cout<< mat_C;
	 cout<<"premiere ligne de la matrice c "<<"\n------------------\n"<< mat_C.block<1, 194>(0,0)<<"\n------------------\n"<<
	 "premiere ligne de la matrice A "<<"\n------------------\n"<< mat_A.block<1, 194>(0,0)<<"\n------------------\n";

	cout << "Voulez vous enregistrez le resultat de mat_A [default :oui]:";
 
    getline(cin, tmpt);
    if (!tmpt.empty()) //user typed something different than Enter
        strt = tmpt;
    else //otherwise use default value
        strt = defaultTexteee;

if (strt == "oui"){
cout << "choisissez le nom de fichier destination [mat_v.csv]:";
string defaultnameA = "mat_v.csv";
    string tmpr;
    getline(cin, tmpr);
    if (!tmpr.empty()){ //user typed something different than Enter
        nameA = tmpr;}
    else //otherwise use default value
        {nameA = defaultnameA;}
 save_matrice_CSV( m , n, mat_A,nameA);}


cout << "Voulez vous enregistrez le resultat de mat_C[default :oui]:";


    getline(cin, tmptt);
    if (!tmptt.empty()) //user typed something different than Enter
        strin = tmptt;
    else //otherwise use default value
        strin = defaultTextee;

if (strin == "oui"){
cout << "choisissez le nom de fichier destination [mat_v.csv]:";
string defaultnameC = "mat_v.csv";
    string tmpw;
    getline(cin, tmpw);
    if (!tmpw.empty()){ //user typed something different than Enter
        nameC = tmpw;}
    else //otherwise use default value
        {nameC = defaultnameC;}
 save_matrice_CSV( m , n, mat_C,nameC);}

      
   }

 return 0;
 }


