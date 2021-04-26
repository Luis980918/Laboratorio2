#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

void cd(char*path);
void cmd_ls(char *path);
void procesos(char *path);
char *args[] = { "/bin/", NULL };


int main(){

    char* param[4];
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
                cmd_ls(path);
                }else{
                    if(strcmp(b, "path")==0){
                        printf("Ejecutando path\n");
                        procesos(path);
                        }else{
                            printf("Comando erroneo, verifique en la ruta path\n");
                        }
                    }
                }
    }
    }while(strcmp(b, "exit")!=0);
    return(0);
}

/*
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
*/

void cd(char* path){
	//preguntamos si el argumento es diferente de null o vacio
  if (path != NULL && path != "") {
    if (chdir(path) != 0){ 
      printf("error: el directorio <%s> no existe \n",path);   
    }
  } else {
      printf("especifica un argumento \"cd\"\n");
  }
  system("pwd");
  //return 1;		
}

/* Función listar el directorio
 */
void cmd_ls(char *path){
    system("ls");
   // return 1;
}

void procesos(char *path){
    //printf("Hola");
    //printf("%s", path);
    
    int pid;
    pid = fork();
    if(pid<0){
        printf("error \n");
    }else if(pid == 0){
        char *ws[1];
        printf("Hola soy Gohan\n");
			execvp(args[0], ws);
			printf("this should't print out\n");
    }else{
        printf("Hola Soy Goku\n");
    }
    }


    /*
    
    void procesos(char *path){
    //printf("Hola");
    //printf("%s", path);
    
    int pid;
    pid = fork();
    if(pid<0){
        printf("error \n");
    }else if(pid == 0){
        printf("Hola soy Gohan\n");
      char *myargs[3];
			myargs[0] = strdup("/bin/");
			myargs[1] = strdup(path);
			myargs[2] = NULL;
			execvp(myargs[0], myargs);
			printf("this should't print out\n");
    }else{
        printf("Hola Soy Goku\n");
    }
    }
    */