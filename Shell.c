#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

void cd(char*path);
void cmd_ls(char *path);
char *rutas[100];
void procesos(char *path[], int c);



int main(){
    
    char b[1024];
    char *delim;
    char *path;
    char *holi;

    do{
    int c=0;
    char *args[10];
    printf("wish> ");
    fgets(b, 1024, stdin);
    
    


    delim=strtok(b, " ");
    if(b[strlen(delim)-1]=='\n'){
      b[strlen(delim)-1]='\0';
    }
    
    while(delim!=NULL){
        if(c==1){
            //printf("%s", delim);
            path=delim;
        }
        if(c!=0){
            args[c-1]=delim;
        }
        delim=strtok(NULL, " "); 
        c++;
    }

    for(int i=0; i<c-1; i++){
        if(args[i][strlen(args[i])-1]=='\n'){
            args[i][strlen(args[i])-1]='\0';
        }
    }

    if(path[strlen(path)-1]=='\n'){
        path[strlen(path)-1]='\0';
    }
    if(strcmp(b, "exit")!=0){
        if(strcmp(b, "cd")==0){
            printf("Ejecutando cd\n");
            cd(path);
            }else{
                if(strcmp(b, "ls")==0){
                printf("Ejecutando ls\n");
                cmd_ls(path);
                }else{
                    if(strcmp(b, "path")==0){
                        printf("Ejecutando path\n");
                        procesos(args, c);
                        }else{
                            if(strcmp("\0", b)==0){
                                printf("\n");
                            }else{
                                printf("Comando erroneo, verifique en la ruta path\n");
                            }
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

void cmd_ls(char *path){
    system("ls");
   // return 1;
}

void procesos(char *args[], int c){
    args[c-1]=NULL;
    rutas[0]="/usr/bin/ls";
    int i=0;
    while(rutas[i]!=NULL){
        if(strcmp(args[0],rutas[i])==0){
            printf("Halowwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
            break;
        }
        i++;
    }




    int pid;
    int status;
    pid=fork();
    if(pid<0) printf("\nError! no se pudo crear un proceso hijo\n");
    if (pid==0){
    status=execv(args[0], args);
        if(status<0){
        printf("\nError! %s no se reconoce o no se pudo ejecutar\n", args[1]);
        exit(0);
      }
    }
}