#pragma warning (disable: 4996 6011)

#include "Dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


// Переделать старые тесты и добавить новые


//bool generalTestPassed(void)
//{
//    DictionaryNode* dictionary = NULL;
//
//    addEntryToDictionary(&dictionary, 5, "a");
//    addEntryToDictionary(&dictionary, 3, "b");
//    addEntryToDictionary(&dictionary, 20, "c");
//    addEntryToDictionary(&dictionary, 1, "d");
//    addEntryToDictionary(&dictionary, 2, "e");
//    addEntryToDictionary(&dictionary, 12, "f");
//    addEntryToDictionary(&dictionary, 32, "g");
//
//    if (!entryInDictionary(dictionary, 12) || !entryInDictionary(dictionary, 5) || !entryInDictionary(dictionary, 2))
//    {
//        deleteDictionary(dictionary);
//        return false;
//    }
//
//    if (strcmp(getValueFromDictionary(dictionary, 5), "a") != 0 || strcmp(getValueFromDictionary(dictionary, 32), "g") != 0
//        || strcmp(getValueFromDictionary(dictionary, 20), "c") != 0)
//    {
//        deleteDictionary(dictionary);
//        return false;
//    }
//
//    removeEntryFromDictionary(&dictionary, 3);
//    removeEntryFromDictionary(&dictionary, 20);
//    removeEntryFromDictionary(&dictionary, 32);
//
//    if (entryInDictionary(dictionary, 3) || entryInDictionary(dictionary, 20) || entryInDictionary(dictionary, 32))
//    {
//        deleteDictionary(dictionary);
//        return false;
//    }
//
//    deleteDictionary(dictionary);
//    return true;
//}

int main(void)
{
    //if (!generalTestPassed())
    //{
    //    printf("Tests Failed ...\n");
    //    return 1;
    //}

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
            char value[100] = { 0 };
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