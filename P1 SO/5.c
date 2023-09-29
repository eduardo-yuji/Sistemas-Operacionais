#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main(){

    int status;
    int resultado_neto, resultado_filho, resultado_pai;
 
    int pid = fork();
    if (pid == 0){
        //criação do processo neto
        pid = fork();
        if (pid == 0){ 
            //calcula 5*4 e da um exit com o resultado
            resultado_neto = 5 * 4;
            exit(resultado_neto);
        }else{
            //processo filho aguarda execução do processo neto
            wait(&status);
            if (WIFEXITED(status)){
                //recebe o valor de saída do neto, multiplica por 3, dando exit com o resultado para o pai
                resultado_neto = WEXITSTATUS(status);
                resultado_filho = resultado_neto * 3;
                exit(resultado_filho);
            }//if processamento de dados do filho
        }//fim do processo filho
    }else{
        //processo pai aguarda execução do processo filho
        wait(&status);
        if (WIFEXITED(status)){
            //recebe o valor de saída do filho, multiplica por 2, e exibindo o resultado final
            resultado_filho = WEXITSTATUS(status);
            resultado_pai = resultado_filho * 2;
            printf("\nResultado de 5!: %i\n\n", resultado_pai);
        }//if processamento de dados do pai
    }//fim do processo pai
    return 0;
}//main