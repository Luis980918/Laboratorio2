#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

void cd(char*path);
void cmd_ls(char *path);
void procesos(char *path[], int c);



int main(){

    char* param[4];
    char *args[10];
    
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
        printf("%c\n", args[i][strlen(args[i])]);
        if(args[i][strlen(args[i])-1]=='\n'){
            args[i][strlen(args[i])-1]='\0';
            
        }
    }
    

    printf("\n%s\n",b);

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

void cmd_ls(char *path){
    system("ls");
   // return 1;
}
//void procesos2();

void procesos(char *args[], int c){
    args[c-1]=NULL;
    printf("%s\n", args[0]);
    printf("\n%d\n\n\n", strcmp("/usr/bin/ls", args[0]));
    if(strcmp(args[0], "/usr/bin/ls")==0){  
        printf("Son iguales(Ruta)\n");
        
    }
    if(strcmp(args[1], "-l")==0){  
        printf("Son iguales(argumento)\n");
        
    }
    int pid;
    int status;
    pid=fork();
    if(pid<0) printf("Error! no se pudo crear un proceso hijo");
    if (pid==0){
    status=execv(args[0], args);
        if(status<0){
        printf("Error! %s no se reconoce o no se pudo ejecutar", args[1]);
        exit(0);
      }
    }
    //procesos2();
}

/*void procesos2(){
    printf("\n\n\n\n");
    char *args[]={"/usr/bin/ls", "-l", NULL};
    int pid;
    int status;
    pid=fork();
    if(pid<0) printf("Error! no se pudo crear un proceso hijo");
    if (pid==0){
    status=execv(args[0], args);
        if(status<0){
        printf("Error! %s no se reconoce o no se pudo ejecutar", args[1]);
        exit(0);
      }
    }
}*/