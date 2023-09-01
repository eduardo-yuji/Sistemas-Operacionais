#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int main(){
    
    int pid,status;

    pid = fork();

    if(pid > 0){
        printf("Processo P1, Pai  %i\n",getpid());
        wait(&status);
    }else if(pid == 0){
        sleep(1);
        printf("Processo P2, Filho de P1  %i\n",getpid());
        sleep(1);
 	wait(&status);
        pid = fork();
 	wait(&status);
 	if(pid == 0)
        printf("Processo P3, Filho de P2  %i\n",getpid());
    }else{
        printf("Erro na criacao\n");
    }

    return 0;
}
