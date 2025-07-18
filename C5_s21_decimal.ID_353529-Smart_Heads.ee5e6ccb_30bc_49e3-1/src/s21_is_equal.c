#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    if (s21_is_zero(value_1) && s21_is_zero(value_2)) {
        result = 1;
    } else if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
        result = 0;
    } else {
        int scale_1 = s21_get_scale(value_1);
        int scale_2 = s21_get_scale(value_2);

        if (scale_1 == scale_2) {
            result = (value_1.bits[0] == value_2.bits[0] && value_1.bits[1] == value_2.bits[1] && value_1.bits[2] == value_2.bits[2]);
        } else {
            s21_decimal norma_value_1 = value_1;
            s21_decimal norma_value_2 = value_2;

            s21_norm(&norma_value_1, &norma_value_2);
            result = (norma_value_1.bits[0] == norma_value_2.bits[0] && norma_value_1.bits[1] == norma_value_2.bits[1] && norma_value_1.bits[2] == norma_value_2.bits[2]);

        }        
    }
    return result;
}