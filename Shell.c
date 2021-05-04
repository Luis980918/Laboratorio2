#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

void cd(char*comando);
void cmd_ls(char *comando);
char *rutas[100];

void procesos(char *comando[], int c);
void path(char *r[], int c);
int getPath(char *palabra);
int getIndex();



int main(){
    
    char b[1024];
    char *delim;
    char *comando;
    
    for(int j=1;j<100;j++){
        rutas[j]=NULL;
    }

    do{
    int c=0;
    char *args[10];
    printf("wish> ");
    fgets(b, 1024, stdin);
    
    for(int i=0;i<10; i++){
        args[i]=NULL;
    }

    delim=strtok(b, " ");
    if(b[strlen(delim)-1]=='\n'){
      b[strlen(delim)-1]='\0';
    }
    
    while(delim!=NULL){
        if(c==1){
            //printf("%s", delim);
            comando=delim;
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

    if(comando[strlen(comando)-1]=='\n'){
        comando[strlen(comando)-1]='\0';
    }
    if(strcmp(b, "exit")!=0){
        if(strcmp(b, "cd")==0){
            printf("Ejecutando cd\n");
            cd(comando);
            }else{
                if(strcmp(b, "ls")==0){
                printf("Ejecutando ls\n");
                cmd_ls(comando);
                }else{
                    if(strcmp(b, "path")==0){
                        printf("Ejecutando path\n");
                        //procesos(args, c);
                        path(args, c);
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

void cd(char* comando){

    printf("%c\n", comando[strlen(comando)-1]);
    comando[strlen(comando)-1]='\0';
    char *directorio=comando;
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

void cmd_ls(char *comando){
    system("ls");
   // return 1;
}

void procesos(char *args[], int c){
    int contador=0;
    //args[c-1]=NULL;
    rutas[0]="/usr/bin/ls";
    int i=0;
    while(rutas[i]!=NULL){
        if(strcmp(args[0],rutas[i])==0){
            printf("Halowwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
            contador++;
        }
        i++;
        break;
    }
    printf("\n%d\n%d\n",i, contador);
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

void path(char *r[], int c){
    for(int i=0;i<c; i++){
        if(r[i]!=NULL){
            if(getPath(r[i])!=1){
                printf("No existe\n");
                getIndex();
            }
        }
    }
}

int getPath(char *palabra){
    rutas[0]="/usr/bin/";
    rutas[1]="/usr/ban/";
    int i=0;
    int k=0;
    for(int j=0;j<100;j++){
        if(rutas[j]!=NULL){
            k++;
            if(strcmp(rutas[j], palabra)==0){
                i=1;
            }
        }
    }
    //printf("%d\n", k);
    return i;
}

int getIndex(){
    int index=0;
    for(int j=0;j<100;j++){
        if(rutas[j]!=NULL){
            index++;
        }
    }
    printf("%d\n", index);
    return index;
}

