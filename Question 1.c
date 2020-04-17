#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


sem_t wrt;
pthread_mutex_t mutex;
int data = 90;
int numreader = 0;

void *writer(void *wno)
{   
    sem_wait(&wrt);
    data = data+90;
    printf("\nProcess %d modified The Value of Veriable to %d\n",(*((int *)wno)),data);
    sem_post(&wrt);

}
void *reader(void *rno)
{   
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) 
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    
    printf("\nProcess %d read  The Veriable as %d\n",*((int *)rno),data);

    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) 
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{   

    pthread_t read[7],write[7];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    int c1[12]={1,2,3,4,5,6,7,8,9,10,11,12},rc=0,wc=0;

    for(int i = 0; i <12; i++) 
    {
        if(i%2==0){
          pthread_create(&read[rc], NULL, (void *)reader, (void *)&c1[i]);
          rc++;}
 
        else{
         pthread_create(&write[wc], NULL, (void *)writer, (void *)&c1[i]);
         wc++;}
    }
  

    for(int i = 0; i < 6; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 6; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}
