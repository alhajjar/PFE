////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                     Lecture fichier CSV                        //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "/usr/include/eigen2/Eigen/LU"// provides LU decomposition
#include "/usr/include/eigen2/Eigen/Array"// provides random matrices

int main()
{
    using namespace std;
    using namespace boost;
    using namespace Eigen;
    /* ************************************************************* */
    /*//recuperation du document csv//*/
    string data("mat_eta.csv");

    ifstream in(data.c_str());
    if (!in.is_open()) return 1;

    typedef tokenizer< escaped_list_separator<char> > Tokenizer;
    typedef Matrix<float, 196, 194> Matrice1;
    /* ************************************************************* */
    vector< string > vec;
     vector< float > vecf;
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
    //splitArrayd.push_back(lexical_cast<float>(splitArray[a]));
            try{
            splitArrayd[a]= boost::lexical_cast<float>(splitArray[a]);
            }
            catch(bad_lexical_cast &){
            splitArrayd.push_back(0);
            }
    //cout<< splitArrayd[a];
        }

    /* ************************************************************* */
    /*//conversion de la matrice en float//*/
        /*string tmp;
        for ( it = splitArray.begin();it != splitArray.end();it++ ){
            tmp=*it;
            cout<<tmp<<"\n";
            float  flo = strtof(tmp.c_str(), NULL);
            cout<<flo<<"\t";
            splitArrayd.push_back(flo);
        }*/

        matrice.push_back(splitArray);
        matricef.push_back(splitArrayd);
    }
        cout<<splitArray.size()<<"\n";
        cout<<splitArrayd.size()<<"\n";

        matrice.erase(matrice.begin());
        matricef.erase(matricef.begin());

        cout<<matrice.size()<<"\n" ;
        cout<<matricef.size()<<"\n";


       /* ************************************************************* */
    /*//Affichage de la matrice//*/
 /*  for(iter_ii=matrice.begin(); iter_ii!=matrice.end()-(matrice.size()-1); iter_ii++){

          for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end(); iter_jj++){

             cout << *iter_jj<<"\t";

           }
        cout << "\n----------------------" << endl;
        }

       for(iter_iif=matricef.begin(); iter_iif!=matricef.end()-(matricef.size()-1); iter_iif++){

          for(iter_jjf=(*iter_iif).begin(); iter_jjf!=(*iter_iif).end(); iter_jjf++){

             cout << *iter_jjf<<"\t";

           }
        cout << "\n----------------------" << endl;
        }*/

        }
    /*
    cout << "Here is, up to permutations, its LU decomposition matrix:"
    << endl << lu.matrixLU() << endl;
    cout << "---------------------------------\n";*/
    /*cout << "Here is the L part:" << endl;
    cout << "---------------------------------\n";
    Matrix5x5 l = Matrix5x5::Identity();
    l.block<500,500>(0,0).part<StrictlyLowerTriangular>() = lu.matrixLU();
    cout << l << endl;
    cout << "Here is the U part:" << endl;
    cout << "---------------------------------\n";
    Matrix5x3 u = lu.matrixLU().part<UpperTriangular>();
    cout << u << endl;
    cout << "---------------------------------\n";
    cout << "Let us now reconstruct the original matrix m:" << endl;
    cout << "---------------------------------\n";*/
    /*// multiplication matrix * matrix/ /*/
    /*Matrix5x3 x = l * u;
    Matrix5x3 y;
    for(int i = 0; i < 190; i++) for(int j = 0; j < 190; j++)
    y(i, lu.permutationQ()[j]) = x(lu.permutationP()[i], j);
    cout << y << endl; // should be equal to the original matrix m
    cout << "---------------------------------\n";
    /}*/

