#include <stdio.h>

int main()
{
    int numericArray[100] = { 0 };
    int n = -1;
    int count = 0;
    printf("Enter the count of numbers:\n");
    int nInput = scanf("%d", &n);
    if (nInput != 1)
    {
        printf("You entered not a number\n");
        return 1;
    }
    printf("Enter %d numbers:\n", n);
    int number = -1;
    for (int i = 0; i < n; i++)
    {
        int input = scanf("%d", &number);
        if (input != 1)
        {
            printf("You entered not a number\n");
            return 1;
        }
        numericArray[i] = number;
    }
    for (int i = 0; i < n; i++)
    {
        if (numericArray[i] == 0)
        {
            count++;
        }
    }
    printf("The count of zero elements in the array: %d\n", count);
}