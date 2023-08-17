#include <unistd.h> //biblioteca do write
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    long int ra;
    char * nome = (char *) malloc(20*sizeof(char));

    write(1, "Digite seu primeiro nome: ", 26);
    read(0, &nome, 20);
   
   
    write(1, "Nome do aluno: ", 15);
    write(1, nome, 20);    
    write(1, "\n", 1);    

   
   
    write(1, "Digite seu RA: ", 7);
    read(0, &ra , sizeof(long int));
    

   
    write(1, "RA do aluno: ",7);
    write(1, &ra,sizeof(long int));    
    write(1, "\n", 1);    
    
    
    
    
    
}