#include <stdio.h>
#include <stdbool.h>

int main()
{
    int number = -1;
    printf("Enter the number up to which you want to know all the prime numbers:\n");
    int input = scanf("%d", &number);
    if (input != 1)
    {
        printf("You entered not a number\n");
        return 1;
    }
    printf("All prime numbers up to n:\n");
    for (int i = 2; i < number + 1; i++)
    {
        int hasDividers = false;
        for (int j = 2; j * j < i; j++)
        {
            if (i % j == 0)
            {
                hasDividers = true;
            }
        }
        if (!hasDividers)
        {
            printf("%d ", i);
        }
    }
}