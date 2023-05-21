#include "FoncFile.h"


//------------------------Implementation------------------------

//------------------------Implementation------------------------
int read_file0(char *c){
    FILE * fp;
    char line[150]; //pour sauvegarde nos ligne 

    fp = fopen(c, "r");
    if (fp == NULL){
        printf("\npas de fichier");
        return -1;
    }
    while(!feof(fp)){
        fgets(line,150,fp);
        printf("%s:\n", line);
    }
    fclose(fp);
    return 1;
}

int get_nb_lines_file(char *nomF){
    FILE * fp;
    char line[150]; //pour sauvegarde nos ligne 
    int nb = 0;

    fp = fopen(nomF, "r");
    if (fp == NULL){
        printf("\npas de fichier");
        return -1;
    }
    while(!feof(fp)){
        fgets(line,150,fp);
        nb += 1;
        // printf("%s:\n", line);
    }
    fclose(fp);
    return nb;
}

char* getSpeceficLine(char * fileName,int lineNumber){
    FILE *file = fopen (fileName, "r");
    int count = 0;
    if ( file != NULL ) {
        char *line = malloc(256);
        while (fgets (line,256, file) != NULL) {
            if (count == lineNumber) {
                // printf("%s", line);
                fclose (file);
                return line;
            }
            count +=1;
        }
        fclose (file);
    }
    return NULL;
}

// char * read_file(char *file_name){
//     FILE *f=fopen(file_name,"r");
//     if(f==NULL){
//         perror("Probleme ouverture de fichier");
//         exit(EXIT_FAILURE);
//     }
//     int r=0;
//     int cour=0;
//     int dec=0;
//     int i=0;
//     char *st="";
//     while((i=fgetc(f))!=EOF){
//         if(i!='\n'){
//             // printf("car %c\n",i);
//             ++dec;
//         }else{
//             r=fseek(f,cour,SEEK_SET);
//             assert(r==0);
//             st=malloc(sizeof(char)*(dec+2));
//             char *st2=fgets(st,dec+1+1,f);
//             assert(st2!=NULL);
//             st[dec] = '\0';
//             printf("st %s.    .%s.\n",st,st2);
//             free(st);
//             cour=cour+dec+2;
//             dec=0;
//         }
//     }
//     r=fclose(f);
//     if(r!=0){
//     perror("Probleme fermeture de fichier");
//     } 
// }

// char* read_file_get_line(char * fileName){
//     FILE *file = fopen (fileName, "r");
//     if (!file){
//         fprintf(stderr, "Error opening file '%s'\n", fileName);
//         return EXIT_FAILURE;
//   }
//     char *line = NULL;
//     size_t len = 0;
//     ssize_t read;
//     if ( file != NULL ) {
//         // char *line = malloc(256);
//         while ((read = getline(&line, &len, file)) != -1) {
//                 printf("%s", line);
//             // count +=1;
//         } 
//         if (line) {
//             free(line);
//         }
//         fclose (file);
//     }
//     return NULL;
// }

// ssize_t getline(char **restrict buffer, size_t *restrict size,FILE *restrict fp) {
//   register int c;
//   register char *cs = *buffer;
// 
//   if (cs == NULL) {
//     register int length = 0;
//     while ((c = getc(fp)) != EOF) {
//       cs = (char *)realloc(cs, ++length);
//       if ((*(cs + length - 1) = c) == '\n') {
//         *(cs + length) = '\0';
//         *buffer = cs;
//                 break;
//       }
//     }
//     return (ssize_t)(*size = length);
//   } else {
//     while (--(*size) > 0 && (c = getc(fp)) != EOF){
//       if ((*cs++ = c) == '\n')
//         break;
//         }
//     *cs = '\0';
//   }
//   return (ssize_t)(*size=strlen(*buffer));
// }