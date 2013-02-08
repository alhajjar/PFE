/** 
 * \file Rgbe.cpp
 * \brief Ce fichier permet la lecture et l'écriture de fichiers ENVI header (.hdr).
 */

#include "Includes/Rgbe.h"

#define RGBE_DONNEES_RED 0
#define RGBE_DONNEES_VERT  1
#define RGBE_DONNEES_BLEU 2

/* Nombre d'octets par pixel */
#define RGBE_DONNEES_SIZE 3

enum codes_erreurs {
	erreur_lecture,
	erreur_ecriture,
	erreur_format,
	erreur_memoire,
};

/** \fn Rgbe::Rgbe()
 *  \brief Constructeur de la classe Rgbe
 */
Rgbe::Rgbe(){}

/** \fn Rgbe::~Rgbe()
 *  \brief Destructeur de la classe Rgbe
 */
Rgbe::~Rgbe(){}

/** \fn int Rgbe::erreur(int codes_erreurs, char *msg)
 *  \brief Méthode gèrant les différentes erreurs (lecture, écriture, format de fichier, errreur de mémoire)
 *  \param codes_erreurs Numéro du type d'erreur
 *  \param msg Message de l'erreur
 *  \return RGBE_RETOUR_ECHEC Erreur de lecture
 */
int Rgbe::erreur(int codes_erreurs, char *msg){
	switch (codes_erreurs) {
		case erreur_lecture:
			perror("Erreur de lecture RGBE");
			break;
		case erreur_ecriture:
			perror("Erreur d'écriture RGBE");
			break;
		case erreur_format:
			fprintf(stderr, "Erreur de format: %s\n", msg);
			break;
		default:
		case erreur_memoire:
			fprintf(stderr, "Erreur de mémoire: %s\n", msg);
	}
	return RGBE_RETOUR_ECHEC;
}

/** \fn void Rgbe::float_to_rgbe(unsigned char rgbe[4], float rouge, float vert, float bleu)
 *  \brief Conversion des 3 composantes R,G,B de type float en 4 composantes R,G,B,E de type char
 *  \param rgbe Tableau de 4 char contenant les composantes RGBE
 *  \param rouge Composante rouge de type float
 *  \param vert Composante vert de type float
 *  \param bleu Composante bleu de type float
 *  \return Rien
 */
void Rgbe::float_to_rgbe(unsigned char rgbe[4], float rouge, float vert, float bleu){
	float valeur;
	int exposant;

	valeur = rouge;
	if (vert > valeur) 
		valeur = vert;
	if (bleu > valeur) 
		valeur = bleu;
	if (valeur < 1e-32) {
		rgbe[0] = rgbe[1] = rgbe[2] = rgbe[3] = 0;
	}
	else {
		valeur = frexp(valeur, &exposant) * 256.0/valeur;
		rgbe[0] = (unsigned char) (rouge * valeur);
		rgbe[1] = (unsigned char) (vert * valeur);
		rgbe[2] = (unsigned char) (bleu * valeur);
		rgbe[3] = (unsigned char) (exposant + 128);
	}
}

/** \fn void Rgbe::rgbe_to_float(float *rouge, float *vert, float *bleu, unsigned char rgbe[4])
 *  \brief Conversion des composantes RGBE en 3 composantes RGB de type float
 *  \param rouge Composante rouge de type float
 *  \param vert Composante vert de type float
 *  \param bleu Composante bleu de type float
 *  \param rgbe Tableau de 4 char contenant les composantes RGBE
 *  \return Rien
 */
void Rgbe::rgbe_to_float(float *rouge, float *vert, float *bleu, unsigned char rgbe[4]){
	float f;

	if (rgbe[3]) {   
		f = ldexp(1.0, rgbe[3] - (int)(128 + 8));
		*rouge = rgbe[0] * f;
		*vert = rgbe[1] * f;
		*bleu = rgbe[2] * f;
	}
	else
		*rouge = *vert = *bleu = 0.0;
}

/** \fn int Rgbe::ecrire_entete(FILE *fichier, int largeur, int hauteur, infos_entete *info)
 *  \brief Ecriture d'un entête dans le fichier
 *  \param fichier Pointeur du fichier où doit être écrit l'entête
 *  \param largeur Largeur de l'image
 *  \param hauteur Hauteur de l'image
 *  \param info Infos à insérer dans le l'entête
 *  \return erreur Définit si il y a une erreur ou non
 */
