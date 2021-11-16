#pragma warning (disable: 4996 6011)

#include "Dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

bool generalTestPassed(void) // Тест не доделан
{
    DictionaryNode* dictionary = NULL;
    
    char* values[7] = { NULL };
    for (int i = 0; i < 7; i++)
    {
        values[i] = calloc(2, sizeof(char));
    }
    strcpy(values[0], "a");
    strcpy(values[1], "b");
    strcpy(values[2], "c");
    strcpy(values[3], "d");
    strcpy(values[4], "e");
    strcpy(values[5], "f");
    strcpy(values[6], "g");

    addEntryToDictionary(&dictionary, 5, values[0]);
    addEntryToDictionary(&dictionary, 3, values[1]);
    addEntryToDictionary(&dictionary, 20, values[2]);
    addEntryToDictionary(&dictionary, 1, values[3]);
    addEntryToDictionary(&dictionary, 2, values[4]);
    addEntryToDictionary(&dictionary, 12, values[5]);
    addEntryToDictionary(&dictionary, 32, values[6]);

    if (!entryInDictionary(dictionary, 12) || !entryInDictionary(dictionary, 5) || !entryInDictionary(dictionary, 2))
    {
        return false;
    }

    if (strcmp(getValueFromDictionary(dictionary, 5), "a") != 0 || strcmp(getValueFromDictionary(dictionary, 32), "g") != 0
        || strcmp(getValueFromDictionary(dictionary, 20), "c") != 0)
    {
        return false;
    }

    removeEntryFromDictionary(&dictionary, 3);
    removeEntryFromDictionary(&dictionary, 20);
    removeEntryFromDictionary(&dictionary, 32);

    if (entryInDictionary(dictionary, 3) || entryInDictionary(dictionary, 20) || entryInDictionary(dictionary, 32))
    {
        return false;
    }

    deleteDictionary(dictionary);
    for (int i = 0; i < 7; i++)
    {
        free(values[i]);
    }

    return true;
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
    while(true)
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
            int key = 0;
            const int keyInput = scanf("%d", &key);
            if (keyInput < 1)
            {
                printf("Введены некорректные данные ...\n");
                deleteDictionary(dictionary);
                return 1;
            }
            printf("Введите значение: ");
            char* value = calloc(100, sizeof(char));
            scanf_s("%s", value, 99);

            addEntryToDictionary(&dictionary, key, value);
            printf("Значение добавлено\n");
            break;
        }
        case 2:
        {
            printf("Введите ключ: ");
            int key = 0;
            const int keyInput = scanf("%d", &key);
            if (keyInput < 1)
            {
                printf("Введены некорректные данные ...\n");
                deleteDictionary(dictionary);
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
            int key = 0;
            const int keyInput = scanf("%d", &key);
            if (keyInput < 1)
            {
                printf("Введены некорректные данные ...\n");
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
            int key = 0;
            const int keyInput = scanf("%d", &key);
            if (keyInput < 1)
            {
                printf("Введены некорректные данные ...\n");
                deleteDictionary(dictionary);
                return 1;
            }

            const bool successfulRemove = removeEntryFromDictionary(&dictionary, key);
            if (successfulRemove)
            {
                printf("Ключ %d и соответствующее ему значение удалены\n", key);
            }
            else
            {
                printf("Ключа %d нет в словаре, поэтому удаление не произошло\n", key);
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