#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if (!result) {
        error = 1;
    } else {
        *result = s21_decimal_set_zero();
        int scale = s21_get_scale(value);
        s21_decimal tmp = value;
        s21_decimal pow10 = s21_get_ten_pow(scale);
        *result = s21_bin_div(value, pow10);
        s21_set_scale(result, 0);
    }
    return error;
}
