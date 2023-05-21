#include "Structure.h"


//------------------fonc liste-------------------
void creation_liste(noeud * n){
    liste_noeud *liste = malloc(sizeof(liste_noeud));
    assert(liste != NULL);
    liste->no = n;
    liste->succ = n->pere->fils;
    n->pere->fils = liste;
}
//------------recherche dans une liste---------------------
noeud *existe_deja(noeud *p_actuellment,char *nom){
    // puts("----------------Fonc existe ------------");
    liste_noeud *p = p_actuellment->fils;
    while( p != NULL){
        if(strcmp(nom,p->no->nom) == 0){
            if(DEBUG) printf("(Fonc EXISTE) Ce nom %s existe deja\n",nom);
            return p->no;
        }
        p = p->succ;
    }
    if(DEBUG) printf("(Fonc EXISTE)pas de fichier portant le nom %s.\n",nom);
    return NULL;
}

int nombre_fils(liste_noeud *liste_fils) {
  int nbr = 0 ;
  liste_noeud *l = liste_fils ;
  while (l != NULL){
    ++nbr ; 
    l = l->succ ;
  }
  return nbr;
}

//--------------affichage d'une liste -------------------------
void print_list(noeud * n){
  liste_noeud *l = n->fils ;
  while(l!=NULL){
    if(l->no->est_dossier){
      printf(" %s (D) ",l->no->nom);
    }else{
      printf(" %s (F) ",l->no->nom);
    }
    l = l->succ ;
  }
  printf("\n");
}

//----------------calcule nb fils ---------------
liste_noeud * detache_element_liste(noeud *pere,noeud* element){
    if(DEBUG) printf("(DETACHE LISTE) pere %s., element %s.\n",pere->nom,element->nom);
    liste_noeud *prec =NULL;
     liste_noeud *l =pere->fils;
    if(pere->fils != NULL){
        while(l->no != element){
            prec = l;
                l = l->succ;
            }
        if(prec == NULL){ // suppresion du premier element dans fils de pere
            pere->fils = l->succ; // le prochain element
        }else{
            prec->succ = l->succ;
        }
        l->succ = NULL;
    }
      return l;
}

void free_liste_noeud(liste_noeud *liste){
    if(liste != NULL){
        free_noeud(liste->no);
        free(liste);
    }
}

//--------------------------------------------------------------------------------------

noeud *init(){
    noeud *Root = malloc(sizeof(noeud));
    assert(Root != NULL);
    Root->est_dossier = true;
    Root->pere = Root;
    Root->racine = Root;
    Root->fils = NULL;
    memmove(Root->nom,"",1);
    return Root;
}

noeud * creation_noeud(bool estDossier, char * nom, noeud * pere){
    noeud * nv = malloc(sizeof(noeud));
    assert(nv != NULL);
    nv->est_dossier = estDossier;
    strcpy(nv->nom,nom);
    nv->fils = NULL;
    nv->pere = pere;
    nv->racine = pere->racine;
    return nv;
}

void free_noeud(noeud * n){
    if(DEBUG) puts("freeenoeud");
    if(n != NULL){
    //    free(n->nom);
    // puts("fnoooo");
       n->pere = NULL;
       n->racine = NULL;
       n->fils = NULL;
    }
    free(n);
}




