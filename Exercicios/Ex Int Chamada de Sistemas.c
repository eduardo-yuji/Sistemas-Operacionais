/*Pesquise o funcionamento das funções read e write da API posix 
do linux e faça um programa, usando apenas essas funções para 
I/O, que receba o nome e o ra de um aluno e imprima na tela.

OBS: RA não pode ser  uma string*/

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    long int ra;
    char *nome = (char *) calloc(20,sizeof(char));

    write(1, "Digite seu primeiro nome: ", 26);
    read(0, nome, 20);
   
    write(1, "Digite seu RA: ", 15);
    read(0, &ra , sizeof(long int));
    write(1, "\n", 1);  
    

    write(1, "Nome do aluno: ", 15);
    write(1, nome, 20);    
    
    write(1, "RA do aluno: ", 14);
    write(1, &ra,sizeof(long int));    
    write(1, "\n", 1);    
    
    return 0;
}