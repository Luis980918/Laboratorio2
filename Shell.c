#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

void cd(char*path);

int main(){
    
    char b[1024];
    char *delim;
    char *path;
    int c=0;

    do{

    printf("wish> ");
    fgets(b, 1024, stdin);
    delim=strtok(b, " ");
    if(b[strlen(delim)-1]=='\n'){
        b[strlen(delim)-1]='\0';
    }
    
    while(delim!=NULL){
        if(c==1){
            printf("%s", delim);
            path=delim;
        }
        delim=strtok(NULL, " "); 
        c++;
    }
    c=0;
    if(strcmp(b, "exit")!=0){
        if(strcmp(b, "cd")==0){
            printf("Ejecutando cd\n");
            cd(path);
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
    }
    }while(strcmp(b, "exit")!=0);
    return(0);
}

void cd(char* path){

    printf("%c\n", path[strlen(path)-1]);
    path[strlen(path)-1]='\0';
    char *directorio=path;
    int i=chdir(directorio);
    chdir(directorio);

    printf("%d\n",i);

    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL){
        fprintf(stdout, "Directorio actual: %s\n", cwd);
    }
    else{
        perror("getcwd() error");
    }
}