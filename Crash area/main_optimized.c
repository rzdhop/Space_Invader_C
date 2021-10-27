#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct args_struct_thread args_thread;
struct args_struct_thread
{
    int argc;
};

void *printinga(void* _threadArgs)
{   
    args_thread *i_ptr_to_struct_args = (args_thread*) _threadArgs;

    printf("\nIl y a %d arguments\n", i_ptr_to_struct_args->argc);
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t thread_id[2];
    printf("\nBegin\n");
    args_thread *args = (args_thread*)malloc(sizeof(args_thread));

    printf("Starting thread 1\n");
    args->argc = 1;

    pthread_create(&thread_id[0], NULL, printinga, (void *)args);
    printf("\n join Thread 1");
    pthread_join(thread_id[0], NULL);
    
    return 0;
}