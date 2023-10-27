#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
 
#define SHM_SIZE 1024


const int REP = 5;
char dado;
key_t key;
int shmid,flagsid;
char *data;
sem_t sem;

int counter;
pthread_t p;
pthread_t c;

void *producer()
{
    printf("Producer was born!\n");
 
    int in = 0;   
 
    while(1){   
    
    while(counter == 5);
           
        sem_wait(&sem);

            data[in] = (char) in + 0x61;   
            printf("Stored... %c \n", data[in]);
            
            counter++;       
    
        sem_post(&sem);

        in = ++in % 5;

    }
       
    
}
 
void *consumer()
{
    printf("Consumer was born!\n");
 
    int in = 0;
    
    while(1){   
    
        while(counter == 0);
		   
        sem_wait(&sem);
    
            dado = data[in];

            data[in] = ' '; 

            printf("Consumed... %c \n", dado);

            counter--;   

        sem_post(&sem);
        in = ++in % 5;
    
    }
 
}
 
int main()
{
    counter = 0;
    sem_init(&sem, 0, 1);

    printf("The Producer x Consumer Problem\n");
    int status;
     

    data = (malloc(5*sizeof(char)));               //     1        
   
   
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
       
       
    pthread_join(p, NULL);   
    pthread_join(c, NULL);
 
    
        
    return 0;
    
}    