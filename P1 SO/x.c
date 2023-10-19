#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <string.h>

int main(){
    char c[3];
    while(1){
        read(0,c,2);
        if(strcmp(c,"ls")==0){
            char *args[]={"-l",NULL};
            execv("/bin/ls",args);
        }else if(strcmp(c, "ps")==0){
            char *args[]={"-l",NULL};
            execv("/bin/ps",args);
        }else{
            printf("resposta inválida");
        }
    }
    return 0;
}


int contador = 0;

void handlerALRM(int Signum){
    write(1, "\nTempo excedido\n", 17);
    exit(0);
}

void handlerINT(int Signum){
    char *leitura = (char *) calloc(2, sizeof(char));
    char *resposta = "y";
    contador++;
    if(contador == 3){
        write(1, "\nDeseja sair do programa?[y/n]: ", 32);
        alarm(3);
        read(0, leitura, 1);
        if(strcmp(leitura, resposta) == 0){
            exit(0);
        }else{
            contador = 0;
            alarm(0);
        }
    }
}

void handlerTSTP(int Signum){
    int aux = contador + '0';
    write(1, "\nQuantidades de Sinal SIGINT: ", 30);
    write(1, &aux, sizeof(int));
    write(1, "\n", 1);
}

int main(){
    signal(SIGALRM, handlerALRM);
    signal(SIGINT, handlerINT);
    signal(SIGTSTP, handlerTSTP);
    while(1){}
    return 0;
}


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