#include <stdio.h>

void flipTheArray(int array[], int beginIndex, int endIndex) // Функция переворота части массива с индекса beginIndex по индекс endIndex
{
    for (int i = beginIndex; i < beginIndex + (endIndex + 1 - beginIndex) / 2; i++)
    {
        int bufferValue = array[i];
        array[i] = array[endIndex - (i - beginIndex)];
        array[endIndex - (i - beginIndex)] = bufferValue;
    }
}

int main()
{
    int joinedArray[100] = { 0 };
    int m = 0;
    int n = 0;
    printf("Enter the length of the first line:\n");
    int mInput = scanf("%d", &m);
    if (mInput != 1 || m <= 0)
    {
        printf("You entered not a number or first line length less than 1 ...\n");
        return 1;
    }
    printf("Enter the length of the second line:\n");
    int nInput = scanf("%d", &n);
    if (nInput != 1 || n <= 0) {
        printf("You entered not a number or second line length less than 1 ...\n");
        return 1;
    }
    printf("Enter numbers for array:\n");
    for (int i = 0; i < m + n; i++)
    {
        int enteredNumber = -1;
        int numberInput = scanf("%d", &enteredNumber);
        if (numberInput != 1)
        {
            printf("You entered not a number ...\n");
            return 1;
        }
        joinedArray[i] = enteredNumber;
    }

    flipTheArray(joinedArray, 0, m - 1);
    flipTheArray(joinedArray, m, m + n - 1);
    flipTheArray(joinedArray, 0, m + n - 1);

    printf("Your inverted array completed: ");
    for (int i = 0; i < m + n; i++)
    {
        printf("%d ", joinedArray[i]);
    }
    printf("\n");
}