////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    main.cpp                                    //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#include "../PFELinux/Includes/Lecture_Ecriture.hpp"
#include "../PFELinux/Includes/Calcul_Lois.hpp"
#include "../PFELinux/Includes/Calcul_Matrice.hpp"
#include "../PFELinux/Includes/Voronoi.hpp"
#include "../PFELinux/Includes/Simulation.hpp"

int main(int argc, char **argv)
{
    int num;
    string numtmp,str,nameC,nameA,tmp,theta,stades,mat_A,mat_C,m_eta,m_p,data_t,data_s,coord_t,coord_s,mat_D,vitesse_h,vitesse_v;

/****************************************************************************************************************************/
			/********************Choisir les dimensions des CSV**********************/
/****************************************************************************************************************************/

Simulation simulation;
Lecture_Ecriture lect;

/****************************************************************************************************************************/
			/********************input**********************/
/****************************************************************************************************************************/
cout << "veuillez entrer le nombre de jour [default : 1 ]:";
    getline(cin, numtmp);
    if (numtmp== "")
    num = 1;
  else
    num = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice eta [default : mat_eta.csv ]:";
    const string defaultText = "mat_eta.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        m_eta  = tmp;
    else
        m_eta  = defaultText;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice P [default :mat_p.csv]:";
    const string defaultText1 = "mat_p.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        m_p = tmp;
    else
        m_p = defaultText1;
cout << "\n         =========================          \n";

cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice A  [default :mat_A.csv]:";
 const string defaultText4 = "mat_A.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        mat_A = tmp;
    else
        mat_A = defaultText4;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice C  [default :mat_C.csv]:";
 const string defaultText5 = "mat_C.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        mat_C = tmp;
    else
        mat_C = defaultText5;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice coordonnee stade  [default :coord_s.csv]:";
 const string defaultText6 = "coord_s.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        coord_s = tmp;
    else
        coord_s = defaultText6;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice data stade  [default :data_s.csv]:";
 const string defaultText7 = "data_s.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        data_s = tmp;
    else
        data_s = defaultText7;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice coordonnee temperature  [default :coord_t.csv]:";
 const string defaultText8 = "coord_t.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        coord_t = tmp;
    else
        coord_t = defaultText8;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice data temperature  [default :data_t.csv]:";
 const string defaultText9 = "data_t.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        data_t = tmp;
    else
        data_t = defaultText9;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice D  [default :mat_D.csv]:";
 const string defaultText10 = "mat_D.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        mat_D = tmp;
    else
        mat_D = defaultText10;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice vitesse horizontale  [default :vitesse_h.csv]:";
 const string defaultText11 = "vitesse_h.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        vitesse_h = tmp;
    else
        vitesse_h = defaultText11;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nom du fichier CSV contenant les valeurs de la matrice vitesse vertical  [default :vitesse_v.csv]:";
 const string defaultText12 = "vitesse_v.csv";
    getline(cin, tmp);
    if (!tmp.empty())
        vitesse_v = tmp;
    else
        vitesse_v = defaultText12;
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer la valeur de k [default : 5]:";
    int num2 ;
    getline(cin, numtmp);
    if (numtmp== "")
        num2 = 5;
    else
        num2 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer la valeur de h [default : 1]:";
    int num3 ;
    getline(cin, numtmp);
    if (numtmp== "")
     num3 = 1;
    else
     num3 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nombre de ligne de la matrice coordonnee stade [default : 22]:";
    int num4 ;
    getline(cin, numtmp);
    if (numtmp== "")
        num4 = 22;
    else
        num4 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nombre de colonne de la matrice coordonnee stade [default : 3]:";
    int num5 ;
    getline(cin, numtmp);
    if (numtmp== "")
     num5 = 3;
    else
     num5 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nombre de ligne de la matrice data stade [default : 367]:";
    int num6 ;
    getline(cin, numtmp);
    if (numtmp== "")
        num6 = 367;
    else
        num6 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nombre de colonne de la matrice data stade [default : 23]:";
    int num7 ;
    getline(cin, numtmp);
    if (numtmp== "")
     num7 = 23;
    else
     num7 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nombre de ligne de la matrice coordonnee temperature [default : 67]:";
    int num8 ;
    getline(cin, numtmp);
    if (numtmp== "")
        num8 = 67;
    else
        num8 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nombre de colonne de la matrice coordonnee temperature [default : 3]:";
    int num9 ;
    getline(cin, numtmp);
    if (numtmp== "")
     num9 = 3;
    else
     num9 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nombre de ligne de la matrice data temperature [default : 4384]:";
    int num10 ;
    getline(cin, numtmp);
    if (numtmp== "")
        num10 = 4384;
    else
        num10 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/******************************************/
cout << "veuillez entrer le nombre de colonne de la matrice data temperature [default : 68]:";
    int num11 ;
    getline(cin, numtmp);
    if (numtmp== "")
     num11 = 68;
    else
     num11 = atoi(numtmp.c_str());
cout << "\n         =========================          \n";
/****************************************************************************************************************************/
			/********************Simulation**********************/
/****************************************************************************************************************************/
simulation.initialisation(num2, num3, mat_C,mat_A, m_p, m_eta, coord_s,num4,num5, data_s,num6,num7,
 coord_t, num8,num9,data_t, num10,num11,mat_D,vitesse_h,vitesse_v);

for ( int i=1;i<=num;i++){
simulation.iteration(i);
simulation.affiche_bloc(0,0,1,194);
}
	
/****************************************************************************************************************************/
			/********************Sauvegarde**********************/
/****************************************************************************************************************************/
cout<<"\n";
const string defaultTextee = "oui";
cout << "Voulez vous enregistrez le resultat de mat_A [default :oui]:\n";
    getline(cin, tmp);
    if (!tmp.empty())
        str = tmp;
    else
        str = defaultTextee;

if (str == "oui"){
cout << "\n";
cout << "choisissez le nom de fichier destination [mat_A_save.csv]:\n";
string defaultnameA = "mat_A_save.csv";
    getline(cin, tmp);
    if (!tmp.empty()){
        nameA = tmp;
	}
    else {nameA = defaultnameA;
	}
lect.EcritureCSV( simulation.get_mat_A(),nameA);
}

cout << "Voulez vous enregistrez le resultat de mat_C[default :oui]:\n";
    getline(cin, tmp);
    if (!tmp.empty())
        str = tmp;
    else
        str = defaultTextee;

if (str == "oui"){
cout << "\n";
cout << "choisissez le nom de fichier destination [mat_C_save.csv]:\n";
string defaultnameC = "mat_C_save.csv";
    getline(cin, tmp);
    if (!tmp.empty()){
        nameC = tmp;
	}
    else{nameC = defaultnameC;
	}
 lect.EcritureCSV( simulation.get_mat_C(),nameC);
}

  /*  lect.EcritureCSV(m_eta,"mat.csv");

    MatriceResultat=lect.LectureGeotiff("erd.tif");
    lect.EcritureGeotiff(MatriceResultat ,"test.tif");

    MatriceResultat=lect.LectureAscii("MNT500_L93_FRANCE.ASC");
    lect.EcritureAscii(MatriceResultat ,"test.ASC"); */
   

 return 0;
 }

