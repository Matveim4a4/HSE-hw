#include <stdio.h>

int main()
{
    int a = 5;

    int *aPtr = &a;
    int **aaPtr = &aPtr;

    printf("%d\n", *aPtr);
    printf("%d", **aaPtr);
    
    return 0;
}