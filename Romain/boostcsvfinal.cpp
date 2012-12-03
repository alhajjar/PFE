////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                     Lecture fichier CSV                        //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include "C:\Users\ArcTan\Desktop\Boost\boost\tokenizer.hpp"
#include "C:\Users\ArcTan\Desktop\Boost\boost\lexical_cast.hpp"
#include "C:\Users\ArcTan\Desktop\Boost\boost\algorithm\string.hpp"
//#include "C:\Users\ArcTan\Desktop\eigen2\Eigen\LU"// provides LU decomposition
//#include "C:\Users\ArcTan\Desktop\eigen2\Eigen\Core"// provides random matrices
//#include "C:\Users\ArcTan\Desktop\eigen2\Eigen\src\Core\Matrix.h"
#include <C:\Users\ArcTan\Desktop\eigen2\Eigen\Dense>
#include "Matrice.h"
using namespace std;

Matrice importation(string fichier)
{
    
    Matrice mat(196,194);
    using namespace std;
    using namespace boost;
    //using namespace Eigen;
    /* ************************************************************* */
    /*//recuperation du document csv//*/
    string data(fichier);

    ifstream in(data.c_str());
    if (!in.is_open()){
       cout<<"fichier non trouve\n";
       //return 1;
    }
    typedef tokenizer< escaped_list_separator<char> > Tokenizer;
    typedef Eigen::Matrix <float, 196, 194> Matrice1;
    /* ************************************************************* */
    vector< string > vec;
    vector<string> splitArray;
    vector<float> splitArrayd;
    vector< vector<string> > matrice;
    vector< vector<float > > matricef;
    vector< string>::iterator iter_jj;
    vector< string>::iterator it;
    vector< vector<string> >::iterator iter_ii;
    vector< float>::iterator iter_jjf;
    vector< vector<float> >::iterator iter_iif;
    Matrice1 m ;
    string line;
    /* ************************************************************* */
    while (getline(in,line))
    {
        Tokenizer tok(line);
        vec.assign(tok.begin(),tok.end());
    /*// decomposition du vecteur obtenu et on le met dans un autre vecteur//*/
        split(splitArray, vec.at(0), is_any_of(";"));
   //cout<<splitArray.size()<<"\n";
        int TempNumOne=splitArray.size();
    for (int a=0;a<TempNumOne;a++){
            try{
            splitArrayd[a]= boost::lexical_cast<float>(splitArray[a]);
            }
            catch(bad_lexical_cast &){
            splitArrayd.push_back(0);
            }
        }

    /* ************************************************************* */

        matrice.push_back(splitArray);
        matricef.push_back(splitArrayd);
    }

        matrice.erase(matrice.begin());
        matricef.erase(matricef.begin());

        /*cout<<"dimension matrice string:"<<"\n";
        cout<<matrice.size()<<"X"<<splitArray.size();
        cout << "\n----------------------" << endl;

        cout<<"dimension matrice float:"<<"\n";
        cout<<matricef.size()<<"X"<<splitArrayd.size();
        cout<<"\n----------------------" << endl;*/

        /* ************************************************************* */
      /*//Copie des valeurs dans une matrice de la classe Matrice//*/
       int i=0;
       int j=0;
       int k=0;
       for(iter_iif=matricef.begin(); iter_iif!=matricef.end(); iter_iif++){
           for(iter_jjf=(*iter_iif).begin(); iter_jjf!=(*iter_iif).end(); iter_jjf++){
             mat.setValue(i,j,*iter_jjf);
             j++;
          if ( j%194==0) j=0;
           }
        i++;
        }
        return mat;    
       /* ************************************************************* */
    /*//Affichage de la matrice//*/
    /*   cout<<"premiere ligne matrice string"<<"\n";
    for(iter_ii=matrice.begin(); iter_ii!=matrice.end(); iter_ii++){

          for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end(); iter_jj++){

             cout << *iter_jj<<"\t";

           }
        cout << "\n----------------------" << endl;
        }
        cout<<"premiere ligne matrice float:"<<"\n";

       for(iter_iif=matricef.begin(); iter_iif!=matricef.end(); iter_iif++){
          for(iter_jjf=(*iter_iif).begin(); iter_jjf!=(*iter_iif).end(); iter_jjf++){
             cout << *iter_jjf<<"\t";
           }
           cout << "\n----------------------" << endl;
        }*/
}


