/** 
  * \file Lecture_Ecriture.cpp
  * \brief Fichier permettant la lecture et l'écriture dans les différents formats de fichiers désirés (CSV, ASCII grid, GeoTIFF et SHP)
  */

#include "Includes/Lecture_Ecriture.hpp"

#define TAILLE_DEFAUT 10

/** \fn Lecture_Ecriture::Lecture_Ecriture()
 *  \brief Constructeur de la classe Lecture_Ecriture
 */
Lecture_Ecriture::Lecture_Ecriture(){


	ncols = 0;
	nrows = 0;
	xllcorner = 0;
	yllcorner = 0;
	cellsize = 0;
	NODATA_value = 0;
	sortie =  Matrice(196,194);
	sortie = Matrice::Zero(196,194);
	cheminFichier = "";
}

/** \fn Lecture_Ecriture::~Lecture_Ecriture()
 *  \brief Destructeur de la classe Lecture_Ecriture
 */
Lecture_Ecriture::~Lecture_Ecriture(){
	//delete(sortie);
}

/** \fn void Lecture_Ecriture::LectureCSV(int m, int n, string cheminFichier)
 *  \brief Méthode permettant la lecture des fichiers CSV
 *  \param m  Nombre de lignes du fichier CSV que l'on souhaite récupérer
 *  \param n  Nombre de colonnes du fichier CSV que l'on souhaite récupérer
 *  \param cheminFichier Chemin du fichier CSV
 *  \return Rien
 */
void Lecture_Ecriture::LectureCSV(int m, int n, string cheminFichier){
/* Déclaration d'une matrice de même dimension que le fichier CSV */
    Matrice mfinal(m,n);
    mfinal = Matrice::Zero(m,n);
	
/* Vecteur récupérant chaque ligne telle qu'elle est. Ex: a;d;c */
	vector< string > vec;
/* Vecteur récupérant le découpage du vecteur vec (découpage de faisant à chaque fois que le caractère ";" est rencontré). Ex: vec == [a b c] */
	vector< string > splitArray;
/* Transformation des valeurs de splitArray de string en double*/
	vector< double > splitArrayd;
	string ligne;
	int nbligne = 0;

    ifstream fichier(cheminFichier.c_str());
/* Si l'ouverture du fichier a échouée */
    if (fichier.fail()){
        cout << cheminFichier << " " << " n'existe pas" << endl;
    }
/* Sinon extraction du contenu du fichier dans une matrice */
    else{
        while (getline(fichier,ligne)){
/* Déclaration d'un jeton sur la ligne du CSV. Ce jeton débute au début de la ligne et se termine à la fin de la ligne */
            Tokenizer tok(ligne);
            vec.assign(tok.begin(),tok.end());
/* Découpage du vecteur obtenu */
            split(splitArray, vec.at(0), is_any_of(";"));
            int nbcolonne = splitArray.size();
/* Stockage du vecteur dans une matrice */
            for (int a=0; a!=nbcolonne; a++){
                try{
					splitArrayd[a] = boost::lexical_cast<double>(splitArray[a]);
                    mfinal(nbligne,a) = splitArrayd.at(a);
                }
                catch(bad_lexical_cast &){
					splitArrayd.push_back(0);
                }
			}
			nbligne++;
		}
/* Suppression de la première ligne de la matrice qui est la ligne d'entête du fichier CSV */
	sortie = mfinal.block(1,0,m-1,n);
	cout<<"\nFin de la lecture de "<<cheminFichier<<"\n";  
    }

}

/** \fn void Lecture_Ecriture::EcritureCSV(Matrice mat, string cheminFichier)
 *  \brief Construit un fichier de type CSV
 *  \param mat Matrice à sauvegarder
 *  \param cheminFichier Nom du fichier CSV à créer
 *  \return Rien
 */
void Lecture_Ecriture::EcritureCSV(Matrice mat, string cheminFichier){
	int m =197, n = 194;
	ofstream fichier;
	
/* Ouverture du fichier */
	fichier.open(cheminFichier.c_str());
/* Si une erreur se produit lors de l'ouverture */
	if( !fichier ) { 
		cerr << "Erreur: Le fichier n'a pas pu être ouvert " << endl;
		exit(1);
	}
stringstream Filename;
 

for (int j=0; j < n-1; j++){
  Filename.clear();
  Filename.str("");
  Filename << "V"<< j+1;
  fichier << Filename.str().c_str()  <<";" ;
}
   Filename.clear();
   Filename.str("");
   Filename << "V"<< n;
   fichier << Filename.str().c_str()  << endl ;

	for (int i = 0; i < m-1; i++){
		for (int j = 0; j < n-1; j++)
			fichier << mat(i,j) << ";";
		fichier << mat(i,n-1) << endl;
	}
	fichier.close();
cout<<"\nFin de l'ecriture de la matrcice dans "<<cheminFichier<<"\n";
}

