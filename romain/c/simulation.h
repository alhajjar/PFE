//
//  simulation.h
//  projet_pfe
//
//  Created by Guillaume LALY on 19/11/12.
//  Copyright (c) 2012 Guillaume LALY. All rights reserved.
//

#ifndef __projet_pfe__simulation__
#define __projet_pfe__simulation__

#include <iostream>
#include "matrice.h"

using namespace std;

Matrice taux_accroissement(Matrice theta, Matrice stades);
Matrice coeff_depot1(float, Matrice);
Matrice coeff_depot2(float, Matrice);
Matrice coeff_depot3(float, Matrice);
Matrice coeff_depot4(float, Matrice);
Matrice coeff_depot5(float, Matrice);
Matrice coeff_envol(int, Matrice, Matrice);

#endif /* defined(__projet_pfe__simulation__) */