/*#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    char *ler = (char*) calloc(2,sizeof(char));
    char *comp = "y";
    write(1,"Deseja ver os programas em execução?[y/n] ",44);
    read(0,ler, sizeof(char));
    if(strcmp(ler, comp) == 0){
        execlp("ps", "ps", "aux", NULL);
		execlp("ls", "ls", "-aux", NULL);
    }else{
        exit(0);
    }
    return 0;
}
*/

#include <unistd.h>
void main(){	execlp("ls", "ls", "-s", NULL);}



/*
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int pid = fork();
	
	if (pid < 0)
	{
		printf("Error");
		exit(1);
	} else {
		
		execlp("ps", "ps", "aux", NULL);
		perror("\nerro ao executar o comando ps\n");
		exit(1);
	}
	return 0;

}*/