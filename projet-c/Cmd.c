#include "Cmd.h"
#include "Debug.h"

bool mkdir(noeud *p_actuellement,char *chaine ){ // mkdir prend pas en arg un chemin juste le nom 
    if(nom_correcte(chaine)&& (existe_deja(p_actuellement,chaine) == NULL)){ //si le nom du dossier/fichier correcte et le nom !existe && check_same_name(p_actuellement,chaine)
            if(DEBUG) puts("(MKDIR)le nom est valide");
            noeud * nv = creation_noeud(true,chaine,p_actuellement);
            assert(nv != NULL);
            creation_liste(nv);
            if(DEBUG) printf("(MKDIR) creation d'un nouveau dossier %s, dans le dossier %s.\n",p_actuellement->fils->no->nom,p_actuellement->nom);
            return true;
    }
    return false;
}

void pwd(noeud* p_actuellment){
    if(p_actuellment->racine != p_actuellment){
        pwd(p_actuellment->pere);
        printf("/%s",p_actuellment->nom);
   }
}

noeud* chemin_valide(noeud *p_actuellment,Chemin *chemin,bool fin){ 
    if(DEBUG) printf("(CHEMIN VALIDE) p actuel %s.\n",p_actuellment->nom);
                int i = 0;
                int nb_total = (fin)? (chemin->nbMot):(chemin->nbMot-1);
                liste_noeud *p = p_actuellment->fils;
                liste_noeud *q = NULL;
                if(DEBUG) printf("(CHEMIN VALIDE)nbTotaleMot dans chemin %d.\n",nb_total);
                while(p != NULL && i < nb_total){
                    if(nom_correcte(chemin->chemin_tab[i])){
                        if(strcmp(p->no->nom,chemin->chemin_tab[i]) == 0){ 
                            if(p->no->est_dossier){//on peut jamais ce deplacer dans un fichier 
                                i += 1;
                                q = p;
                                p = p->no->fils; 
                            }else{
                                return NULL;
                            }
                        }else{
                            q = p;
                            p = p->succ;
                        }
                    }else{
                        return NULL;
                    }
                }
                if(i == nb_total){
                    if(q != NULL){
                        if(DEBUG) printf("(CHEMIN VALIDE)chemin valid fin de cd dans %s.\n",q->no->nom);
                        return q->no;
                    }else{
                        if(DEBUG) printf("(CHEMIN VALIDE)q est null on a p ==  %s.\n",p_actuellment->nom);
                        return p_actuellment;
                    }
                }
                return NULL; 
}  

noeud * cd_dernier(noeud *p_actuellment,Chemin * path,bool est_destination){
    noeud *s = cd(p_actuellment,path,false);
    // printf("(CP) nom de source1 %s\n",s->nom);
    if(s != NULL){
        if(est_destination){
            mkdir(s,path->chemin_tab[path->nbMot - 1]);
        }
        noeud *s1 =  existe_deja(s,path->chemin_tab[path->nbMot - 1]);
        if(s1 == NULL) return NULL;
        s = s1;
        if(DEBUG) printf("(CP_DERNIER) nom de source %s.\n",s->nom);
    }
    return s;   
}

noeud *cd(noeud *p_actuellment,Chemin * path,bool fin){
    if(path == NULL ||( path->nbMot == 0 && !path->absolu)){
        if(DEBUG) puts("(CD) chemin vers racine\n");
        return p_actuellment->racine;
    }else{
        if(path->nbMot == 1 && strcmp(path->chemin_tab[0],"..") == 0 ){
            if(DEBUG) printf("(CD)chemin vers le pere %s\n",p_actuellment->pere->nom);
            return p_actuellment->pere;
        }else{
            if(path->absolu){ //on a un path aboslu
                p_actuellment = p_actuellment->racine;
                if(DEBUG) printf("(CD)on a un chemin absolu %s.\n",p_actuellment->nom);
            }// on passe au teste de leur existance au sein de notre arbre
            return chemin_valide(p_actuellment,path,fin);
        }
    }
}


void ls(noeud * p_actuellment){
    puts("----------------- ls -----------------");
    liste_noeud * p = p_actuellment->fils;
    while(p != NULL){
        printf("%s ",p->no->nom);
        p = p->succ;
    }
    puts("\n--------------------------------------");
}

