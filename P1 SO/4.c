#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();

    if (pid == 0){
        pid = fork();
        
        if(pid == 0){
            wait(NULL);
            sleep(1);
            printf("Processo C %d, filho de B %d\n", pid, getpid());
        
        }else{
            wait(NULL);
            sleep(1);
            printf("Processo B %d, filho de A %d\n", pid, getpid());
        }

    }else if(pid >= 0){
        wait(NULL);
        sleep(1);
        printf("Processo A %d\n", pid);

    }else{
        printf("Erro na criação\n");
    }
    return 0;
}