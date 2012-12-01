#include <iostream>
#include <cmath>
#include "shapefil.h"

using namespace std;

int main(){
	SHPHandle h;
	SHPObject* objet;
	int nb_polygone;
	int nb_point;
	int type;
	int minx;
	int maxx;
	int miny;
	int maxy;
	int ecarty;
	int ecartx;
	h=SHPOpen("france.shp","rb+");

	objet = SHPReadObject( h, 0 );

	SHPClose(h);
	
	nb_polygone = objet->nParts;
	nb_point = objet->nVertices;

	for(int i=0;i < nb_polygone;i++)
	
	cout<<i<<" "<<objet->panPartType[i]<<" "<<objet->panPartStart[i]<<endl;
	
	for(int j=0; j < nb_point;j++){
		if (j==0){
			minx= objet->padfX[j];
			maxx= objet->padfX[j];
			miny= objet->padfY[j];
			maxy= objet->padfY[j];
		}
		if(j==1){
			ecartx= abs((objet->padfX[j] - objet->padfX[j-1]));
			ecarty= abs((objet->padfY[j] - objet->padfY[j-1]));
		}
		if(abs((objet->padfX[j] - objet->padfX[j-1])) < ecartx)
			cout <<abs((objet->padfX[j] - objet->padfX[j-1])) <<"X"<<endl;
		if(abs((objet->padfY[j] - objet->padfY[j-1])) < ecarty)
			cout <<abs((objet->padfY[j] - objet->padfY[j-1])) <<"Y"<<endl;
		if (objet->padfX[j] < minx)
			minx= objet->padfX[j];
		if (objet->padfX[j] > maxx)
			maxx= objet->padfX[j];
		if (objet->padfY[j] < miny)
			miny= objet->padfY[j];
		if (objet->padfY[j] > maxy)
			maxy= objet->padfY[j];	
			
	//	cout << objet->padfX[j] << " " << objet->padfY[j] << endl;
	
	}
	
	cout <<minx<<" " <<maxx<<" " <<miny<<" " <<maxy<<endl;
	cout <<maxx-minx<<" "<<maxy-miny<<endl;


	return 0;
}