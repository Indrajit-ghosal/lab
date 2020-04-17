#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include<sys/wait.h>

sem_t wrt;
pthread_mutex_t mutex1,mutex2,mutex3;
int data1= 90,data2=100,data3=2000,wc=0;
int numreader = 0;
pthread_t pc[3];

void *pc1(void *wno)
{   
  pthread_mutex_lock(&mutex1);
  data1=data1+10;
  wait(NULL);
  pthread_mutex_lock(&mutex2);
  data2=data2+data1;
  printf("\nCritical Section OF thread 1 Update\n");
  //pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);
}
void *pc2(void *wno)
{   
  pthread_mutex_lock(&mutex2);
  data2=data2+210;
  wait(NULL);
  pthread_mutex_lock(&mutex3);
  data2=data2+data1;
  printf("\nCritical Section OF thread 2 Update\n");
  pthread_mutex_unlock(&mutex2);
  pthread_mutex_unlock(&mutex3);
}
void *pc3(void *wno)
{   
  pthread_mutex_lock(&mutex3);
  data3=data3+100;
  wait(NULL);
  pthread_mutex_lock(&mutex1);
  data2=data2+data1+data3;
  printf("\nCritical Section OF thread 3 Update\n");
  pthread_mutex_unlock(&mutex3);
  pthread_mutex_unlock(&mutex1);
}
int main()
{   


    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_mutex_init(&mutex3, NULL);
    sem_init(&wrt,0,1);

    int c1[6]={1,2,3};

         pthread_create(&pc[wc], NULL, (void *)pc1, (void *)&c1[wc]);
         wc++;
         pthread_create(&pc[wc], NULL, (void *)pc2, (void *)&c1[wc]);
         wc++;
         pthread_create(&pc[wc], NULL, (void *)pc3, (void *)&c1[wc]);
         wc++;
  
    for(int i = 0; i < 6; i++) 
    {
    
        pthread_join(pc[i], NULL);
    }

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    pthread_mutex_destroy(&mutex3);
    sem_destroy(&wrt);

    return 0;
    
}
