#include <stdio.h>

#define SIGN_BIT_MASK 0x80000000
#define FIRST_DEGREE_BIT_MASK 0x40000000
#define FIRST_MANTISSA_BIT_MASK 0x400000
#define SET_MANTISSA_BITS_MASK 0x7FFFFF
#define DEGREE_SHIFT 127
#define NUMBER_BITS_IN_DEGREE 8
#define NUMBER_BITS_IN_MANTISSA 23
#define NUMBER_BITS_IN_FLOAT 32

typedef struct float_s {
    unsigned int value_;
} Float;

void SetSign(Float* temp) { temp->value_ |= (1 << (NUMBER_BITS_IN_FLOAT - 1)); }

void PrintSign(Float temp) {
    printf("\033[31m");
    printf("%4d", !!((temp.value_) & SIGN_BIT_MASK));
    printf("\033[0m");
}

void PrintDegree(Float temp) {
    unsigned int mask = FIRST_DEGREE_BIT_MASK;
    printf("\033[34m");
    for (int i = 30; i >= NUMBER_BITS_IN_MANTISSA; i--, mask >>= 1)
        printf("%d", !!((temp.value_) & mask));
    printf("\033[0m");
}

void PrintMantissa(Float temp) {
    unsigned int mask = FIRST_MANTISSA_BIT_MASK;
    printf("\033[32m");
    for (int i = 22; i >= 0; i--, mask >>= 1)
        printf("%d", !!((temp.value_) & mask));
    printf("\033[0m");
}

void PrintBits(Float temp) {
    printf("Sign|Matissa |other\n");
    PrintSign(temp);
    printf(" ");
    PrintDegree(temp);
    printf(" ");
    PrintMantissa(temp);
    printf("\n");
}

int GetSign(Float temp){return temp.value_ & SIGN_BIT_MASK;}

int CalcDegreeForFloat(unsigned int value) {
    int exp = 0;
    while (value >>= 1) exp++;
    return exp;
}

int IntWithoutSign(int value) { return (value >= 0) ? value : -value; }

Float IntToFloat(int value) {
    Float temp = {0};
    if (!(value & 0xFFFFFFFF)) return temp;
    if (value & SIGN_BIT_MASK) SetSign(&temp), value = IntWithoutSign(value);
    int exp = CalcDegreeForFloat(value);
    temp.value_ |= (exp + DEGREE_SHIFT) << 23;
    exp--;
    int mantissa = exp > 22 ? value >> (exp - 22) : value << (22 - exp);
    temp.value_ |= (mantissa & SET_MANTISSA_BITS_MASK);
    return temp;
}
int FloatToInt(Float value) {
    int temp=0;
    int exp=((value.value_&0x7F800000)>>NUMBER_BITS_IN_MANTISSA)-127;
    int mantissa=(value.value_&SET_MANTISSA_BITS_MASK)|(FIRST_MANTISSA_BIT_MASK<<1);
    while(!(mantissa&0x00000001)) mantissa>>=1;
    int mantissa_copy=mantissa;
    while (mantissa_copy != 1) {
        exp--; 
        mantissa_copy >>= 1;
    }
    printf("exp: %d\n",exp);
    printf("mantissa: %d\n",mantissa);
    return mantissa * (1<<exp) * (GetSign(value)?(-1):(1));
}
// 
Float FloatToFloat(float value) {
    Float temp = {*((int*)&value)};
    return temp;
}