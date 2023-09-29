#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

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