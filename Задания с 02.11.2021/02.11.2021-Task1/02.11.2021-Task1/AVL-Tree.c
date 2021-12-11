#pragma warning (disable: 4996 5045 6011 6387)

#include "Dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>

DictionaryNode* addStandardValues(DictionaryNode* dictionary, int* entriesCount)
{
    char* keyA = calloc(2, sizeof(char));
    char* keyB = calloc(2, sizeof(char));
    char* keyC = calloc(2, sizeof(char));
    char* keyD = calloc(2, sizeof(char));
    char* keyE = calloc(2, sizeof(char));
    char* keyF = calloc(2, sizeof(char));
    char* keyG = calloc(2, sizeof(char));
    char* keyH = calloc(2, sizeof(char));
    char* keyI = calloc(2, sizeof(char));
    char* keyK = calloc(2, sizeof(char));
    char* keyL = calloc(2, sizeof(char));
    char* keyM = calloc(2, sizeof(char));

    strcpy(keyA, "a");
    strcpy(keyB, "b");
    strcpy(keyC, "c");
    strcpy(keyD, "d");
    strcpy(keyE, "e");
    strcpy(keyF, "f");
    strcpy(keyG, "g");
    strcpy(keyH, "h");
    strcpy(keyI, "i");
    strcpy(keyK, "k");
    strcpy(keyL, "l");
    strcpy(keyM, "m");

    char* valueA = calloc(2, sizeof(char));
    char* valueB = calloc(2, sizeof(char));
    char* valueC = calloc(2, sizeof(char));
    char* valueD = calloc(2, sizeof(char));
    char* valueE = calloc(2, sizeof(char));
    char* valueF = calloc(2, sizeof(char));
    char* valueG = calloc(2, sizeof(char));
    char* valueH = calloc(2, sizeof(char));
    char* valueI = calloc(2, sizeof(char));
    char* valueK = calloc(2, sizeof(char));
    char* valueL = calloc(2, sizeof(char));
    char* valueM = calloc(2, sizeof(char));

    strcpy(valueA, "a");
    strcpy(valueB, "b");
    strcpy(valueC, "c");
    strcpy(valueD, "d");
    strcpy(valueE, "e");
    strcpy(valueF, "f");
    strcpy(valueG, "g");
    strcpy(valueH, "h");
    strcpy(valueI, "i");
    strcpy(valueK, "k");
    strcpy(valueL, "l");
    strcpy(valueM, "m");

    dictionary = addEntryToDictionary(dictionary, keyA, valueA);
    dictionary = addEntryToDictionary(dictionary, keyB, valueB);
    dictionary = addEntryToDictionary(dictionary, keyC, valueC);
    dictionary = addEntryToDictionary(dictionary, keyD, valueD);
    dictionary = addEntryToDictionary(dictionary, keyE, valueE);
    dictionary = addEntryToDictionary(dictionary, keyF, valueF);
    dictionary = addEntryToDictionary(dictionary, keyG, valueG);
    dictionary = addEntryToDictionary(dictionary, keyH, valueH);
    dictionary = addEntryToDictionary(dictionary, keyI, valueI);
    dictionary = addEntryToDictionary(dictionary, keyK, valueK);
    dictionary = addEntryToDictionary(dictionary, keyL, valueL);
    dictionary = addEntryToDictionary(dictionary, keyM, valueM);

    *entriesCount += 12;
    return dictionary;
}

bool dictionaryTestsPassed(void)
{
    DictionaryNode* dictionary = NULL;
    
    char* keyA = calloc(2, sizeof(char));
    char* keyB = calloc(2, sizeof(char));
    char* keyC = calloc(2, sizeof(char));
    char* keyD = calloc(2, sizeof(char));
    char* keyE = calloc(2, sizeof(char));
    char* keyF = calloc(2, sizeof(char));
    char* keyG = calloc(2, sizeof(char));

    strcpy(keyA, "a");
    strcpy(keyB, "b");
    strcpy(keyC, "c");
    strcpy(keyD, "d");
    strcpy(keyE, "e");
    strcpy(keyF, "f");
    strcpy(keyG, "g");

    char* valueA = calloc(2, sizeof(char));
    char* valueB = calloc(2, sizeof(char));
    char* valueC = calloc(2, sizeof(char));
    char* valueD = calloc(2, sizeof(char));
    char* valueE = calloc(2, sizeof(char));
    char* valueF = calloc(2, sizeof(char));
    char* valueG = calloc(2, sizeof(char));

    strcpy(valueA, "a");
    strcpy(valueB, "b");
    strcpy(valueC, "c");
    strcpy(valueD, "d");
    strcpy(valueE, "e");
    strcpy(valueF, "f");
    strcpy(valueG, "g");

    dictionary = addEntryToDictionary(dictionary, keyA, valueA);
    dictionary = addEntryToDictionary(dictionary, keyB, valueB);
    dictionary = addEntryToDictionary(dictionary, keyC, valueC);
    dictionary = addEntryToDictionary(dictionary, keyD, valueD);
    dictionary = addEntryToDictionary(dictionary, keyE, valueE);
    dictionary = addEntryToDictionary(dictionary, keyF, valueF);
    dictionary = addEntryToDictionary(dictionary, keyG, valueG);

    if (!entryInDictionary(dictionary, keyE) || !entryInDictionary(dictionary, keyG) || !entryInDictionary(dictionary, keyA))
    {
        deleteDictionary(dictionary);
        return false;
    }

    if (strcmp(getValueFromDictionary(dictionary, keyA), valueA) != 0 || strcmp(getValueFromDictionary(dictionary, keyG), valueG) != 0
        || strcmp(getValueFromDictionary(dictionary, keyC), valueC) != 0)
    {
        deleteDictionary(dictionary);
        return false;
    }

    bool successfulRemove = false;

    dictionary = removeEntryFromDictionary(dictionary, keyC, &successfulRemove);
    if (!successfulRemove)
    {
        deleteDictionary(dictionary);
        return false;
    }

    dictionary = removeEntryFromDictionary(dictionary, keyF, &successfulRemove);
    if (!successfulRemove)
    {
        deleteDictionary(dictionary);
        return false;
    }

    dictionary = removeEntryFromDictionary(dictionary, keyB, &successfulRemove);
    if (!successfulRemove)
    {
        deleteDictionary(dictionary);
        return false;
    }

    dictionary = removeEntryFromDictionary(dictionary, keyA, &successfulRemove);
    if (!successfulRemove)
    {
        deleteDictionary(dictionary);
        return false;
    }

    successfulRemove = false;
    char* keyZ = calloc(2, sizeof(char));
    strcpy(keyZ, "z");
    dictionary = removeEntryFromDictionary(dictionary, keyZ, &successfulRemove);
    free(keyZ);
    if (successfulRemove)
    {
        deleteDictionary(dictionary);
        return false;
    }

    deleteDictionary(dictionary);
    return true;
}

