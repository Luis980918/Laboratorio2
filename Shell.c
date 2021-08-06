#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

void cd(char*comando);
void cmd_ls(char *comando);
void ls(char *r[], int c);
char *rutas[100];

int redir2 (char * b, int c);
int procesos(char* b, char *comando[], int c, char* cdir);
void path(char *r[], int c);
void cmds(char* b);
int getPath(char *palabra);
int getIndex();



int main(int argc, char* argv[]){


    /*if(argv[1]){
        FILE* flujo=fopen(argv[1], "rb");
	    char cadena[100];
	
        while(feof(flujo)==0){
            fscanf(flujo, "%s\n", cadena);
            printf("%s\n", cadena);
        }
    }*/
    

    char b[1024];
    char *delim;
    char *comando;
    char cdir[1024];
    
    
    for(int j=1;j<100;j++){
        rutas[j]=NULL;
    }
    rutas[0]="/usr/bin/";
    
    do{
        
    int c=0;
    char *args[10];
    printf("wish> ");
    fgets(b, 1024, stdin);

    strcpy(cdir, b);

    //tokenizo(b, argsz);//separo por argz
    
    for(int i=0;i<10; i++){
        args[i]=NULL;
    }

    
    delim=strtok(b, " ");
    if(b[strlen(delim)-1]=='\n'){
        b[strlen(delim)-1]='\0';
    }
                 
    while(delim!=NULL){
        if(c==1){
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
    

    if(strcmp(b, "exit")!=0){
        if(strcmp(b, "cd")==0){
            printf("Ejecutando cd\n");
            cd(comando);
            }else{
                if(strcmp(b, "path")==0){
                    printf("Ejecutando path\n");
                    path(args, c);
                }else{
                    if(strcmp("\0", b)==0){
                        printf("\n");
                    }else{
                        procesos(b, args, c, cdir);
                    }
                }
            }
        }
    }while(strcmp(b, "exit")!=0);
    return(0);
}

void cmds(char* cadenaCompleta){
    char *token = strtok(cadenaCompleta, " & ");
    if(token != NULL){
        while(token != NULL){
            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
            printf("Token: %s\n", token);
            token = strtok(NULL, " & ");
            if(token != NULL){
                int c=0;
                char *args[10];
                printf("wish> ");
                char b[1024];
                strcpy(b, token);
                char *delim;
                char *comando;
                char cdir[1024];
                strcpy(cdir, b);
                for(int i=0;i<10; i++){
                    args[i]=NULL;
                }
                
                delim=strtok(b, " ");
                if(b[strlen(delim)-1]=='\n'){
                    b[strlen(delim)-1]='\0';
                }
                            
                while(delim!=NULL){
                    if(c==1){
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
                int returnStatus=0;
                waitpid(procesos(b, args, c, cdir),&returnStatus,0);                        
                if (returnStatus == 1){
                    printf("Error xd");    
                }
            }
        }
    }
}

void cd(char* comando){
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

int procesos(char* b, char *args[], int c, char* cdir){
    char cat[1024];
    char *arguments[100];
    char *ruta;
    int ejecutar=0;
    int pid;
    if(strstr(cdir, ">")!=NULL){
        pid = redir2(cdir, c);
    }else{
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
                                arguments[i+1]=args[i];
                            }
                        }
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
    return pid;
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

int tokenizo(char * b, char * argsz[]){

    //para redir
    int u = b[strlen(b)];  
    int v;
    for(v=0;v<u;v++) argsz[v]=NULL;
    strtok(b," "), v=0; 
    argsz[v]=b; 
    while((argsz[++v]=strtok(NULL," "))!=NULL);
    //para redir
       
}

int redir2 (char * b, int c) {
char *argsx[15];
char *argsz[10];

int rc = fork();
		if(rc < 0){
			fprintf(stderr, "fork failed\n");
			exit(1);
		}else if(rc == 0){
            char *arc;
            
            if(arc = strtok(b, ">")){
            arc = strtok(NULL, "> ");
                  
                if(arc[strlen(arc)-1]=='\n'){
                    arc[strlen(arc)-1]='\0';
                    
                }

            int i;
            for(i=0;i<strlen(b);i++) argsz[i]=NULL;
            strtok(b," "), i=0; 
            argsz[i]=b; 
            while((argsz[++i]=strtok(NULL," "))!=NULL);

            int err = open(arc, O_WRONLY|O_CREAT|O_TRUNC,0666);
            
                       
            if (- 1 == dup2(err, fileno(stdout))){
                perror("No se pudo"); 
                return 225;
            }
           
            execvp(argsz[0], argsz);

		}else{
			int rc_wait = wait(NULL);
		}

        }

    return rc;

     
}