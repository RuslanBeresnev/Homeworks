#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <math.h>

#define INT_BITS_COUNT sizeof(int) * 8

#pragma warning (disable: 4774 5045 4996)

void bitwiseAddition(int firstNumber[], int secondNumber[], int resultNumber[])
{
    int currentBitSum = 0;
    int position = INT_BITS_COUNT - 1;
    while (position >= 0)
    {
        currentBitSum += (firstNumber[position] == 1) ? 1 : 0;
        currentBitSum += (secondNumber[position] == 1) ? 1 : 0;
        resultNumber[position] = currentBitSum % 2;
        currentBitSum /= 2;
        position--;
    }
}

void convertToBinary(int number, int binaryArray[])
{
    int bit = 1;
    for (int i = INT_BITS_COUNT - 1; i >= 0; i--)
    {
        binaryArray[i] = (number & bit) ? 1 : 0;
        bit = bit << 1;
    }
}

int convertToDecimal(int array[], int length)
{
    int decimalNumber = 0;
    int twoInNaturalPower = 1;
    for (int i = 0; i < length; i++)
    {
        decimalNumber += twoInNaturalPower * array[length - i - 1];
        twoInNaturalPower *= 2;
    }
    return decimalNumber;
}

void printBinaryNumber(int binaryArray[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf(i % 8 == 7 ? "%d " : "%d", binaryArray[i]);
    }
    printf("\n");
}

void printDecimalNumberInBinary(int number)
{
    int binaryArray[INT_BITS_COUNT] = { 0 };
    convertToBinary(number, binaryArray);
    printBinaryNumber(binaryArray, INT_BITS_COUNT);
}

bool testModule(int firstNumber, int secondNumber, int supposedSum)
{
    int firstNumberInBinary[INT_BITS_COUNT] = { 0 };
    int secondNumberInBinary[INT_BITS_COUNT] = { 0 };
    convertToBinary(firstNumber, firstNumberInBinary);
    convertToBinary(secondNumber, secondNumberInBinary);
    int sumOfTwonumbers[INT_BITS_COUNT] = { 0 };
    bitwiseAddition(firstNumberInBinary, secondNumberInBinary, sumOfTwonumbers);
    return convertToDecimal(sumOfTwonumbers, 32) == supposedSum;
}

bool generalTest(void)
{
    return testModule(5, 8, 13) && testModule(-5, -8, -13) && testModule(8, -9, -1) && testModule(0, 0, 0) && 
        testModule(2147483647, 5, -2147483644) && testModule(-2147483647, -2, 2147483647) && testModule(2147483647, 2147483647, -2);
}

int main(void)
{
    if (!generalTest())
    {
        printf("Tests Failed ...\n");
        return 1;
    }
    setlocale(LC_ALL, "Russian");
    printf("Введите два числа:\n");
    int firstNumber = 0;
    int secondNumber = 0;
    const int firstInput = scanf("%d", &firstNumber);
    if (firstInput != 1)
    {
        printf("Вы ввели некорректные данные ...\n");
        return 1;
    }
    const int secondInput = scanf("%d", &secondNumber);
    if (secondInput != 1)
    {
        printf("Вы ввели некорректные данные ...\n");
        return 1;
    }
    printf("\n");

    printf("Первое число в двоичном представлении: ");
    printDecimalNumberInBinary(firstNumber);

    printf("Второе число в двоичном представлении: ");
    printDecimalNumberInBinary(secondNumber);

    int firstNumberInBinary[INT_BITS_COUNT] = { 0 };
    int secondNumberInBinary[INT_BITS_COUNT] = { 0 };
    convertToBinary(firstNumber, firstNumberInBinary);
    convertToBinary(secondNumber, secondNumberInBinary);
    int sumOfTwonumbers[INT_BITS_COUNT] = { 0 };
    bitwiseAddition(firstNumberInBinary, secondNumberInBinary, sumOfTwonumbers);
    printf("Сумма двух чисел в двоичном представлении: ");
    printBinaryNumber(sumOfTwonumbers, INT_BITS_COUNT);
    printf("Сумма двух чисел в десятичном представлении: ");
    const int sumInDecimal = convertToDecimal(sumOfTwonumbers, 32);
    printf("%d", sumInDecimal);
    printf("\n");
}