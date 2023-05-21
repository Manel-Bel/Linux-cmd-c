#ifndef CMD_H
#define CMD_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "FoncString.h"
#include "Structure.h"

#define MaxLen = 100;


//  void printNoeud(noeud *n);
extern bool mkdir(noeud *p_actuellement,char *chaine);
extern void pwd( noeud* p_actuellment);
extern noeud* chemin_valide(noeud *p_actuellment,Chemin *chemin,bool fin);
extern noeud *cd(noeud *p_actuellment,Chemin * pathn,bool fin);
extern noeud * cd_dernier(noeud *p_actuellment,Chemin * path,bool est_destination);
extern void ls(noeud * p_actuellment);
extern bool touch(noeud *p_actuellement,char *chaine );
extern void print (noeud *n, int inc);
extern bool cp(noeud *p_actuellment,Chemin *source, Chemin* destination);
extern bool creation_sous_arbre(noeud *d, liste_noeud *source,bool suite);
extern bool d_est_sous_Arbre_s(noeud *s, noeud *d);
extern bool rm(noeud *p_actuellment,Chemin *source);
extern bool mv(noeud *p_actuellment,Chemin *source, Chemin* destination);
extern bool executer(char *nomF,noeud *root, noeud *p_actuellement);
extern void suppression_sous_arbre_2(noeud * n,liste_noeud *liste_ou_est_n);
extern bool switch_cmd(noeud *root, noeud **p_actuellement,char * chaine,int *i);
#endif