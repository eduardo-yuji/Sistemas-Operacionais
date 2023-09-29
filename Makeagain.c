#include <unistd.h>
#include <signal.h>
#include <string.h>

int main(){
    long int ra;
    char *nome = (char*)calloc(20,sizeof(char));
    
    write(1, "Digite seu nome: ", 17);
    read(0, nome, 20);

    write(1, "Digite seu RA: ", 15);
    read(0, ra, 10);
    
    write(1, nome, 20);
    write(1, ra, 10);


    return 0;
}