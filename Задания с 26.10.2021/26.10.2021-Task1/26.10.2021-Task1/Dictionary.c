#pragma warning (disable: 4090 4996 5045 6011)

#include "Dictionary.h"

#include <stdlib.h>
#include <string.h>

void addEntryToDictionary(DictionaryNode** dictionary, const int key, const char value[])
{
    if (*dictionary == NULL)
    {
        *dictionary = calloc(1, sizeof(DictionaryNode));
        (*dictionary)->key = key;
        strcpy((*dictionary)->value, value);
        return;
    }

    if (key > (*dictionary)->key)
    {
        addEntryToDictionary(&((*dictionary)->rightSon), key, value);
    }
    else if (key < (*dictionary)->key)
    {
        addEntryToDictionary(&((*dictionary)->leftSon), key, value);
    }
    else
    {
        strcpy((*dictionary)->value, value);
    }
}

char* getValueFromDictionary(DictionaryNode* dictionary, const int key)
{
    if (dictionary == NULL)
    {
        return NULL;
    }
    if (key < dictionary->key)
    {
        return getValueFromDictionary(dictionary->leftSon, key);
    }
    else if (key > dictionary->key)
    {
        return getValueFromDictionary(dictionary->rightSon, key);
    }
    else
    {
        return dictionary->value;
    }
}

bool removeEntryFromDictionary(DictionaryNode** dictionary, const int key)
{
    if (*dictionary == NULL)
    {
        return false;
    }
    bool successfulRemove = true;
    if (key < (*dictionary)->key)
    {
        successfulRemove = removeEntryFromDictionary(&((*dictionary)->leftSon), key);
    }
    else if (key > (*dictionary)->key)
    {
        successfulRemove = removeEntryFromDictionary(&((*dictionary)->rightSon), key);
    }
    else
    {
        if ((*dictionary)->leftSon == NULL && (*dictionary)->rightSon == NULL)
        {
            free(*dictionary);
            *dictionary = NULL;
        }
        else if ((*dictionary)->leftSon != NULL && (*dictionary)->rightSon != NULL)
        {
            if ((*dictionary)->rightSon->leftSon == NULL)
            {
                (*dictionary)->key = (*dictionary)->rightSon->key;
                strcpy((*dictionary)->value, (*dictionary)->rightSon->value);
                DictionaryNode* rightSon = (*dictionary)->rightSon;
                (*dictionary)->rightSon = (*dictionary)->rightSon->rightSon;
                free(rightSon);
            }
            else
            {
                DictionaryNode* replacementNode = (*dictionary)->rightSon;
                DictionaryNode* replacementNodeParent = NULL;
                while (replacementNode->leftSon != NULL)
                {
                    if (replacementNode->leftSon->leftSon == NULL)
                    {
                        replacementNodeParent = replacementNode;
                    }
                    replacementNode = replacementNode->leftSon;
                }
                (*dictionary)->key = replacementNode->key;
                strcpy((*dictionary)->value, replacementNode->value);
                removeEntryFromDictionary(&replacementNode, replacementNode->key);
                replacementNodeParent->leftSon = NULL;
            }
        }
        else
        {
            if ((*dictionary)->leftSon != NULL)
            {
                (*dictionary)->key = (*dictionary)->leftSon->key;
                strcpy((*dictionary)->value, (*dictionary)->leftSon->value);
                (*dictionary)->rightSon = (*dictionary)->leftSon->rightSon;
                DictionaryNode* leftSon = (*dictionary)->leftSon;
                (*dictionary)->leftSon = leftSon->leftSon;
                free(leftSon);
            }
            else if ((*dictionary)->rightSon != NULL)
            {
                (*dictionary)->key = (*dictionary)->rightSon->key;
                strcpy((*dictionary)->value, (*dictionary)->rightSon->value);
                (*dictionary)->leftSon = (*dictionary)->rightSon->leftSon;
                DictionaryNode* rightSon = (*dictionary)->rightSon;
                (*dictionary)->rightSon = rightSon->rightSon;
                free(rightSon);
            }
        }
    }
    return successfulRemove;
}

bool entryInDictionary(DictionaryNode* dictionary, const int key)
{
    return getValueFromDictionary(dictionary, key) != NULL;
}

void deleteDictionary(DictionaryNode* dictionary)
{
    if (dictionary == NULL)
    {
        return;
    }
    if (dictionary->leftSon == NULL && dictionary->rightSon == NULL)
    {
        free(dictionary);
        return;
    }
    if (dictionary->leftSon != NULL)
    {
        deleteDictionary(dictionary->leftSon);
    }
    if (dictionary->rightSon != NULL)
    {
        deleteDictionary(dictionary->rightSon);
    }
    free(dictionary);
}