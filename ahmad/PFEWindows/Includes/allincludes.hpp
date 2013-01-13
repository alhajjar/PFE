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
#include "eigen3/Eigen/Core"
#include "cs.h"
#include <cstdlib> 

	using std::cerr;
	using std::endl;
	using std::ofstream;
    	using namespace std;
    	using namespace Eigen;
    	using namespace boost;

    typedef tokenizer< escaped_list_separator<char> > Tokenizer;
    typedef MatrixXd Matrice;
    typedef VectorXd Vecteur;

#endif
