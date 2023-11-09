#include <iostream>
#include "thread.h"
#include "mutex.h"
 
#define NUM_THREADS 5
 
using namespace std;
 
int saldo = 1000;
Mutex mutex;  

int AtualizaSaldo(int n)
{
    mutex.lock();
    saldo += n*100;
    cout << "Novo saldo = " << saldo << endl;
    mutex.unlock();
  
}
 
int main()
{
    Thread * threads[NUM_THREADS];

    for(int i = 0; i < 5; i++){
        threads[i] = new Thread(&AtualizaSaldo,i);
    }
    for(int i = 0; i < 5; i++){
        threads[i] -> join(NULL);
    }



    cout << "Saldo final é " << saldo << "." << endl;
}



