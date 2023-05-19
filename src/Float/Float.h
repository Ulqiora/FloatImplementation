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

/**
 * Multiplication
 * умножение двух чисел.
 * @param[in] val1 первое число.
 * @param[in] val2 второе число.
 * @return Результат вычисления.
 */
Float Multiplication(Float val1,Float val2);
/**
 * SetSign
 * Выставление бита знака.
 * @param[out] temp число, бит знака которого надо выставить.
 */
void SetSign(Float* temp);
/**
 * ResetSign
 * Сброс бита знака.
 * @param[out] temp число, бит знака которого надо сбросить.
 */
void ResetSign(Float* temp);
/**
 * GetSign
 * Получает бит знака.
 * @param[out] temp число, знак которого надо получить.
 * @return состояния бита знака(0-1).
 */
int GetSign(Float temp);
/**
 * GetMantissa
 * Данная фунция вычисляет значение мантиссы с учетом первой единицы и смещением до первой единицы с конца.
 * @param[in] value число, чью мантиссу необходимо получить.
 * @return Мантиссу числа.
 */
int GetMantissa(Float value);
/**
 * SetMantissa
 * Устанавливает биты для мантиссы, которая уже смещена под нужные разряды.
 * @param[out] res число, чью мантиссу необходимо изменить.
 * @param[in] mantissa мантисса, вставляемая в переменную.
 */
void SetMantissa(Float* temp,int mantissa);
/**
 * GetDegree
 * получает порядок числа.
 * @param[in] value число, чей порядок необходимо получить.
 * @return порядок числа(диапазон: 0-255).
 */
int GetDegree(Float value);
/**
 * SetDegree
 * Устанавливает порядок числа
 * @param[out] res число, чей порядок необходимо изменить.
 * @param[in] degree порядок числа(диапазон: 0-255).
 */
void SetDegree(Float* temp,int value);
/**
 * calcNumDigitsAfterDot
 * Получает число цифр после первой единицы справа
 * @param[out] value аргумент, число цифр котрого необходимо определить.
 * @return результат.
 */
int calcNumDigitsAfterDot(unsigned int value);
/**
 * CustomAbs
 * Модуль числа
 * @param[out] res число, модуль которого берется.
 * @return результат.
 */
int CustomAbs(int value);
/**
 * IntToCustomFloat
 * Получает число цифр после первой единицы справа
 * @param[in] value число, котрое надо кастовать к Float.
 * @return результат преобразования.
 */
Float IntToCustomFloat(int value);
/**
 * CustomFloatToInt
 * опреобразование в int
 * @param[in] value число, которое надо кастовать к int.
 * @return результат преобразования.
 */
int CustomFloatToInt(Float value);
/**
 * addiction
 * сложение двух чисел.
 * @param[in] val1 первое число.
 * @param[in] val2 второе число.
 * @return Результат вычисления.
 */
Float addiction(Float val1,Float val2);
/**
 * AdditionWithoutSign
 * Сложение двух чисел без учета знака.
 * @param[in] val1 первое число.
 * @param[in] val2 второе число.
 * @return Результат вычисления.
 */
Float AdditionWithoutSign(Float val1,Float val2);
/**
 * SubtractionWithoutSign
 * вычитание двух чисел без учета знака.
 * @param[in] val1 первое число.
 * @param[in] val2 второе число.
 * @return Результат вычисления.
 */
Float SubtractionWithoutSign(Float val1,Float val2);
/**
 * CustomFloatToInt
 * опреобразование в int
 * @param[out] mant1 мантисса первого числа.
 * @param[out] mant2 мантисса второго числа.
 * @param[in] numberAfterDot1 число цифр после запятой для первого числа.
 * @param[in] numberAfterDot2 число цифр после запятой для второго числа.
 * @return номер бита, после которого поставлена точка в мантиссах.
 */
int shiftByDot(int* mant1,int* mant2,int degree1,int degree2);
/**
 * CustomFloatToInt
 * опреобразование в int
 * @param[out] mant1 мантисса первого числа.
 * @param[out] mant1 мантисса второго числа.
 * @param[in] degree1 порядок первого числа.
 * @param[in] degree2 порядок второго числа.
 * @return порядок, по которому выравнены числа.
 */
int shiftByDegree(int* mant1,int* mant2,int degree1,int degree2);
/**
 * FunctionActivation
 * функция активации.
 * @param[in] value аргумент.
 * @return результат(0.0-1.0).
 */
Float FunctionActivation(Float value);
/**
 * FunctionActivation
 * результат функции y=1/x.
 * @param[in] value аргумент.
 * @return результат   y .
 */
Float HyperbolicFunction(Float value);
//                                                                          Для тестирования
/**
 * CustomFloatToInt
 * преобразование float к Float
 * @param[in] value число, которое надо кастовать к Float.
 * @return результат преобразования.
 */
Float StandartFloatToCustomFloat(float value);
//  Для отладки
void PrintSign(Float temp);
void PrintDegree(Float temp);
void PrintMantissa(Float temp);
void PrintBits(Float temp);