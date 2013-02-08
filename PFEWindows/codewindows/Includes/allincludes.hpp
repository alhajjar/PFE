/** 
 * \file allincludes.hpp
 * \brief Fichier d'inclusion de toutes les bibliothèques communes aux différentes classes du projet
*/

#ifndef __ALLINCLUDES__
#define __ALLINCLUDES__

#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "eigen3/Eigen/Core"
#include "cs.h"
#include <tiffio.h>
#include <cstdlib> 
#include <math.h>
#include <string>
#include <memory.h>
#include <stdio.h>

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
