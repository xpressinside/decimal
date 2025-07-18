#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    int error = 0;
    int sign = s21_get_sign(value);
    *result = value;

    if (0) {
        error = 1;
    } else if (sign) {
        s21_set_sign(result, 0);
    } else {
        s21_set_sign(result, 1);
    }

    return error;
}