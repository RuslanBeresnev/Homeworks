#pragma warning (disable: 4090 4820 4996 5045 6011 6387)

#include "Dictionary.h"

#include <stdlib.h>
#include <string.h>

typedef struct DictionaryNode
{
    char* key;
    char* value;
    int height;
    struct DictionaryNode* leftSon;
    struct DictionaryNode* rightSon;
} DictionaryNode;

DictionaryNode* rotateLeft(DictionaryNode* a)
{
    DictionaryNode* b = a->rightSon;
    DictionaryNode* c = b->leftSon;
    b->leftSon = a;
    a->rightSon = c;
    return b;
}

DictionaryNode* rotateRight(DictionaryNode* a)
{
    DictionaryNode* b = a->leftSon;
    DictionaryNode* c = b->rightSon;
    b->rightSon = a;
    a->leftSon = c;
    return b;
}

DictionaryNode* bigRotateLeft(DictionaryNode* a)
{
    a->rightSon = rotateRight(a->rightSon);
    return rotateLeft(a);
}

DictionaryNode* bigRotateRight(DictionaryNode* a)
{
    a->leftSon = rotateLeft(a->leftSon);
    return rotateRight(a);
}

int getHeight(DictionaryNode* dictionary)
{
    if (dictionary == NULL)
    {
        return -1;
    }
    return dictionary->height;
}

int calculateHeight(DictionaryNode* dictionary)
{
    if (dictionary->leftSon == NULL && dictionary->rightSon == NULL)
    {
        return 0;
    }
    int leftHeight = 0;
    int rightHeight = 0;
    if (dictionary->leftSon != NULL)
    {
        leftHeight = calculateHeight(dictionary->leftSon);
    }
    if (dictionary->rightSon != NULL)
    {
        rightHeight = calculateHeight(dictionary->rightSon);
    }
    int maxHeight = 0;
    if (leftHeight >= rightHeight)
    {
        maxHeight = leftHeight + 1;
    }
    else
    {
        maxHeight = rightHeight + 1;
    }
    return maxHeight;
}

int calculateDifference(DictionaryNode* dictionary)
{
    return getHeight(dictionary->rightSon) - getHeight(dictionary->leftSon);
}

void correctHeightsInTree(DictionaryNode* dictionary)
{
    if (dictionary == NULL)
    {
        return;
    }

    correctHeightsInTree(dictionary->leftSon);
    correctHeightsInTree(dictionary->rightSon);
    dictionary->height = calculateHeight(dictionary);
}

DictionaryNode* balance(DictionaryNode* dictionary)
{
    if (calculateDifference(dictionary) == 2)
    {
        if (calculateDifference(dictionary->rightSon) >= 0)
        {
            return rotateLeft(dictionary);
        }
        return bigRotateLeft(dictionary);
    }
    else if (calculateDifference(dictionary) == -2)
    {
        if (calculateDifference(dictionary->leftSon) <= 0)
        {
            return rotateRight(dictionary);
        }
        return bigRotateRight(dictionary);
    }
    return dictionary;
}

DictionaryNode* addEntryToDictionary(DictionaryNode* dictionary, const char* key, const char* value)
{
    if (dictionary == NULL)
    {
        DictionaryNode* newEntry = calloc(1, sizeof(DictionaryNode));
        newEntry->key = calloc(100, sizeof(char));
        newEntry->value = calloc(100, sizeof(char));
        strcpy_s(newEntry->key, 99, key);
        strcpy_s(newEntry->value, 99, value);
        return newEntry;
    }

    if (strcmp(key, dictionary->key) > 0)
    {
        dictionary->rightSon = addEntryToDictionary(dictionary->rightSon, key, value);
    }
    else if (strcmp(key, dictionary->key) < 0)
    {
        dictionary->leftSon = addEntryToDictionary(dictionary->leftSon, key, value);
    }
    else
    {
        strcpy_s(dictionary->value, 99, value);
        return dictionary;
    }

    correctHeightsInTree(dictionary);
    dictionary = balance(dictionary);
    correctHeightsInTree(dictionary);
    return dictionary;
}

