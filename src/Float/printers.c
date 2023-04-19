#include "Float.h"

void PrintSign(Float temp) {
    printf("\033[31m");
    printf("%4d", !!((temp.value_) & SIGN_BIT_MASK));
    printf("\033[0m");
}

void PrintDegree(Float temp) {
    unsigned int mask = FIRST_DEGREE_BIT_MASK;
    printf("\033[34m");
    for (int i = 30; i >= NUMBER_BITS_IN_MANTISSA; i--, mask >>= 1)
        printf("%d", !!((temp.value_) & mask));
    printf("\033[0m");
}

void PrintMantissa(Float temp) {
    unsigned int mask = FIRST_MANTISSA_BIT_MASK;
    printf("\033[32m");
    for (int i = 22; i >= 0; i--, mask >>= 1)
        printf("%d", !!((temp.value_) & mask));
    printf("\033[0m");
}

void PrintBits(Float temp) {
    printf("Sign|Matissa |other\n");
    PrintSign(temp);
    printf(" ");
    PrintDegree(temp);
    printf(" ");
    PrintMantissa(temp);
    printf("\n");
}
