#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

int main(){
    
    char b[20];

    do{

     printf("wish> ");
     scanf("%s",b);
    }while(strcmp(b, "exit")!=0);
    return(0);
}
