#include <stdio.h>

void tree(int h) 
{
    int i, j, s;

    for (i = 1; i <= h; i++) {
        s = h - i;

        for (j = 1; j <= s; j++) {
            printf(" ");
        }

        for (j = 1; j <= 2 * i - 1; j++) {
            printf("#");
        }

        printf("\n");
    }

    for (i = 1; i <= h / 3; i++) {
        for (j = 1; j <= h - 1; j++) {
            printf(" ");
        }

        printf("#\n");
    }
}

int main() 
{
    int h;

    printf("Введите высоту ёлочки: ");
    scanf("%d", &h);

    if (h <= 0) {
        printf("Высота должна быть положительным числом!\n");
        return 1;
    }

    tree(h);

    return 0;
}