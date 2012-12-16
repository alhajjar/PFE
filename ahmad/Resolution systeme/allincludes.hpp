////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    allincludes.hpp                             //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#ifndef __projet_pfe__allincludes__
#define __projet_pfe__allincludes__
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/LU>
#include "test.h"


//#include <eigen3/unsupported/Eigen/SuperLUSupport>


    using namespace std;
    using namespace Eigen;
    using namespace boost;

    typedef tokenizer< escaped_list_separator<char> > Tokenizer;
    typedef Matrix<float, 196,194> Matrice;
    typedef Matrix<float, 1 ,196*194> Vecteur;
    typedef Matrix<double, 1 ,196*194> Vecteurd;
    typedef SparseMatrix<float> SpMat;
    typedef SparseVector<float> SpVec;
    typedef Matrix<float, 197,194> Matrice1;



#endif
