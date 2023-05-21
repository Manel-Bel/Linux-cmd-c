#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "FoncString.h"
#include "Debug.h"
#include "Cmd.h"
#define _GNU_SOURCE



// int ddddd = 3;
// #define nomF = "Cmd.txt";
int main(int argc, char* argv[]){ // lire un efichier en entré
    if(argc < 2){
        printf("Veuiller enter le fichier");
    }else{
        char *nomF = argv[1];
        //-------------initialisation ----------------------
        noeud *root = init();
        noeud *p_actuel = root;
        bool d = executer(nomF,root,p_actuel);
        if(DEBUG) printf("\n%d\n",d);
        printf("\n%d\n",d);
        suppression_sous_arbre_2(root,NULL);
    }
    return 0;
}