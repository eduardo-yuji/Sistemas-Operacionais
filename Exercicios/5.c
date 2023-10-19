#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char const argv[])
{
    int pid, status, inicial;
    inicial = 5;
    pid = fork();
    if(pid > 0) {
        wait(&status);
        inicial = WEXITSTATUS(status);
        inicial = inicial * 1;
        printf("%d\n", inicial);
    }
    else if(pid == 0) {
        pid = fork();
        if(pid > 0) {
            wait(&status);
            inicial = WEXITSTATUS(status);
            inicial = inicial * 2;
            exit(inicial);
        }
        else if(pid == 0 ) {
            pid = fork();
            if(pid > 0) {
                wait(&status);
                inicial = WEXITSTATUS(status);
                inicial = inicial * 3;
                exit(inicial);
            }
            else if(pid == 0 ) {
                pid = fork();
                if(pid > 0) {
                    inicial = inicial * 4;
                    exit(inicial);
                }
            }
        }
    }
    return 0;
} 
