#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

int main(){
    
    char b[20];
    char *delim;
    do{

     printf("wish> ");
     scanf("%s",b);
    printf("%c\n",b[strlen(b)-1]);
    if(b[strlen(b)+1]==' '){
        b[strlen(b)+1]=',';
        //delim=strtok(b, '\0');
        printf("%s\n", b);
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
    }

    }while(strcmp(b, "exit")!=0);
    return(0);
}
