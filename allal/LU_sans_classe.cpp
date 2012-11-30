////////////////////////////////////////////////////////////////////
//						
//                 -------------------------                      //
//                     Décompositon LU                           //
//                                                                //
//                                                                //
////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
#include <cstdlib>
#define taille 4
using namespace std;


int main(int argc, char *argv[])
{

	
			/***********************************************************************************/
		   /*******************************Corps du programme**********************************/
		  /***********************************************************************************/	

	/*initialisation des matrices*/	
	int i,j,k;

	float tab_a[taille] ={0,3,2,1};
	float tab_b[taille]={1 ,4, 3,3};
	float tab_c[taille]={4 ,1 ,4,0};

	float tab_N1[taille][taille]={{1, 4, 0 ,0 },{3 ,4, 1, 0},{ 0 ,2 ,3 ,4},{0 ,0, 1, 3}};


	float tab_L [taille][taille];
	float tab_U [taille][taille];

	float tab_Uinv [taille][taille];
	float tab_Linv [taille][taille];

	float tab_N1_calcule[taille][taille];
	float tab_N1_inverse[taille][taille];


	for (i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
		{
			tab_L [i][j] = 0;
		}
	}


	for (i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
		{

			tab_U[i][j] = tab_L[i][j];
			tab_Uinv  [i][j] =tab_L [i][j];
			tab_Linv [i][j] = tab_L [i][j];

		}
	}

	/***Diagonale principale ègale à 1 dans les matrices U et Uinv***/

	for (i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
		{
			if(i==j)
			{
			tab_Uinv [i][j] = 1;
			tab_U [i][j] = 1;
			}
		}
	}	

	
	/* **********************Matrice U triangulaire supérieure droite******************************** */
	/**Calcul matrice U**/

	tab_U[0][1] = tab_c[0]/tab_b[0];
	

	for(i=1;i<taille;i++)
	{
	
		tab_U[i][i+1]= tab_c[i]/(tab_b[i] -tab_a[i]*tab_U[i-1][i]);
	}



	/**Calcul inverse U**/

    
	for(j=0;j<taille;j++)
	{

            for(i=j;i>0;i--)
	    {
		   tab_Uinv[i-1][j]=-(tab_U[i-1][i]*tab_Uinv[i][j]/tab_U[i-1][i-1]);
            }
    	}
	
	/* **********************Matrice L triangulaire inferieure gauche******************************** */
	
	/*Calcul matrice L*/
	tab_L[0][0] = tab_b[0];
   for (i=0;i<taille;i++)
	{

	for (i=1;i<taille;i++)
	{
		tab_L[i][i] = tab_b[i]-tab_a[i]*tab_c[i-1]/tab_L[i-1][i-1];
		tab_L[i][i-1] = tab_a[i];
			
	}
}

	/****Calcul diagonale principale de Linv****/

	   for (i=0;i<taille;i++)
	{

		tab_Linv [i][i] = 1/tab_L[i][i];
			
	}

	
	 /****Calcul de l'inverse de L****/
	  
		for(j=0;j<taille;j++)
		{
			for(i=j;i<taille-1;i++)
			{
				tab_Linv[i+1][j]=(-(tab_L[i+1][i]*tab_Linv[i][j]/tab_L[i+1][i+1]));
			}
		}

	


	/*Calcul de la matrice N1*/

	for(i=0;i<taille;i++)
        {
            for(j=0;j<taille;j++)
            {
                tab_N1_calcule[i][j]=0;
                for(k=0;k<taille;k++)
                {
                    tab_N1_calcule[i][j]+=(tab_L[i][k]*tab_U[k][j]);
                    /*mult[0][0]=m1[0][0]*m2[0][0]+m1[0][1]*m2[1][0]+m1[0][2]*m2[2][0];*/
                }
           
            }
           
        }
	/*Calcul de la matrice inverse de N1********************/

for(i=0;i<taille;i++)
        {
            for(j=0;j<taille;j++)
            {
                tab_N1_inverse[i][j]=0;
                for(k=0;k<taille;k++)
                {
                    tab_N1_inverse[i][j]+=(tab_Uinv[i][k]*tab_Linv[k][j]);
                    /*mult[0][0]=m1[0][0]*m2[0][0]+m1[0][1]*m2[1][0]+m1[0][2]*m2[2][0];*/
                }
           
            }
           
        }

/***************TEST DES DIFFERENTES MATRICES************/
cout<<"matrice N1\n";
     for (i=0;i<taille;i++)
	{
		for (j=0;j<taille;j++)
		{
			cout<<tab_N1[i][j]<<" ";
		}		
	cout<<"\n";
        }
	cout<<"\n";    

 cout<<"matrice U\n";
     for (i=0;i<taille;i++)
	{
		for (j=0;j<taille;j++)
		{
			cout<<tab_U[i][j]<<" ";
		}		
	cout<<"\n";
        }
	cout<<"\n";

  cout<<"matrice L \n";
   for (i=0;i<taille;i++)
	{
		for (j=0;j<taille;j++)
		{
			cout<<tab_L[i][j]<<" ";
		}		
		cout<<"\n";
        }
	cout<<"\n";

  cout<<"matrice Uinv \n";
   for (i=0;i<taille;i++)
	{
		for (j=0;j<taille;j++)
		{
			cout<<tab_Uinv[i][j]<<" ";
		}		
	cout<<"\n";
        }
	cout<<"\n";

  cout<<"matrice Linv \n";
   for (i=0;i<taille;i++)
	{
		for (j=0;j<taille;j++)
		{
			cout<<tab_Linv[i][j]<<" ";
		}		
	cout<<"\n";
        }
	cout<<"\n";

  cout<<"matrice N1inv \n";
   for (i=0;i<taille;i++)
	{
		for (j=0;j<taille;j++)
		{
			cout<<tab_N1_inverse[i][j]<<" ";
		}		
	cout<<"\n";
        }






		
	//system("PAUSE");
	return EXIT_SUCCESS;
}