bool touch(noeud *p_actuellement,char *chaine ){ // touch prend pas en arg un chemin
   if(nom_correcte(chaine)&& (existe_deja(p_actuellement,chaine) == NULL)){ //si le nom du dossier/fichier correcte et le nom !existe && check_same_name(p_actuellement,chaine)
            if(DEBUG) puts("(TOUCH)le nom est valide");
            noeud * nv = creation_noeud(false,chaine,p_actuellement);
            creation_liste(nv);
            if(DEBUG) printf("(TOUCH) creation d'un nouveau fichier %s dans le dossier %s.\n",p_actuellement->fils->no->nom,p_actuellement->nom);
            return true;
    }
    return false;
}

void print(noeud *root , int dec) {
    if(root == NULL ){
        return;
    }
    for (int i = 0; i < dec; i++){
        printf("=");
    }
    if(root->est_dossier){
        printf("niveau %d dossier %s : %d fils->pere %s\n",dec,root->nom,nombre_fils(root->fils),root->pere->nom) ;
    }else{
        printf("niveau %d fichier %s : %d fils->pere %s\n",dec,root->nom,nombre_fils(root->fils),root->pere->nom) ;
    }
    if(root->fils != NULL) {
        liste_noeud *l = root->fils;
        while(l != NULL) {
            print(l->no,dec+1);   
            l=l->succ;
        } 
    }
}

bool cp(noeud *p_actuellment,Chemin *source, Chemin* destination){
    if(DEBUG) printf("(CP) p actuel  %s\n",p_actuellment->nom);
    noeud *s = cd_dernier(p_actuellment,source,false);
    if(s != NULL){
        
        if(DEBUG) printf("(CP) nom de source %s.\n",s->nom);
        noeud *d = cd_dernier(p_actuellment,destination,true);
        if(d != NULL){
            if(!d->est_dossier){
                    if(DEBUG) printf("(CP) destination non valide %s, est un fichier\n",d->nom);
                        return false;
                    }
            if(DEBUG) printf("(CP) nom de destination %s\n",d->nom);

            if(d_est_sous_Arbre_s(s,d)){
                if(DEBUG) puts("(CP) pas possible votre destination est un sous arbre de source");
                return false;
            }
            if(!s->est_dossier){
                if(DEBUG) puts("(CP)la source n'est qu'un fichier");
                return touch(d,s->nom);
            } 
            // mkdir(d,s->nom);
            // d = d->fils->no;
            return creation_sous_arbre(d,s->fils,true); 
        }else{
            if(DEBUG) puts("(CP)la destination est null");
        } 
    }
    return false;
}

bool creation_sous_arbre(noeud *d, liste_noeud *source,bool suite){
    if(source != NULL && suite) {
        if( DEBUG) printf("source actuel %s, d actuel %s.\n",source->no->nom,d->nom);
        if(!source->no->est_dossier){
            suite = touch(d, source->no->nom);
        }else{
            suite = mkdir(d, source->no->nom);
            // if(source->no->fils != NULL){
               creation_sous_arbre(d->fils->no,source->no->fils,suite); 
            // }    
        }
        if(source->succ != NULL){
            if( DEBUG) printf("on va voir le succ source actuel %s, d actuel %s.\n",source->no->nom,d->nom);
            creation_sous_arbre(d,source->succ,suite); 
        }
    }
    return suite;
}

bool d_est_sous_Arbre_s(noeud *s, noeud *d){
    while (d != d->racine){
        if(s == d) return true;
        d = d->pere;
    }
    return false;   
}

bool rm(noeud *p_actuellment,Chemin *source) {
    noeud *s = cd_dernier(p_actuellment,source,false);
    if(s != NULL){
        if(DEBUG) puts("(RM) path valide pour source");
        if(d_est_sous_Arbre_s(s,p_actuellment)){
            puts("(ERREUR RM) p est sous arbre de source");
            return false;
        }else{
            if(DEBUG) printf("(RM) nv se de sous arbre %s.\n",s->nom);
            liste_noeud * l = detache_element_liste(s->pere,s);
            if(DEBUG) puts("(RM) print racine");
            suppression_sous_arbre_2(l->no,l);
            // free(l);
            return true;
            }
        }
    //    }
    if(DEBUG) puts("(RM) cd non valide");
    return false;
}

