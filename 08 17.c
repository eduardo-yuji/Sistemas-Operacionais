#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char *msg = "Hello World\n";
int contador = 0;

void handlerINT(int signum){

    write(1, "Sinal de Alarme cancelado\n", 27);
    alarm(0);

}

void handlerTSTP(int signum){
    
    contador++;
    write(1, "ctrl z recebido\n", 16);
    
    int aux = contador + '0';
    write(1, "contador: ", 11);
    write(1, &aux, 1);
    write(1, "\n", 1);
    
    if(contador == 3) exit(0);

}

void handlerALRM(int signum){

    write(1, "Sinal de alarme\n",16);

    while(1){alarm(3);pause();}
    

}



int main(){ 

    signal(SIGALRM, handlerALRM);
    signal(SIGTSTP, handlerTSTP);
    signal(SIGINT, handlerINT);

    //read(0, msg, 20);
    //malloc
    //write(1, msg,20);

    alarm(2);
    pause();
    

    return 0;
}