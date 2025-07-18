#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if (!result) {
        error = 1;
    } else {
        s21_decimal one;
        s21_from_int_to_decimal(1, &one);
        s21_decimal truncated;
        s21_decimal zero = {0};

        s21_truncate(value, &truncated);

        
    }
}