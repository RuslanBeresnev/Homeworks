#pragma warning (disable: 4996 6031)

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

bool isRealNumber(const char number[])
{
    int state = 0;
    int position = 0;

    while (position != 10)
    {
        char symbol = number[position];
        switch (state)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
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

int main(void)
{
    setlocale(LC_ALL, "Russian");

    printf("Введите последовательность: ");
    char sequence[30] = { 0 };
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