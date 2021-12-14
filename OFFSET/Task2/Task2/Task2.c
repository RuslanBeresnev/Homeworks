#pragma warning (disable: 4996 6031)

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

bool isDigit(char symbol)
{
    if (symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4' || symbol == '5' || symbol == '6' || symbol == '7'
        || symbol == '8' || symbol == '9')
    {
        return true;
    }
    return false;
}

bool isCorrectName(const char name[])
{
    int state = 0;
    int position = 0;

    while (position != 10)
    {
        char symbol = name[position];
        switch (state)
        {
        case 0:
            if (isDigit(symbol))
            {
                state = 1;
                break;
            }
            state = -1;
            break;
        case 1:
            if (isDigit(symbol))
            {
                state = 2;
                break;
            }
            state = -1;
            break;
        case 2:
            if (symbol == '.')
            {
                state = 3;
                break;
            }
            state = -1;
            break;
        case 3:
            if (symbol == 'B' || symbol == 'M' || symbol == 'S')
            {
                state = 4;
                break;
            }
            state = -1;
            break;
        case 4:
            if (isDigit(symbol))
            {
                state = 5;
                break;
            }
            state = -1;
            break;
        case 5:
            if (isDigit(symbol))
            {
                state = 6;
                break;
            }
            state = -1;
            break;
        case 6:
            if (symbol == '-')
            {
                state = 7;
                break;
            }
            state = -1;
            break;
        case 7:
            if (symbol == 'm')
            {
                state = 8;
                break;
            }
            state = -1;
            break;
        case 8:
            if (symbol == 'm')
            {
                state = 9;
                break;
            }
            state = -1;
            break;
        case 9:
            if (symbol != '\0')
            {
                state = -1;
                break;
            }
            break;
        }

        if (state == -1)
        {
            return false;
        }
        position++;
    }
    return true;
}

bool correctNameTestPassed(void)
{
    char group1[15] = "21.B10-mm";
    char group2[15] = "21.M10-mm";
    char group3[15] = "21.S10-mm";
    return isCorrectName(group1) && isCorrectName(group2) && isCorrectName(group3);
}

bool incorrectNameTestPassed(void)
{
    char group[15] = "21.V10-mm";
    return !isCorrectName(group);
}

bool correctNameWithSymbolsInEndingTestPassed(void)
{
    char group[20] = "21.B10-mmbestofall";
    return !isCorrectName(group);
}

bool generalTestPassed(void)
{
    return correctNameTestPassed() && incorrectNameTestPassed() && correctNameWithSymbolsInEndingTestPassed();
}

int main(void) 
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");
    printf("Введите название группы: ");
    char group[100] = { 0 };
    scanf("%s", &group);

    if (isCorrectName(group))
    {
        printf("Название группы корректно\n");
    }
    else
    {
        printf("Название группы некорректно\n");
    }
}