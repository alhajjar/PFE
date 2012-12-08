#include "pseudoinverse.hpp"

Matriceinv pseudoinv(Matrice mat){

// {[(transpose(B conjuge )) * B] exp -1 } *(transpose(B conjuge )) = pseudo inverse
Matriceinv matr =Matriceinv::Zero();
matr = (((mat.conjugate().transpose())*mat).inverse())*(mat.conjugate().transpose());
//cout<< matr.block<1, 196>(0,0);
return matr;

}
