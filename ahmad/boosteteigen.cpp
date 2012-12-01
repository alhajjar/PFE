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
    string data("coord.csv");

    ifstream in(data.c_str());
    if (!in.is_open()) return 1;

    typedef tokenizer< escaped_list_separator<char> > Tokenizer;
    typedef Matrix<float, 196, 194> Matrice1;
    /* ************************************************************* */
    vector< string > vec;
    vector<string> splitArray;
    vector<string> splitArrayd;
    vector< vector<string> > matrice;
    vector< string>::iterator iter_jj;
    vector< string>::iterator it;
    vector< vector<string> >::iterator iter_ii;
    Matrice1 m ;
    string line;
    /* ************************************************************* */
    while (getline(in,line))
    {
        Tokenizer tok(line);
        vec.assign(tok.begin(),tok.end());
    /*// decomposition du vecteur obtenu et on le met dans un autre vecteur//*/
        split(splitArray, vec.at(0), is_any_of(";"));
    /* ************************************************************* */
    /*//conversion de la matrice en float//*/
        /*string tmp;
        for ( it = splitArray.begin();it != splitArray.end();it++ ){
            tmp=*it;
            cout<<tmp<<"\n";
            float  flo = strtof(tmp.c_str(), NULL);
            cout<<flo<<"\t";
            splitArrayd.push_back(flo);
            cout<< splitArrayd.at(0)<<"\n";
            cout<<splitArrayd.at()<<"\n";
        }
        cout<<splitArrayd.at(2)<<"\n";
        cout<<splitArrayd.at()<<"\n";
        */

        matrice.push_back(splitArray);
    }
        matrice.erase(matrice.begin());
       /* ************************************************************* */
    /*//Affichage de la matrice//*/
    /*for(iter_ii=matrice.begin(); iter_ii!=matrice.end(); iter_ii++){

          for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end(); iter_jj++){

             cout << *iter_jj<<"\t";

           }
        cout << "\n----------------------" << endl;
        }
    */
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

