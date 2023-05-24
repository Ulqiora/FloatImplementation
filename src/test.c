#include <stdio.h>
#include <gtest/gtest.h>
#include <cmath>
#include "Float/Float.h"
TEST(FloatSign, GetSignTest1) {
    Float test=IntToCustomFloat(5);
    EXPECT_EQ(0,GetSign(test));
}
TEST(FloatSign, GetSignTest2) {
    Float test=IntToCustomFloat(-5);
    EXPECT_EQ(1,GetSign(test));
}
TEST(FloatSign, SetSignTest1) {
    Float test=IntToCustomFloat(5);
    SetSign(&test);
    EXPECT_EQ(1,GetSign(test));
}
TEST(FloatSign, SetSignTest2) {
    Float test=IntToCustomFloat(-5);
    SetSign(&test);
    EXPECT_EQ(1,GetSign(test));
}
TEST(FloatSign, ResetSignTest1) {
    Float test=IntToCustomFloat(5);
    ResetSign(&test);
    EXPECT_EQ(0,GetSign(test));
}
TEST(FloatSign, ResetSignTest2) {
    Float test=IntToCustomFloat(-5);
    ResetSign(&test);
    EXPECT_EQ(0,GetSign(test));
}
TEST(FloatMantissa, GetMantissa1) {
    Float test=StandartFloatToCustomFloat(14.0);
    EXPECT_EQ(0b111,GetMantissa(test));
}
TEST(FloatMantissa, GetMantissa2) {
    Float test=StandartFloatToCustomFloat(13.0);
    EXPECT_EQ(0b1101,GetMantissa(test));
}
TEST(FloatMantissa, GetMantissa3) {
    Float test=StandartFloatToCustomFloat(5.5);
    EXPECT_EQ(0b1011,GetMantissa(test));
}
TEST(FloatMantissa, GetMantissa4) {
    Float test=StandartFloatToCustomFloat(5.75);
    EXPECT_EQ(0b10111,GetMantissa(test));
}
TEST(FloatMantissa, GetMantissa5) {
    Float test=StandartFloatToCustomFloat(5.875);
    EXPECT_EQ(0b101111,GetMantissa(test));
}
TEST(FloatMantissa, SetMantissa1) {
    Float test=IntToCustomFloat(0b11110001);
    SetMantissa(&test,0b111<<13);
    // PrintBits(test);
    EXPECT_EQ(0b10000000111,GetMantissa(test));
}
TEST(FloatMantissa, SetMantissa2) {
    Float test=IntToCustomFloat(1);
    SetMantissa(&test,0b111<<20);
    // PrintBits(test);
    EXPECT_EQ(0b1111,GetMantissa(test));
}
TEST(FloatDegree, GetDegree1) {
    Float test=IntToCustomFloat(1);
    EXPECT_EQ(127,GetDegree(test));
}
TEST(FloatDegree, GetDegree2) {
    Float test=IntToCustomFloat(4);
    EXPECT_EQ(129,GetDegree(test));
}
TEST(FloatDegree, GetDegree3) {
    Float test=StandartFloatToCustomFloat(0.526);
    EXPECT_EQ(126,GetDegree(test));
}
TEST(FloatDegree, SetDegree1) {
    Float test=IntToCustomFloat(1);
    SetDegree(&test,129);
    EXPECT_EQ(129,GetDegree(test));
}
TEST(FloatDegree, SetDegree2) {
    Float test=IntToCustomFloat(1);
    SetDegree(&test,123);
    EXPECT_EQ(123,GetDegree(test));
}
TEST(FloatDegree, СalcNumDigitsAfterDot1) {
    unsigned int test=23;
    EXPECT_EQ(4,CalcNumDigitsAfterDot(test));
}
TEST(MyFloat, IntToCustomFloat1) {
    Float test=IntToCustomFloat(63);
    PrintBits(test);
    EXPECT_EQ(0,GetSign(test));
    EXPECT_EQ(5,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0b111111,GetMantissa(test));
}
TEST(MyFloat, IntToCustomFloat2) {
    Float test=IntToCustomFloat(-127);
    PrintBits(test);
    EXPECT_EQ(1,GetSign(test));
    EXPECT_EQ(6,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0b1111111,GetMantissa(test));
}
TEST(MyFloat, IntToCustomFloat3) {
    Float test=IntToCustomFloat(0x7FFFFFFF);
    PrintBits(test);
    EXPECT_EQ(0,GetSign(test));
    EXPECT_EQ(30,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0x7FFFFFFF>>7,GetMantissa(test));
}
TEST(MyFloat, StandartFloatToCustomFloat3) {
    Float test=StandartFloatToCustomFloat(42.5f);
    PrintBits(test);
    EXPECT_EQ(0,GetSign(test));
    EXPECT_EQ(5,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0b1010101,GetMantissa(test));
}
TEST(MyFloat, StandartFloatToCustomFloat4) {
    Float test=StandartFloatToCustomFloat(42.5f);
    PrintBits(test);
    EXPECT_EQ(0,GetSign(test));
    EXPECT_EQ(5,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0b1010101,GetMantissa(test));
}
TEST(MyFloat, StandartFloatToCustomFloat5) {
    Float test=StandartFloatToCustomFloat(42.5f);
    PrintBits(test);
    EXPECT_EQ(0,GetSign(test));
    EXPECT_EQ(5,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0b1010101,GetMantissa(test));
}
TEST(MyFloat, Addiction1) {
    Float val1=StandartFloatToCustomFloat(42.5f);
    Float val2=StandartFloatToCustomFloat(42.5f);
    Float res = Addiction(val1, val2);
    float resFloat = *(float*)&res,resStand=85.0f;
    EXPECT_EQ(resFloat,resStand);
}
TEST(MyFloat, Addiction2) {
    float temp1 = 8954.632f, temp2 = 895.5632f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Addiction(val1, val2);
    float resFloat = *(float*)&res,resStand=temp1 + temp2;
    printf("%g\n",resFloat);
    printf("%g\n",resStand);
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-2);
}
TEST(MyFloat, Addiction3) {
    float temp1 = 0.75638f, temp2 = 0.125364f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Addiction(val1, val2);
    float resFloat = *(float*)&res,resStand=temp1 + temp2;
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-6);
}

