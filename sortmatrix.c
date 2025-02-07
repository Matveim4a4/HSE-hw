#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 0
#define MAX 100

int compare_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int compare_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Использование: %s <кол-во строк> <кол-во столбцов>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int *matrix = (int *)malloc(rows * cols * sizeof(int));
    if (!matrix) {
        printf("Error\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < rows * cols; i++) {
        *(matrix + i) = MIN + rand() % (MAX - MIN + 1);
    }

    printf("matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", *(matrix + i * cols + j));
        }
        printf("\n");
    }

    int index, type, isRow;
    printf("0 for row, 1 for col: ");
    scanf("%d", &isRow);
    printf("index: ");
    scanf("%d", &index);
    printf("0 for up, 1 for down: ");
    scanf("%d", &type);

    int (*compare)(const void *, const void *) = (type == 0) ? compare_asc : compare_desc;

    if (isRow == 0) {
        qsort(matrix + index * cols, cols, sizeof(int), compare);
    } else {
        int *temp = (int *)malloc(rows * sizeof(int));
        if (!temp) {
            printf("Error\n");
            free(matrix);
            return 1;
        }
        for (int i = 0; i < rows; i++) {
            *(temp + i) = *(matrix + i * cols + index);
        }
        qsort(temp, rows, sizeof(int), compare);
        for (int i = 0; i < rows; i++) {
            *(matrix + i * cols + index) = *(temp + i);
        }
        free(temp);
    }

    printf("Sort matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", *(matrix + i * cols + j));
        }
        printf("\n");
    }

    free(matrix);
    return 0;
}
