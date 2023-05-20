#include "Float.h"

Float AdditionWithoutSign(Float val1, Float val2) {
    Float result = {0};
    int mantissa1 = GetMantissa(val1), mantissa2 = GetMantissa(val2);
    int exp1 = CalcNumDigitsAfterDot(mantissa1),
        exp2 = CalcNumDigitsAfterDot(mantissa2);
    printf("exp1 = %d\n",exp1);
    printf("exp2 = %d\n",exp2);
    int numAfterDot = ShiftByDot(&mantissa1, &mantissa2, exp1, exp2);
    int currentDegree =
        ShiftByDegree(&mantissa1, &mantissa2, GetDegree(val1), GetDegree(val2)) -
        DEGREE_SHIFT;
    int mantissa = mantissa1 + mantissa2;
    int expRes= CalcNumDigitsAfterDot(mantissa) - 1;
    // if (expRes > numAfterDot)
    //     mantissa >>= (expRes - numAfterDot);
    // else
    //     mantissa <<= (numAfterDot - expRes);
    int numberSignAfterDots = CalcNumDigitsAfterDot(mantissa);
    mantissa = (numberSignAfterDots > 23)
                ? mantissa >> (numberSignAfterDots - 23) 
                : mantissa << (23 - numberSignAfterDots);
    currentDegree+=(expRes - numAfterDot);
    SetMantissa(&result, mantissa);
    SetDegree(&result, currentDegree + DEGREE_SHIFT+1);
    return result;
}

Float SubtractionWithoutSign(Float val1, Float val2){
    Float result = {0};
    int mantissa1 = GetMantissa(val1), mantissa2 = GetMantissa(val2);
    int exp1 = CalcNumDigitsAfterDot(mantissa1) - 1,
        exp2 = CalcNumDigitsAfterDot(mantissa2) - 1;
    int numAfterDot = ShiftByDot(&mantissa1, &mantissa2, exp1, exp2);
    int currentDegree =
        ShiftByDegree(&mantissa1, &mantissa2, GetDegree(val1), GetDegree(val2)) -
        DEGREE_SHIFT;
    int mantissa = mantissa1 - mantissa2;
    if (mantissa & SIGN_BIT_MASK) {
        mantissa = mantissa2 - mantissa1;
        SetSign(&result);
    }
    // int expRes= СalcNumDigitsAfterDot(mantissa) - 1;
    // if (expRes > numAfterDot)
    //     mantissa >>= (expRes - numAfterDot);
    // else
    //     mantissa <<= (numAfterDot - expRes);
    int exp = CalcNumDigitsAfterDot(mantissa) - 1;
    currentDegree+=(exp - numAfterDot);
    mantissa = (exp > 22) ? mantissa >> (exp - 22) : mantissa << (22 - exp);
    SetMantissa(&result, mantissa);
    SetDegree(&result, currentDegree + DEGREE_SHIFT);
    return result;
}

Float Addiction(Float val1,Float val2){
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

int ShiftByDot(int* mant1, int* mant2, int numberAfterDot1, int numberAfterDot2) {
    if (numberAfterDot1 > numberAfterDot2) {
        (*mant2) <<= (numberAfterDot1 - numberAfterDot2);
        return numberAfterDot1;
    } else {
        (*mant1) <<= (numberAfterDot2 - numberAfterDot1);
        return numberAfterDot2;
    }
}

int ShiftByDegree(int* mant1, int* mant2, int degree1, int degree2) {
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
    return degree1;
}