TEST(MyFloat, Addiction4) {
    float temp1 = 1.75638f, temp2 = -0.75638f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Addiction(val1, val2);
    float resFloat = *(float*)&res,resStand=temp1 + temp2;
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-6);
}
TEST(MyFloat, Addiction5) {
    float temp1 = 1489.75638f, temp2 = -5729.75638f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Addiction(val1, val2);
    float resFloat = *(float*)&res,resStand=temp1 + temp2;
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-6);
}
TEST(MyFloat, Addiction6) {
    float temp1 = -1489.75638f, temp2 = -5729.75638f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Addiction(val1, val2);
    float resFloat = *(float*)&res,resStand=temp1 + temp2;
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-6);
}
TEST(MyFloat, Multiplication1) {
    float temp1 = -148.75638f, temp2 = -579.75638f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Multiplication(val1, val2);
    float resFloat = *(float*)&res,resStand=temp1 * temp2;
    printf("%f\n",resFloat);
    printf("%f\n",resStand);
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e1);
}
TEST(MyFloat, Multiplication2) {
    float temp1 = -1.5f, temp2 = 1.5f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Multiplication(val1, val2);
    float resFloat = *(float*)&res,resStand=temp1 * temp2;
    printf("%f\n",resFloat);
    printf("%f\n",resStand);
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-5);
}
TEST(MyFloat, Multiplication3) {
    float temp1 = -0.53684f, temp2 = 0.234985f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Multiplication(val1, val2);
    float resFloat = *(float*)&res,resStand=temp1 * temp2;
    printf("%f\n",resFloat);
    printf("%f\n",resStand);
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-3);
}
TEST(MyFloat, Multiplication4) {
    float temp1 = 236.5986f, temp2 = -2.4569f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Multiplication(val1, val2);
    float resFloat = *(float*)&res,resStand=temp1 * temp2;
    printf("%f\n",resFloat);
    printf("%f\n",resStand);
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-1);
}
TEST(MyFloat, Multiplication5) {
    float temp1 = 2.12366f, temp2 = 0.03569f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float val2=StandartFloatToCustomFloat(temp2);
    Float res = Multiplication(val1, val2);
    PrintBits(res);
    float resFloat = *(float*)&res,resStand=temp1 * temp2;
    PrintBits(*(Float*)(&resStand));
    printf("%f\n",resFloat);
    printf("%f\n",resStand);
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-5);
}
TEST(MyFloat, HyperbolicFunction1) {
    float temp1 = -0.53684f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float res = HyperbolicFunction(val1);
    float resFloat = *(float*)&res,resStand=1/temp1;
    printf("%f\n",resFloat);
    printf("%f\n",resStand);
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-5);
}
TEST(MyFloat, HyperbolicFunction2) {
    float temp1 = -234651.53684f;
    Float val1=StandartFloatToCustomFloat(temp1);
    Float res = HyperbolicFunction(val1);
    float resFloat = *(float*)&res,resStand=1/temp1;
    printf("%f\n",resFloat);
    printf("%f\n",resStand);
    EXPECT_TRUE(fabs(resFloat - resStand) < 1e-5);
}


int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}