/** \fn void Lecture_Ecriture::LectureAscii(string fichiergeomatique)
 *  \brief Lecture d'un fichier au format ASCII 
 *  \param fichiergeomatique Nom du fichier à lire 
 *  \return Rien
 */
Matrice Lecture_Ecriture::LectureAscii(string fichiergeomatique){
	int entier;
	string tamp; 
/* Ouverture du fichier */
	ifstream fichier(fichiergeomatique.c_str(), ios::in);
	if(fichier){
		
		fichier >> tamp >> ncols >> tamp >> nrows >> tamp >> xllcorner >> tamp>> yllcorner >> tamp >> cellsize >> tamp >> NODATA_value;
		Matrice mat(nrows,ncols);
		mat = Matrice::Zero(nrows,ncols);
		for(int i=0; i<nrows; i++){
			for(int j=0; j<ncols; j++){
				fichier >> entier;
				mat(i,j) = entier;
			}
		}
		sortie = mat;
		cout<<"\nFin de la lecture de "<<fichiergeomatique<<"\n";
/* Fermeture du fichier */
		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
		  
	return sortie;
}    

/** \fn Lecture_Ecriture::EcritureAscii(Matrice mat_donnees_geomatiques, string fichiergeomatique)
 *  \brief Ecriture dans un fichier de type ascii grid
 *  \param mat Matrice contenant les valeurs à enregistrer dans le fichier
 *  \param fichiergeomatique Nom du fichier à créer
 *  \return Rien
 */  
void Lecture_Ecriture::EcritureAscii(Matrice mat_donnees_geomatiques, string fichiergeomatique){
/* Ouverture en écriture avec effacement du fichier ouvert */
	ofstream fichier(fichiergeomatique.c_str(), ios::out | ios::trunc);  
	
	if(fichier){
/* Nombre de colonnes de la matrice */
		fichier << "ncols         " << ncols << endl;
/* Nombre de lignes de la matrice */
		fichier << "nrows         " << nrows << endl;
/* Position initiale des valeurs en x */
		fichier << "xllcorner     " << xllcorner << endl;
/* Position iniale des valeurs en y */
		fichier << "yllcorner     " << yllcorner << endl;
/* Pas entre chaque valeur */
		fichier << "cellsize      " << cellsize << endl;
/* Valeur par défaut du manque de donnée */
		fichier << "NODATA_value  " << NODATA_value << endl;
/* Insertion des données de la matrice */
		for(int i=0; i < nrows; i++){
			for(int j=0; j < ncols; j++){
				fichier << mat_donnees_geomatiques(i,j) << " ";
            }
            fichier << endl;
		}   
/* Fermeture du fichier */
		fichier.close();
	}  
 else
                cerr << "Impossible d'ouvrir le fichier !" << endl;
		cout<<"\nFin de l'ecriture de la matrcice dans "<<fichiergeomatique<<"\n";     
}

/** \fn void Lecture_Ecriture::LectureGeotiff(string fichiergeomatique)
 *  \brief Lecture d'un fichier de type Geotiff 
 *  \param fichiergeomatique Nom du fichier Geotiff à lire
 *  \return Rien
 */ 
void Lecture_Ecriture::LectureGeotiff(string fichiergeomatique){
   /* Ouverture du fichier */
    TIFF* tif = TIFFOpen(fichiergeomatique.c_str(), "r");
/* Si il n'y a pas d'erreurs de lecture */
    if (tif) {
        int largeur, hauteur;
        int sampleperpixel = 3;
        size_t npixels;
        uint32* raster;
/* Récuperation largeur image */
        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &largeur); 
/* Recuperation hauteur image */		
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &hauteur);  
        nrows = hauteur;
        ncols = largeur;
        Matrice mat_donnees_geomatiques(hauteur, largeur*3);
/* Calcul du nombre de pixels à récupérer */
        npixels = largeur * hauteur;   
/* Allocation de la mémoire de la variable où sont recuperées les données */
        raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
        if (raster != NULL) {
/* Lecture de tout le fichier image. Raster se remplit également à cet endroit */
            if (TIFFReadRGBAImage(tif, largeur, hauteur, raster, 1)) { 	
/* L'image est inversée (la fin de raster est le haut de l'image et le début de raster le bas de l'image */
				for(int i = hauteur - 1; i != -1; i--){   
					for(int j=0; j < largeur; j++){			
/* ici on recupere que la matrice de la composante rouge de l'image */
/* On ne peut pas utiliser les donnees de raster telle quelle puisqu'une donnee de raster est sous la forme suivante */
/* c'est la concatenation de 8 bits de rouge, 8 de vert, 8 de bleu et 8 de transparence */
/* c'est pour cela que j'utilise la fonction ci-dessous */
                       mat_donnees_geomatiques(i,j*sampleperpixel) = TIFFGetR(raster[(i*largeur)+j]);
					   mat_donnees_geomatiques(i,j*sampleperpixel + 1) = TIFFGetG(raster[(i*largeur)+j]);
					   mat_donnees_geomatiques(i,j*sampleperpixel + 2) = TIFFGetB(raster[(i*largeur)+j]);
					}
				}
            }
			sortie = mat_donnees_geomatiques;
            _TIFFfree(raster);
        }
    	cout<<"\nFin de la lecture de "<<fichiergeomatique<<"\n";  
        TIFFClose(tif);
    }
}

