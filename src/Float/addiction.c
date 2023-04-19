#include "Float.h"

Float addiction(Float val1, Float val2) {
    Float result = {0};
    printf("before alignment by dot\n");
    int mantissa1 = GetMantissa(val1), mantissa2 = GetMantissa(val2);

    int exp1 = CalcDegreeForFloat(mantissa1) - 1,
        exp2 = CalcDegreeForFloat(mantissa2) - 1;
    int numAfterDot = shiftByDot(&mantissa1, &mantissa2, exp1, exp2);
    for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
        printf("%d", !!(mantissa1 & mask));
    printf("\n");
    for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
        printf("%d", !!(mantissa2 & mask));
    printf("\n");
    int currentDegree =
        shiftByOrder(&mantissa1, &mantissa2, GetDegree(val1), GetDegree(val2)) -
        DEGREE_SHIFT;
    int mantissa = mantissa1 + mantissa2;
    int expRes= CalcDegreeForFloat(mantissa) - 1;
    if (expRes > numAfterDot)
        mantissa >>= (expRes - numAfterDot);
    else
        mantissa <<= (numAfterDot - expRes);
    for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
        printf("%d", !!(mantissa & mask));
    printf("\n");
    printf("currentDegree = %d\n",currentDegree);
    printf("expRes = %d\n",expRes);
    printf("numAfterDot = %d\n",numAfterDot);
    currentDegree+=(expRes - numAfterDot);
    SetMantissa(&result, mantissa);
    SetDegree(&result, currentDegree + DEGREE_SHIFT);
    // int exp = CalcDegreeForFloat(mantissa) - 1;
    // mantissa = (exp > 22) ? mantissa >> (exp - 22) : mantissa << (22 - exp);
    // if(exp > 22) exp=22;
    // SetMantissa(&result, mantissa);
    // printf("exp  =  %d\n",exp);
    // printf("numAfterDot  =  %d\n",numAfterDot);
    // printf("alignOrder  =  %d\n",alignOrder);
    // SetDegree(&result, exp - numAfterDot + alignOrder+DEGREE_SHIFT);
    return result;
}

int shiftByDot(int* mant1, int* mant2, int degree1, int degree2) {
    if (degree1 > degree2) {
        (*mant2) <<= (degree1 - degree2);
        return degree1;
    } else {
        (*mant1) <<= (degree2 - degree1);
        return degree2;
    }
}
int shiftByOrder(int* mant1, int* mant2, int degree1, int degree2) {
    printf("after alignment by dot\n");
    if (degree1 > degree2) {
        while(degree1 != degree2 && (!(*mant1&0x40000000))) degree1--, *mant1<<=1;
    } else {
        while(degree1 != degree2 && (!(*mant2&0x40000000))) degree2--, *mant2<<=1;
    }
    if(degree1 > degree2){
        while(degree1 != degree2) degree2++, *mant2>>=1;
    } else if(degree1 < degree2){
        while(degree1 != degree2) degree1++, *mant1>>=1;
    }
    printf("exp1  =  %d   %d\n",degree1 - DEGREE_SHIFT,degree2 - DEGREE_SHIFT);
    for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
        printf("%d", !!((*mant1) & mask));
    printf("\n");
    for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
        printf("%d", !!((*mant2) & mask));
    printf("\n");
    return degree1;
}

// int shiftMantisses(int* mantissa1,int* mantissa2, int shift){
//     if(shift == 0) return 0;
//     if(shift<0)
// }
// 100000110001001001101111