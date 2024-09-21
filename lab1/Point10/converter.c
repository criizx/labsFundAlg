#include "converter.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Функция для перевода числа в строковое представление в системе счисления с основанием base
void convert_to_base(int num, int base, char *result) {
    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer[50];
    int is_negative = num < 0;
    num = abs(num);
    int i = 0;

    if (num == 0) {
        strcpy(result, "0");
        return;
    }

    // Преобразование числа в систему счисления
    while (num > 0) {
        buffer[i++] = digits[num % base];
        num /= base;
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    // Инвертируем строку, так как цифры были добавлены в обратном порядке
    int len = strlen(buffer);
    for (int j = 0; j < len; j++) {
        result[j] = buffer[len - j - 1];
    }
    result[len] = '\0';
}
