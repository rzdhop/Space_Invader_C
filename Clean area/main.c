#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void *printinga(void *arg)
{   
    //CODE du thread
    printf("\n%.*d",1, 5);
    
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t thread_id;

    printf("\nBegin\n");

    printf("Starting thread 1\n");
    pthread_create(&thread_id, NULL, printinga, NULL);
    printf("\n join Thread 1");
    pthread_join(thread_id, NULL);

    pthread_cancel(thread_id);
    return 0; 
}