#ifndef LISTE_H
#define LISTE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Debug.h"

struct noeud {
    bool est_dossier;
    char nom[100];
    struct noeud * pere ;
    struct noeud * racine ;
    struct liste_noeud * fils ;
};

struct liste_noeud {
    struct noeud * no ;
    struct liste_noeud * succ ;
};

typedef struct noeud noeud ;
typedef struct liste_noeud liste_noeud ;


extern void creation_liste(noeud * n);
extern noeud *existe_deja(noeud *p_actuellment,char *nom);
extern int nombre_fils(liste_noeud *liste_fils) ;
extern void print_list(noeud * n);
extern liste_noeud * detache_element_liste(noeud *pere,noeud* element);
extern void free_liste_noeud(liste_noeud *liste);

extern noeud *init();
extern noeud * creation_noeud(bool estDossier, char * nom, noeud * pere);
extern void free_noeud(noeud * n);

#endif