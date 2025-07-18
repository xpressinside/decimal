#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    int overflow = 0;
    memset(result, 0, sizeof(s21_decimal));

    s21_norm(&value_1,&value_2);
    int scale = s21_get_scale(value_1);
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);

    if ((sign_1 || sign_2) && !(sign_1 && sign_2)) {
        unsigned long long carry = 0;
        for (int i = 0; i < 3; i++) {
            unsigned long long sum = (unsigned long long)value_1.bits[i] - value_2.bits[i] + carry;
            result->bits[i] = (unsigned long)(sum & 0xFFFFFFFF);
            carry = sum >> 32;
        }
    } else {
        unsigned long long carry = 0;
        // int overflow = 0;

        for (int i = 0; i < 3; i++) {
            unsigned long long sum = (unsigned long long)value_1.bits[i] + value_2.bits[i] + carry;
            result->bits[i] = (unsigned long)(sum & 0xFFFFFFFF);
            carry = sum >> 32;

            if (i == 2 && carry != 0) {
                overflow = 1;
            }
        }
        
    }

    if (overflow) {
        if (scale > 0) {
            scale--;
            s21_set_scale(result, scale);

            unsigned long long rem = 0;
            for (int i = 2; i >= 0; i--) {
                unsigned long long value = (rem << 32) | result->bits[i];
                result->bits[i] = (unsigned)(value / 10);
                rem = value % 10;
            }
            if (rem > 5 || (rem == 5 && (result->bits[0] & 1))) {
                s21_decimal one = {{1, 0, 0, 0}};
                s21_add(*result, one, result);
            }
            overflow = 0;
            for (int i = 0; i < 3; i++) {
                if (result->bits[i] != 0) {
                    break;
                }
                if (i == 2) {
                    error = sign_1 ? 2 : 1;
                }
            }
        } else {
            error = sign_1 ? 2 : 1;
        }
        
    }   

    

    s21_set_scale(result, scale);
    if (sign_1) {
        s21_set_sign(result, 1);
    }
    return error;
}