/** \fn void Lecture_Ecriture::EcritureGeotiff(Matrice mat_donnees_geomatiques, string fichiergeomatique)
 *  \brief Construit un fichier de type Geotiff 
 *  \param mat_donnees_geomatiques Matrice contenant les données à écrire 
 *  \param fichiergeomatique Nom du fichier image créé
 *  \return Rien
 */
void Lecture_Ecriture::EcritureGeotiff(Matrice mat_donnees_geomatiques, string fichiergeomatique){
/* Ouverture du fichier */
	TIFF *fichier = TIFFOpen(fichiergeomatique.c_str(), "w");
	
/* sampleperpixel représente les différentes couches de couleur (ici RGB) pour un pixel */
	int sampleperpixel = 3; 
	int hauteur = nrows;
	int largeur = ncols;
	char *image = new char [largeur*hauteur*sampleperpixel];

/* On copie la matrice dans un vecteur qui sert à l'écriture dans l'image*/
	for(int i=0; i < hauteur; i++){
		for(int j=0; j < largeur*sampleperpixel; j++) {
			   image[i*largeur*sampleperpixel + j] = (char) mat_donnees_geomatiques(i,j);
		}
	}
	   
/* Configure la largeur de l'image */
	TIFFSetField(fichier, TIFFTAG_IMAGEWIDTH, largeur);
/* Configure la hauteur de l'image */	
	TIFFSetField(fichier, TIFFTAG_IMAGELENGTH, hauteur);
/* Configure le nombre de couche(s) (1 :image nuance de gris, 3 : rouge vert bleu) */	
	TIFFSetField(fichier, TIFFTAG_SAMPLESPERPIXEL, sampleperpixel);
/* Configure le nombre de bits par échantillon (8 pour le rouge, 8 pour le vert et 8 pour le bleu) */	
	TIFFSetField(fichier, TIFFTAG_BITSPERSAMPLE, 8);
/* Configure l'origine de l'image */
	TIFFSetField(fichier, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
/* Configure ce que représente les images (ici l'image sera un seul plan. Cela aurait pu être plusieurs couches) */	
	TIFFSetField(fichier, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
/* Configure le type de couleur qui va être insérer dans l'image */	
	TIFFSetField(fichier, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

/* Longueur d'une ligne de pixels de l'image */
	tsize_t  linebytes = sampleperpixel * largeur;
/* Buffer utilisé pour stocker la ligne d'informations de pixels pour l'écriture du fichier */	
	unsigned char *buf = NULL;

/* Allocation mémoire pour stocker les pixels de la ligne courante */
	if (TIFFScanlineSize(fichier) == linebytes)
		buf = (unsigned char *)_TIFFmalloc(linebytes);
	else
		buf = (unsigned char *)_TIFFmalloc(TIFFScanlineSize(fichier));

/* Configure le nombre de bits pour une ligne d'image */
	TIFFSetField(fichier, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(fichier, largeur*sampleperpixel));
	
/* Ecriture de l'image */
	for (uint32 row = 0; row < (uint32)hauteur;row++)
	{
		memcpy(buf, &image[(hauteur-row-1)*linebytes], linebytes);
		if (TIFFWriteScanline(fichier, buf, row, 0) < 0)
		break;
	}
cout<<"\nFin de l'ecriture de la matrcice dans "<<fichiergeomatique<<"\n";
/* Fermeture du fichier */
	(void) TIFFClose(fichier);
/* Libération de la mémoire du stockeur de lignes temporaire */
	if (buf)
		_TIFFfree(buf);

}

/** \fn Lecture_Ecriture::get_CSV()
 *  \brief Méthode de renvoi de la matrice mat_csv
 *  \return sortie Matrice comportant les valeurs récupérées pour un fichier CSV
 */
Matrice Lecture_Ecriture::get_CSV(){
	return sortie;
}

/** \fn int Lecture_Ecriture::getRows()
 *  \brief Méthode de renvoi du nombre de lignes
 *  \return nrows Nombre de lignes pour un fichier geotiff ou ASCII grid
 */
int Lecture_Ecriture::getRows() {
    return nrows;	
}

/** \fn int Lecture_Ecriture::getCols()
 *  \brief Méthode de renvoi du nombre de colonnes
 *  \return ncols Nombre de colonnes pour un fichier geotiff ou ASCII grid
 */
int Lecture_Ecriture::getCols() {
    return ncols;
}

/** \fn int Lecture_Ecriture::getXllcorner()
 *  \brief Méthode de renvoi de l'abscisse de l'origine pour un fichier ASCII grid
 *  \return xllcorner Abscisse de l'origine pour un fichier ASCII grid
 */
int Lecture_Ecriture::getXllcorner() {
    return xllcorner;	
}

/** \fn int Lecture_Ecriture::getYllcorner()
 *  \brief Méthode de renvoi de l'ordonnée de l'origine pour un fichier ASCII grid
 *  \return yllcorner Ordonnée de l'origine pour un fichier ASCII grid
 */
int Lecture_Ecriture::getYllcorner() {
    return yllcorner;	
}

/** \fn int Lecture_Ecriture::getCellsize()
 *  \brief Méthode de renvoi de la taille de la cellule pour un fichier ASCII grid
 *  \return cellsize Taille de la cellule pour un fichier ASCII grid
 */
int Lecture_Ecriture::getCellsize() {
	return cellsize;	
}

/** \fn int Lecture_Ecriture::getNODATA_value()
 *  \brief Méthode de renvoi de la valeur par défaut quand il y a un manque de données pour un fichier ASCII grid
 *  \return NODATA_value Valeur par défaut quand il y a un manque de données pour un fichier ASCII grid
 */
int Lecture_Ecriture::getNODATA_value() {
	return NODATA_value;	
}

/** \fn void Lecture_Ecriture::setRows(int rows)
 *  \brief Méthode de modification du nombre de lignes
 *  \param rows Nombre de lignes pour un fichier geotiff ou ASCII grid
 *  \return Rien
 */
void Lecture_Ecriture::setRows(int val) {
     nrows = val;	
}

/** \fn void Lecture_Ecriture::setCols(int val)
 *  \brief Méthode de modification du nombre de colonnes
 *  \param val Nombre de colonnes pour un fichier geotiff ou ASCII grid
 *  \return Rien
 */
void Lecture_Ecriture::setCols(int val) {
     ncols = val;	
}

/** \fn void Lecture_Ecriture::setXllcorner(int val)
 *  \brief Méthode de modification de l'abscisse d'origine
 *  \param val Abcsisse de l'origine pour un fichier ASCII grid
 *  \return Rien
 */
void Lecture_Ecriture::setXllcorner(int val) {
     xllcorner = val;	
}

/** \fn void Lecture_Ecriture::setYllcorner(int val)
 *  \brief Méthode de modification de l'ordonnée d'origine
 *  \param val Ordonnée de l'origine pour un fichier ASCII grid
 *  \return Rien
 */
void Lecture_Ecriture::setYllcorner(int val) {
     yllcorner = val;	
}

/** \fn void Lecture_Ecriture::setCellsize(int val)
 *  \brief Méthode de modification de la taille de la cellule
 *  \param val Taille de la cellule pour un fichier ASCII grid
 *  \return Rien
 */
void Lecture_Ecriture::setCellsize(int val) {
     cellsize = val;	
}

/** \fn void Lecture_Ecriture::setNODATA_value(int val)
 *  \brief Méthode de modification no_value 
 *  \param val Valeur par défaut quand il y a un manque de données pour un fichier ASCII grid
 *  \return Rien
 */
void Lecture_Ecriture::setNODATA_value(int val) {
     NODATA_value = val;	
}
