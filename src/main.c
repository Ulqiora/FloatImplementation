#include "Float/Float.h"
#include <stdio.h>
int main() {
    float val=10000;
    float val2=1/val;
    Float temp = StandartFloatToCustomFloat(val);
    Float temp2 = StandartFloatToCustomFloat(val2);
    // Float res = Addiction(temp,temp2);
    PrintBits(temp);
    PrintBits(temp2);
    // PrintBits(res);
    // Float res2=StandartFloatToCustomFloat(val+val2);
    // printf("%g\n",*((float*)&res2));
    // printf("%g\n",*((float*)&res));
    // printf("%g\n",1.75);
    // printf("%g\n",1/1.75);
    // printf("%d\n",1000000000/7);
    // FunctionActivation(temp2);
    Float res = HyperbolicFunction(temp);
    PrintBits(res);
    printf("My res = %g\n",*(float*)&res);
    printf("True res = %g\n",1/val);
}
