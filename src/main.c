#include "float.h"

int main(){
    float val2=1256984.0;
    int val=1256984;
    unsigned int mask = SIGN_BIT_MASK;
    //printf("%d\n",0xFFFFFFFF>>32);
    printf("\n%d\n",val);
    Float temp = IntToFloat(val);
    // printf("KU");
    Float temp2 = FloatToFloat(val2);
    PrintBits(temp);
    PrintBits(temp2);
    printf("%d\n",FloatToInt(temp));
    printf("%f\n",val2);
}
// 11111111111111
// 1111111111111111
// 11111111111111