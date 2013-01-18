
#ifndef __projet_pfe__calcul_lois__
#define __projet_pfe__calcul_lois__

#include "allincludes.hpp"

class lecture
{
	public :
		lecture();
		~lecture();

		int getRows();
		int getCols();
		int getXllcorner();
		int getYllcorner();
		int getCellsize();
		int getNODATA_value();
		Matrice  get_CSV();

		void setRows(int);
		void setCols(int);
		void setXllcorner(int);
		void setYllcorner(int);
		void setCellsize(int);
		void setNODATA_value(int);

		//lecture et ecriture du CSV
		void LectureCSV(int m,int n, string filePath);
	        void EcritureCSV(Matrice mat,string str);
		//lecture et ecriture de l'ascii grid
		Matrice LectureAscii(std::string fichiergeomatique);
		void EcritureAscii(Matrice ,std::string fichiergeomatique);

		//lecture et ecriture du geotiff
		Matrice LectureGeotiff(std::string fichiergeomatique);
		void EcritureGeotiff(Matrice ,std::string fichiergeomatique);


	
	private :
		int m,n;
		Matrice sortie;
		string filePath;
		int ncols , nrows,xllcorner,yllcorner,cellsize,NODATA_value;
};

#endif /* defined(__projet_pfe__simulation__) */
		
		
		
		
		
	
