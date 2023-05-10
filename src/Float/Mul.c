#include "Float.h"

Float MultiplicationWithoutSign(Float val1,Float val2){
    Float res;
    int mantissa1 = GetMantissa(val1), mantissa2 = GetMantissa(val2);
    int degree1 = GetDegree(val1) - 127,
        degree2 = GetDegree(val2) - 127;
    int mantissa = mantissa1 * mantissa2;
    int degreeRes=degree1+degree2;
    printf("value1:\ndegree = %d\n",degree1);
    for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
        printf("%d", !!(mantissa1 & mask));
    printf("\n");
    printf("value2:\ndegree = %d\n",degree2);
    for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
        printf("%d", !!(mantissa2 & mask));
    printf("\n");
    int numberSignAfterDots = calcNumDigitsAfterDot(mantissa)-1;

    SetDegree(&res,degreeRes+127);
    mantissa = (numberSignAfterDots > 22)
                   ? mantissa >> (numberSignAfterDots - 22)
                   : mantissa << (22 - numberSignAfterDots);
    SetMantissa(&res,mantissa);
    // printf("result of mul: %d\n",mantissa);
    return res;
}