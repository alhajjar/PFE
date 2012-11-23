////////////////////////////////////////////////////////////////////
//						   main.cpp                               //
    //                 -------------------------                  //
   //                     Décompositon LU                        //
  //                                                            //
 //                                                            //
////////////////////////////////////////////////////////////////
#include <iostream>
#include <math.h>
#include "/usr/include/eigen2/Eigen/LU"// provides LU decomposition
#include "/usr/include/eigen2/Eigen/Array"// provides random matrices
using namespace Eigen;
using namespace std;
int main()
{
/*//on defini une matrice de float 5x3  //*/
typedef Matrix<float, 5, 3> Matrix5x3;
/*//on defini une matrice de float 5x3  //*/
typedef Matrix<float, 5, 5> Matrix5x5;
/*// on creer une matrice m de type matrice 5*3 et on la rempli randomli //*/
Matrix5x3 m = Matrix5x3::Random();
cout << "Here is the matrix m:" << endl << m << endl;
cout << "---------------------------------\n";
//
Eigen::LU<Matrix5x3> lu(m);
cout << "Here is, up to permutations, its LU decomposition matrix:"
<< endl << lu.matrixLU() << endl;
cout << "---------------------------------\n";
cout << "Here is the L part:" << endl;
cout << "---------------------------------\n";
Matrix5x5 l = Matrix5x5::Identity();
l.block<5,3>(0,0).part<StrictlyLowerTriangular>() = lu.matrixLU();
cout << l << endl;
cout << "Here is the U part:" << endl;
cout << "---------------------------------\n";
Matrix5x3 u = lu.matrixLU().part<UpperTriangular>();
cout << u << endl;
cout << "---------------------------------\n";
cout << "Let us now reconstruct the original matrix m:" << endl;
cout << "---------------------------------\n";
/*// multiplication matrix * matrix/ /*/
Matrix5x3 x = l * u;
Matrix5x3 y;
for(int i = 0; i < 5; i++) for(int j = 0; j < 3; j++)
y(i, lu.permutationQ()[j]) = x(lu.permutationP()[i], j);
cout << y << endl; // should be equal to the original matrix m
cout << "---------------------------------\n";
}

