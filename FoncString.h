#ifndef FONCSTRING_H
#define FONCSTRING_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>



struct Chemin
{
    bool absolu;
    int nbMot;
    char ** chemin_tab;
};
typedef struct Chemin Chemin;

struct Ligne
{
    int nbMots;
    char* cmd;
    Chemin * source;
    Chemin *destination;
};
typedef struct Ligne Ligne;


extern Ligne *init_Ligne(char * cmd, char *s, char * d);
extern void free_ligne(Ligne *l);
extern void print_ligne(Ligne *l);
extern int nb_mot(const char *s,char delimiteur);
extern int len_word(const char *w,char delimiteur);
extern char *next_word(char *w,int taille_premier_mot,char delimiteur);
extern char *extract_word(const char *w,int *pl,char delimiteur);
extern int vraiChaine(char *s);
extern Ligne *string_to_line(char * chaine,int nbP,char delimiteur);
extern bool isalphaWord(char *chaine);
extern Chemin* find_path(char *chaine);
extern bool nom_correcte(char *chaine);


#endif
