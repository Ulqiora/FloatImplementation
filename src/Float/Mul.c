#include "Float.h"

Float Multiplication(Float val1,Float val2){
    Float res;
    printf("sign1= %d\n",GetSign(val1));
    if (GetSign(val1) ^ GetSign(val2)) SetSign(&res);
    int mantissa1 = GetMantissa(val1), mantissa2 = GetMantissa(val2);
    int degree1 = GetDegree(val1) - 127,
        degree2 = GetDegree(val2) - 127;
    int sumSign = calcNumDigitsAfterDot(mantissa2) + calcNumDigitsAfterDot(mantissa1);
    for(;sumSign>30;sumSign-=2){
        mantissa1>>=1;
        mantissa2>>=1;
    }
    int mantissa = mantissa1 * mantissa2;
    int numberSignAfterDots = calcNumDigitsAfterDot(mantissa);
    SetDegree(&res,degree1+degree2+127+numberSignAfterDots-sumSign);
    mantissa = (numberSignAfterDots > 23)
                   ? mantissa >> (numberSignAfterDots - 23) 
                   : mantissa << (23 - numberSignAfterDots);
    SetMantissa(&res,mantissa);
    return res;
}
