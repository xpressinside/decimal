#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int error = 0;
    if (!dst) {
        error = 1;
    } else if (src.bits[1] || src.bits[2]) {
        error = 1;
    } else if (!src.bits[0] && !src.bits[1] && !src.bits[2]) {
        *dst = 0;
    } else {
        int sign = s21_get_sign(src);
        s21_decimal tmp;
        s21_truncate(src, &tmp);
        for (int i = 0; i < MAX_BITS_NUMBER; i++) {
            if (s21_get_bit(tmp, i) != 0) {
                *dst += pow(2, i);
            }
        }
        if (sign) {
            *dst = -*dst;
        }

    }      
    return error;
}