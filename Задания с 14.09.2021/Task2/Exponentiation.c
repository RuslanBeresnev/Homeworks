#include <stdio.h>
#include <stdbool.h>

float binaryExponentiation(int number, int power)
{
    if (number == 0 && power <= 0) {
        return -1;
    }
    if (power == 0)
    {
        return 1;
    }
    else if (abs(power) % 2 == 1)
    {
        if (power < 0) {
            return (float)(binaryExponentiation(number, power + 1) / (float)number);
        }
        return binaryExponentiation(number, power - 1) * number;
    }
    float halfPower = binaryExponentiation(number, power / 2);
    return halfPower * halfPower;
}

float simpleExponentiation(int number, int power)
{
    if (number == 0 && power <= 0) {
        return -1;
    }
    float result = 1;
    if (power >= 0)
    {
        for (int i = 0; i < power; i++)
        {
            result *= number;
        }
    }
    else
    {
        for (int i = 0; i < -power; i++)
        {
            result /= number;
        }
    }
    return result;
}

bool numberInPositivePower()
{
    return binaryExponentiation(5, 4) == 625 && simpleExponentiation(5, 4) == 625;
}

bool numberInNegativePower()
{
    return binaryExponentiation(2, -1) == 0.5 && simpleExponentiation(2, -1) == 0.5;
}

bool numberInZeroPower()
{
    return binaryExponentiation(5, 0) == 1 && simpleExponentiation(5, 0) == 1;
}

bool zeroInNotPositivePower()
{
    return binaryExponentiation(0, 0) == -1 && simpleExponentiation(0, 0) == -1 && binaryExponentiation(0, -1) == -1 && simpleExponentiation(0, -1) == -1;
}

bool generalTest()
{
    return numberInNegativePower() && numberInNegativePower() && numberInZeroPower() && zeroInNotPositivePower();
}

int main()
{
    if (!generalTest())
    {
        printf("Tests failed ...\n");
        return 1;
    }

    printf("Enter the number and power separated by a space:\n");
    int number = -1;
    int power = -1;
    int input = scanf("%d %d", &number, &power);
    if (input != 2)
    {
        printf("Something went wrong ...\n");
        return 1;
    }
    if (power >= 0)
    {
        printf("Raising the number %d to a power %d in linear time O(n): %d\n", number, power, (int)simpleExponentiation(number, power));
        printf("Raising the number %d to a power %d in logarithmic time O(log n): %d\n", number, power, (int)binaryExponentiation(number, power));
    }
    else
    {
        printf("Raising the number %d to a power %d in linear time O(n): %f\n", number, power, simpleExponentiation(number, power));
        printf("Raising the number %d to a power %d in logarithmic time O(log n): %f\n", number, power, binaryExponentiation(number, power));
    }
}