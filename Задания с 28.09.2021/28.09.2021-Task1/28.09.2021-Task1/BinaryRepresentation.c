#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <math.h>
#define INT_BITS_COUNT sizeof(int) * 8

void copyNumbersArray(int originArray[], int length, int copiedArray[])
{
    for (int i = 0; i < length; i++)
    {
        copiedArray[i] = originArray[i];
    }
}

void reverseArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        const int bufferElement = array[length - 1];
        for (int j = length - 2; j >= i; j--)
        {
            array[j + 1] = array[j];
        }
        array[i] = bufferElement;
    }
}

void bitwiseAddition(int firstNumber[], int firstLength, int secondNumber[], int secondLength, int resultNumber[])
{
    reverseArray(firstNumber, firstLength);
    reverseArray(secondNumber, secondLength);
    int currentBitSum = 0;
    int position = 0;
    const int maxLength = (firstLength < secondLength) ? secondLength : firstLength;
    while (position < INT_BITS_COUNT && (currentBitSum > 0 || position < maxLength))
    {
        if (position < firstLength)
        {
            currentBitSum += (firstNumber[position] == 1) ? 1 : 0;
        }
        if (position < secondLength)
        {
            currentBitSum += (secondNumber[position] == 1) ? 1 : 0;
        }
        resultNumber[position] = currentBitSum % 2;
        currentBitSum /= 2;
        position++;
    }
    reverseArray(resultNumber, position);
}

//void convertToBinary(int number, int binaryArray[])
//{
//    bool negativeNumber = false;
//    if (number < 0)
//    {
//        negativeNumber = true;
//        number = -number;
//    }
//    int length = 0;
//    while (number > 0)
//    {
//        binaryArray[length] = number % 2;
//        number /= 2;
//        length++;
//    }
//    for (int i = length; i < INT_BITS_COUNT; i++)
//    {
//        binaryArray[i] = 0;
//    }
//    reverseArray(binaryArray, INT_BITS_COUNT);
//    if (negativeNumber)
//    {
//        binaryArray[0] = 1;
//        for (int i = 1; i < INT_BITS_COUNT; i++)
//        {
//            binaryArray[i] = (binaryArray[i] == 1) ? 0 : 1;
//        }
//        int unit[1] = { 1 };
//        int binaryArrayCopy[INT_BITS_COUNT] = { 0 };
//        copyNumbersArray(binaryArray, INT_BITS_COUNT, binaryArrayCopy);
//        bitwiseAddition(binaryArrayCopy, INT_BITS_COUNT, unit, 1, binaryArray);
//    }
//}

void convertToBinary(int number, int binaryArray[])
{
    int bit = 0b00000000000000000000000000000001;
    for (int i = INT_BITS_COUNT - 1; i >= 0; i--)
    {
        binaryArray[i] = (number & bit) ? 1 : 0;
        bit = bit << 1;
    }
}

int convertToDecimal(int array[], int length)
{
    int decimalNumber = 0;
    for (int power = length - 1; power >= 0; power--)
    {
        decimalNumber += (int)pow(2, power) * array[length - power - 1];
    }
    return decimalNumber;
}

void printBinaryNumber(int binaryArray[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (i % 8 == 7)
        {
            printf("%d ", binaryArray[i]);
        }
        else
        {
            printf("%d", binaryArray[i]);
        }
    }
    printf("\n");
}

void printDecimalNumberInBinary(number)
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
    bitwiseAddition(firstNumberInBinary, INT_BITS_COUNT, secondNumberInBinary, INT_BITS_COUNT, sumOfTwonumbers);
    return convertToDecimal(sumOfTwonumbers, 32) == supposedSum;
}

bool generalTest()
{
    return testModule(5, 8, 13) && testModule(-5, -8, -13) && testModule(8, -9, -1) && testModule(0, 0, 0) && testModule(2147483647, 5, -2147483644) && testModule(-2147483647, -2, 2147483647) && testModule(2147483647, 2147483647, -2);
}

int main()
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
    bitwiseAddition(firstNumberInBinary, INT_BITS_COUNT, secondNumberInBinary, INT_BITS_COUNT, sumOfTwonumbers);
    printf("Сумма двух чисел в двоичном представлении: ");
    printBinaryNumber(sumOfTwonumbers, INT_BITS_COUNT);
    printf("Сумма двух чисел в десятичном представлении: ");
    const int sumInDecimal = convertToDecimal(sumOfTwonumbers, 32);
    printf("%d", sumInDecimal);
    printf("\n");
}