#ifndef H_S21_DECIMAL
// #define H_S21_DECIMAL

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_BITS_NUMBER 96
#define D_MAX 79228162514264337593543950335.0L
#define D_MIN 1e-28L

typedef struct 
{
    int bits[4];
} s21_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add_by_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub_by_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);


int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);


//функции others
int s21_get_bit(s21_decimal value, int index);
void s21_set_bit(s21_decimal *result, int bit_index, int sum);
int s21_get_sign(s21_decimal value);
int s21_get_scale(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);
void s21_set_scale(s21_decimal *value, int scale);
int s21_is_zero(s21_decimal value);
void s21_mul_10(s21_decimal *value);
void s21_norm(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal s21_decimal_set_zero(void);
s21_decimal s21_get_ten_pow(int scale);
s21_decimal s21_bin_div(s21_decimal value_1, s21_decimal value_2);

static const s21_decimal ten_pows[29] = {
    [0] = {{0x1, 0x0, 0x0, 0x0}},
    [1] = {{0xA, 0x0, 0x0, 0x0}},
    [2] = {{0x64, 0x0, 0x0, 0x0}},
    [3] = {{0x3E8, 0x0, 0x0, 0x0}},
    [4] = {{0x2710, 0x0, 0x0, 0x0}},
    [5] = {{0x186A0, 0x0, 0x0, 0x0}},
    [6] = {{0xF4240, 0x0, 0x0, 0x0}},
    [7] = {{0x989680, 0x0, 0x0, 0x0}},
    [8] = {{0x5F5E100, 0x0, 0x0, 0x0}},
    [9] = {{0x3B9ACA00, 0x0, 0x0, 0x0}},
    [10] = {{0x540BE400, 0x2, 0x0, 0x0}},
    [11] = {{0x4876E800, 0x17, 0x0, 0x0}},
    [12] = {{0xD4A51000, 0xE8, 0x0, 0x0}},
    [13] = {{0x4E72A000, 0x918, 0x0, 0x0}},
    [14] = {{0x107A4000, 0x5AF3, 0x0, 0x0}},
    [15] = {{0xA4C68000, 0x38D7E, 0x0, 0x0}},
    [16] = {{0x6FC10000, 0x2386F2, 0x0, 0x0}},
    [17] = {{0x5D8A0000, 0x1634578, 0x0, 0x0}},
    [18] = {{0xA7640000, 0xDE0B6B3, 0x0, 0x0}},
    [19] = {{0x89E80000, 0x8AC72304, 0x0, 0x0}},
    [20] = {{0x63100000, 0x6BC75E2D, 0x5, 0x0}},
    [21] = {{0xDEA00000, 0x35C9ADC5, 0x36, 0x0}},
    [22] = {{0xB2400000, 0x19E0C9BA, 0x21E, 0x0}},
    [23] = {{0xF6800000, 0x2C7E14A, 0x152D, 0x0}},
    [24] = {{0xA1000000, 0x1BCECCED, 0xD3C2, 0x0}},
    [25] = {{0x4A000000, 0x16140148, 0x84595, 0x0}},
    [26] = {{0xE4000000, 0xDCC80CD2, 0x52B7D2, 0x0}},
    [27] = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x0}},
    [28] = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}}
    // [29] = {{0x1, 0x0, 0x0, 0x0}},
    // [30] = {{0x1, 0x0, 0x0, 0x0}},
    // [31] = {{0x1, 0x0, 0x0, 0x0}},
    // [32] = {{0x1, 0x0, 0x0, 0x0}},
    // [33] = {{0x1, 0x0, 0x0, 0x0}},
    // [34] = {{0x1, 0x0, 0x0, 0x0}},
    // [35] = {{0x1, 0x0, 0x0, 0x0}},
    // [36] = {{0x1, 0x0, 0x0, 0x0}},
    // [37] = {{0x1, 0x0, 0x0, 0x0}},
    // [38] = {{0x1, 0x0, 0x0, 0x0}}
};

//time function
char* s21_decimal_to_string(s21_decimal d);
void s21_print_bits_debug(const s21_decimal d);
int check_value(s21_decimal value);
double s21_decimal_to_double(s21_decimal value);




#endif //H_S21_DECIMAL