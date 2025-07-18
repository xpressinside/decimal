#include "s21_decimal.h"
//need more checks
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    int overflow = 0;
    memset(result, 0, sizeof(s21_decimal));


    // s21_decimal tmp_1 = value_1;
    // s21_decimal tmp_2 = value_2;
    s21_norm(&value_1, &value_2);
    int scale = s21_get_scale(value_1);
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);
    int compare = s21_is_less(value_1, value_2);
    if (compare) {
        s21_decimal tmp = value_1;
        value_1 = value_2;
        value_2 = tmp;
    }

    if (sign_1 && sign_2) {
        // Both negative: (-a) - (-b) = b - a
        int carry = 0;
        for (int i = 0; i < 3; i++) {
            unsigned long long sub = value_2.bits[i] - value_1.bits[i] - carry;
            result->bits[i] = (unsigned long)sub & 0xFFFFFFFF;
            carry = (sub >> 32) ? 1 : 0;
        }
    } else if (sign_1) {
        // value_1 is negative, value_2 is positive: (-a) - b = -(a + b)
        int carry = 0;
        for (int i = 0; i < 3; i++) {
            unsigned long long sub = value_1.bits[i] + value_2.bits[i] + carry;
            result->bits[i] = (unsigned long)sub & 0xFFFFFFFF;
            carry = sub >> 32;
        }
        s21_set_sign(result, 1);
    } else if (sign_2) {
        // value_1 is positive, value_2 is negative: a - (-b) = a + b
        int carry = 0;
        for (int i = 0; i < 3; i++) {
            unsigned long long sub = value_2.bits[i] + value_1.bits[i] + carry;
            result->bits[i] = (unsigned long)sub & 0xFFFFFFFF;
            carry = sub >> 32;
        }
    } else {
        int carry = 0;
        for (int i = 0; i < 3; i++) {
            unsigned long long sub = value_1.bits[i] - value_2.bits[i] - carry;
            result->bits[i] = (unsigned long)sub & 0xFFFFFFFF;
            carry = (sub >> 32) ? 1 : 0;
        }
    }

    s21_set_scale(result, scale);
    if (compare) {
        s21_set_sign(result, 1);
    }
    

    // // Compare absolute values
    // int cmp = s21_is_less(value_1, value_2);
    // if (cmp) {
    //     // Swap if value_1 < value_2 to ensure value_1 >= value_2
    //     s21_decimal temp = value_1;
    //     value_1 = value_2;
    //     value_2 = temp;
    //     s21_set_sign(result, 1);
    // }

    // // Perform subtraction
    // unsigned long long borrow = 0;
    // for (int i = 0; i < 3; i++) {
    //     unsigned long long diff = (unsigned long long)value_1.bits[i] - value_2.bits[i] - borrow;
    //     result->bits[i] = (unsigned int)(diff & 0xFFFFFFFF);
    //     borrow = (diff >> 32) ? 1 : 0;
    // }


    // // Set the scale
    // s21_set_scale(result, scale);

    // // Check for zero result to handle possible underflow
    // if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0) {
    //     s21_set_sign(result, 0);
    // }

    return error;

}