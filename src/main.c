#include "Float/Float.h"
// #include <gtest/gtest.h>
int main(){
    float val=4.5;
    int val2=-5;
    // unsigned int mask = SIGN_BIT_MASK;
    //printf("%d\n",0xFFFFFFFF>>32);
    Float temp = IntToCustomFloat(val2);

    // Float temp2 = FloatToFloat(val2);
    // Float res = MultiplicationWithoutSign(temp,temp2);
    PrintBits(temp);
    // PrintBits(temp2);
    // PrintBits(res);
    // PrintBits(FloatToFloat(22.5f));
    // PrintBits(FloatToFloat(0.42));
    // printf("%d",FloatToInt(FloatToFloat(0.5)));
    // printf("%d",(int)0.42);
    // printf("%d\n",FloatToInt(res));
    // printf("%d\n",FloatToInt(temp2));
}
