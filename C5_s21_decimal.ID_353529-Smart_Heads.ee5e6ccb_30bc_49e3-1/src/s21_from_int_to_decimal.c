#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int error = 0;
    if (!dst) {
        error = 1;
    } else {
        *dst = s21_decimal_set_zero();
        if (src < 0) {
            s21_set_sign(dst, 1);
            src = -src;
        }
        dst->bits[0] = (unsigned int)src;
        s21_set_scale(dst, 0);
    }
    return error;
}
