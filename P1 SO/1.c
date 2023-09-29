#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void handlerALRM(int Signum){
    write(1, "Oi Sefora <3\n", 13);
}

int main(){
    
    signal(SIGALRM, handlerALRM);

    while(1){
        alarm(10);
        pause();
    }

    return 0;
}