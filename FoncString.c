#include "FoncString.h"
#include "Debug.h"

//------------------------Implementation------------------------

Ligne *init_Ligne(char * c, char *s, char * d){
        Ligne* l = malloc(sizeof(Ligne));
        l->source = NULL;
        l->destination = NULL;
        l->nbMots = 0;
        l->cmd = malloc((strlen(c)+1)* sizeof(char));
        assert(c != NULL);
        strcpy(l->cmd,c);
        // printf("c == %s. cmd %s.",c,l->cmd);
        l->nbMots += 1;
        if(s != NULL){
            l->source = find_path(s);
            l->nbMots += 1;
        }
        if(d != NULL && l->source != NULL){
            l->destination = find_path(d);
            l->nbMots += 1;
        }
        return l;
}

void free_chemin(Chemin *c){
    for(int i = c->nbMot -1; i>=0;--i){
        if(DEBUG) printf("(FREE CHEMIN) %s.\n",c->chemin_tab[i]);
        free(c->chemin_tab[i]);
    }
    free(c->chemin_tab);
    free(c);
}

void free_ligne(Ligne *l){
    if(l != NULL){
        if(l->cmd != NULL){
            if(DEBUG) printf("(FREE LIGNE CMD) %s\n",l->cmd);
            free(l->cmd);
        }
        if(l->source != NULL){
            if(DEBUG) printf("(FREE LIGNE source)\n");
           free_chemin(l->source);
        }
        // free(l->source);
        if(l->destination != NULL){
            if(DEBUG) printf("(FREE LIGNE DESTINATION)\n");
           free_chemin(l->destination);
        }
        // free(l->destination);
        free(l);
    }
}

void print_ligne(Ligne *l){
    if(l != NULL){
        printf("\nLa commande : %s.",l->cmd);
        if(l->source != NULL){
            printf("\nLa source : ");
            if(l->source->absolu){
                printf("/");
            }
            for(int i = 0; i< l->source->nbMot;i++){
                printf("%s. ",l->source->chemin_tab[i]);
            }
        }   
       if(l->destination != NULL){
            printf("\nLa destination : ");
            if(l->destination->absolu){
                printf("/");
            }
            for(int i = 0; i< l->destination->nbMot;i++){
                printf("%s. ",l->destination->chemin_tab[i]);
            }
        }    
    } 
    printf("\n");   
}


int nb_mot(const char *s,char delimiteur){ // la ligne se compose au max de 3 parties 
    int nbMot = 0;
    size_t i = 1;
    while(i <=strlen(s)){
        if(s[i-1] != delimiteur && (s[i] == '\0' ||s[i] == delimiteur)){  // on cherhce la fin du mot
            nbMot++;
        }
        i++;
    }
    return nbMot;
}

int len_word(const char *w,char delimiteur){ //une chaine d'un debut normal jusqu'au delimiteur 
    int lenMot = 0;
    if(w[0] != ' '){
         while(w[lenMot] != delimiteur && w[lenMot] != '\0' && w[lenMot] != '\n'){
                lenMot++;
            }
    }
    return lenMot;
}

char *extract_word(const char *w,int *pl,char delimiteur){
    // printf("\nla chaine actuelle %s.\n",w);
    *pl = 0;
    if(w != NULL && strcmp(w,"") != 0){
        *pl = len_word(w,delimiteur);
        char *pw  = malloc(((*pl) +1));
        strncpy(pw,w,*pl);
        pw[*pl] = '\0';
        if(DEBUG) printf("le mot extrait apres le slash %s.\n",pw);
        return pw;  
    }
    return NULL;  
}

char *next_word(char *w,int taille_premier_mot,char delimiteur){
    if(w[taille_premier_mot] != '\0'){
        return w+taille_premier_mot+vraiChaine(w+taille_premier_mot);
    }
    else{
        return NULL;
    }
}

int vraiChaine(char *s){ // on commance pas par des espace
    int comp = 0;
    while((*s == ' ') && *s != '\0' && *s != '\n'){
        comp+=1;
        ++s;
    }
    if(comp == 0){
        return 1;
    }
    return comp;
}

Ligne *string_to_line(char * chaine,int nbP,char delimiteur){ // on suppose les conditions de 0 et > 3 sont deja faites
    // if(strcmp(chaine," ") || strcmp(chaine,"\n") ){}
    Ligne *l = NULL;
    char * p = NULL;
    char *s = NULL;
    char *d = NULL;
    int nb  = 0;
    int nb_espace = 0;
    if(chaine[0]== ' ' ) nb_espace = vraiChaine(chaine);
    chaine = chaine+nb_espace ;
    char *c = extract_word(chaine,&nb, delimiteur);
    if(nbP > 1){
        p = next_word(chaine,nb,delimiteur);
        s = extract_word(p,&nb, delimiteur); 
        if(nbP >2){
            p = next_word(p,nb,delimiteur);
            d = extract_word(p,&nb, delimiteur);
        }
    }
    l = init_Ligne(c,s,d);
    free(s);
    free(d);
    free(c);
    return l;
}

//--------pour renvoyer un tableau de mot du chemin a partir de la chaine avec /ll/kk/
Chemin* find_path(char *chaine){ // la chaine c'est soit la source soit la destination
    Chemin *s = malloc(sizeof(Chemin));
    s->absolu = false;
    char *ch = chaine;
    if(ch[0] == '/'){ //on a un chemin absolu
        s->absolu = true;
        ch = ch +1;
    }
    int nb = nb_mot(ch,'/');
        if(DEBUG) printf("(FIND PATH )nombre de mot dans le chemin %s. %d.\n",chaine,nb);
        s->chemin_tab = malloc(nb*sizeof(char*));
        s->nbMot = 0;
        int taille = 0;
        for(size_t i = 0; i< nb;i++){
            s->chemin_tab[i] = extract_word(ch,&taille,'/');
                s->nbMot += 1;
                ch = next_word(ch,taille,'/');
        }
        // free(chaine);
        return s;
}

bool nom_correcte(char *chaine){
    return ((strcmp(chaine,"")!= 0) && (strlen(chaine) < 100) && isalphaWord(chaine) );
}

bool isalphaWord(char *chaine){
    int n = strlen(chaine);
    for(int i=0 ;i<n ;i++){
        if(!isalnum(chaine[i])){
            return false;
        }
    }
    return true;
}