int Rgbe::ecrire_entete(FILE *fichier, int largeur, int hauteur, infos_entete *info){
	char *programtype = "RADIANCE";
  
	if (info && (info->valid & RGBE_VALID_PROGRAMTYPE))
		programtype = info->programtype;

	if (fprintf(fichier, "#?%s\n", programtype) < 0)
		return erreur(erreur_ecriture, NULL);

	fprintf(fichier, "# Made with 100%c pure HDR Shop\n", 0x25);

	if (fprintf(fichier, "FORMAT=32-bit_rle_rgbe\n") < 0)
		return erreur(erreur_ecriture, NULL);

	fprintf(fichier, "EXPOSURE=          1.0000000000000\n\n");

	if (fprintf(fichier, "-Y %d +X %d\n", hauteur, largeur) < 0)
		return erreur(erreur_ecriture, NULL);

	return RGBE_RETOUR_SUCCES;
}

/** \fn int Rgbe::lire_entete(FILE *fichier, int *largeur, int *hauteur, infos_entete *info)
 *  \brief Lecture d'un entête
 *  \param fichier Pointeur du fichier où doit être écrit l'entête
 *  \param largeur Largeur de l'image
 *  \param hauteur Hauteur de l'image
 *  \param info Infos à insérer dans le l'entête
 *  \return erreur Définit si il y a une erreur de lecture
 */
int Rgbe::lire_entete(FILE *fichier, int *largeur, int *hauteur, infos_entete *info){
	int i;
	char str[200];
	char cmd[200];
	char reso[200];
	char c = 0, oldc;

	fread(str, 10, 1, fichier);
	if (memcmp(str, "#?RADIANCE", 10)) {
		fclose(fichier);
		return erreur(erreur_ecriture, NULL);
	}
	fseek(fichier, 1, SEEK_CUR);
    
	i = 0;
	while(true) {
		oldc = c;
		c = fgetc(fichier);
		if (c == 0xa && oldc == 0xa)
			break;
		cmd[i++] = c;
	}

	i = 0;
	while(true) {
		c = fgetc(fichier);
		reso[i++] = c;
		if (c == 0xa)
			break;
	}

	if (!sscanf(reso, "-Y %ld +X %ld", hauteur, largeur)) {
		fclose(fichier);
        return RGBE_RETOUR_SUCCES;
	}
}

/** \fn int Rgbe::ecrire_pixels(FILE *fichier, float *donnees, int nombre_pixels)
 *  \brief Ecriture des pixels dans le fichier
 *  \param fichier Pointeur du fichier où doit être écrit les pixels
 *  \param donnees Pixels à écrire
 *  \param nombre_pixels Nombre de pixels à écrire
 *  \return erreur Définit si il y a une erreur d'écriture
 */
int Rgbe::ecrire_pixels(FILE *fichier, float *donnees, int nombre_pixels){
	unsigned char rgbe[4];

	while (nombre_pixels-- > 0){
		float_to_rgbe(rgbe, donnees[RGBE_DONNEES_RED], donnees[RGBE_DONNEES_VERT], donnees[RGBE_DONNEES_BLEU]);
		donnees += RGBE_DONNEES_SIZE;
		if (fwrite(rgbe, sizeof(rgbe), 1, fichier) < 1)
			return erreur(erreur_ecriture,NULL);
	}
	return RGBE_RETOUR_SUCCES;
}

/** \fn int Rgbe::lire_pixels(FILE *fichier, float *donnees, int nombre_pixels)
 *  \brief Lecture des pixels d'un fichier ENVI
 *  \param fichier Pointeur du fichier où doit être lu les pixels
 *  \param donnees Pixels lus du fichier
 *  \param nombre_pixels Nombre de pixels à lire
 *  \return erreur Définit si il y a une erreur ou non
 */
int Rgbe::lire_pixels(FILE *fichier, float *donnees, int nombre_pixels){
	unsigned char rgbe[4];

	while(nombre_pixels-- > 0){
		if (fread(rgbe, sizeof(rgbe), 1, fichier) < 1)
			return erreur(erreur_lecture,NULL);
		rgbe_to_float(&donnees[RGBE_DONNEES_RED], &donnees[RGBE_DONNEES_VERT], &donnees[RGBE_DONNEES_BLEU], rgbe);
		donnees += RGBE_DONNEES_SIZE;
	}

	return RGBE_RETOUR_SUCCES;
}

