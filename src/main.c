#include "Float/Float.h"

int main(){
    float val=15.56;
    float val2=0.256;
    // unsigned int mask = SIGN_BIT_MASK;
    //printf("%d\n",0xFFFFFFFF>>32);
    Float temp = FloatToFloat(val);
    Float temp2 = FloatToFloat(val2);
    Float res = SubtractionWithoutSign(temp,temp2);
    Float temp3 = FloatToFloat(val-val2);
    PrintBits(temp);
    PrintBits(temp2);
    PrintBits(res);
    // PrintBits(FloatToFloat(0.42));
    printf("%d",FloatToInt(FloatToFloat(0.5)));
    // printf("%d",(int)0.42);
    // printf("%d\n",FloatToInt(temp));
    // printf("%d\n",FloatToInt(temp2));
}
// 11111111111111
// 1111111111111111
// 11111111111111