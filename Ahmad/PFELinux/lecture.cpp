#include "Includes/lecture.hpp"
#define TAILLE_DEFAUT 10
/** \fn CSVParser(int m,int n, string filePath)
* \brief Methode permettant la lecture des fichiers CSV
* \param m  Nombre de lignes du fichier CSV
* \param n  Nombre de colonnes du fichier CSV
* \param filePath  le chemin du fichier CSV
* \return Rien
*/

 lecture::lecture(){
};

 lecture::~lecture(){
};

void lecture::LectureCSV(int m,int n, string filePath){


/** \declaration d'une matrice qui est de meme dimension du fichier CSV
*/
    Matrice mfinal(m,n);
    mfinal = Matrice::Zero(m,n);
    sortie = Matrice(196,194);
/** \declaration d'une matrice de sortie dont le nombre de lignes 
*   \est egale au nombre de lignes du fichier CSV -1 et de meme nombre de colonnes 
*/
    /*Matrice mfin(m-1,n);
    mfin = Matrice::Zero(m-1,n);
/** \ouverture du fichier CSV
*/
    string data(filePath);
    ifstream in(data.c_str());
/** \s'il ne s'ouvre pas on aura une message d'erreur
*/
    if (in.fail()){
        cout <<filePath <<" "<<"not found" <<endl;
    }
/** \sinon il extrait son contenu et il le met dans une matrice
*/
    else{
/** \declaration trois vecteurs deux de type string et un de type double 
    \dans le premier on stocke une ligne du fichier CSV telquelle est.
    \exemple: a;d;c mais ce vecteur est former d'une seule case
    \on parcourt le premier vecteur et on le decoupe quand on trouve un ";"
    \puis on  stock les valeurs obtenues dans le deuxieme vecteur   
*/ 
        vector< string > vec;
        vector<string> splitArray;
        vector<double> splitArrayd;
        string line;
        int nbligne=0;
        /* ************************************************************* */
        while (getline(in,line))
        {
/** \on declare un jeton sur la ligne du CSV son debut est le debut de la ligne 
    \et sa fin est la fin du ligne
*/
            Tokenizer tok(line);
            vec.assign(tok.begin(),tok.end());
        /*// decomposition du vecteur obtenu et on le met dans un autre vecteur//*/
            split(splitArray, vec.at(0), is_any_of(";"));
            int nbcolonne=splitArray.size();
/** \on stocke le vecteur dans une matrice
*/
            for (int a=0;a!=nbcolonne;a++){
                try{
                    splitArrayd[a]= boost::lexical_cast<double>(splitArray[a]);
                    mfinal(nbligne,a)= splitArrayd.at(a);
                 }
                 catch(bad_lexical_cast &){
                    splitArrayd.push_back(0);
                   }
             }
          nbligne++;
          }
/** \on efface la premiere ligne de la matrice qui est la ligne d'entete du CSV
*/ 
sortie = mfinal.block(1,0,m-1,n);
    }
}

void lecture::EcritureCSV(Matrice mat,string str){
int m =197, n = 194;
ofstream outdata; // outdata is like cin
   int i=0,j=0; // loop index

  outdata.open(str.c_str()); // opens the file
   if( !outdata ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }

  	for (j=0; j<n-1; j++){

  	    outdata << "V" <<";" ;
 	 }
  outdata  << "V"<<endl ;
  for (i=0; i<m-1; i++){

  	for (j=0; j<n-1; j++){
  	    outdata << mat(i,j)<<";" ;
 	 }
	outdata <<mat(i,j)<<endl ;
   }
   outdata.close();
}

Matrice lecture:: LectureAscii(string fichiergeomatique){                   
      ifstream fichier(fichiergeomatique.c_str(), ios::in);  // on ouvre le fichier en lecture
        if(fichier)  // si l'ouverture a réussi
        {        
            int entier;
	        string tamp; 
            fichier >> tamp >> ncols >> tamp >> nrows>>tamp>>xllcorner>>tamp>>yllcorner>>tamp>>cellsize>>tamp>>NODATA_value;
            Matrice mat(nrows,ncols);
            for(int i=0;i<nrows;i++){
                for(int j=0;j<ncols;j++){
                    fichier >> entier;
                    mat(i,j)=entier;
                }
            }
           return mat;
           fichier.close();  // on ferme le fichier
        }
        else  // sinon
             cerr << "Impossible d'ouvrir le fichier !" << endl;
}    

