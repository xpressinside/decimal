#include "s21_decimal.h"

char* s21_decimal_to_string(s21_decimal d) {
    int sign = s21_get_sign(d);
    int scale = s21_get_scale(d);

    // Проверка scale на корректность (0..28)
    if (scale < 0 || scale > 28) {
        return strdup("[INVALID_SCALE]");  // Ошибка: некорректный scale
    }

    // 1. Преобразуем 96-битное число в строку (без учёта scale)
    char buffer[29 + 1] = {0};
    unsigned int digits[3] = {d.bits[0], d.bits[1], d.bits[2]};
    int len = 0;

    // Конвертируем 96-битное число в строку (делением на 10)
    while (1) {
        // Проверяем, равно ли число нулю
        int is_zero = 1;
        for (int i = 0; i < 3; i++) {
            if (digits[i] != 0) {
                is_zero = 0;
                break;
            }
        }
        if (is_zero) break;

        // Делим digits на 10
        unsigned long long remainder = 0;
        for (int i = 2; i >= 0; i--) {
            remainder = (remainder << 32) | digits[i];
            digits[i] = remainder / 10;
            remainder %= 10;
        }

        // Добавляем цифру в начало строки
        // if (len + 1 >= 29) {
        //     return strdup("[OVERFLOW]");  // Слишком большое число
        // }
        memmove(buffer + 1, buffer, len);
        buffer[0] = '0' + (char)remainder;
        len++;
    }

    // Если число было нулём
    if (len == 0) {
        buffer[0] = '0';
        len = 1;
    }

    // 2. Выделяем память с запасом (знак, точка, нули)
    int result_size = len + scale + 3;  // +3 для знака, точки и '\0'
    char* result = malloc(result_size);
    if (!result) {
        return NULL;  // Ошибка выделения памяти
    }
    memset(result, 0, result_size);

    // 3. Добавляем знак
    int pos = 0;
    if (sign) {
        result[pos++] = '-';
    }

    // 4. Вставляем точку в зависимости от scale
    if (scale == 0) {
        // Без дробной части
        memcpy(result + pos, buffer, len);
    } else if (scale >= len) {
        // Число вида 0.000...buffer
        result[pos++] = '0';
        result[pos++] = '.';
        for (int i = 0; i < scale - len; i++) {
            result[pos++] = '0';
        }
        memcpy(result + pos, buffer, len);
    } else {
        // Обычный случай: вставляем точку после (len - scale) цифр
        int point_pos = len - scale;
        for (int i = 0; i < len; i++) {
            if (i == point_pos) {
                result[pos++] = '.';
            }
            result[pos++] = buffer[i];
        }
    }

    // 5. Удаляем лишние нули после точки (если scale > 0)
    if (scale > 0) {
        int new_len = strlen(result);
        while (new_len > 0 && result[new_len - 1] == '0') {
            result[new_len - 1] = '\0';
            new_len--;
        }
        if (new_len > 0 && result[new_len - 1] == '.') {
            result[new_len - 1] = '\0';
        }
    }

    return result;
    
}

void s21_print_bits_debug(const s21_decimal d) {
    printf("====== s21_decimal bits ======\n");

    for (int i = 3; i >= 0; i--) {
        printf("bits[%d]: ",i);

        for (int j = 31; j >= 0; j--) {
            printf("%d", (d.bits[i] >> j) & 1);

            if (j == 24 || j == 16 || j == 8) {
                printf(" ");
            }
        }
        printf("\n");
    }
}