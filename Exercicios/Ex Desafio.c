#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int count = 0;
int timer;

void handlerINT(int Signum){
    char *resp = (char *) calloc(2,sizeof(char));
    write(1, "\nSinal SIGINT\n", 14);
    count++;
    if(count == 3){
        write(1, "\nDeseja sair do programa?(y/n)\n", 31);
        alarm(4);
        read(0, resp, 1);
        if(strcmp(resp,"y") == 0){
            write(1, "Saindo do programa\n", 19);
            exit(0);
        }else{
            count = 0;
            alarm(0);
        }
    }
}

void handlerTSTP(int Signum){
    int aux = count + '0';
    write(1, "\nQuantidades de Sinal SIGINT: ", 30);
    write(1, &aux, sizeof(int));
    write(1, "\n", 1);
}

void handlerALRM(int Signum){
    write(1,"Tempo limite, encerrando programa\n", 34);
    exit(0);
}



int main(){

    signal(SIGALRM, handlerALRM);
    signal(SIGTSTP, handlerTSTP);
    signal(SIGINT, handlerINT);


    while(1){}

    return 0;
}