#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#pragma warning (disable: 4090 4996 5045)

int findSmallerNumbers(const int numbersArray[], const int length, const int maxValue, int resultNumbersArray[])
{
    int counter = 0;
    for (int i = 0; i < length; i++)
    {
        if (numbersArray[i] < maxValue)
        {
            resultNumbersArray[counter] = numbersArray[i];
            counter++;
        }
    }
    return counter;
}

int readNumbersFromFile(const char fileName[], int numbersArray[])
{
    FILE* numbersFile = fopen(fileName, "r");
    if (numbersFile == NULL)
    {
        return -1;
    }
    int numbersRead = 0;
    while (!feof(numbersFile))
    {
        int number = 0;
        const int countOfReadedNumbers = fscanf(numbersFile, "%d", &number);
        if (countOfReadedNumbers < 0)
        {
            break;
        }
        numbersArray[numbersRead] = number;
        numbersRead++;
    }
    fclose(numbersFile);
    return numbersRead;
}

int writeNumbersToFile(const char filename[], const int numbersArray[], const int count)
{
    FILE* numbersFile = fopen(filename, "w");
    if (numbersFile == NULL)
    {
        return -1;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(numbersFile, "%d ", numbersArray[i]);
    }
    fclose(numbersFile);
    return 0;
}

bool compaireTwoIntArrays(int arrayOne[], int arrayTwo[], int length)
{
    bool verdict = true;
    for (int i = 0; i < length; i++)
    {
        if (arrayOne[i] != arrayTwo[i])
        {
            verdict = false;
            break;
        }
    }
    return verdict;
}

bool generalTest(void)
{
    int numbersArray[100] = { 0 };
    const int numbersCount = readNumbersFromFile("f_test.txt", numbersArray);

    int maxNumber[1] = { 0 };
    const int readingErrorCode = readNumbersFromFile("g_test.txt", maxNumber);

    int resultNumbersArray[100] = { 0 };
    const int resultNumbersCount = findSmallerNumbers(numbersArray, numbersCount, maxNumber[0], resultNumbersArray);
    const int writingErrorCode = writeNumbersToFile("h_test.txt", resultNumbersArray, resultNumbersCount);

    int testedNumbersArray[100] = { 0 };
    const int correctNumbersArray[3] = { 5, 0, 2 };
    readNumbersFromFile("h_test.txt", testedNumbersArray);
    return compaireTwoIntArrays(testedNumbersArray, correctNumbersArray, 3);
}

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "1") == 0)
    {
        if (generalTest())
        {
            printf("Tests Passed!\n");
            return 0;
        }
        printf("Tests Failed ...\n");
        return 1;
    }

    int numbersArray[100] = { 0 };
    const int numbersCount = readNumbersFromFile("f.txt", numbersArray);
    if (numbersCount == -1)
    {
        printf("Something went wrong ...\n");
        return 1;
    }

    int maxNumber[1] = { 0 };
    const int readingErrorCode = readNumbersFromFile("g.txt", maxNumber);
    if (readingErrorCode == -1)
    {
        printf("Something went wrong ...\n");
        return 1;
    }

    int resultNumbersArray[100] = { 0 };
    const int resultNumbersCount = findSmallerNumbers(numbersArray, numbersCount, maxNumber[0], resultNumbersArray);
    const int writingErrorCode = writeNumbersToFile("h.txt", resultNumbersArray, resultNumbersCount);
    if (writingErrorCode == -1)
    {
        printf("Something went wrong ...\n");
        return 1;
    }
}