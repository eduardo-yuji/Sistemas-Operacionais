#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int main(){
    
    int pid,status,teste;

    pid = fork();
    //Fork cria uma cópia que recebe o PID = 0

    if(pid > 0){
        teste=10;
        printf("Processo P1  %i\n",getpid());
        printf("Valor do pai: %d\n", teste);
<<<<<<< HEAD
        wait(&status);
=======
        //wait(&status);
>>>>>>> ec3227380101137ffc8baf7739550bdd0cef47f6
        
    }else if(pid == 0){
        printf("Processo P2  %i\n",getpid());
        printf("Valor do filho: %d\n", teste);
        
<<<<<<< HEAD
        //while(1);
=======
        /*while(1);
>>>>>>> ec3227380101137ffc8baf7739550bdd0cef47f6
        if(WIFEXITED(status)){//if filho executou o exit
            printf("Pos wait: \nWEXITSTATUS = %i\n", WEXITSTATUS(status));
        }else if(WIFSIGNALED(status)){
            printf("Processo foi morto: Sinal = %i\n", WTERMSIG(status));
        }
<<<<<<< HEAD
        exit(105);
=======
        exit(105);*/
>>>>>>> ec3227380101137ffc8baf7739550bdd0cef47f6
        
    }else{
        printf("Erro na criacao\n");
    }

    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> ec3227380101137ffc8baf7739550bdd0cef47f6
