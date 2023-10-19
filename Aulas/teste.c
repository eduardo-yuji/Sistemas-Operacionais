#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

int count = 0;

void handlerCTRLC(int signum) {
    char input[1];
    count++;
    if (count == 3) {
        write(1, "Deseja sair ?\n", 15);
        alarm(3);
        read(0, input, 1);
        if (strcmp(input, "y") == 0)
        {
            exit(0);
        } else {
            count = 0;
            alarm(0);
        }
    }
}

void handlerALARM(int signum) {
    write(1, "Out of time\n", 13);
    exit(0);
}

void handlerCTRLZ(int signum) {
    int aux = count + '0';
    write(1, "Contador ", 9);
    write(1, &aux, 2);
}

int main() {
    signal(SIGALRM, handlerALARM);
    signal(SIGINT, handlerCTRLC);
    signal(SIGTSTP, handlerCTRLZ);
    
    while (1);
    
    return 0;
}