#include "Float/Float.h"

int main(){
    float val=0.256;
    float val2=15986.00000256;
    // unsigned int mask = SIGN_BIT_MASK;
    //printf("%d\n",0xFFFFFFFF>>32);
    Float temp = FloatToFloat(val);
    Float temp2 = FloatToFloat(val2);
    Float res = addiction(temp,temp2);
    Float temp3 = FloatToFloat(val+val2);
    PrintBits(temp);
    PrintBits(temp2);
    PrintBits(res);
    PrintBits(temp3);
    // printf("%d\n",FloatToInt(temp));
    // printf("%d\n",FloatToInt(temp2));
}
// 11111111111111
// 1111111111111111
// 11111111111111