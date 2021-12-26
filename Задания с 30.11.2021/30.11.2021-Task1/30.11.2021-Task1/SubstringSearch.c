#pragma warning (disable: 4668 4996 5045 6031)

#define MAX_STRING_LENGTH 100
#define MAX_TEXT_LENGTH 10000
#define PRIME_NUMBER 3

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <math.h>

int hash(const char string[])
{
    const int length = (int)strlen(string);
    int hash = 0;

    for (int i = 0; i < length; i++)
    {
        hash = hash * PRIME_NUMBER + (unsigned char)string[i];
    }

    return hash;
}

void getStringFragment(const char source[], char destination[], const int beginPosition, const int endPosition)
{
    for (int i = 0; i < endPosition - beginPosition + 1; i++)
    {
        destination[i] = source[beginPosition + i];
    }
}

bool compareSubstringWithString(const char string[], const char substring[], const int startPos, const int endPos)
{
    for (int i = startPos; i < endPos + 1; i++)
    {
        if (string[i] != substring[i - startPos])
        {
            return false;
        }
    }
    return true;
}

int rabinKarpSearch(const char string[], const char substring[])
{
    const int stringLength = (int)strlen(string);
    const int substringLength = (int)strlen(substring);

    const int substringHash = hash(substring);

    char currentString[30] = { 0 };
    getStringFragment(string, currentString, 0, substringLength - 1);
    int currentStringHash = hash(currentString);

    const int primeNumberInPower = (int)pow(PRIME_NUMBER, substringLength - 1);

    for (int i = 0; i < stringLength - substringLength + 1; i++)
    {
        if (currentStringHash == substringHash)
        {
            if (compareSubstringWithString(string, substring, i, i + substringLength - 1))
            {
                return i;
            }
        }

        currentStringHash = (currentStringHash - (unsigned char)string[i] * primeNumberInPower) * PRIME_NUMBER + (unsigned char)string[i + 1];
    }

    return -1;
}

void destroyLinefeedCharacter(char string[])
{
    int position = 0;
    while (true)
    {
        if (string[position] == '\n')
        {
            string[position] = '\0';
            break;
        }
        if (string[position] == '\0')
        {
            break;
        }

        position++;
    }
}

int readTextFromFile(const char fileName[], char array[], const int maxTextLength)
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -1;
    }

    int textLength = 0;
    while (!feof(file))
    {
        char string[MAX_STRING_LENGTH] = { 0 };
        fgets(string, MAX_STRING_LENGTH, file);
        destroyLinefeedCharacter(string);

        strcat(array, string);
        textLength += (int)strlen(string);

        if (textLength + MAX_STRING_LENGTH > maxTextLength)
        {
            break;
        }
    }

    fclose(file);
    return textLength;
}

bool generalTestPassed(void)
{
    char text[MAX_TEXT_LENGTH] = { 0 };
    readTextFromFile("Test Input.txt", text, MAX_TEXT_LENGTH);

    char standardSubstring[MAX_STRING_LENGTH] = "r";
    const int standardSubstringFirstPosition = rabinKarpSearch(text, standardSubstring);

    return standardSubstringFirstPosition == 1;
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");

    char text[MAX_TEXT_LENGTH] = { 0 };
    readTextFromFile("Input.txt", text, MAX_TEXT_LENGTH);

    printf("Введите подстроку, которую хотите найти: ");
    char substring[MAX_STRING_LENGTH] = { 0 };
    scanf("%s", substring);

    const int substringFirstPosition = rabinKarpSearch(text, substring);
    if (substringFirstPosition == -1)
    {
        printf("Данная подстрока не содержится в тексте ...\n");
    }
    else
    {
        printf("Первое вхождение подстроки в текст имеет индекс: %d\n", substringFirstPosition);
    }
}