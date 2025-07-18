#include "s21_decimal.h"

void main() {
    s21_decimal number = {{0x000000FF, 0x00000000, 0x00000000, 0x00000000}};
    // int res = 0;
    // s21_from_decimal_to_int(number, &res);
    // printf("%i\n", res);
    s21_decimal number_2 = {{0x000000FF, 0x00000000, 0x00000000, 0x00000000}};
    // int eq = s21_is_equal(number, number_2);
    // printf("res eq = %i\n", eq);
    // char* str = s21_decimal_to_string(number);
    // char* str2 = s21_decimal_to_string(number_2);
    // printf("%s\n", str);
    // printf("%s\n", str2);
    s21_decimal result = {{0}};

    s21_add_by_bit(number, number_2, &result);
    s21_print_bits_debug(number);
    s21_print_bits_debug(number_2);

    s21_print_bits_debug(result);
    char* str = s21_decimal_to_string(number);
    char* str2 = s21_decimal_to_string(number_2);
    char* str3 = s21_decimal_to_string(result);

    printf("%s\n", str);
    printf("%s\n", str2);
    printf("%s\n", str3);


    // s21_sub(number, number_2, &result);
    // int is_less = s21_is_less(number, number_2);
    // int is_greater = s21_is_greater(number, number_2);
    // int is_equal = s21_is_equal(number, number_2);
    // int is_less_or_equal = s21_is_less_or_equal(number,number_2);
    // int is_greater_or_equal = s21_is_greater_or_equal(number,number_2);
    // int is_not_equal = s21_is_not_equal(number,number_2);
    // char* str = s21_decimal_to_string(number);
    // char* str2 = s21_decimal_to_string(number_2);
    // // char* str3 = s21_decimal_to_string(result);

    // printf("%s\n", str);
    // printf("79228162514264337593543950335\n");
    // printf("%s\n", str2);
    // printf("is less = %d\n", is_less);
    // printf("is greater = %d\n", is_greater);
    // printf("is equal = %d\n", is_equal);
    // printf("is less or equal = %d\n", is_less_or_equal);
    // printf("is greater or equal = %d\n", is_greater_or_equal);
    // printf("is not equal = %d\n", is_not_equal);
    
    // s21_add(number, number_2, &result);
    // int err = check_value(result);
    // printf("check error = %d\n", err);
    // char* str3 = s21_decimal_to_string(result);
    // printf("%s\n", str3);
    // char* str;
    // s21_print_bits_debug(number);    
    // s21_print_bits_debug(number_2);
    // s21_print_bits_debug(result);
    // printf("Decimal value: %s\n", str);
    // free(str);


    // int bit = s21_get_bit(number, 0);
    // printf("%i\n", bit);
    // for (int i = 0; i < 128; i++)
    // {
    //     int bit = s21_get_bit(number, i);
    //     printf("%i", bit);
    //     if ((i == 7) || (i == 15) || (i == 23) || (i == 31) || (i == 39) || (i == 47) || (i == 55) || (i == 63) || (i == 71) || (i == 79) || (i == 87) || (i == 95) || (i == 103) || (i == 111) || (i == 119))
    //     {
    //         printf(" ");
    //     }
        
    //     if ((i == 31) || (i == 63) || (i == 95)) {
    //         printf("\n");
    //     }
    // }
    // printf("\n");
    
    // int sign = s21_get_sign(number);
    // char* str = s21_decimal_to_string(number);
    // int dst = 0;
    // s21_from_decimal_to_int(number, &dst);
    // int res = s21_from_decimal_to_int(number, &dst);
    // printf("%i\n", dst);
    // printf("%i\n", res);

    
    // char* str;
    // s21_print_bits_debug(number);    
    // printf("Decimal value: %s\n", str);
    // free(str);

    // s21_decimal result = {{0}};
    // s21_truncate(number, &result);
    // char* str2 = s21_decimal_to_string(result);
    // printf("Decimal value: %s\n", str2);
    // free(str2);


    // s21_set_sign(&number, 0);
    // char* str2 = s21_decimal_to_string(number);
    // s21_print_bits_debug(number);    
    // printf("Decimal value: %s\n", str2);
    // free(str2);

    // s21_decimal a = {{0, 0, 0xFFFFFFFF, 0x00000000}};
    // char* stra = s21_decimal_to_string(a);    *result = value;
    // s21_set_sign(result, 1);
    // printf("Dec value: %s \n", str);
    // free(str);
    // printf("%d\n", check);


}