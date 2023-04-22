#include <stdio.h>

#define SIGN_BIT_MASK 0x80000000
#define FIRST_DEGREE_BIT_MASK 0x40000000
#define GET_DEGREE_BIT_MASK 0x7F800000
#define FIRST_MANTISSA_BIT_MASK 0x400000
#define SET_MANTISSA_BITS_MASK 0x7FFFFF
#define DEGREE_SHIFT 127
#define NUMBER_BITS_IN_DEGREE 8
#define NUMBER_BITS_IN_MANTISSA 23
#define NUMBER_BITS_IN_FLOAT 32

typedef struct float_s {
    unsigned int value_;
} Float;


void PrintSign(Float temp);
void PrintDegree(Float temp);
void PrintMantissa(Float temp);
void PrintBits(Float temp);

void SetSign(Float* temp);
int GetSign(Float temp);
int GetMantissa(Float value);
void SetMantissa(Float* temp,int mantissa);
int GetDegree(Float value);
void SetDegree(Float* temp,int value);


int CalcDegreeForFloat(unsigned int value);
int IntWithoutSign(int value);
Float IntToFloat(int value);
int FloatToInt(Float value);
// 
Float FloatToFloat(float value);
//

Float AdditionWithoutSign(Float val1,Float val2);
Float SubtractionWithoutSign(Float val1,Float val2);
int shiftByDot(int* mant1,int* mant2,int degree1,int degree2);
int shiftByOrder(int* mant1,int* mant2,int degree1,int degree2);
// int shiftMantisses(int* mantissa1,int* mantissa2, int shift);