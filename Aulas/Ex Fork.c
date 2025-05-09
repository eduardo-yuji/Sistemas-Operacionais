#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>



int main(){

    int pid, status;
    
    pid = fork();
    
    if(pid < 0){
        printf("Erro na chamada fork\n");
    
    }else if(pid == 0){   
           
        printf("Filho  pid %d \n", getpid());
        while(1);   
       
        exit(5);
    }else{
    
        printf("Pai pid %d \n", getpid());
        wait(&status);
        if(WIFEXITED(status)){
            printf("O programa rodou normalmente com o código %d \n", WEXITSTATUS(status));       
       
        }if(WIFSIGNALED(status)){
            printf("O programa foi morto por um kill %d \n", WTERMSIG(status));       
       
        }
       
       
        printf("Pai rodou filho que terminou com status %d \n",status);
    }
   
    return 0;

}

