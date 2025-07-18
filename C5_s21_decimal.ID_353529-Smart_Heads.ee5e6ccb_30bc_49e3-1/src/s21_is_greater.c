#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);

    if (sign_1 && !sign_2) {
        result = 0;
    } else if (!sign_1 && sign_2) {
        result = 1;
    } else if (sign_1 && sign_2) {
        s21_norm(&value_1, &value_2);

        for (int i = 2; i >= 0; i--) {
            if (value_1.bits[i] < value_2.bits[i]) {
                result = 1;
            } else if (value_1.bits[i] > value_2.bits[i]) {
                result = 0;
            }
        }
        
    } else if (!sign_1 && !sign_2) {
        s21_norm(&value_1, &value_2);

        for (int i = 2; i >= 0; --i) {
            if (value_1.bits[i] < value_2.bits[i]) {
                result = 0;
            } else if (value_1.bits[i] > value_2.bits[i]) {
                result = 1;
            }
        }
    }
    return result;
}