/** \fn int Rgbe::ecrire_octets_encodes(FILE *fichier, unsigned char *donnees, int nombre_octets)
 *  \brief Ecriture d'octets encodés
 *  \param fichier Pointeur du fichier où doit être écrit les octets encodés
 *  \param donnees Octets à écrire
 *  \param nombre_pixels Nombre d'octets à écrire
 *  \return erreur Définit si il y a une erreur ou non
 */
int Rgbe::ecrire_octets_encodes(FILE *fichier, unsigned char *donnees, int nombre_octets){
#define MINRUNLENGTH 4
	int cur, beg_run, run_count, old_run_count, nonrun_count;
	unsigned char buf[2];

	cur = 0;
	while(cur < nombre_octets) {
		beg_run = cur;
		run_count = old_run_count = 0;
		while((run_count < MINRUNLENGTH) && (beg_run < nombre_octets)) {
			beg_run += run_count;
			old_run_count = run_count;
			run_count = 1;
			while((donnees[beg_run] == donnees[beg_run + run_count]) && (beg_run + run_count < nombre_octets) && (run_count < 127))
				run_count++;
		}
		if ((old_run_count > 1)&&(old_run_count == beg_run - cur)) {
			buf[0] = 128 + old_run_count;
			buf[1] = donnees[cur];
			if (fwrite(buf, sizeof(buf[0])*2, 1, fichier) < 1)
				return erreur(erreur_ecriture, NULL);

			cur = beg_run;
		}

		while(cur < beg_run){
			nonrun_count = beg_run - cur;
			if (nonrun_count > 128) 
				nonrun_count = 128;
			buf[0] = nonrun_count;
			if (fwrite(buf, sizeof(buf[0]), 1, fichier) < 1)
				return erreur(erreur_ecriture, NULL);
			if (fwrite(&donnees[cur], sizeof(donnees[0])*nonrun_count, 1, fichier) < 1)
				return erreur(erreur_ecriture, NULL);
			cur += nonrun_count;
		}

		if (run_count >= MINRUNLENGTH){
			buf[0] = 128 + run_count;
			buf[1] = donnees[beg_run];
			if (fwrite(buf, sizeof(buf[0])*2, 1, fichier) < 1)
				return erreur(erreur_ecriture, NULL);
			cur += run_count;
		}
	}
	return RGBE_RETOUR_SUCCES;
#undef MINRUNLENGTH
}

/** \fn int Rgbe::ecrire_pixels_encodes(FILE *fichier, float *donnees, int largeur_ligne, int nombre_lignes)
 *  \brief Ecriture des pixels encodés
 *  \param fichier Pointeur du fichier où doit être écrit les pixels encodés
 *  \param donnees Pixels à écrire
 *  \param largeur_ligne Largeur d'une ligne de pixels
 *  \param nombre_lignes Nombre de lignes de pixels à écrire
 *  \return erreur Définit si il y a une erreur ou non
 */
int Rgbe::ecrire_pixels_encodes(FILE *fichier, float *donnees, int largeur_ligne, int nombre_lignes){
	unsigned char rgbe[4];
	unsigned char *buffer;
	int i, err;

	if ((largeur_ligne < 8)||(largeur_ligne > 0x7fff))
		return ecrire_pixels(fichier,donnees,largeur_ligne*nombre_lignes);

	buffer = (unsigned char *)malloc(sizeof(unsigned char)*4*largeur_ligne);

	if (buffer == NULL) 
		return ecrire_pixels(fichier, donnees, largeur_ligne*nombre_lignes);

	while(nombre_lignes-- > 0){
		rgbe[0] = 2;
		rgbe[1] = 2;
		rgbe[2] = largeur_ligne >> 8;
		rgbe[3] = largeur_ligne & 0xFF;
		if (fwrite(rgbe, sizeof(rgbe), 1, fichier) < 1) {
			free(buffer);
			return erreur(erreur_ecriture, NULL);
		}
		for(i=0; i<largeur_ligne; i++) {
			float_to_rgbe(rgbe, donnees[RGBE_DONNEES_RED], donnees[RGBE_DONNEES_VERT], donnees[RGBE_DONNEES_BLEU]);
			buffer[i] = rgbe[0];
			buffer[i+largeur_ligne] = rgbe[1];
			buffer[i+2*largeur_ligne] = rgbe[2];
			buffer[i+3*largeur_ligne] = rgbe[3];
			donnees += RGBE_DONNEES_SIZE;
		}
		for(i=0; i<4; i++){
			if ((err = ecrire_octets_encodes(fichier, &buffer[i*largeur_ligne], largeur_ligne)) != RGBE_RETOUR_SUCCES){
				free(buffer);
				return err;
			}
		}
	}

	free(buffer);
	return RGBE_RETOUR_SUCCES;
}
      
