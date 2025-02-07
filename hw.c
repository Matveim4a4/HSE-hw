#include <stdio.h>
#include <string.h>

void removeExtraSpaces(char *str) {
    int i, j;
    int s = 0;

    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
            s = 0;
        }
        else if (s == 0) {
            str[j++] = str[i];
            s = 1;
        }
    }

    str[j] = '\0';
}

int main() {
    char input[100];

    fgets(input, sizeof(input), stdin);

    removeExtraSpaces(input);

    printf("%s\n", input);

    return 0;
}