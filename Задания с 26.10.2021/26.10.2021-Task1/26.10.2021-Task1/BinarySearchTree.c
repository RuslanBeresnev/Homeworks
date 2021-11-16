#pragma warning (disable: 4090 4715 4996 5045 6011 6031)

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
} Node;

void insertNode(Node** tree, const int key, const char* value)
{
    if (*tree == NULL)
    {
        *tree = calloc(1, sizeof(Node));
        (*tree)->key = key;
        char* oldValue = (*tree)->value;
        (*tree)->value = value;
        free(oldValue);
        return;
    }

    if (key > (*tree)->key)
    {
        insertNode(&((*tree)->rightSon), key, value);
    }
    else if (key < (*tree)->key)
    {
        insertNode(&((*tree)->leftSon), key, value);
    }
    else
    {
        char* oldValue = (*tree)->value;
        (*tree)->value = value;
        free(oldValue);
    }
}

char* getValue(Node* tree, const int key)
{
    if (tree == NULL)
    {
        return NULL;
    }
    if (key < tree->key)
    {
        return getValue(tree->leftSon, key);
    }
    else if (key > tree->key)
    {
        return getValue(tree->rightSon, key);
    }
    else
    {
        return tree->value;
    }
}

bool removeNode(Node** tree, const int key)
{
    if (*tree == NULL)
    {
        return false;
    }
    bool successfulRemove = true;
    if (key < (*tree)->key)
    {
        successfulRemove = removeNode(&((*tree)->leftSon), key);
    }
    else if (key > (*tree)->key)
    {
        successfulRemove = removeNode(&((*tree)->rightSon), key);
    }
    else
    {
        if ((*tree)->leftSon == NULL && (*tree)->rightSon == NULL)
        {
            free((*tree)->value);
            free(*tree);
            *tree = NULL;
        }
        else if ((*tree)->leftSon != NULL && (*tree)->rightSon != NULL)
        {
            if ((*tree)->rightSon->leftSon == NULL)
            {
                (*tree)->key = (*tree)->rightSon->key;
                char* oldValue = (*tree)->value;
                (*tree)->value = (*tree)->rightSon->value;
                free(oldValue);
                Node* rightSon = (*tree)->rightSon;
                (*tree)->rightSon = (*tree)->rightSon->rightSon;
                free(rightSon);
            }
            else
            {
                Node* replacementNode = (*tree)->rightSon;
                Node* replacementNodeParent = NULL;
                while (replacementNode->leftSon != NULL)
                {
                    if (replacementNode->leftSon->leftSon == NULL)
                    {
                        replacementNodeParent = replacementNode;
                    }
                    replacementNode = replacementNode->leftSon;
                }
                (*tree)->key = replacementNode->key;
                char* oldValue = (*tree)->value;
                (*tree)->value = replacementNode->value;
                free(oldValue);
                removeNode(&replacementNode, replacementNode->key);
                replacementNodeParent->leftSon = NULL;
            }
        }
        else
        {
            if ((*tree)->leftSon != NULL)
            {
                (*tree)->key = (*tree)->leftSon->key;
                char* oldValue = (*tree)->value;
                (*tree)->value = (*tree)->leftSon->value;
                free(oldValue);
                (*tree)->rightSon = (*tree)->leftSon->rightSon;
                Node* leftSon = (*tree)->leftSon;
                (*tree)->leftSon = leftSon->leftSon;
                free(leftSon->value);
                free(leftSon);
            }
            else if ((*tree)->rightSon != NULL)
            {
                (*tree)->key = (*tree)->rightSon->key;
                char* oldValue = (*tree)->value;
                (*tree)->value = (*tree)->rightSon->value;
                free(oldValue);
                (*tree)->leftSon = (*tree)->rightSon->leftSon;
                Node* rightSon = (*tree)->rightSon;
                (*tree)->rightSon = rightSon->rightSon;
                free(rightSon->value);
                free(rightSon);
            }
        }
    }
    return successfulRemove;
}

bool keyInTree(Node* tree, const int key)
{
    return getValue(tree, key) != NULL;
}

void deleteTree(Node* tree)
{
    if (tree->leftSon == NULL && tree->rightSon == NULL)
    {
        free(tree->value);
        free(tree);
        return;
    }
    if (tree->leftSon != NULL)
    {
        deleteTree(tree->leftSon);
    }
    if (tree->rightSon != NULL)
    {
        deleteTree(tree->rightSon);
    }
    free(tree->value);
    free(tree);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    Node* tree = NULL;
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
            scanf_s("%s", value, 99);

            insertNode(&tree, key, value);
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

            const bool successfulRemove = removeNode(&tree, key);
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