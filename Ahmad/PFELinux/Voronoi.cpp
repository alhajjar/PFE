#include "Voronoi.hpp"
#include "Voronoi_fct.hpp"
//#include <ctime>


using namespace std;

// ********** Constructeur Voronoi **********
Voronoi::Voronoi(string coord_file_name, int coord_nb_row, int coord_nb_col, string data_file_name, int data_nb_row, int data_nb_col){


	mat_coord= Matrice(coord_nb_row,coord_nb_col);	
	mat_coord = voronoi_lecture_coord(coord_file_name,coord_nb_row,coord_nb_col); 

	mat_data= Matrice(data_nb_row,data_nb_col);	
	mat_data = voronoi_lecture_data(data_file_name,data_nb_row,data_nb_col);

	mat_index= Matrice(194,196);
	mat_index = voronoi_build_index(mat_coord,coord_nb_row,coord_nb_col,data_nb_row,data_nb_col);


	Matrice mat_finale(194,196);	
	mat_finale = Matrice::Zero(194,196);


	


}

// ********** Destructeur Voronoi **********
Voronoi::~Voronoi(){
  /*delete(&mat_coord);
  delete(&mat_data);
  delete(&mat_index);
  delete(&mat_finale);*/
}

Matrice Voronoi::getcoordMatrix(){
	return mat_coord;	
}

Matrice Voronoi::getdataMatrix(){
	return mat_data;
}

Matrice Voronoi::getindexMatrix(){
	return mat_index;
}

Matrice Voronoi::getfinalMatrix(){
	return mat_finale;
}

void Voronoi::setfinalMatrix(Matrice mat_finale1){
	mat_finale = mat_finale1;

}

Matrice Voronoi::iteration(int jour){
	Matrice mat(194,196);
	setfinalMatrix(voronoi_iteration(jour, getdataMatrix(), getindexMatrix()));
	mat = getfinalMatrix();
	return mat;
}
