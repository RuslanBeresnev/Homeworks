#pragma warning (disable: 4996 6031)

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

enum States
{
    START,
    INTEGER,
    INTEGER_AND_POINT,
    FLOAT,
    EXPONENTIAL_NUMBER_BEGINNING,
    SIGNS_POSITION,
    EXPONENTIAL_NUMBER
};

bool isRealNumber(const char sequence[])
{
    int state = START;
    int position = 0;

    while (sequence[position] != '\0')
    {
        char symbol = sequence[position];

        switch (state)
        {
        case START:
            if (symbol >= '0' && symbol <= '9')
            {
                state = INTEGER;
                break;
            }
            return false;
        case INTEGER:
            if (symbol == 'E')
            {
                state = EXPONENTIAL_NUMBER_BEGINNING;
                break;
            }
            else if (symbol == '.')
            {
                state = INTEGER_AND_POINT;
                break;
            }
            else if (symbol >= '0' && symbol <= '9')
            {
                state = INTEGER;
                break;
            }
            return false;
        case INTEGER_AND_POINT:
            if (symbol >= '0' && symbol <= '9')
            {
                state = FLOAT;
                break;
            }
            return false;
        case FLOAT:
            if (symbol == 'E')
            {
                state = EXPONENTIAL_NUMBER_BEGINNING;
                break;
            }
            else if (symbol >= '0' && symbol <= '9')
            {
                state = FLOAT;
                break;
            }
            return false;
        case EXPONENTIAL_NUMBER_BEGINNING:
            if (symbol == '+' || symbol == '-')
            {
                state = SIGNS_POSITION;
                break;
            }
            else if (symbol >= '0' && symbol <= '9')
            {
                state = EXPONENTIAL_NUMBER;
                break;
            }
            return false;
        case SIGNS_POSITION:
            if (symbol >= '0' && symbol <= '9')
            {
                state = EXPONENTIAL_NUMBER;
                break;
            }
            return false;
        case EXPONENTIAL_NUMBER:
            if (symbol >= '0' && symbol <= '9')
            {
                state = EXPONENTIAL_NUMBER;
                break;
            }
            return false;
        }

        position++;
    }

    if (state != INTEGER && state != FLOAT && state != EXPONENTIAL_NUMBER)
    {
        return false;
    }
    return true;
}

bool integerNumberTestPassed(void)
{
    return isRealNumber("567");
}

bool floatNumberTestPassed(void)
{
    return isRealNumber("111.32");
}

bool exponentialNumberTestPassed(void)
{
    return isRealNumber("5.5E+98") && isRealNumber("1E79");
}

bool incompleteNumberTestPassed(void)
{
    return !isRealNumber("4.5E+");
}

bool realNumberWithSymbolsInEndingTestPassed(void)
{
    return !isRealNumber("3.2E+98.E");
}

bool notRealNumberTestPassed(void)
{
    return !isRealNumber("RazbeR");
}

bool generalTestPassed(void)
{
    return integerNumberTestPassed() && floatNumberTestPassed() && exponentialNumberTestPassed() && incompleteNumberTestPassed()
        && realNumberWithSymbolsInEndingTestPassed() && notRealNumberTestPassed();
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");

    printf("Введите последовательность: ");
    char sequence[50] = { 0 };
    scanf("%s", sequence);

    if (isRealNumber(sequence))
    {
        printf("Это вещественное число !\n");
    }
    else
    {
        printf("Это не вещественное число ...\n");
    }
}