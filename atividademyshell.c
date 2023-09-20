#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>


int main(int argc, char *argv[]){
    
    int pid, status;
    char *comando = (char*) calloc(25, sizeof(char));
    pid = fork();

    
    if(pid > 0){
        write(1, "Lista de comandos:\n", 19);
        write(1, "arquivos = Exibe os arquivos do diretorio\n", 42);
        
        while(1){
            write(1, "Digite um comando: ", 19);
            fgets(comando,20,stdin);

            if(strcmp(comando, "arquivos")){
                pid = fork();
                char *args[] = {"-ls",NULL};
                execv("/bin/ls", args);
            }
            if(strcmp(comando, "informacoes")){
                pid = fork();
                char *args[] = {"-ls",NULL};
                execv("/bin/ps", args);
            }
        }
    
    }else{
        printf("Erro na criacao\n");
    }
    
    
    



    return 0;
}