void lecture:: EcritureAscii(Matrice mat,std::string fichiergeomatique){
        ofstream fichier(fichiergeomatique.c_str(), ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
        if(fichier)
        {
/*nclos le nombre de colonne de la matrice, nrows le nombre de ligne de la matrice
xllcorner position initiale des valeurs en x,yllcornerposition iniale des valeurs en y
cellsize pas entre chaque valeur, NODATA_value valeur par defaut du manque de donnée*/
                fichier << "ncols         " <<ncols<< endl;
                fichier << "nrows         " <<nrows<< endl;
                fichier << "xllcorner     " <<xllcorner<< endl;
                fichier << "yllcorner     " <<yllcorner<< endl;
                fichier << "cellsize      " <<cellsize<< endl;
                fichier << "NODATA_value  " <<NODATA_value<< endl;
                for(int i=0;i<nrows;i++){
                        for(int j=0;j<ncols;j++){
                                fichier << mat(i,j)<<" ";
                        }
                        fichier<<endl;
                }   
                fichier.close();
        }
        else
                cerr << "Impossible d'ouvrir le fichier !" << endl;         
}

Matrice lecture::LectureGeotiff(std::string fichiergeomatique){
    TIFF* tif = TIFFOpen(fichiergeomatique.c_str(), "r");
    if (tif) {
        int w, h;
        int sampleperpixel=3;
        size_t npixels;
        uint32* raster;
        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);  /* Recuperation largeur image */
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);  /* Recuperation hauteur image */
        nrows=h;
        ncols=w;
        Matrice matrice(h,w*3);
        npixels = w * h;   /* Calcul nombre de pixels a recuperer */
        raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));   /* Allocation de la memoire de raster qui est la variable ou on recupere les donnees */
        if (raster != NULL) {
            if (TIFFReadRGBAImage(tif, w, h, raster, 1)) { /* Lecture de tous le fichier image. Raster se remplit également a cet endroit */
                int i,j;
				
				for(i = h - 1; i != -1; i--){   /* Le parcours des donnees de l'image (raster) est bizarre:  */
					for(j=0;j<w;j++){			/* l'image est inversee (la fin de raster est le haut de l'image et le debut de raster le bas ed l'image */
						/* ici on recupere que la matrice de la composante rouge de l'image */
						/* On ne peut pas utiliser les donnees de raster telle quelle puisqu'une donnee de raster est sous la forme suivante */
						/* c'est la concatenation de 8 bits de rouge, 8 de vert, 8 de bleu et 8 de transparence */
						/* c'est pour cela que j'utilise la fonction ci-dessous */
                       matrice(i,j*sampleperpixel) =TIFFGetR(raster[(i*w)+j]);
					   matrice(i,j*sampleperpixel +1)=TIFFGetG(raster[(i*w)+j]);
					   matrice(i,j*sampleperpixel +2)=TIFFGetB(raster[(i*w)+j]);
					}
				}
            }
            return(matrice);
            _TIFFfree(raster);
        }
        TIFFClose(tif);
    }  
}

void lecture::EcritureGeotiff(Matrice matrice,std::string fichiergeomatique){        
TIFF *out= TIFFOpen(fichiergeomatique.c_str(), "w");
//sampleperpixel permet de coder les differentes couches de couleur
int sampleperpixel = 3; 
int height=nrows;
int width=ncols;
char *image=new char [width*height*sampleperpixel];
//On copie la matrice dans un vecteur
for(int i=0; i<height; i++){
    for(int j=0; j<width*sampleperpixel; j++) {
           image[i*width*sampleperpixel + j]=(char)matrice(i,j);}}
            
TIFFSetField (out, TIFFTAG_IMAGEWIDTH, width);  // configure la largeur de l'image
TIFFSetField(out, TIFFTAG_IMAGELENGTH, height);    // configure la hauteur de l'image
TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, sampleperpixel);   // configure le nombre de couche (1 :image nuance de gris, 3 : rouge vert bleu) 
TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);    // configure le nombre de bit par pixel
TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);    // configure l'origine de l'image
TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

tsize_t  linebytes = sampleperpixel * width;     // longueurd'une rangée de pixel de l'image
unsigned char *buf = NULL;        // buffer utilisée pour stocker la ligne d'informations de pixels pour l'écriture du fichier

//    Allocation mémoire pour stocker les pixels de la ligne courante
if (TIFFScanlineSize(out)==linebytes)
    buf =(unsigned char *)_TIFFmalloc(linebytes);
else
    buf = (unsigned char *)_TIFFmalloc(TIFFScanlineSize(out));

TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(out, width*sampleperpixel));

int h=height;
//Ecriture de l'image
for (uint32 row = 0; row < h;row++)
{
    memcpy(buf, &image[(h-row-1)*linebytes], linebytes);
    if (TIFFWriteScanline(out, buf, row, 0) < 0)
    break;
}

(void) TIFFClose(out);
if (buf)
    _TIFFfree(buf);
}

Matrice  lecture::get_CSV(){
return sortie;
}

int lecture::getRows() {
    return nrows;	
}

/** \méthode de renvoi du nombre de colonne
 *  \brief 
 */
int lecture::getCols() {
     return ncols;
}

/** \méthode de renvoi de l'abscisse de l'origine
 *  \brief 
 */
int lecture::getXllcorner() {
     return xllcorner;	
}

/** \méthode de renvoi de l'ordonné de l'origine
 *  \brief 
 */
int lecture::getYllcorner() {
     return yllcorner;	
}

/** \méthode de renvoi de la taille de la cellule
 *  \brief 
 */
int lecture::getCellsize() {
     return cellsize;	
}

/** \méthode de renvoi du no value
 *  \brief 
 */
int lecture::getNODATA_value() {
     return NODATA_value;	
}


/** \méthode de modification du nombre de ligne
 *  \brief 
 */
void lecture::setRows(int rows) {
     nrows = rows;	
}

/** \méthode de modification du nombre de colonne
 *  \brief 
 */
void lecture::setCols(int cols) {
     ncols = cols;	
}

/** \méthode de modification de l'abscisse d'origine
 *  \brief 
 */
void lecture::setXllcorner(int xcorner) {
     xllcorner = xcorner;	
}

/** \méthode de modification de l'ordonné d'origine
 *  \brief 
 */
void lecture::setYllcorner(int ycorner) {
     yllcorner = ycorner;	
}

/** \méthode de modification de la taille de la cellule
 *  \brief 
 */
void lecture::setCellsize(int sizecell) {
     cellsize = sizecell;	
}

/** \méthode de modification du no value
 *  \brief 
 */
void lecture::setNODATA_value(int novalue) {
     NODATA_value = novalue;	
}


