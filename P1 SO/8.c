#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    int pid, i = 1;
    pid = fork();
    if(pid == 0){
        i = 100;
        printf("Processo Filho - pid: %d\n", getpid());
        printf("Valor no processo Filho: %d\n", i);
    }else if(pid >= 0){
        
        printf("Processo Pai - pid: %d\n", getpid());
        printf("Valor no processo Pai: %d\n",i);
    }else{
        printf("Erro na criação\n");
    }



    return 0;
}