/** \fn int Rgbe::lire_pixels_encodes(FILE *fichier, float *donnees, int largeur_ligne, int nombre_lignes)
 *  \brief Lecture des pixels encodés
 *  \param fichier Pointeur du fichier où doit être lu les pixels encodés
 *  \param donnees Pixels à lire
 *  \param largeur_ligne Largeur d'une ligne de pixels
 *  \param nombre_lignes Nombre de lignes de pixels à lire
 *  \return erreur Définit si il y a une erreur ou non
 */
int Rgbe::lire_pixels_encodes(FILE *fichier, float *donnees, int largeur_ligne, int nombre_lignes){
	unsigned char rgbe[4], *ligne_temporaire, *ptr, *ptr_end;
	int i, count;
	unsigned char buf[2];

	if ((largeur_ligne < 8)||(largeur_ligne > 0x7fff))
		return lire_pixels(fichier, donnees, largeur_ligne*nombre_lignes);
	ligne_temporaire = NULL;
	while(nombre_lignes > 0) {
		if (fread(rgbe, sizeof(rgbe), 1, fichier) < 1) {
			free(ligne_temporaire);
			return erreur(erreur_lecture,NULL);
		}
		if ((rgbe[0] != 2) || (rgbe[1] != 2) || (rgbe[2] & 0x80)) {
			rgbe_to_float(&donnees[0], &donnees[1], &donnees[2], rgbe);
			donnees += RGBE_DONNEES_SIZE;
			free(ligne_temporaire);
			return lire_pixels(fichier, donnees, largeur_ligne*nombre_lignes-1);
		}
		if ((((int)rgbe[2]) << 8 | rgbe[3]) != largeur_ligne) {
			free(ligne_temporaire);
			return erreur(erreur_format, "Mauvaise largeur de ligne");
		}
		if (ligne_temporaire == NULL)
			ligne_temporaire = (unsigned char *)
		malloc(sizeof(unsigned char)*4*largeur_ligne);
		if (ligne_temporaire == NULL) 
			return erreur(erreur_memoire, "Impossible d'allouer de la mémoire temporaire");
    
		ptr = &ligne_temporaire[0];
		for(i=0; i<4; i++) {
			ptr_end = &ligne_temporaire[(i+1)*largeur_ligne];
			while(ptr < ptr_end) {
				if (fread(buf, sizeof(buf[0])*2, 1, fichier) < 1) {
					free(ligne_temporaire);
					return erreur(erreur_lecture,NULL);
				}
				if (buf[0] > 128) {
					count = buf[0]-128;
					if ((count == 0)||(count > ptr_end - ptr)) {
						free(ligne_temporaire);
						return erreur(erreur_format, "Mauvaise ligne de donnees");
					}
					while(count-- > 0)
						*ptr++ = buf[1];
				}
				else{
					count = buf[0];
					if ((count == 0)||(count > ptr_end - ptr)) {
						free(ligne_temporaire);
						return erreur(erreur_format, "Mauvaise ligne de donnees");
					}
					*ptr++ = buf[1];
					if (--count > 0) {
						if (fread(ptr, sizeof(*ptr)*count, 1, fichier) < 1) {
							free(ligne_temporaire);
							return erreur(erreur_lecture, NULL);
						}
						ptr += count;
					}
				}
			}
		}
		for(i=0; i<largeur_ligne; i++) {
			rgbe[0] = ligne_temporaire[i];
			rgbe[1] = ligne_temporaire[i+largeur_ligne];
			rgbe[2] = ligne_temporaire[i+2*largeur_ligne];
			rgbe[3] = ligne_temporaire[i+3*largeur_ligne];
			rgbe_to_float(&donnees[RGBE_DONNEES_RED], &donnees[RGBE_DONNEES_VERT], &donnees[RGBE_DONNEES_BLEU], rgbe);
			donnees += RGBE_DONNEES_SIZE;
		}
		nombre_lignes--;
	}
	free(ligne_temporaire);
	return RGBE_RETOUR_SUCCES;
}

