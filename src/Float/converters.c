#include "Float.h"

void SetSign(Float* temp) { temp->value_ |= SIGN_BIT_MASK; }

int GetSign(Float temp) { return !!(temp.value_ & SIGN_BIT_MASK); }

void ResetSign(Float* temp){ temp->value_ &=~ SIGN_BIT_MASK;}

int GetMantissa(Float value) {
    if(value.value_ == 0) return 0;
    int mantissa = (value.value_&SET_MANTISSA_BITS_MASK)|(FIRST_MANTISSA_BIT_MASK<<1);
    while ((!(mantissa & 1))) { mantissa >>= 1; }
    return mantissa;
}

void SetMantissa(Float* res,int mantissa) {
    res->value_ &=~ SET_MANTISSA_BITS_MASK;
    res->value_ |= (mantissa & SET_MANTISSA_BITS_MASK);
}

int GetDegree(Float value){
    return ((value.value_ & GET_DEGREE_BIT_MASK) >> NUMBER_BITS_IN_MANTISSA);
}

void SetDegree(Float* res, int degree){
    res->value_ &=~ GET_DEGREE_BIT_MASK;
    res->value_ |= (degree) << NUMBER_BITS_IN_MANTISSA;
}

int calcNumDigitsAfterDot(unsigned int value) {
    int exp = 0;
    while (value >>= 1) exp++;
    return exp;
}

int CustomAbs(int value) { return (value >= 0) ? value : -value; }

Float IntToCustomFloat(int value) {
    Float temp = {0};
    if (!(value & 0xFFFFFFFF)) return temp;
    if (value & SIGN_BIT_MASK) SetSign(&temp), value = CustomAbs(value);
    int digitsAfterDots = calcNumDigitsAfterDot(value);
    SetDegree(&temp,(digitsAfterDots--)+DEGREE_SHIFT);
    int mantissa = (digitsAfterDots > 22) ? value >> (digitsAfterDots - 22) : value << (22 - digitsAfterDots);
    SetMantissa(&temp,mantissa);
    return temp;
}

int CustomFloatToInt(Float value) {
    int exp = GetDegree(value) - DEGREE_SHIFT;
    int mantissa = GetMantissa(value), mantissa_copy = mantissa;
    if (exp >= 0) {
        int numberAfterDot= calcNumDigitsAfterDot(mantissa);
        mantissa<<=exp;
        mantissa>>=numberAfterDot;
        return mantissa * (GetSign(value) ? (-1) : (1));
    } else {
        mantissa>>(-exp);
        int numberAfterDot= calcNumDigitsAfterDot(mantissa);
        if(mantissa & 1<<(numberAfterDot-1+exp) || mantissa & 1<<(numberAfterDot-2+exp)) return 1;
        return 0;
    }
}

Float StandartFloatToCustomFloat(float value) {
    Float temp = {*((unsigned int*)&value)};
    return temp;
}