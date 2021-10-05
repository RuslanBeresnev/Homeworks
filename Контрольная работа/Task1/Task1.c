#include <stdio.h>
#include <stdbool.h>

int numbersArrayInput(int array[], int count)
{
    for (int i = 0; i < count; i++)
    {
        int number = 0;
        const int numberInput = scanf("%d", &number);
        if (numberInput != 1)
        {
            return 1;
        }
        array[i] = number;
    }
    return 0;
}

void numbersArrayOutput(int array[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int getNumberLength(int number)
{
    int length = 0;
    while (number > 0)
    {
        length++;
        number /= 10;
    }
    return length;
}

int getDigitsSumm(int number)
{
    int numberSumm = 0;
    while (number > 0)
    {
        numberSumm += number % 10;
        number /= 10;
    }
    return numberSumm;
}

int getNumbersWithMaxSumm(int array[], int count, int resultArray[])
{
    int maxSumm = 0;
    for (int i = 0; i < count; i++)
    {
        const int numberSumm = getDigitsSumm(array[i]);
        if (numberSumm > maxSumm)
        {
            maxSumm = numberSumm;
        }
    }

    int j = 0;
    for (int i = 0; i < count; i++)
    {
        if (getDigitsSumm(array[i]) == maxSumm)
        {
            resultArray[j] = array[i];
            j++;
        }
    }
    return j;
}

bool standardCase()
{
    int testedArray[3] = { 555, 55, 5 };
    int resultArray[3] = { 0 };
    getNumbersWithMaxSumm(testedArray, 3, resultArray);
    return resultArray[0] == 555;
}

bool severalResultNumsCase()
{
    int testedArray[3] = { 555, 663, 5 };
    int resultArray[3] = { 0 };
    getNumbersWithMaxSumm(testedArray, 3, resultArray);
    return resultArray[0] == 555 && resultArray[1] == 663;
}

bool generalTest()
{
    return standardCase() && severalResultNumsCase();
}

int main()
{
    if (!generalTest())
    {
        printf("Tests Failed ...\n");
        return 1;
    }
    int count = 0;
    printf("Enter count of numbers in array:\n");
    const int countInput = scanf("%d", &count);
    if (countInput != 1)
    {
        printf("Something went wrong ...\n");
        return 1;
    }
    if (count <= 0)
    {
        return 0;
    }
    printf("Enter numbers for array:\n");
    int array[100] = { 0 };
    const int errorCode = numbersArrayInput(array, count);
    if (errorCode != 0)
    {
        printf("Something went wrong ...\n");
        return 1;
    }
    
    int numbersWithMaxSumm[100] = { 0 };
    int resultCount = getNumbersWithMaxSumm(array, count, numbersWithMaxSumm);
    printf("Numbers with max summ: ");
    numbersArrayOutput(numbersWithMaxSumm, resultCount);
    printf("\n");
}