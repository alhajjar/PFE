////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    CSVParser.h                                 //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#ifndef CSVParser_H
#define CSVParser_H

#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "/usr/include/eigen2/Eigen/LU"// provides LU decomposition
#include "/usr/include/eigen2/Eigen/Array"// provides random matrices
#include <string>



    using namespace std;
    using namespace boost;
    using namespace Eigen;

    typedef Matrix<float, 196,194> Matrice;
    typedef tokenizer< escaped_list_separator<char> > Tokenizer;
    typedef Matrix<float, 197,194> Matrice1;

    Matrice CSVParser(const string filePath,Matrice matrice);


#endif


