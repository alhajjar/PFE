
////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    simulation.h                                //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#ifndef __projet_pfe__simulation__
#define __projet_pfe__simulation__


#include <iostream>
#include "/usr/include/eigen2/Eigen/Array"
#include "/usr/include/eigen2/Eigen/Core"
#include "/usr/include/eigen2/Eigen/LU"
#include "/usr/include/eigen2/Eigen/Dense"

    using namespace std;
    using namespace Eigen;

    typedef Matrix<float, 196,194> Matrice;
    typedef Matrix<float, 197,194> Matrice1;

    Matrice taux_accroissement( Matrice theta, Matrice stades);
    Matrice coeff_depot1      ( Matrice m    , Matrice n     );
    Matrice coeff_depot2      ( Matrice m    , Matrice n     );
    Matrice coeff_depot3      ( Matrice m    , Matrice n     );
    Matrice coeff_depot4      ( Matrice m    , Matrice n     );
    Matrice coeff_depot5      ( Matrice m    , Matrice n     );
    Matrice coeff_envol       ( int a , Matrice m , Matrice n);

#endif /* defined(__projet_pfe__simulation__) */
