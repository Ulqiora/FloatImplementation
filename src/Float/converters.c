#include "Float.h"
void SetSign(Float* temp) { temp->value_ |= (1 << (NUMBER_BITS_IN_FLOAT - 1)); }
int GetSign(Float temp) { return temp.value_ & SIGN_BIT_MASK; }

//      Получает значение мантиссы с учетом целочисленной единицы и удалением пустых нулей в конце
int GetMantissa(Float value) {
    if(value.value_ == 0) return 0;
    int mantissa = (value.value_&SET_MANTISSA_BITS_MASK)|(FIRST_MANTISSA_BIT_MASK<<1);
    while ((!(mantissa & 1))) { mantissa >>= 1; }
    return mantissa;
}
//      Устанавливает биты для мантиссы
void SetMantissa(Float* res,int mantissa) {
    res->value_ |= (mantissa & SET_MANTISSA_BITS_MASK);
}
//      Возвращает порядок числа
int GetDegree(Float value){
    return ((value.value_ & GET_DEGREE_BIT_MASK) >> NUMBER_BITS_IN_MANTISSA);
}
//      Устанавливает порядок числа
void SetDegree(Float* temp,int value){
    temp->value_ |= (value) << NUMBER_BITS_IN_MANTISSA;
}
//      Получаем самую старшую степень двойки в числе
int CalcDegreeForFloat(unsigned int value) {
    int exp = 0;
    while (value >>= 1) exp++;
    return exp;
}
//      Модуль числа
int IntWithoutSign(int value) { return (value >= 0) ? value : -value; }
//      конвертер из int во Float
Float IntToFloat(int value) {
    Float temp = {0};
    if (!(value & 0xFFFFFFFF)) return temp;
    if (value & SIGN_BIT_MASK) SetSign(&temp), value = IntWithoutSign(value);
    int exp = CalcDegreeForFloat(value)-1;
    SetDegree(&temp,exp+DEGREE_SHIFT);
    int mantissa = (exp > 22) ? value >> (exp - 22) : value << (22 - exp);
    SetMantissa(&temp,mantissa);
    return temp;
}
//      конвертер из Float в Int
int FloatToInt(Float value) {
    int exp = GetDegree(value) - DEGREE_SHIFT;
    int mantissa = GetMantissa(value), mantissa_copy = mantissa;
    printf("exp: %d\n",exp);
    printf("mantissa: %d\n",mantissa);
    while (mantissa_copy != 1) {
        exp--;
        mantissa_copy >>= 1;
    }
    printf("exp: %d\n",exp);
    printf("mantissa: %d\n",mantissa);
    return mantissa * (1 << (exp)) * (GetSign(value) ? (-1) : (1));
}
Float FloatToFloat(float value) {
    Float temp = {*((int*)&value)};
    return temp;
}