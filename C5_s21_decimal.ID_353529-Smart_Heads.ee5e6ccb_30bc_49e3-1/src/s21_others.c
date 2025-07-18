#include "s21_decimal.h"

// Get Bit
int s21_get_bit(s21_decimal value, int index) {
    int int_index = index / 32; //получим индекс bits[index]
    int bit_pos = index % 32;   //получим позицию бита
    return (value.bits[int_index] >> bit_pos) & 1;
}

//установить бит
void s21_set_bit(s21_decimal *result, int bit_index, int sum) {
    if (!result || bit_index < 0 || bit_index > 95) {
        return;  // Некорректные входные данные
    }

    int word_index = bit_index / 32;  // Определяем, в каком words[0..3] находится бит
    int bit_in_word = bit_index % 32; // Позиция бита в word (0..31)

    if (sum) {
        // Устанавливаем бит в 1 (используем OR)
        result->bits[word_index] |= (1u << bit_in_word);
    } else {
        // Устанавливаем бит в 0 (используем AND с инверсией)
        result->bits[word_index] &= ~(1u << bit_in_word);
    }
}

// получить знак
int s21_get_sign(s21_decimal value) {
    return (value.bits[3] >> 31) & 1;
}

// установить знак
void s21_set_sign(s21_decimal *value, int sign) {
    if (sign) {
        value->bits[3] |= 0x80000000;
    } else {
        value->bits[3] &= ~0x80000000;
    }
}

// получить степень
int s21_get_scale(s21_decimal value) {          
    return (value.bits[3] >> 16) & 0xFF;
}

// указать степень
void s21_set_scale(s21_decimal *value, int scale) {
    value->bits[3] &= 0x80000000;
    value->bits[3] |= (scale << 16);
}

// zero check
int s21_is_zero(s21_decimal value) {
    return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

// multiply by 10
void s21_mul_10(s21_decimal *value) {
    unsigned long carry = 0;
    for (int i = 0; i < 3; i++) {
        unsigned long tmp = (unsigned long)value->bits[i] * 10 + carry;
        value->bits[i] = tmp & 0xFFFFFFFF;
        carry = tmp >> 32;
    }
    s21_set_scale(value, s21_get_scale(*value) + 1);
}

// normalize 2 decimal value
void s21_norm(s21_decimal *value_1, s21_decimal *value_2) {
    int scale_1 = s21_get_scale(*value_1);
    int scale_2 = s21_get_scale(*value_2);
    while (scale_1 < scale_2) {
        s21_mul_10(value_1);
        scale_1++;
    }
    while (scale_2 < scale_1) {
        s21_mul_10(value_2);
        scale_2++;
    }
    s21_set_scale(value_1,scale_1);
    s21_set_scale(value_2,scale_1);    
}

// set zero decimal value
s21_decimal s21_decimal_set_zero(void) {
    s21_decimal value;
    value.bits[0] = 0;
    value.bits[1] = 0;
    value.bits[2] = 0;
    value.bits[3] = 0;
    return value;
}

// return number of 10^scale only form 0 to 28
s21_decimal s21_get_ten_pow(int scale) {
    return ten_pows[scale];
}

s21_decimal s21_bin_div(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal result = {0};
    if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        return result;
    }

    unsigned long long num = (unsigned long long)value_1.bits[1] << 32 | value_1.bits[0];
    unsigned long long dnom = (unsigned long long)value_2.bits[1] << 32 | value_2.bits[0];

    if (dnom == 0) {
        return result;
    }

    unsigned long long quot = num / dnom;

    result.bits[0] = (unsigned)(quot & 0xFFFFFFFF);
    result.bits[1] = (unsigned)(quot >> 32);
    return result;

}


double s21_decimal_to_double(s21_decimal value) {
    double result = 0.0;
    for (int i = 0; i < 3; i++) {
        result += value.bits[i] * pow(2.0, 32 * i);
    }
    int scale = s21_get_scale(value);
    result /= pow(10, scale);
    if (s21_get_sign(value)) {
        result = -result;
    }
    return result;

}


int check_value(s21_decimal value) {
    int error = 0;
    int sign = s21_get_sign(value);
    if (sign) {
        s21_set_sign(&value, 0);
    }
    double new_value = s21_decimal_to_double(value);
    if (new_value > D_MAX) {
        error = 1;
    } else if (new_value > 0 && new_value < D_MIN) {
        error = 2;
    }
    return error;
    
}