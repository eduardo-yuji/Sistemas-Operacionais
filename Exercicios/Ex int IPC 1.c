#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    int pid;
    int pp[2];
    pipe(pp);
    int pp2[2];
    pipe(pp2);
    int pp3[2];
    pipe(pp3);
    char buff[10];
    pid = fork();

    if(pid > 0) {

        read(pp3[0], buff, 10);
        printf ("Mensagem recebida pelos pipes: %s",buff);

    } else if(pid == 0) {
        pid = fork();
        if (pid > 0) {

            read(pp2[0], buff, 10);
            write(pp3[1], buff, 10);

        } else if (pid == 0) {
            pid = fork();
            if (pid > 0) {

                read(pp[0], buff, 10);
                write(pp2[1], buff, 10);

            } else if (pid == 0) {

                write(pp[1], "Mensagem\n", 10);

            } else {

                printf("Erro na Criação do Processo\n");

            }


        } else {

            printf("Erro na Criação do Processo\n");
        }

    } else {

        printf("Erro na Criação do Processo\n");

    }

    return 0;
}