#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main(){

    int status, resultado_neto, resultado_filho, resultado_pai;
 
    int pid = fork();
    if (pid == 0){
        pid = fork();
        if (pid == 0){ 
            resultado_neto = 5 * 4;
            exit(resultado_neto);
        }else{
            wait(&status);
            resultado_neto = WEXITSTATUS(status);
            resultado_filho = resultado_neto * 3;
            exit(resultado_filho);
        }
    }else{
        wait(&status);
        resultado_filho = WEXITSTATUS(status);
        resultado_pai = resultado_filho * 2;
        printf("\nResultado de 5!: %i\n\n", resultado_pai);
    }
    return 0;
}