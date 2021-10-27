#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct args_func
{
    int space;
    int sleepTime;
};
struct args_ptr_struct_thread
{
    struct args_func *ptr;
};

void *printinga(void* _args_ptr_struct_thread_param)
{   
    struct args_ptr_struct_thread *i_ptr_to__args_func = (struct args_ptr_struct_thread*) _args_ptr_struct_thread_param;
    struct args_func *args = (struct args_func*) i_ptr_to__args_func->ptr;
    
    //sleep(args.sleepTime);
    printf("\nAH :%*s a", args->space, "");
    
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t thread_id[2];
    printf("\nBegin\n");
    struct args_ptr_struct_thread args_thread;
    struct args_func _struct_args_func;

    printf("Starting thread 1\n");
    _struct_args_func.space = 2;
    _struct_args_func.sleepTime = 1;
    args_thread.ptr = &_struct_args_func;
    pthread_create(&thread_id[0], NULL, printinga, &args_thread);
    printf("\n join Thread 1");
    pthread_join(thread_id[0], NULL);
    
    return 0;
}