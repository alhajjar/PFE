#include "Voronoi_fct.hpp"

Matrice voronoi_lecture_coord(string file_name_coord, int nb_row_coord, int nb_col_coord){

	// *** Lecture du fichier coord *****************************************************************
	Matrice mat_coord(nb_row_coord,nb_col_coord);	
	//mat_coord = Matrice::Zero(nb_row_coord,nb_col_coord); // Initialisation de la matrice des coordonnées des villes
	    lecture lect;
	lect.LectureCSV(nb_row_coord,nb_col_coord,file_name_coord);
	mat_coord = lect.get_CSV();

	for(int i=0 ; i<nb_row_coord-1 ; i++){
		mat_coord(i,0) = i ; // La 1ere colonne devient la colonne des indices des villes
		mat_coord(i,1) = (int)(mat_coord(i,1)-47700)/5000 ;   // coordonnées X de 0 à 193
		mat_coord(i,2) = (int)(mat_coord(i,2)-1703600)/5000 ; // coordonnées Y de 0 à 195	// TYPE !!!
	}
	return mat_coord;
}

Matrice voronoi_lecture_data(string file_name_data, int nb_row_data, int nb_col_data){

	
    lecture lect;
	Matrice mat_data_temp(nb_row_data,nb_col_data);	
	// mat_data_temp = Matrice::Zero(nb_row_data,nb_col_data); 

	Matrice mat_data(nb_row_data,nb_col_data-1);	
	// mat_data = Matrice::Zero(nb_row_data,nb_col_data-1); 

	
	lect.LectureCSV(nb_row_data,nb_col_data,file_name_data);	// PROBLEME ICI !!!
	mat_data_temp = lect.get_CSV();
		//cout<<mat_data_temp;
	for(int j=0 ; j<nb_row_data-1 ; j++){
		for(int k=0 ; k<nb_col_data-1 ; k++){
			mat_data(j+1,k)=mat_data_temp(j,k+1);
		}
	}

	
	for(int m=0 ; m<nb_row_data ; m++){
				mat_data(m,0) = m ;
	}

	
	for(int n=0 ; n<nb_col_data-2 ; n++){
				mat_data(0,n+1) = n ;
	}	

	return mat_data;
}

Matrice voronoi_build_index(Matrice mat_coord, int nb_row_coord, int nb_col_coord,int nb_row_data, int nb_col_data){
	Matrice mat_dist(nb_row_coord-1,2);	
	//mat_dist = Matrice::Zero(nb_row_coord-1,2); // Initialisation de la matrice des indices
	
	Matrice mat_index(194,196);	
	//mat_index = Matrice::Zero(194,196);

	for(int a=0 ; a<194 ; a++){
		for(int b=0 ; b<196 ; b++){
			

			for(int p=0 ; p<nb_row_coord-1 ; p++){
				mat_dist(p,0) = p;
				//mat_dist(p,1) = (mat_coord(p,1)-a)*(mat_coord(p,1)-a) + (mat_coord(p,2)-b)*(mat_coord(p,2)-b);
				mat_dist(p,1) = pow((mat_coord(p,1)-a),2) + pow((mat_coord(p,2)-b),2);
				// Carré ! Vérifier résultat
				
			}		

			// *** Recherche de l'indice du minimum de distance ***

			int itemp = 0 ; // initialisation indice temporaire (1ère ville)
			int temp = 0 ;  // initialisation valeur temporaire de distance minimale

			for(int q=1 ; q<nb_row_coord-1 ; q++){	              // On parcourt toutes les villes...		 
				 temp = min(mat_dist(itemp,1),mat_dist(q,1)); // deux à deux...	
				 if (temp == mat_dist(q,1)){              // et on conserve l'indice de la ville dont la valeur de la
					 itemp = q;                       // distance est la plus faible pour la prochaine itération
				 }	
			}
			mat_index(a,b) = itemp; // une fois l'indice trouvé, il est stocké dans la matrice des indices	
		}
		
	}
	return mat_index;
	
}

void affiche_matrice_194_196(Matrice matrice){
	cout << endl << "Matrice :" << endl ;
	for(int c=0 ; c<15 ; c++){
		for(int d=0 ; d<15 ; d++){
			cout << matrice(12*c,12*d) << " ";
			if ( (matrice(12*c,12*d)) < 10){
				cout << " ";
			}
		}
			cout << endl ;
	}
}






Matrice voronoi_iteration(int jour, Matrice mat_data, Matrice mat_index){
	
	Matrice mat_final(194,196);	
	Matrice mat_finale(196,194);

	for(int u=0 ; u<194 ; u++){
		for(int v=0 ; v<196 ; v++){
			mat_final(u,v)= mat_data(jour,mat_index(u,v)+1);
			mat_finale(v,u) = mat_final(u,195-v);
		}
	}
	
	return mat_finale;
}

