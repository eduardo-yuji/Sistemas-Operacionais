#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

const int REP = 5;
char dado;
key_t key;
int shmid, flagsid;
char *data;
int *flags;

int producer(int n)
{
    printf("Producer was born!\n");

    for (int i = 0; i < REP; i++)
    {

        flags[0] = 1;

        while (flags[1] && (flags[3] == 1));
        data[i] = (char)i + 0x61;
        printf("Stored... %c \n", data[i]);
        // flags[3] = turn
        flags[3] = 1;

        flags[0] = 0;
    }

    return n;
}

int consumer(int n)
{
    printf("Consumer was born!\n");

    for (int i = 0; i < REP; i++)
    {

        flags[1] = 1;

        while (flags[0] && (flags[3] == 0));

        dado = data[i];

        data[i] = ' ';
        printf("Consumed... %c \n", dado);

        flags[3] = 0;

        flags[1] = 0;
    }

    return n;
}

int main()
{
    printf("The Producer x Consumer Problem\n");
    int status;

    key = ftok("/home", 'A');                    //  Segmento
    shmid = shmget(key, 1024, 0644 | IPC_CREAT); //
    data = (malloc(5 * sizeof(char)));           //     1
    data = shmat(shmid, (void *)0, 0);           //

    // Peterson
    key = ftok("/home/downloads", 'B');            //  Segmento
    flagsid = shmget(key, 1024, 0644 | IPC_CREAT); //
    flags = (malloc(3 * sizeof(int)));             //     2
    flags = shmat(flagsid, (void *)0, 0);          //

    flags[0] = 1;
    flags[1] = 0;
    flags[3] = 0;

    int pid = fork();

    if (pid == 0)
    {
        producer(5);
    }
    else
    {

        consumer(5);

        shmdt(data);                   // segmento 3
        shmctl(shmid, IPC_RMID, NULL); //

        shmdt(flags);                    // segmento 4
        shmctl(flagsid, IPC_RMID, NULL); //
    }

    return 0;
}
