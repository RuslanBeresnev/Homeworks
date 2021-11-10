#pragma warning (disable: 4090 4715 4996 5045 6031)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

typedef struct Node
{
    int key;
    char* value;
    struct Node* leftSon;
    struct Node* rightSon;
}Node;

void insertNode(Node* tree, const int key, const char* value)
{
    if (tree->value == NULL)
    {
        tree->key = key;
        tree->value = value;
        tree->leftSon = calloc(1, sizeof(Node));
        tree->rightSon = calloc(1, sizeof(Node));
        return;
    }
    if (key > tree->key)
    {
        insertNode(tree->rightSon, key, value);
    }
    else if (key < tree->key)
    {
        insertNode(tree->leftSon, key, value);
    }
    else
    {
        tree->value = value;
    }
}

char* getValue(Node* tree, const int key)
{
    if (tree->value == NULL)
    {
        return NULL;
    }
    if (key < tree->key)
    {
        getValue(tree->leftSon, key);
    }
    else if (key > tree->key)
    {
        getValue(tree->rightSon, key);
    }
    else
    {
        return tree->value;
    }
}

void removeNode(Node* tree, const int key)
{
    if (tree->value == NULL)
    {
        return;
    }
    if (key < tree->key)
    {
        removeNode(tree->leftSon, key);
    }
    else if (key > tree->key)
    {
        removeNode(tree->rightSon, key);
    }
    else
    {
        if (tree->leftSon->value == NULL && tree->rightSon->value == NULL)
        {
            free(tree->leftSon);
            free(tree->rightSon);
            tree->key = 0;
            tree->value = NULL;
            tree->leftSon = NULL;
            tree->rightSon = NULL;
        }
        else if (tree->leftSon->value != NULL && tree->rightSon->value != NULL)
        {
            if (tree->rightSon->leftSon->value == NULL)
            {
                tree->key = tree->rightSon->key;
                tree->value = tree->rightSon->value;
                Node* rightSon = tree->rightSon;
                tree->rightSon = tree->rightSon->rightSon;
                free(rightSon->leftSon);
                free(rightSon);
            }
            else
            {
                Node* replacementNode = tree->rightSon;
                while (replacementNode->leftSon->value != NULL)
                {
                    replacementNode = replacementNode->leftSon;
                }
                tree->key = replacementNode->key;
                tree->value = replacementNode->value;
                removeNode(replacementNode, replacementNode->key);
            }
        }
        else
        {
            if (tree->leftSon->value != NULL)
            {
                tree->key = tree->leftSon->key;
                tree->value = tree->leftSon->value;
                tree->rightSon = tree->leftSon->rightSon;
                Node* leftSon = tree->leftSon;
                tree->leftSon = leftSon->leftSon;
                free(leftSon);
            }
            else if (tree->rightSon->value != NULL)
            {
                tree->key = tree->rightSon->key;
                tree->value = tree->rightSon->value;
                tree->leftSon = tree->rightSon->leftSon;
                Node* rightSon = tree->rightSon;
                tree->rightSon = rightSon->rightSon;
                free(rightSon);
            }
        }
    }
}

bool keyInTree(Node* tree, const int key)
{
    return getValue(tree, key) != NULL;
}

void deleteTree(Node* tree)
{
    if (tree->value == NULL)
    {
        free(tree);
        return;
    }
    deleteTree(tree->leftSon);
    deleteTree(tree->rightSon);
    free(tree);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    Node* tree = calloc(1, sizeof(Node));
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
            deleteTree(tree);
            return 1;
        }

        switch (option)
        {
        case 0:
        {
            deleteTree(tree);
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
                deleteTree(tree);
                return 1;
            }
            printf("Введите значение: ");
            char* value = calloc(100, sizeof(char));
            scanf("%s", value);

            insertNode(tree, key, value);
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
                deleteTree(tree);
                return 1;
            }

            const char* value = getValue(tree, key);
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
                deleteTree(tree);
                return 1;
            }
            if (keyInTree(tree, key))
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
                deleteTree(tree);
                return 1;
            }

            removeNode(tree, key);
            printf("Ключ %d и соответствующее ему значение удалены\n", key);
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