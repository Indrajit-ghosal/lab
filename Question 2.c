#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include<sys/wait.h>

sem_t wrt;
pthread_mutex_t mutex;
int data = 90,rc=0,wc=0 ,temp;
int numreader = 0;
pthread_t read[7],write[7];

void *writer(void *wno)
{   
    temp=data;
    temp=temp+90;
    printf("\nProcess %d modified The Value of Veriable to %d\n",(*((int *)wno)),temp);
    wait(NULL);
    wait(NULL);
    data=temp;
    printf("\nProcess %d Writed The Value of Veriable to %d\n",(*((int *)wno)),data);

}

int main()
{   


    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    int c1[6]={1,2,3,4,5,6};

    for(int i = 0; i <6; i++) 
    {
  
         pthread_create(&write[wc], NULL, (void *)writer, (void *)&c1[i]);
         wc++;
      }
  
    for(int i = 0; i < 6; i++) {
    
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}
