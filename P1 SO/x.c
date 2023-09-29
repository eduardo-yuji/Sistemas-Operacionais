#include <unistd.h> //biblioteca do write
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main()
{
    long int RA;
    char nome = (char)malloc(20 * sizeof(char));

    write(1, "\nDigite seu Ra: ", 17);
    read(0, &RA, sizeof(long int));

    write(1, "\nDigite seu nome: ", 19);
    read(0, nome, 20);

    write(1, "\nSeu Ra: ", 10);
    write(1, &RA, sizeof(long int));

    write(1, "\nSeu nome: ", 12);
    write(1, nome, 20);

    write(1, "\n\n", 2);
    return 0;
}