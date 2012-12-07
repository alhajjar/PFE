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
    typedef Matrix<float, 197,194> Matrice1;
    typedef Matrix<float, 196,194> Matrice2;
    /* ************************************************************* */
    vector< string > vec;
    vector<string> splitArray;
    vector<float> splitArrayd;
    Matrice1 m ;
    string line;
    int nbligne=0;
    /* ************************************************************* */
    while (getline(in,line))
    {
        Tokenizer tok(line);
        vec.assign(tok.begin(),tok.end());
    /*// decomposition du vecteur obtenu et on le met dans un autre vecteur//*/
        split(splitArray, vec.at(0), is_any_of(";"));
        int nbcolonne=splitArray.size();

    for (int a=0;a<nbcolonne;a++){
            try{
            splitArrayd[a]= boost::lexical_cast<float>(splitArray[a]);
             m(nbligne,a)= splitArrayd.at(a);
            }
            catch(bad_lexical_cast &){
            splitArrayd.push_back(0);

            }
        }
    nbligne++;

    }
    /*// delete first row//*/
        Matrice2 mfinal=m.block<196,194>(1,0);
       // std::cout << "The matrix m is of size "<< m.rows() << "x" << m.cols() << std::endl;
      //  std::cout << "The matrix mfinal is of size "<< mfinal.rows() << "x" << mfinal.cols() << std::endl;
        //cout<<" matrice :"<<"\n"<< mfinal(28,44)<<"\n";
       // cout<<" matrice mfinal premiere ligne:"<<"\n"<< mfinal.block<1,194>(0,0)<<"\n";
        //cout<<m(0,0)<<"\n";
      // cout<<" matrice eigen:"<<"\n"<< mfinal<<"\n";
        }
