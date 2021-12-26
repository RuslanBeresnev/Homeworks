#pragma warning (disable: 4996 6031)

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

int power(const int number, const int power)
{
    int result = 1;
    for (int i = 0; i < power; i++)
    {
        result *= number;
    }
    return result;
}

int convertBinaryToDecimal(const char binaryString[])
{
    const int length = (int)strlen(binaryString);
    int decimalNumber = 0;

    for (int position = 0; position < length; position++)
    {
        if ((int)binaryString[position] - 48 > 1)
        {
            return -1;
        }
        decimalNumber += ((int)binaryString[position] - 48) * power(2, length - position - 1);
    }

    return decimalNumber;
}

bool standardTestPassed(void)
{
    char binaryString[10] = "10010";
    return convertBinaryToDecimal(binaryString) == 18;
}

bool nullNumberTestPassed(void)
{
    char binaryString[10] = "000000000";
    return convertBinaryToDecimal(binaryString) == 0;
}

bool generalTest(void)
{
    return standardTestPassed() && nullNumberTestPassed();
}

int main(void)
{
    if (!generalTest())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");
    printf("Введите двоичное представление числа: ");
    char binaryString[100] = { 0 };
    scanf("%s", &binaryString);
    const int decimalNumber = convertBinaryToDecimal(binaryString);
    if (decimalNumber == -1)
    {
        printf("Вы ввели не двоичное число ...\n");
        return 1;
    }
    printf("Десятичное представление числа: %d\n", decimalNumber);
}