bool AVLTreeTestPassed(void)
{
    DictionaryNode* dictionary = NULL;
    int entriesCount = 0;

    dictionary = addStandardValues(dictionary, &entriesCount);

    return (int)(log(entriesCount) / log(2)) == getHeight(dictionary);
}

bool generalTestPassed(void)
{
    return dictionaryTestsPassed() && AVLTreeTestPassed();
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");
    DictionaryNode* dictionary = NULL;
    while (true)
    {
        printf("\n");
        printf("Выберите одну из операций:\n");
        printf("0 - Выйти\n");
        printf("1 - Добавить значение по заданному ключу в словарь\n");
        printf("2 - Получить значение по заданному ключу из словаря\n");
        printf("3 - Проверить наличие заданного ключа в словаре\n");
        printf("4 - Удалить заданный ключ и связанное с ним значение из словаря\n");
        printf("\n");

        int option = 0;
        const int optionInput = scanf("%d", &option);
        if (optionInput < 1)
        {
            printf("Введены некорректные данные ...\n");
            deleteDictionary(dictionary);
            return 1;
        }

        switch (option)
        {
        case 0:
        {
            deleteDictionary(dictionary);
            return 0;
        }
        case 1:
        {
            printf("Введите ключ: ");
            char* key = calloc(100, sizeof(char));
            const int keyInput = scanf_s("%s", key, 99);
            if (keyInput < 1)
            {
                printf("Введены некорректные данные ...\n");
                free(key);
                deleteDictionary(dictionary);
                return 1;
            }
            printf("Введите значение: ");
            char* value = calloc(100, sizeof(char));
            scanf_s("%s", value, 99);

            dictionary = addEntryToDictionary(dictionary, key, value);
            printf("Значение добавлено\n");
            break;
        }
        case 2:
        {
            printf("Введите ключ: ");
            char* key = calloc(100, sizeof(char));
            const int keyInput = scanf_s("%s", key, 99);
            if (keyInput < 1)
            {
                printf("Введены некорректные данные ...\n");
                deleteDictionary(dictionary);
                free(key);
                return 1;
            }

            const char* value = getValueFromDictionary(dictionary, key);
            if (value == NULL)
            {
                printf("Данного ключа пока нет в словаре\n");
                continue;
            }
            printf("Значение по данному ключу: %s\n", value);
            break;
        }
        case 3:
        {
            printf("Введите ключ: ");
            char* key = calloc(100, sizeof(char));
            const int keyInput = scanf_s("%s", key, 99);
            if (keyInput < 1)
            {
                printf("Введены некорректные данные ...\n");
                free(key);
                deleteDictionary(dictionary);
                return 1;
            }
            if (entryInDictionary(dictionary, key))
            {
                printf("Ключ содержится в словаре\n");
                continue;
            }
            printf("Ключа нет в словаре\n");
            break;
        }
        case 4:
        {
            printf("Введите ключ: ");
            char* key = calloc(100, sizeof(char));
            const int keyInput = scanf_s("%s", key, 99);
            if (keyInput < 1)
            {
                printf("Введены некорректные данные ...\n");
                deleteDictionary(dictionary);
                return 1;
            }

            bool successfulRemove = true;
            dictionary = removeEntryFromDictionary(dictionary, key, &successfulRemove);
            if (successfulRemove)
            {
                printf("Ключ %s и соответствующее ему значение удалены\n", key);
            }
            else
            {
                printf("Ключа %s нет в словаре, поэтому удаление не произошло\n", key);
            }
            break;
        }
        default:
        {
            printf("Такой операции пока нет\n");
            continue;
        }
        }
    }
}