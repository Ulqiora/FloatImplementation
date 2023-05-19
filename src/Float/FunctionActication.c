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
    int numberSignInMantissa = calcNumDigitsAfterDot(mantissa);
    int divisible = 1<<numberSignInMantissa;
    int degreeOfResult = 0;
    int mantissaResult = 0;
    // printf("%d\n%d\n",divisible,mantissa);
    while (divisible < mantissa) {
        divisible <<= 1;
        degreeOfResult--;
    }
    for(int i=0;i<=23;i++){
        mantissaResult = (mantissaResult << 1) |(divisible > mantissa ? 1:0) ;
        if(divisible > mantissa)divisible -= mantissa;
        divisible<<=1;
    }
    // unsigned int mask = SIGN_BIT_MASK;
    // for (int i = 31; i >= 0; mask >>= 1, i--) {
    //     printf("%d", !!(mantissaResult & mask));
    //     if(i==31 || i == 23)printf("  ");
    // }
    // printf("\n");
    // printf("%d\n%d\n", divisible, mantissa);
    degreeOfResult +=  (-degree+127);
    // for (int i = 31; i >= 0; mask >>= 1, i--) {
    //     printf("%d", !!(degreeOfResult & mask));
    //     if(i==31 || i == 23)printf("  ");
    // }
    sign == 0?ResetSign(&res):SetSign(&res);
    SetDegree(&res,degreeOfResult);
    SetMantissa(&res,mantissaResult);
    return res;
}
