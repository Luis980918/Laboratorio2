#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

void cd(char*comando);
void cmd_ls(char *comando);
void ls(char *r[], int c);
char *rutas[100];

void procesos(char* b, char *comando[], int c);
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
    rutas[0]="/usr/bin/";
    
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
                if(strcmp(b, "path")==0){
                    printf("Ejecutando path\n");
                    path(args, c);
                    for(int i=0;i<100;i++){
                        if(rutas[i]!=NULL){
                            printf("%s\n",rutas[i]);
                        }
                    }
                }else{
                    if(strcmp("\0", b)==0){
                        printf("\n");
                    }else{
                        procesos(b, args, c);
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

void procesos(char* b, char *args[], int c){
    char cat[1024];
    char *arguments[100];
    char *ruta;
    int ejecutar=0;
    for(int i=0; i<100;i++){
        if(rutas[i]!=NULL){
            printf("%s\n", rutas[i]);
            strcpy(cat, rutas[i]);
            ruta=strcat(cat, b);
            if(access(ruta, X_OK)==0){
                    printf("%c\n", ruta[strlen(ruta)]);
                    ruta[strlen(ruta)]='\0';
                    arguments[0]=ruta;
                    for(int i=0; i<c; i++){
                        if(args[i]!=NULL){
                            printf("%s\n", args[i]);
                            arguments[i+1]=args[i];
                        }
                    }
                    int pid;
                    int status;
                    pid=fork();
                    if(pid<0) printf("\nError! no se pudo crear un proceso hijo\n");
                    if (pid==0){
                    status=execv(ruta, arguments);
                        if(status<0){
                        printf("\nComando erroneo, verifique en la ruta path%s\n", args[1]);
                        exit(0);
                    }
                }
            }else{
                printf("\nComando erroneo, verifique en la ruta path%s\n", args[1]);
            }
        }
    }
}

void path(char *r[], int c){
    char * p;
    for(int i=0;i<c; i++){
        if(r[i]!=NULL){
            strcpy(p, r[i]);
            //printf("%s\n", r[i]);
            if(access(r[i], X_OK)==0){
                rutas[i]=p;
                //printf("%s\n", rutas[i]);
            }else{
                printf("La ruta %s no existe\n", r[i]);
            }
        }
    }
}

void ls(char *r[], int c){
    
    int cont=0;
    for(int i=0;i<c;i++){
        if(r[i]!=NULL){
            if(strcmp(r[i], ">")==0){
                cont++;
            }
            if(cont>0 && strcmp(r[i], ">")!=0){
                printf("%s\n", r[i]);
            }
        }
    }
}
