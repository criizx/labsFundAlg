#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "converter.h"  // Подключаем заголовочный файл с функцией конвертации

int main() {
    int base;
    printf("Enter the base of the number system (from 2 to 36): ");
    scanf("%d", &base);

    if (base < 2 || base > 36) {
        printf("Error: base must be between 2 and 36.\n");
        return 1;
    }

    int numbers[100];  // Массив для хранения введённых чисел
    int count = 0;
    char input[50];

    // Ввод чисел
    printf("Enter numbers (or 'Stop' to finish):\n");
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "Stop") == 0) break;

        // Преобразование строки в число в заданной системе счисления
        char *endptr;
        int number = strtol(input, &endptr, base);

        if (*endptr != '\0') {
            printf("Error: '%s' is not a valid number in base %d.\n", input, base);
        } else {
            numbers[count++] = number;
        }
    }

    if (count == 0) {
        printf("No numbers were entered.\n");
        return 1;
    }

    // Нахождение максимального по модулю числа
    int max_number = numbers[0];
    for (int i = 1; i < count; i++) {
        if (abs(numbers[i]) > abs(max_number)) {
            max_number = numbers[i];
        }
    }

    // Вывод максимального числа
    printf("Maximum absolute number: %d\n", max_number);

    // Перевод максимального числа в системы счисления 9, 18, 27, 36
    int bases[] = {9, 18, 27, 36};
    for (int i = 0; i < 4; i++) {
        char converted[50];
        convert_to_base(max_number, bases[i], converted);  // Используем функцию из другого файла
        printf("Representation in base %d: %s\n", bases[i], converted);
    }

    return 0;
}
