#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

int main(){
    
    char b[101];
    char *delim;
    int c=0;

    do{

    printf("wish> ");
    fgets(b, 101, stdin);
    delim=strtok(b, " ");
    if(b[strlen(delim)-1]=='\n'){
        b[strlen(delim)-1]='\0';
    }
    
    while(delim!=NULL){
        if(c==1){
            printf("%s", delim);
        }
        delim=strtok(NULL, " "); 
        c++;
    }
    c=0;
    if(strcmp(b, "cd")==0){
    printf("Ejecutando cd\n");
    }else{
        if(strcmp(b, "ls")==0){
        printf("Ejecutando ls\n");
        }else{
            if(strcmp(b, "path")==0){
                printf("Ejecutando path\n");
                }else{
                    printf("Comando erroneo, verifique en la ruta path\n");
                }
            }
        }
    }while(strcmp(b, "exit")!=0);
    return(0);
}
