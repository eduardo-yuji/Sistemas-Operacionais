#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int main(){
    
    int pid;
    int pp[2];
    char buffer[1024];
    pipe(pp);

    pid = fork();
    if(pid > 0){
    	write(pp[1],"Hello\n",7);
    
        
    }else if(pid == 0){
	read(pp[0],buffer,1024);
	printf("Mensagem recebida do filho: %s", buffer);	
	
    }else{
        printf("Erro na criacao\n");
    }

    return 0;
}
