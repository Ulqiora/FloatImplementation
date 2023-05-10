#include "Float.h"
/**
 * PrintSign
 * печать состояния бита для знака
 */
void PrintSign(Float temp) {
    printf("\033[31m");
    printf("%4d", !!((temp.value_) & SIGN_BIT_MASK));
    printf("\033[0m");
}
/**
 * PrintDegree
 * печать состояния битов для порядка числа 
 */
void PrintDegree(Float temp) {
    unsigned int mask = FIRST_DEGREE_BIT_MASK;
    printf("\033[34m");
    for (int i = 30; i >= NUMBER_BITS_IN_MANTISSA; i--, mask >>= 1)
        printf("%d", !!((temp.value_) & mask));
    printf("\033[0m");
}
/**
 * PrintMantissa
 * печать состояния битов для мантиссы числа 
 */
void PrintMantissa(Float temp) {
    unsigned int mask = FIRST_MANTISSA_BIT_MASK;
    printf("\033[32m");
    for (int i = 22; i >= 0; i--, mask >>= 1)
        printf("%d", !!((temp.value_) & mask));
    printf("\033[0m");
}
/**
 * PrintMantissa
 * вывод шапки для печати результата
 */
void PrintBits(Float temp) {
    printf("Sign|Degree  |Mantissa\n");
    PrintSign(temp);
    printf(" ");
    PrintDegree(temp);
    printf(" ");
    PrintMantissa(temp);
    printf("\n");
}
