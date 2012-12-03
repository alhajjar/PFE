////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    CSVParser.h                                 //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#ifndef CSVParser_H
#define CSVParser_H

#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "/usr/include/eigen2/Eigen/Array"

    using namespace std;
    using namespace boost;
    using namespace Eigen;


    typedef tokenizer< escaped_list_separator<char> > Tokenizer;
    typedef Matrix<float, 196,194> Matrice;
    typedef Matrix<float, 197,194> Matrice1;

    Matrice CSVParser(const string filePath);


#endif


