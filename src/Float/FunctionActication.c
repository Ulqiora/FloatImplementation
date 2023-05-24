#include "Float.h"

Float FunctionActivation(Float value){
    ResetSign(&value);
    Float one = IntToCustomFloat(1);
    value = AdditionWithoutSign(one, value);
    return HyperbolicFunction(value);
}

Float HyperbolicFunction(Float value){
    Float res;
    char sign= GetSign(value);
    int degree=GetDegree(value)-DEGREE_SHIFT;
    int mantissa = GetMantissa(value);
    int numberSignInMantissa = CalcNumDigitsAfterDot(mantissa);
    int divisible = 1<<numberSignInMantissa;
    int degreeOfResult = 0;
    int mantissaResult = 0;
    while (divisible < mantissa) {
        divisible <<= 1;
        degreeOfResult--;
    }
    for(int i=0;i<=23;i++){
        mantissaResult = (mantissaResult << 1) |(divisible > mantissa ? 1:0) ;
        if(divisible > mantissa)divisible -= mantissa;
        divisible<<=1;
    }
    degreeOfResult +=  (-degree+127);
    sign == 0?ResetSign(&res):SetSign(&res);
    SetDegree(&res,degreeOfResult);
    SetMantissa(&res,mantissaResult);
    return res;
}
