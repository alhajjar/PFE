////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    Resolution_systeme.hpp                      //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////
#ifndef __projet_pfe__Resolution_systeme__
#define __projet_pfe__Resolution_systeme__

#include "allincludes.hpp"


    Matrice Resolution_apteres(int h , Matrice A , Matrice C , Matrice alpha2, MatriceN N1);
    Matrice Resolution_ailees (int h , Matrice A , Matrice C , Matrice alpha1,Matriceinv N22,int iteration );

#endif
