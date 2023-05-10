#include <stdio.h>
#include <gtest/gtest.h>
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
TEST(FloatDegree, calcNumDigitsAfterDot1) {
    unsigned int test=23;
    EXPECT_EQ(4,calcNumDigitsAfterDot(test));
}
TEST(FloatDegree, IntToCustomFloat1) {
    Float test=IntToCustomFloat(63);
    PrintBits(test);
    EXPECT_EQ(0,GetSign(test));
    EXPECT_EQ(5,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0b111111,GetMantissa(test));
}
TEST(FloatDegree, IntToCustomFloat2) {
    Float test=IntToCustomFloat(-127);
    PrintBits(test);
    EXPECT_EQ(1,GetSign(test));
    EXPECT_EQ(6,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0b1111111,GetMantissa(test));
}
TEST(FloatDegree, IntToCustomFloat3) {
    Float test=IntToCustomFloat(0x7FFFFFFF);
    PrintBits(test);
    EXPECT_EQ(0,GetSign(test));
    EXPECT_EQ(30,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0x7FFFFFFF>>7,GetMantissa(test));
}
TEST(FloatDegree, StandartFloatToCustomFloat3) {
    Float test=StandartFloatToCustomFloat(42.5f);
    PrintBits(test);
    EXPECT_EQ(0,GetSign(test));
    EXPECT_EQ(5,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0b1010101,GetMantissa(test));
}
TEST(FloatDegree, StandartFloatToCustomFloat3) {
    Float test=StandartFloatToCustomFloat(42.5f);
    PrintBits(test);
    EXPECT_EQ(0,GetSign(test));
    EXPECT_EQ(5,GetDegree(test)-DEGREE_SHIFT);
    EXPECT_EQ(0b1010101,GetMantissa(test));
}


int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}