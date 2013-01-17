#include "Includes/Formatgeomatique.hpp"
#include <tiffio.h> 
#define TAILLE_DEFAUT 10




/** \Constructeur Ascii
 *  \brief Constructeur et initialisation des attributs
 */
Formatgeomatique:: Formatgeomatique(){
        ncols = 0;
        nrows = 0 ;
        xllcorner =0;
        yllcorner = 0;
        cellsize = 0;
        NODATA_value =0;
}

/** \Destructeur Ascii
 *  \brief Destructeur
 */
Formatgeomatique::~Formatgeomatique(){

}

/** \méthode de renvoi du nombre de ligne
 *  \brief 
 */
int Formatgeomatique::getRows() {
    return nrows;	
}

/** \méthode de renvoi du nombre de colonne
 *  \brief 
 */
int Formatgeomatique::getCols() {
     return ncols;
}

/** \méthode de renvoi de l'abscisse de l'origine
 *  \brief 
 */
int Formatgeomatique::getXllcorner() {
     return xllcorner;	
}

/** \méthode de renvoi de l'ordonné de l'origine
 *  \brief 
 */
int Formatgeomatique::getYllcorner() {
     return yllcorner;	
}

/** \méthode de renvoi de la taille de la cellule
 *  \brief 
 */
int Formatgeomatique::getCellsize() {
     return cellsize;	
}

/** \méthode de renvoi du no value
 *  \brief 
 */
int Formatgeomatique::getNODATA_value() {
     return NODATA_value;	
}


/** \méthode de modification du nombre de ligne
 *  \brief 
 */
void Formatgeomatique::setRows(int rows) {
     nrows = rows;	
}

/** \méthode de modification du nombre de colonne
 *  \brief 
 */
void Formatgeomatique::setCols(int cols) {
     ncols = cols;	
}

/** \méthode de modification de l'abscisse d'origine
 *  \brief 
 */
void Formatgeomatique::setXllcorner(int xcorner) {
     xllcorner = xcorner;	
}

/** \méthode de modification de l'ordonné d'origine
 *  \brief 
 */
void Formatgeomatique::setYllcorner(int ycorner) {
     yllcorner = ycorner;	
}

/** \méthode de modification de la taille de la cellule
 *  \brief 
 */
void Formatgeomatique::setCellsize(int sizecell) {
     cellsize = sizecell;	
}

/** \méthode de modification du no value
 *  \brief 
 */
void Formatgeomatique::setNODATA_value(int novalue) {
     NODATA_value = novalue;	
}

/** \Lecture des differents formats
 *  \brief Lit les formats ascii, tif et shp
 *  \param[in] fichiergeomatique est le fichier a lire
 *  \param[out] retour est la matrice de donnée
 */
Matrice Formatgeomatique::Lecture(string fichiergeomatique){
      Matrice retour(TAILLE_DEFAUT,TAILLE_DEFAUT);
      int taille=fichiergeomatique.size();   
      if (fichiergeomatique.find("ASC")<taille){
         retour=LectureAscii(fichiergeomatique);
         cout<< "Lecture du format Ascii effectuee\n";
      }else {
            if (fichiergeomatique.find("tif")<taille){
              retour=LectureGeotiff(fichiergeomatique);
              cout<< "Lecture du format Tif effectuee\n";
            }else {
                  if (fichiergeomatique.find("shp")<taille){
                     //retour=LectureGeotiff(fichiergeomatique);
                     cout<< "Lecture du format SHP effectuee\n";
                  }else cout<< "Le format du fichier n'est pas reconnu\n";
            }
      }
      return retour;
}
/** \Ecriture des differents formats
 *  \brief Ecrit les données dans un fichier de type ascii, tif ou shp
 *  \param[in] fichiergeomatique est le fichier a lire
 */
void Formatgeomatique:: Ecriture(Matrice mat,std::string fichiergeomatique){
     int taille=fichiergeomatique.size();  
     if (fichiergeomatique.find("ASC")<taille){
         EcritureAscii(mat,fichiergeomatique);
         cout<< "Ecriture du format Ascii effectuee\n";
     } else {
            if (fichiergeomatique.find("tif")<taille){
               EcritureGeotiff(mat,fichiergeomatique);
               cout<< "Ecriture du format Tif effectuee\n";
            }else {
                  if (fichiergeomatique.find("shp")<taille){
                     //EcritureGeotiff(fichiergeomatique);
                     cout<< "Ecriture du format SHP effectuee\n";
                  }else cout<< "Le format du fichier n'est pas reconnu\n";
            }
     }
}


/** \Stockage des données dans une matrice
 *  \brief Stock dans une matrice les valeurs contenu dans un fichier ainsi que les données 
 *  \nclos le nombre de colonne de la matrice, nrows le nombre de ligne de la matrice
 *  \xllcorner position iniale des valeurs en x,yllcornerposition iniale des valeurs en y
 *  \cellsize pas entre chaque valeur, NODATA_value valeur par defaut du manque de donnée
 *  \param[in] fichiergeomatique : contient les données a stocker
 *  \return mat: matrice contenant seulement les valeurs du fichier
 */
Matrice Formatgeomatique:: LectureAscii(string fichiergeomatique){                   
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

/** \Création d'un fichier ASCII
 *  \brief Construit un fichier de type ascii grid
 *  \param[in] mat : contient les valeurs a enregistrer dans le fichier, fichiergeomatique nom qu'aura le fichier 
 */
void Formatgeomatique:: EcritureAscii(Matrice mat,std::string fichiergeomatique){
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
/** \Lecture d'un fichier Geotiff
 *  \brief lit un fichier de type Geotiff 
 *  \param[in] matrice contient les données a ecrire, fichiergeomatique est le nom que portera le fichier
 *  \param[out] matrice contient les données a ecrire, fichiergeomatique est le nom que portera le fichier
 */  
Matrice Formatgeomatique::LectureGeotiff(std::string fichiergeomatique){
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

/** \Création d'un fichier Geotiff
 *  \brief Construit un fichier de type Geotiff 
 *  \param[in] matrice contient les données a ecrire, fichiergeomatique est le nom que portera le fichier
 */
void Formatgeomatique::EcritureGeotiff(Matrice matrice,std::string fichiergeomatique){        
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
