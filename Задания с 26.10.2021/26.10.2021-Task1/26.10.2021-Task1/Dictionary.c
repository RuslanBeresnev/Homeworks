#pragma warning (disable: 4090 5045 6011)

#include "Dictionary.h"

#include <stdlib.h>

void addEntryToDictionary(DictionaryNode** dictionary, const int key, const char* value)
{
    if (*dictionary == NULL)
    {
        *dictionary = calloc(1, sizeof(DictionaryNode));
        (*dictionary)->key = key;
        char* oldValue = (*dictionary)->value;
        (*dictionary)->value = value;
        free(oldValue);
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
        char* oldValue = (*dictionary)->value;
        (*dictionary)->value = value;
        free(oldValue);
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
            free((*dictionary)->value);
            free(*dictionary);
            *dictionary = NULL;
        }
        else if ((*dictionary)->leftSon != NULL && (*dictionary)->rightSon != NULL)
        {
            if ((*dictionary)->rightSon->leftSon == NULL)
            {
                (*dictionary)->key = (*dictionary)->rightSon->key;
                char* oldValue = (*dictionary)->value;
                (*dictionary)->value = (*dictionary)->rightSon->value;
                free(oldValue);
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
                char* oldValue = (*dictionary)->value;
                (*dictionary)->value = replacementNode->value;
                free(oldValue);
                removeEntryFromDictionary(&replacementNode, replacementNode->key);
                replacementNodeParent->leftSon = NULL;
            }
        }
        else
        {
            if ((*dictionary)->leftSon != NULL)
            {
                (*dictionary)->key = (*dictionary)->leftSon->key;
                char* oldValue = (*dictionary)->value;
                (*dictionary)->value = (*dictionary)->leftSon->value;
                free(oldValue);
                (*dictionary)->rightSon = (*dictionary)->leftSon->rightSon;
                DictionaryNode* leftSon = (*dictionary)->leftSon;
                (*dictionary)->leftSon = leftSon->leftSon;
                free(leftSon->value);
                free(leftSon);
            }
            else if ((*dictionary)->rightSon != NULL)
            {
                (*dictionary)->key = (*dictionary)->rightSon->key;
                char* oldValue = (*dictionary)->value;
                (*dictionary)->value = (*dictionary)->rightSon->value;
                free(oldValue);
                (*dictionary)->leftSon = (*dictionary)->rightSon->leftSon;
                DictionaryNode* rightSon = (*dictionary)->rightSon;
                (*dictionary)->rightSon = rightSon->rightSon;
                free(rightSon->value);
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
    if (dictionary->leftSon == NULL && dictionary->rightSon == NULL)
    {
        free(dictionary->value);
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
    free(dictionary->value);
    free(dictionary);
}