bool mv(noeud *p_actuellment,Chemin *source, Chemin* destination) {
   noeud *s = cd_dernier(p_actuellment,source,false);
    if(s != NULL){
        noeud *d = cd_dernier(p_actuellment,destination,true);
        if(d != NULL){
                if(!d->est_dossier){
                    if(DEBUG) printf("(MV) destination non valide %s, est un fichier\n",d->nom);
                        return false;
                    }
                // d = d1;
                if(d_est_sous_Arbre_s(s,d)){
                    if(DEBUG) puts("(MV) pas possible votre destination est un sous arbre de source");
                    return false;
                }
                liste_noeud *p = detache_element_liste(s->pere,s);
                if(p == NULL){
                    return false;
                }
                liste_noeud *p2 = d->fils;
                d->fils = p;
                p->succ = p2;
                s->pere = d;
                return true;
        }
    }
    return false;
}

bool executer(char *nomF,noeud *root, noeud *p_actuellement){
    bool done = true;
    // Ligne *ligne = NULL;
    FILE *f=fopen(nomF,"r");
    if(f==NULL){
        perror("Probleme ouverture de fichier");
       return false;
    }
    int r=0;
    int cour=0;
    int dec=0;
    int i=0;
    int nbLinge = 0;
    char *chaine="";
    while(((i=fgetc(f))!=EOF) && done){
        // char * chaine = getSpeceficLine(nomF,*i+1);
        if(i!='\n'){
            ++dec;
        }else{
            r=fseek(f,cour,SEEK_SET);
            assert(r==0);
            chaine=malloc(sizeof(char)*(dec+2)); 
            fgets(chaine,dec+1+1,f); //recuperation de toute la ligne
            assert(chaine!=NULL);
            chaine[dec] = '\0'; //st2 == chaine
            cour=cour+dec+1;
            dec=0;
        
            done= switch_cmd(root,&p_actuellement,chaine,&nbLinge);
        }
    }
    r=fseek(f,cour,SEEK_SET);
    assert(r==0);
    chaine=malloc(sizeof(char)*(dec+2)); 
    fgets(chaine,dec+1+1,f); //recuperation de toute la ligne
    assert(chaine!=NULL);
    chaine[dec] = '\0'; //st2 == chaine
    done = switch_cmd(root ,&p_actuellement,chaine,&nbLinge);
    
    r=fclose(f);
    if(r!=0){
        perror("Probleme fermeture de fichier");
    } 
    if(done){
        if(DEBUG) puts("lecture finie sans erreur");
        return true;
    }else{
        return false;
    }
}
bool switch_cmd(noeud *root, noeud **p_actuellement,char * chaine,int *i){
    int x = nb_mot(chaine,' '); // pour avoir le nombre de partit par exemple si nbP> 2 on peut pasexecuter mkdir 
    Ligne *ligne = NULL;
    bool done= true;
    if(x>3 ){
        printf("NOMBRE D'ARGUMENTS NON VALIDE a la ligne %d\n",*i+1);
        free(chaine);
        // return false;
        done = false;
    }
    if(x<= 0){
                // puts("LIGNE vide continue ");
                free(chaine);
                return true;
    }
    if(DEBUG) printf("(SWITCH CMD) chaine %s.\n",chaine);
    ligne= string_to_line(chaine,x,' ');
    free(chaine);
    if(DEBUG) print_ligne(ligne);
    if(ligne != NULL){
        if(strcmp(ligne->cmd,"mkdir") == 0){
                    if((ligne->nbMots > 2) || (ligne->source->nbMot== 1 &&ligne->source->absolu) ){
                        printf("ARGUMENTS NOT VALID FOR mkdir LIGNE numero %d\n",*i+1);
                        done = false;
                    }else{
                        done = mkdir(*p_actuellement,ligne->source->chemin_tab[0]);
                        if(!done){
                            printf("MKDIR FAIlED LIGNE numero %d\n",*i+1);
                        }
                    }
                    // free_ligne(ligne);
                    *i +=1;
                    // return done;
                }
        else if(strcmp(ligne->cmd,"touch") == 0){
                    if((ligne->nbMots > 2) || (ligne->source->nbMot== 1 && ligne->source->absolu) ){
                        printf("ARGUMENTS NOT VALID FOR touch ligne %d\n",*i+1);
                        done = false;
                    }else{
                        done = touch(*p_actuellement,ligne->source->chemin_tab[0]);
                        if(!done){
                            printf("TOUCH FAIlED ligne %d\n",*i+1);
                        }
                    }
                    // free_ligne(ligne);
                    *i +=1;
                    // return done;
                }
        else if(strcmp(ligne->cmd,"pwd") == 0){
                    if((ligne->nbMots > 1) ){
                        printf("TOO MANY ARGUMENTS FOR pwd ligne %d\n",*i+1);
                        done = false;
                    }else{
                        puts("----------------- pwd ----------------");
                        if(*p_actuellement == (*p_actuellement)->racine){
                        printf("/\n");
                        }else{
                            pwd(*p_actuellement); 
                            printf("\n");
                        }
                    }
                    // free_ligne(ligne);
                    *i +=1;
                    // return done;
                }
        else if(strcmp(ligne->cmd,"ls") == 0){
                    if((ligne->nbMots > 1) ){
                         printf("TOO MANY ARGUMENTS FOR ls ligne %d\n",*i+1);
                        done = false;
                    }else{
                        ls(*p_actuellement);
                    }
                    // free_ligne(ligne);
                    *i +=1;
                    // return done;
                }
        else if(strcmp(ligne->cmd,"cd") == 0){
                    if((ligne->nbMots > 2)){
                         printf("TOO MANY ARGUMENTS FOR cd ligne %d\n",*i+1);
                        done = false;
                    }else{
                        noeud *tmp =  cd(*p_actuellement,ligne->source,true);
                        if(tmp != NULL){
                            *p_actuellement = tmp;
                            done = true;
                        }else{
                             printf("CD FAIlED ligne %d\n",*i+1);
                            done = false;
                        }
                    }
                    *i +=1;
                    // free_ligne(ligne);
                    // return done;
                }
        else if(strcmp(ligne->cmd,"cp") == 0){
                    if((ligne->nbMots < 3)) {
                         printf("NOT ENOUGH ARGUMENTS FOR cp ligne %d\n",*i+1);
                        done = false;
                    }else{
                        done = cp(*p_actuellement,ligne->source,ligne->destination);
                        if(!done){
                             printf("CP FAIlED ligne %d\n",*i+1);
                        }
                    }
                    // free_ligne(ligne);
                    *i +=1;
                    // return done;
                }
        else if(strcmp(ligne->cmd,"rm") == 0){
                     if((ligne->nbMots > 2)){
                         printf("OO MANY ARGUMENTS FOR rm ligne %d\n",*i+1);
                        done = false;
                    }else{
                        done = rm(*p_actuellement,ligne->source);
                        if(!done){
                             printf("RM FAIlED ligne %d\n",*i+1);
                        }
                    }
                    // free_ligne(ligne);
                    *i +=1;
                    // return done;
                }
        else if(strcmp(ligne->cmd,"mv") == 0){
                     if((ligne->nbMots < 3)){
                         printf("NOT ENOUGH ARGUMENTS FOR mv ligne %d\n",*i+1);
                        done = false;
                    }else{
                        done = mv(*p_actuellement,ligne->source,ligne->destination);
                        if(!done){
                             printf("MV FAIlED ligne %d\n",*i+1);
                        }
                    }
                    // free_ligne(ligne);
                    *i +=1;
                    // return done;
                }
        else if(strcmp(ligne->cmd,"print") == 0){
                    puts("-----------------print-------------");
                    print(root,0);
                    // free_ligne(ligne);
                    puts("--------------------------------------");
                    *i +=1;
                    // return done;
                }else{
                    printf("CMD INEXISTANTE ligne %d\n",*i+1);
                    done = false;
                    // free_ligne(ligne);
                    // return done;
                    // return false;
                }
            }
    free_ligne(ligne);
    return done;    
}

void suppression_sous_arbre_2(noeud * n,liste_noeud *liste_ou_est_n){
    liste_noeud *p = NULL;
    if(n != NULL){
        if(DEBUG) printf("(Suppression SOUS ARBRE de ) %s.\n",n->nom);
        while(n->fils!= NULL){
            p = n->fils;
            n->fils = n->fils->succ;
            p->succ = NULL;
            if(DEBUG) printf("(SOUS ARBRE)noeud no %s.\n",p->no->nom);
            if(p->no->fils == NULL){
                free_liste_noeud(p);
            }else{
                suppression_sous_arbre_2(p->no,p);
            }
            // free_liste_noeud(p);
        }
        if(DEBUG) printf("(SUPPRESSION SOUS ARBRE)noeud no %s.\n",n->nom);
        free_noeud(n);
        free(liste_ou_est_n);
        // if(DEBUG) printf("(SOUS ARBRE)fils de liste de no vide %s.\n",liste->no->nom);
        // free_liste_noeud(liste);
    }
}

