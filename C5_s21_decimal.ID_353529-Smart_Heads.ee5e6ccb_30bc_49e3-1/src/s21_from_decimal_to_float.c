#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int error = 0;
    if (!dst) {
        error = 1;
    } else if (src.bits[1] || src.bits[2]) {
        error = 1;
    } else if (!src.bits[0] && !src.bits[1] && !src.bits[2]) {
        *dst = 0;
    } else {
        int sign = s21_get_sign(src);
        int scale = s21_get_scale(src);
    
        s21_decimal result;
        result.bits[0] = src.bits[0];
    
        while (scale-- > 0) {
            result.bits[0] /= 10;
        }
        
        *dst = result.bits[0];
        if (sign) {
            *dst *= -1;
        }
    }      
    return error;
}