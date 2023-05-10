#include "Float.h"
// сложение чисел без учета знака
Float AdditionWithoutSign(Float val1, Float val2) {
    Float result = {0};
    int mantissa1 = GetMantissa(val1), mantissa2 = GetMantissa(val2);
    int exp1 = calcNumDigitsAfterDot(mantissa1) - 1,
        exp2 = calcNumDigitsAfterDot(mantissa2) - 1;
    int numAfterDot = shiftByDot(&mantissa1, &mantissa2, exp1, exp2);
    int currentDegree =
        shiftByDegree(&mantissa1, &mantissa2, GetDegree(val1), GetDegree(val2)) -
        DEGREE_SHIFT;
    int mantissa = mantissa1 + mantissa2;
    int expRes= calcNumDigitsAfterDot(mantissa) - 1;
    if (expRes > numAfterDot)
        mantissa >>= (expRes - numAfterDot);
    else
        mantissa <<= (numAfterDot - expRes);
    // for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
    //     printf("%d", !!(mantissa & mask));
    // printf("\n");
    // printf("currentDegree = %d\n",currentDegree);
    // printf("expRes = %d\n",expRes);
    // printf("numAfterDot = %d\n",numAfterDot);
    currentDegree+=(expRes - numAfterDot);
    SetMantissa(&result, mantissa);
    SetDegree(&result, currentDegree + DEGREE_SHIFT);
    // int exp = calcNumDigitsAfterDot(mantissa) - 1;
    // mantissa = (exp > 22) ? mantissa >> (exp - 22) : mantissa << (22 - exp);
    // if(exp > 22) exp=22;
    // SetMantissa(&result, mantissa);
    // printf("exp  =  %d\n",exp);
    // printf("numAfterDot  =  %d\n",numAfterDot);
    // printf("alignOrder  =  %d\n",alignOrder);
    // SetDegree(&result, exp - numAfterDot + alignOrder+DEGREE_SHIFT);
    return result;
}

Float SubtractionWithoutSign(Float val1, Float val2){
    Float result = {0};
    int mantissa1 = GetMantissa(val1), mantissa2 = GetMantissa(val2);
    int exp1 = calcNumDigitsAfterDot(mantissa1) - 1,
        exp2 = calcNumDigitsAfterDot(mantissa2) - 1;
    int numAfterDot = shiftByDot(&mantissa1, &mantissa2, exp1, exp2);
    int currentDegree =
        shiftByDegree(&mantissa1, &mantissa2, GetDegree(val1), GetDegree(val2)) -
        DEGREE_SHIFT;
    exp1 = calcNumDigitsAfterDot(mantissa1) - 1,
    exp2 = calcNumDigitsAfterDot(mantissa2) - 1;
    int mantissa = mantissa1 - mantissa2;
    if (mantissa & SIGN_BIT_MASK) {
        mantissa = mantissa2 - mantissa1;
        SetSign(&result);
    }
    int expRes= calcNumDigitsAfterDot(mantissa) - 1;
    if (expRes > numAfterDot)
        mantissa >>= (expRes - numAfterDot);
    else
        mantissa <<= (numAfterDot - expRes);
    currentDegree+=(expRes - numAfterDot);
    int exp = calcNumDigitsAfterDot(mantissa) - 1;
    mantissa = (exp > 22) ? mantissa >> (exp - 22) : mantissa << (22 - exp);
    SetMantissa(&result, mantissa);
    SetDegree(&result, currentDegree + DEGREE_SHIFT);
    return result;
}

Float addiction(Float val1,Float val2){
    if(GetSign(val1) == GetSign(val2)){
        int sign = GetSign(val1);
        if(sign) ResetSign(&val1), ResetSign(&val1);
        Float result=AdditionWithoutSign(val1,val2);
        if(sign) SetSign(&result);
        return result;
    } else {
        int neg = GetSign(val1)?1:2;
        ResetSign(&val1),ResetSign(&val2);
        if(neg==1) return SubtractionWithoutSign(val2,val1);
        else return SubtractionWithoutSign(val1,val2);
    }
}
/**
 * CustomFloatToInt
 * опреобразование в int
 * @param[out] value мантисса первого числа.
 * @param[out] value мантисса второго числа.
 * @param[in] value порядок первого числа.
 * @param[in] value порядок второго числа.
 * @return порядок, по которому выравнены числа.
 */
int shiftByDot(int* mant1, int* mant2, int degree1, int degree2) {
    if (degree1 > degree2) {
        (*mant2) <<= (degree1 - degree2);
        return degree1;
    } else {
        (*mant1) <<= (degree2 - degree1);
        return degree2;
    }
}

int shiftByDegree(int* mant1, int* mant2, int degree1, int degree2) {
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
    // printf("exp1  =  %d   %d\n",degree1 - DEGREE_SHIFT,degree2 - DEGREE_SHIFT);
    // for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
    //     printf("%d", !!((*mant1) & mask));
    // printf("\n");
    // for (unsigned int i = 32,mask = SIGN_BIT_MASK; i > 0; i--, mask >>= 1)
    //     printf("%d", !!((*mant2) & mask));
    // printf("\n");
    return degree1;
}
