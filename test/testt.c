#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
long    ft_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    // printf("%ld\n",tv.tv_sec * 1000 );
    // printf("%ld\n",tv.tv_usec / 1000 );
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
int main()
{
    struct timeval tv,tt;
    long timetaken;
    long start = ft_time();
   // printf("%ld\n " ,start);
    // printf("%ld\n %ld\n" , tv.tv_sec , tv.tv_usec);
    usleep(10000);
    long end = ft_time();
    // printf("%ld\n %ld\n" , tt.tv_sec , tt.tv_usec);
    // timetaken = (tt.tv_sec - tv.tv_sec) * 1000000;
    // timetaken = (timetaken + (tt.tv_usec - tv.tv_usec) )/ 1000;
    printf("%ld\n " ,end  - start);
}