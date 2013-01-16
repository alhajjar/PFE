#include "allincludes.hpp"
#include "Voronoi_fct.hpp"

class Voronoi {
private:  
  Matrice mat_coord;
  Matrice mat_data;  
  Matrice mat_index; 
  Matrice mat_finale;
public:
  Voronoi(string , int , int , string , int , int );
  ~Voronoi();  Matrice getcoordMatrix();  Matrice getdataMatrix();  Matrice getindexMatrix();
  Matrice getfinalMatrix();
  void setfinalMatrix(Matrice);
  Matrice iteration(int);
 };
