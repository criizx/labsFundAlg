#include <stdio.h>
#include <stdlib.h>

void convertToBase2R(unsigned int num, int r) {
    unsigned int base = 1 << r;
    unsigned int mask = base - 1; 

    char* result = (char*) malloc(32 * sizeof(char));
    int i = 0;

    while (num) {
        result[i++] = (num & mask); 
        num >>= r;
    }

    printf("Число в системе с основанием 2^%d: ", r);
    for (int j = i - 1; j >= 0; j--) {
        if (r == 1 || r == 2 || r == 4) {
            printf("%X", result[j]);
        } 
        else if (r == 3) {
            printf("%o", result[j]);
        } 
        else if (r == 5) {
            if (result[j] < 10) {
                printf("%d", result[j]);
            } else {
                printf("%c", 'A' + (result[j] - 10));
            }
        }
    }
    printf("\n");

    free(result);
}

int main() {
    unsigned int num;
    int r;

    printf("Введите число: ");
    scanf("%u", &num);

    printf("Введите r (основание системы счисления 2^r): ");
    scanf("%d", &r);

    if (r < 1 || r > 5) {
        printf("Ошибка: r должно быть в диапазоне от 1 до 5\n");
        return 1;
    }
    convertToBase2R(num, r);

    return 0;
}
