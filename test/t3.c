#include <stdio.h>
#ifdef SIZE
// This block will NOT be compiled
int a = SIZE;
printf("DEBUG: SIZE is defined. 'a' is initialized.\n");
#else
// This block WILL be compiled
printf("DEBUG: SIZE is NOT defined.\n");
int a = -1; // 'a' is initialized to -1 because SIZE is not defined
#endif
int main()
{
    printf("%d\n", a);
}
