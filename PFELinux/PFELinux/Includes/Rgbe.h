/** 
 * \file Rgbe.h
 * \brief Fichier d'entête de la bibliothèque de la lecture/écriture des fichiers ENVI header (.hdr)
*/

#ifndef _H_RGBE
#define _H_RGBE

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	int valid;            
	char programtype[16]; 
	float gamma;         
	float exposure;
} infos_entete;

/* Flags indiquant quels champs dans l'entête sont valides */
#define RGBE_VALID_PROGRAMTYPE 0x01
#define RGBE_VALID_GAMMA       0x02
#define RGBE_VALID_EXPOSURE    0x04

/* Codes pour la gestion des erreurs */
#define RGBE_RETOUR_SUCCES 0
#define RGBE_RETOUR_ECHEC -1

/** \class Rgbe
  * \brief Classe gérant la lecture/écriture des fichiers ENVI header (.hdr)
  */
class Rgbe {
public:
	 Rgbe();
	 ~Rgbe();

/* Ecrire ou lire un entête */
	 int ecrire_entete(FILE *fichier, int largeur, int hauteur, infos_entete *info);
	 int lire_entete(FILE *fichier, int *largeur, int *hauteur, infos_entete *info);

/* Ecrire ou lire des pixels */
	 int ecrire_pixels(FILE *fichier, float *donnees, int nombre_pixels);
	 int lire_pixels(FILE *fichier, float *donnees, int nombre_pixels);

/* Ecrire ou lire des fichiers avec des pixels encodés */
	 int ecrire_pixels_encodes(FILE *fichier, float *donnees, int largeur_ligne, int nombre_lignes);
	 int lire_pixels_encodes(FILE *fichier, float *donnees, int largeur_ligne, int nombre_lignes);

private:
	 int erreur(int codes_erreurs, char *msg);
	 int ecrire_octets_encodes(FILE *fichier, unsigned char *donnees, int nombre_octets);

	 void rgbe_to_float(float *rouge, float *vert, float *bleu, unsigned char rgbe[4]);
	 void float_to_rgbe(unsigned char rgbe[4], float rouge, float vert, float bleu);
};

#endif



