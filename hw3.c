#include <stdio.h>

int gcd(int a, int b)
{
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }

    return gcd(b, a % b);
}

int main() 
{
    int n1, n2;

    printf("Numbers: ");
    scanf("%d %d", &n1, &n2);

    int result = gcd(n1, n2);

    printf("NOD %d and %d = %d\n", n1, n2, result);

    return 0;
}