#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *routine(void *args)
{
    // for (int i =0;i < 10000;i++)
    // {
    //     printf("%d\n", i);
    // }
    usleep(500000);
}

int main()
{
    pthread_t t1;
    printf("%d\n", 1);
    pthread_create(&t1,NULL, routine, NULL);
    
    usleep(500000);
    pthread_join(t1, NULL);
    
    // for (int i =0;i < 10000;i++)
    // {
    //     printf("%d\n", i);
    // }
}