char* getValueFromDictionary(DictionaryNode* dictionary, const char* key)
{
    if (dictionary == NULL)
    {
        return NULL;
    }
    if (strcmp(key, dictionary->key) < 0)
    {
        return getValueFromDictionary(dictionary->leftSon, key);
    }
    else if (strcmp(key, dictionary->key) > 0)
    {
        return getValueFromDictionary(dictionary->rightSon, key);
    }
    else
    {
        return dictionary->value;
    }
}

DictionaryNode* moveSubTree(DictionaryNode* dictionary, bool* entryRemoved)
{
    DictionaryNode* replacementNode = dictionary->rightSon;
    DictionaryNode* replacementNodeParent = NULL;
    while (replacementNode->leftSon != NULL)
    {
        if (replacementNode->leftSon->leftSon == NULL)
        {
            replacementNodeParent = replacementNode;
        }
        replacementNode = replacementNode->leftSon;
    }
    strcpy(dictionary->key, replacementNode->key);
    strcpy(dictionary->value, replacementNode->value);
    dictionary = removeEntryFromDictionary(replacementNode, replacementNode->key, entryRemoved);
    replacementNodeParent->leftSon = NULL;
    return dictionary;
}

DictionaryNode* removeEntryFromDictionary(DictionaryNode* dictionary, const char* key, bool* entryRemoved)
{
    if (dictionary == NULL)
    {
        *entryRemoved = false;
        return NULL;
    }
    if (strcmp(key, dictionary->key) < 0)
    {
        dictionary->leftSon = removeEntryFromDictionary(dictionary->leftSon, key, entryRemoved);
    }
    else if (strcmp(key, dictionary->key) > 0)
    {
        dictionary->rightSon = removeEntryFromDictionary(dictionary->rightSon, key, entryRemoved);
    }
    else
    {
        *entryRemoved = true;
        if (dictionary->leftSon == NULL && dictionary->rightSon == NULL)
        {
            free(dictionary->key);
            free(dictionary->value);
            free(dictionary);
            return NULL;
        }
        else if (dictionary->leftSon != NULL && dictionary->rightSon != NULL)
        {
            if (dictionary->rightSon->leftSon == NULL)
            {
                DictionaryNode* rightSon = dictionary->rightSon;
                strcpy(dictionary->key, rightSon->key);
                strcpy(dictionary->value, rightSon->value);
                dictionary->rightSon = dictionary->rightSon->rightSon;

                free(rightSon->key);
                free(rightSon->value);
                free(rightSon);
            }
            else
            {
                dictionary = moveSubTree(dictionary, entryRemoved);
            }
        }
        else
        {
            if (dictionary->leftSon != NULL)
            {
                strcpy(dictionary->key, dictionary->leftSon->key);
                strcpy(dictionary->value, dictionary->leftSon->value);
                dictionary->rightSon = dictionary->leftSon->rightSon;
                DictionaryNode* leftSon = dictionary->leftSon;
                dictionary->leftSon = leftSon->leftSon;

                free(leftSon->key);
                free(leftSon->value);
                free(leftSon);
            }
            else if (dictionary->rightSon != NULL)
            {
                strcpy(dictionary->key, dictionary->rightSon->key);
                strcpy(dictionary->value, dictionary->rightSon->value);
                dictionary->leftSon = dictionary->rightSon->leftSon;
                DictionaryNode* rightSon = dictionary->rightSon;
                dictionary->rightSon = rightSon->rightSon;

                free(rightSon->key);
                free(rightSon->value);
                free(rightSon);
            }
        }
    }

    correctHeightsInTree(dictionary);
    dictionary = balance(dictionary);
    correctHeightsInTree(dictionary);
    return dictionary;
}

bool entryInDictionary(DictionaryNode* dictionary, const char* key)
{
    return getValueFromDictionary(dictionary, key) != NULL;
}

void deleteDictionary(DictionaryNode* dictionary)
{
    if (dictionary == NULL)
    {
        return;
    }

    deleteDictionary(dictionary->leftSon);
    deleteDictionary(dictionary->rightSon);

    free(dictionary->key);
    free(dictionary->value);
    free(dictionary);
}