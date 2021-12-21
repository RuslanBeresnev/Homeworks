#pragma warning (disable: 4668 4996 5045 6031)

#define MAX_STRING_LENGTH 100
#define MAX_TEXT_LENGTH 10000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

int hash(const char string[], const int module)
{
    const int length = (int)strlen(string);
    const int primeNumber = 3;
    int hash = 0;

    for (int i = 0; i < length; i++)
    {
        hash = (hash * primeNumber + (unsigned char)string[i]) % module;
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

int RabinKarpSearch(const char string[], const char substring[])
{
    const int module = 1000;
    const int stringLength = (int)strlen(string);
    const int substringLength = (int)strlen(substring);

    const int substringHash = hash(substring, module);

    char currentString[30] = { 0 };

    for (int i = 0; i < stringLength - substringLength + 1; i++)
    {
        getStringFragment(string, currentString, i, i + substringLength - 1);
        int currentStringHash = hash(currentString, module);

        if (currentStringHash == substringHash)
        {
            if (strcmp(currentString, substring) == 0)
            {
                return i;
            }
        }
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

    char standardSubstring[MAX_STRING_LENGTH] = "подстроки";
    const int standardSubstringFirstPosition = RabinKarpSearch(text, standardSubstring);

    char prefixSubstring[MAX_STRING_LENGTH] = "Реализовать";
    const int prefixSubstringFirstPosition = RabinKarpSearch(text, prefixSubstring);

    char missingSubstring[MAX_STRING_LENGTH] = "RazbeR";
    const int missingSubstringFirstPosition = RabinKarpSearch(text, missingSubstring);

    return standardSubstringFirstPosition == 18 && prefixSubstringFirstPosition == 0 && missingSubstringFirstPosition == -1;
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char text[MAX_TEXT_LENGTH] = { 0 };
    readTextFromFile("Input.txt", text, MAX_TEXT_LENGTH);

    printf("Введите подстроку, которую хотите найти: ");
    char substring[MAX_STRING_LENGTH] = { 0 };
    scanf("%s", substring);

    const int substringFirstPosition = RabinKarpSearch(text, substring);
    if (substringFirstPosition == -1)
    {
        printf("Данная подстрока не содержится в тексте ...\n");
    }
    else
    {
        printf("Первое вхождение подстроки в текст имеет индекс: %d\n", substringFirstPosition);
    }
}