/*Elabore um programa que a cada 5 segundos exiba na tela a 
mensagem "dentro de um loop". Quando o usuáro digitar CTRL_C 
o programa deverá exibir uma mensagem "saindo..." e sair do programa. 
OBS: Não use nada que não seja da API POSX.*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handlerALRM(int Signum){
    write(1, "Dentro de um loop\n", 18);
}

void handlerINT(int Signum){
    write(1, "\nSaindo...\n", 11);
    exit(0);
}

int main(){
    signal(SIGALRM, handlerALRM);
    signal(SIGINT, handlerINT);

    while(1){
        alarm(5);
        pause();
    }
    
    return 0;
}