#include "allincludes.hpp"
#include "lecture_ecriture.hpp"

class Voronoi {
private:  
  Matrice *mat_coord;
  Matrice *mat_data;
  Matrice *mat_index;
  Matrice *mat_finale;
public:

  Voronoi(string , int , int , string , int , int );
  void voronoi_lecture_coord(string file_name_coord, int nb_row_coord, int nb_col_coord); // param�tres des fichiers .csv
  void voronoi_lecture_data(string file_name_data, int nb_row_data, int nb_col_data);
  void voronoi_build_index(Matrice mat_coord, int nb_row_coord, int nb_col_coord,int nb_row_data, int nb_col_data);
  void voronoi_iteration(int jour, Matrice mat_data, Matrice mat_index);
  ~Voronoi();

  Matrice getcoordMatrix();  
  Matrice getdataMatrix();  
  Matrice getindexMatrix();
  Matrice getfinalMatrix();

  void setcoordMatrix(Matrice);
  void setdataMatrix(Matrice);
  void setindexMatrix(Matrice);
  void setfinalMatrix(Matrice);

  void iteration(int);
};
