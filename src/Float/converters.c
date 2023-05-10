#include "Float.h"
void SetSign(Float* temp) { temp->value_ |= SIGN_BIT_MASK; }
int GetSign(Float temp) { return !!(temp.value_ & SIGN_BIT_MASK); }
void ResetSign(Float* temp){ temp->value_ &=~ SIGN_BIT_MASK;}
/**
 * GetMantissa
 * Данная фунция вычисляет значение мантиссы с учетом первой единицы и смещением до первой единицы с конца.
 * @param[in] value число, чью мантиссу необходимо получить.
 * @return Мантиссу числа.
 */
int GetMantissa(Float value) {
    if(value.value_ == 0) return 0;
    int mantissa = (value.value_&SET_MANTISSA_BITS_MASK)|(FIRST_MANTISSA_BIT_MASK<<1);
    while ((!(mantissa & 1))) { mantissa >>= 1; }
    return mantissa;
}
/**
 * SetMantissa
 * Устанавливает биты для мантиссы, которая уже смещена под нужные разряды.
 * @param[out] res число, чью мантиссу необходимо изменить.
 * @param[in] mantissa мантисса, вставляемая в переменную.
 */
void SetMantissa(Float* res,int mantissa) {
    res->value_ &=~ SET_MANTISSA_BITS_MASK;
    res->value_ |= (mantissa & SET_MANTISSA_BITS_MASK);
}
//      Возвращает порядок числа
/**
 * GetDegree
 * получает порядок числа.
 * @param[in] value число, чей порядок необходимо получить.
 * @return порядок числа(диапазон: 0-255).
 */
int GetDegree(Float value){
    return ((value.value_ & GET_DEGREE_BIT_MASK) >> NUMBER_BITS_IN_MANTISSA);
}
/**
 * SetDegree
 * Устанавливает порядок числа
 * @param[out] res число, чей порядок необходимо изменить.
 * @param[in] degree порядок числа(диапазон: 0-255).
 */
void SetDegree(Float* res, int degree){
    res->value_ &=~ GET_DEGREE_BIT_MASK;
    res->value_ |= (degree) << NUMBER_BITS_IN_MANTISSA;
}
/**
 * calcNumDigitsAfterDot
 * Получает число цифр после первой единицы справа
 * @param[out] value аргумент, число цифр котрого необходимо определить.
 * @return результат.
 */
int calcNumDigitsAfterDot(unsigned int value) {
    int exp = 0;
    while (value >>= 1) exp++;
    return exp;
}
/**
 * CustomAbs
 * Модуль числа
 * @param[out] res число, модуль которого берется.
 * @return результат.
 */
int CustomAbs(int value) { return (value >= 0) ? value : -value; }
/**
 * IntToCustomFloat
 * Получает число цифр после первой единицы справа
 * @param[in] value число, котрое надо кастовать к Float.
 * @return результат преобразования.
 */
Float IntToCustomFloat(int value) {
    Float temp = {0};
    if (!(value & 0xFFFFFFFF)) return temp;
    if (value & SIGN_BIT_MASK) SetSign(&temp), value = CustomAbs(value);
    int digitsAfterDots = calcNumDigitsAfterDot(value);
    printf("number sign  after dot: %d\n", digitsAfterDots);
    SetDegree(&temp,(digitsAfterDots--)+DEGREE_SHIFT);
    int mantissa = (digitsAfterDots > 22) ? value >> (digitsAfterDots - 22) : value << (22 - digitsAfterDots);
    SetMantissa(&temp,mantissa);
    return temp;
}
/**
 * CustomFloatToInt
 * опреобразование в int
 * @param[in] value число, которое надо кастовать к int.
 * @return результат преобразования.
 */
int CustomFloatToInt(Float value) {
    int exp = GetDegree(value) - DEGREE_SHIFT;
    int mantissa = GetMantissa(value), mantissa_copy = mantissa;
    if (exp >= 0) {
        int numberAfterDot= calcNumDigitsAfterDot(mantissa);
        mantissa<<=exp;
        mantissa>>=numberAfterDot;
        return mantissa * (GetSign(value) ? (-1) : (1));
    } else {
        mantissa>>(-exp);
        int numberAfterDot= calcNumDigitsAfterDot(mantissa);
        if(mantissa & 1<<(numberAfterDot-1+exp) || mantissa & 1<<(numberAfterDot-2+exp)) return 1;
        return 0;
    }
}
/**
 * CustomFloatToInt
 * преобразование float к Float
 * @param[in] value число, которое надо кастовать к Float.
 * @return результат преобразования.
 */
Float StandartFloatToCustomFloat(float value) {
    Float temp = {*((int*)&value)};
    return temp;
}