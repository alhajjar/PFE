#include "Includes/Voronoi.hpp"


// ********** Constructeur Voronoi **********

Voronoi::Voronoi(string coord_file_name, int coord_nb_row, int coord_nb_col, string data_file_name, int data_nb_row, int data_nb_col){


	Matrice matcoord(coord_nb_row,coord_nb_col);
	matcoord= Matrice::Zero(coord_nb_row,coord_nb_col);
	voronoi_lecture_coord(coord_file_name,coord_nb_row,coord_nb_col);
	matcoord =getcoordMatrix();

	 Matrice matdata(data_nb_row,data_nb_col);
	 matdata = Matrice::Zero(data_nb_row,data_nb_col);
	voronoi_lecture_data(data_file_name,data_nb_row,data_nb_col);
	matdata =getdataMatrix();

	voronoi_build_index(matcoord,coord_nb_row,coord_nb_col,data_nb_row,data_nb_col);

}

// ********** Destructeur Voronoi **********
Voronoi::~Voronoi(){
  delete(mat_coord);
  delete(mat_data);
  delete(mat_index);
  delete(mat_finale);
}

Matrice Voronoi::getcoordMatrix(){
	return *mat_coord;
}

Matrice Voronoi::getdataMatrix(){
	return *mat_data;
}

Matrice Voronoi::getindexMatrix(){
	return *mat_index;
}

Matrice Voronoi::getfinalMatrix(){
	return *mat_finale;
}

void Voronoi::setcoordMatrix(Matrice coord){
	 *mat_coord = coord;
}
void Voronoi::setdataMatrix(Matrice data){
	 *mat_data = data;
}

void Voronoi::setindexMatrix(Matrice matindex){
	*mat_index = matindex;
}


void Voronoi::setfinalMatrix(Matrice mat_finale1){
	*mat_finale = mat_finale1;

}

void Voronoi::iteration(int jour){

	voronoi_iteration(jour, getdataMatrix(),getindexMatrix());
	//setfinalMatrix(getfinalMatrix());
}

void Voronoi::voronoi_lecture_coord(string file_name_coord, int nb_row_coord, int nb_col_coord){

	// *** Lecture du fichier coord *****************************************************************
	Matrice matcoord(nb_row_coord,nb_col_coord);
	matcoord = Matrice::Zero(nb_row_coord,nb_col_coord);
	mat_coord = new Matrice (nb_row_coord,nb_col_coord);
	*mat_coord = Matrice::Zero(nb_row_coord,nb_col_coord);
	lecture_ecriture lect;
	lect.LectureCSV(nb_row_coord,nb_col_coord,file_name_coord);
	matcoord = lect.get_CSV();

	for(int i=0 ; i<nb_row_coord-1 ; i++){
		matcoord(i,0) = i ; // La 1ere colonne devient la colonne des indices des villes
		matcoord(i,1) = (int)(matcoord(i,1)-47700)/5000 ;   // coordonn�es X de 0 � 193
		matcoord(i,2) = (int)(matcoord(i,2)-1703600)/5000 ; // coordonn�es Y de 0 � 195	// TYPE !!!
	}
	setcoordMatrix(matcoord);
}

void Voronoi::voronoi_lecture_data(string file_name_data, int nb_row_data, int nb_col_data){


	lecture_ecriture lect;
	Matrice mat_data_temp(nb_row_data,nb_col_data);
	mat_data_temp = Matrice::Zero(nb_row_data,nb_col_data);

	Matrice matdata(nb_row_data,nb_col_data-1);
	matdata = Matrice::Zero(nb_row_data,nb_col_data-1);
	mat_data = new Matrice (nb_row_data,nb_col_data-1);
	*mat_data = Matrice::Zero(nb_row_data,nb_col_data-1);

	lect.LectureCSV(nb_row_data,nb_col_data,file_name_data);	// PROBLEME ICI !!!
	mat_data_temp = lect.get_CSV();
		//cout<<mat_data_temp;
	for(int j=0 ; j<nb_row_data-1 ; j++){
		for(int k=0 ; k<nb_col_data-1 ; k++){
			matdata(j+1,k)=mat_data_temp(j,k+1);
		}
	}

	for(int m=0 ; m<nb_row_data ; m++){
				matdata(m,0) = m ;
	}


	for(int n=0 ; n<nb_col_data-2 ; n++){
				matdata(0,n+1) = n ;
	}

	setdataMatrix(matdata);
}

void Voronoi::voronoi_build_index(Matrice mat_coord, int nb_row_coord, int nb_col_coord,int nb_row_data, int nb_col_data){
	Matrice mat_dist(nb_row_coord-1,2);
	mat_dist = Matrice::Zero(nb_row_coord-1,2); // Initialisation de la matrice des indices

	Matrice matindex(194,196);
	matindex = Matrice::Zero(194,196);
	mat_index = new Matrice (194,196);
	*mat_index = Matrice::Zero(194,196);

	for(int a=0 ; a<194 ; a++){
		for(int b=0 ; b<196 ; b++){


			for(int p=0 ; p<nb_row_coord-1 ; p++){
				mat_dist(p,0) = p;
				//mat_dist(p,1) = (mat_coord(p,1)-a)*(mat_coord(p,1)-a) + (mat_coord(p,2)-b)*(mat_coord(p,2)-b);
				mat_dist(p,1) = pow((mat_coord(p,1)-a),2) + pow((mat_coord(p,2)-b),2);
				// Carr� ! V�rifier r�sultat

			}

			// *** Recherche de l'indice du minimum de distance ***

			int itemp = 0 ; // initialisation indice temporaire (1�re ville)
			int temp = 0 ;  // initialisation valeur temporaire de distance minimale

			for(int q=1 ; q<nb_row_coord-1 ; q++){	              // On parcourt toutes les villes...
				 temp = min(mat_dist(itemp,1),mat_dist(q,1)); // deux � deux...
				 if (temp == mat_dist(q,1)){              // et on conserve l'indice de la ville dont la valeur de la
					 itemp = q;                       // distance est la plus faible pour la prochaine it�ration
				 }
			}
			matindex(a,b) = itemp; // une fois l'indice trouv�, il est stock� dans la matrice des indices
		}

	}

	setindexMatrix(matindex);
}




void Voronoi::voronoi_iteration(int jour, Matrice mat_data, Matrice mat_index){
   mat_finale = new Matrice (196,194);
   *mat_finale = Matrice::Zero(196,194);
	Matrice mat_final(194,196);
	mat_final = Matrice::Zero(194,196);
	Matrice matfinale(196,194);
	matfinale= Matrice::Zero(196,194);

	for(int u=0 ; u<194 ; u++){
		for(int v=0 ; v<196 ; v++){
			mat_final(u,v)= mat_data(jour,mat_index(u,v)+1);
			matfinale(v,u) = mat_final(u,195-v);
		}
	}

	setfinalMatrix(matfinale);
}

