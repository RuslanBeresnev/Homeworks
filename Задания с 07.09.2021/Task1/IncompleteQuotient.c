#include <stdio.h>
#include <stdlib.h>

int main()
{

    int a = 0;
    int b = 0;
    printf("Enter dividend and divider separated by a space to get the incomplete quotient of division:\n");
    const int input = scanf("%d %d", &a, &b);
    if (input != 2 || b == 0)
    {
        printf("We are amazed at your failure ...\n");
        return 1;
    }
    const int moduleA = abs(a);
    const int moduleB = abs(b);
    int incompleteQuotient = 0;
    int aDecreasing = moduleA;
    while (aDecreasing >= moduleB)
    {
        incompleteQuotient++;
        aDecreasing -= moduleB;
    }
    const int signOfNumberB = b >= 0 ? 1 : -1;
    if (a >= 0)
    {
        incompleteQuotient = incompleteQuotient * signOfNumberB;
    }
    else
    {
        if (aDecreasing == 0)
        {
            incompleteQuotient = incompleteQuotient * -signOfNumberB;
        }
        else
        {
            incompleteQuotient = (incompleteQuotient + 1) * -signOfNumberB;
        }
    }
    printf("Incomplete quotient of division: %d\n", incompleteQuotient);
}