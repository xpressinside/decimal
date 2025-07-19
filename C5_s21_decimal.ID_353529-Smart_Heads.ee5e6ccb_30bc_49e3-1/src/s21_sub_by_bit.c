#include "s21_decimal.h"

int s21_sub_by_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    int overflow = 0;

    memset(result, 0, sizeof(s21_decimal));

    s21_norm(&value_1,&value_2);
    int scale = s21_get_scale(value_1);
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);

    // printf("sign 1 = %i \nsign 2 = %i \n", sign_1, sign_2);
    

    // (-v1) - (-v2) = - v1 + v2 = - (v1 - v2)
    if (sign_1 && sign_2) {
        int carry = 0;
        for (int i = 0; i < 96; i++) {
            int diff = s21_get_bit(value_1, i) - s21_get_bit(value_2, i) - carry;
            if (diff == -1) {
                s21_set_bit(result, i, 1);
                carry = 1;
            } else if (diff == -2) {
                s21_set_bit(result, i, 0);
                carry = 1;
            } else {
                s21_set_bit(result, i, diff);
                carry = 0;
            }
        }
        if (carry) {
            error = 1;
        }
        s21_set_sign(result, 1);
    // -v1 - v2 = - (v1 + v2)
    } else if (sign_1) {
                int carry = 0;
        for (int i = 0; i < 96; i++) {
            int sum = 0;
            sum = s21_get_bit(value_1, i) + s21_get_bit(value_2, i) + carry;
            if (sum == 2) {
                carry = 1;
                s21_set_bit(result, i, 0);
            } else if (sum == 3) {
                s21_set_bit(result, i, 1);
                carry = 1;
            } else {
                s21_set_bit(result, i, sum);
                carry = 0;
            }
        }
        if (carry) {
            error = 1;
        }
        s21_set_sign(result, 1);
    // v1 - (-v2) = v1 + v2
    } else if (sign_2) {
        int carry = 0;
        for (int i = 0; i < 96; i++) {
            int sum = 0;
            sum = s21_get_bit(value_1, i) + s21_get_bit(value_2, i) + carry;
            if (sum == 2) {
                carry = 1;
                s21_set_bit(result, i, 0);
            } else if (sum == 3) {
                s21_set_bit(result, i, 1);
                carry = 1;
            } else {
                s21_set_bit(result, i, sum);
                carry = 0;
            }
        }
        if (carry) {
            error = 1;
        }
    // v1 - v2
    } else {
        int carry = 0;
        for (int i = 0; i < 96; i++) {
            int diff = s21_get_bit(value_1, i) - s21_get_bit(value_2, i) - carry;
            if (diff == -1) {
                s21_set_bit(result, i, 1);
                carry = 1;
            } else if (diff == -2) {
                s21_set_bit(result, i, 0);
                carry = 1;
            } else {
                s21_set_bit(result, i, diff);
                carry = 0;
            }
        }
        if (carry) {
            error = 1;
        }
    }
    

    return error;
}

