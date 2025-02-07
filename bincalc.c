#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Binary;  // Псевдоним для строки, представляющей двоичное число

// Функции для двоичных операций
Binary add(Binary a, Binary b);
Binary subtract(Binary a, Binary b);
Binary shift_left(Binary a, int count);
Binary shift_right(Binary a, int count);

// Указатели на функции для выполнения операций
Binary (*op_func)(Binary, Binary);
Binary (*shift_func)(Binary, int);

// Функция сложения двух двоичных чисел
Binary add(Binary a, Binary b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int len = (len_a > len_b ? len_a : len_b) + 1;  // Дополнительный бит для переноса
    Binary result = (Binary)malloc(len + 1);  // Выделяем память для результата
    result[len] = '\0';

    int carry = 0, sum, i = len_a - 1, j = len_b - 1, k = len - 1;

    while (i >= 0 || j >= 0 || carry) {
        int bit_a = (i >= 0) ? (a[i--] - '0') : 0;
        int bit_b = (j >= 0) ? (b[j--] - '0') : 0;

        sum = bit_a + bit_b + carry;
        result[k--] = (sum % 2) + '0';
        carry = sum / 2;
    }

    return result + (result[0] == '0');  // Убираем ведущий 0, если есть
}

// Функция вычитания (a > b)
Binary subtract(Binary a, Binary b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    Binary result = (Binary)malloc(len_a + 1);
    result[len_a] = '\0';

    int borrow = 0, i = len_a - 1, j = len_b - 1, diff;

    while (i >= 0) {
        int bit_a = a[i] - '0';
        int bit_b = (j >= 0) ? (b[j] - '0') : 0;

        diff = bit_a - bit_b - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[i--] = diff + '0';
        if (j >= 0) j--;
    }

    // Убираем ведущие нули
    while (*result == '0' && *(result + 1) != '\0') result++;

    return result;
}

// Функция сдвига влево
Binary shift_left(Binary a, int count) {
    int len = strlen(a);
    Binary result = (Binary)malloc(len + count + 1);

    strcpy(result, a);
    for (int i = 0; i < count; i++) {
        result[len + i] = '0';
    }
    result[len + count] = '\0';

    return result;
}

// Функция сдвига вправо
Binary shift_right(Binary a, int count) {
    int len = strlen(a);
    if (count >= len) { 
        Binary result = (Binary)malloc(2);
        strcpy(result, "0");
        return result;
    }

    Binary result = (Binary)malloc(len - count + 1);
    strncpy(result, a, len - count);
    result[len - count] = '\0';

    return result;
}

int main() {
    Binary a = (Binary)malloc(100);
    Binary b = (Binary)malloc(100);

    // Ввод чисел
    printf("Введите первое число (двоичное): ");
    scanf("%s", a);
    printf("Введите второе число (двоичное): ");
    scanf("%s", b);

    // Выбор операции
    char operation;
    printf("Выберите операцию (+, -, <<, >>): ");
    scanf(" %c", &operation);

    // В зависимости от операции выбираем соответствующую функцию
    if (operation == '+') {
        op_func = add;
    } else if (operation == '-') {
        op_func = subtract;
    } else if (operation == '<') {
        shift_func = shift_left;
    } else if (operation == '>') {
        shift_func = shift_right;
    } else {
        printf("Ошибка: неизвестная операция!\n");
        free(a);
        free(b);
        return 1;
    }

    if (operation == '+' || operation == '-') {
        printf("Результат: %s\n", op_func(a, b));
    } else {
        int shift_count;
        printf("Введите количество сдвигов: ");
        scanf("%d", &shift_count);
        if (operation == '<') {
            printf("Результат сдвига влево: %s\n", shift_func(a, shift_count));
        } else if (operation == '>') {
            printf("Результат сдвига вправо: %s\n", shift_func(a, shift_count));
        }
    }

    // Освобождаем память
    free(a);
    free(b);

    return 0;
}
