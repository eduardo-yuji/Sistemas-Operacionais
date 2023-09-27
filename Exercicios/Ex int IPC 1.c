/*Construa um “pipeline”. Crie um programa que conecte 4 
processos através de 3 pipes. Utilize fork() para criar vários 
processos. Mande uma mensagem do quarto processo e faça a mensagem 
viajar pelos pipes  até chegar no primeiro processo, e exiba a 
mensagem.*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int pid, pp[2], pp1[2], pp2[2], pp3[2];
    char buffer[1024];
    pipe(pp); pipe(pp1); pipe(pp2); pipe(pp3);
    pid = fork();

    if(pid > 0){
        printf("a");
        printf("f %s", buffer);
        write(pp3[1],"Mensagem\n",9);
        

    }else if(pid == 0){
        printf("b");
        read(pp2[0],buffer,1024);
        write(pp3[1],buffer,7);
        pid = fork();

        if(pid > 0){
            printf("c");
            read(pp1[0],buffer,1024);
            write(pp2[1],buffer,7);

        }else if(pid == 0){
            printf("d");
            read(pp[0],buffer,1024);
            write(pp1[1],buffer,7);
            pid = fork();

            if(pid > 0){
                printf("e");
                
            }else if(pid == 0){
                printf("f");
                read(pp[0],buffer,1024);
                printf("Mensagem recebida do filho: %s", buffer);
            }
        }
    }else{
            printf("Erro na criacao\n");
        }
    return 0;
}

