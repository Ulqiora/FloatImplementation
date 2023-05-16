#include "Float/Float.h"
// #include <gtest/gtest.h>
#include <stdio.h>
int main() {
    float val=1.75;
    float val2=1.8125;
    Float intres = {0b11101*0b111};
    Float temp = StandartFloatToCustomFloat(val2);
    Float temp2 = StandartFloatToCustomFloat(val);
    Float res = MultiplicationWithoutSign(temp,temp2);
    PrintBits(temp);
    PrintBits(temp2);
    PrintBits(res);
    Float res2=StandartFloatToCustomFloat(val*val2);
    printf("%g\n",*((float*)&res2));
    printf("%g\n",*((float*)&res));
}
