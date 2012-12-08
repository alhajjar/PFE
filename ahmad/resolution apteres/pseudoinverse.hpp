////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    pseudoinverse.hpp                           //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#ifndef __projet_pfe__pseudoinverse__
#define __projet_pfe__pseudoinverse__


#include <iostream>
#include "/usr/include/eigen2/Eigen/Array"
#include "/usr/include/eigen2/Eigen/Core"
#include "/usr/include/eigen2/Eigen/LU"
#include "/usr/include/eigen2/Eigen/Dense"

    using namespace std;
    using namespace Eigen;

    typedef Matrix<float, 196,194> Matrice;
    typedef Matrix<float, 194 ,196> Matriceinv;

    Matriceinv pseudoinv(Matrice mat);

#endif
