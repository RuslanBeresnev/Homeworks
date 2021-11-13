#pragma warning (disable: 4715 4820 4996 6011)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

typedef struct Node
{
    int number;
    char operand;
    struct Node* leftSon;
    struct Node* rightSon;
}Node;

void readLineFromFile(const char fileName[], char line[], const int length)
{
    FILE* treeFile = fopen(fileName, "r");
    fgets(line, length, treeFile);
    fclose(treeFile);
}

void writeLineToFile(const char fileName[], const char line[])
{
    FILE* treeFile = fopen(fileName, "w");
    fprintf(treeFile, "%s", line);
    fclose(treeFile);
}

Node* createTreeFromLine(const char treeLine[])
{
    if (treeLine[0] == '\0')
    {
        return NULL;
    }

    writeLineToFile("tmp.txt", treeLine);
    FILE* treeFile = fopen("tmp.txt", "r");
    Node* tree = calloc(1, sizeof(Node));

    char currentSymbol[2] = { 0 };
    int currentNumber = 0;

    int nestingDepth = 0;
    bool isFirstOperandRead = false;

    char newTreeLine[100] = { 0 };
    int newTreeLineLength = 0;

    while (!feof(treeFile))
    {
        fgets(currentSymbol, 2, treeFile);
        
        if (currentSymbol[0] == '(')
        {
            nestingDepth++;
        }
        else if (currentSymbol[0] == ')')
        {
            nestingDepth--;

            if (nestingDepth == 1)
            {
                newTreeLine[newTreeLineLength] = currentSymbol[0];
                newTreeLineLength++;

                if (isFirstOperandRead)
                {
                    tree->rightSon = createTreeFromLine(newTreeLine);
                }
                else
                {
                    tree->leftSon = createTreeFromLine(newTreeLine);
                    isFirstOperandRead = true;
                }

                memset(newTreeLine, '\0', newTreeLineLength);
                newTreeLineLength = 0;
            }
        }
        if (nestingDepth >= 2)
        {
            newTreeLine[newTreeLineLength] = currentSymbol[0];
            newTreeLineLength++;
        }
        else if (nestingDepth == 1)
        {
            if (currentSymbol[0] == ')' || currentSymbol[0] == '(' || currentSymbol[0] == ' ')
            {
                continue;
            }
            else if (currentSymbol[0] != '+' && currentSymbol[0] != '-' && currentSymbol[0] != '*' && currentSymbol[0] != '/')
            {
                ungetc(currentSymbol[0], treeFile);
                currentSymbol[0] = '\0';
                const int numberInput = fscanf(treeFile, "%d", &currentNumber);

                if (numberInput != 1)
                {
                    return NULL;
                }
                if (!isFirstOperandRead)
                {
                    Node* newTree = calloc(1, sizeof(Node));
                    newTree->number = currentNumber;
                    tree->leftSon = newTree;
                    isFirstOperandRead = true;
                }
                else
                {
                    Node* newTree = calloc(1, sizeof(Node));
                    newTree->number = currentNumber;
                    tree->rightSon = newTree;
                }
            }
            else
            {
                tree->operand = currentSymbol[0];
            }
        }
    }

    fclose(treeFile);
    remove("tmp.txt");
    return tree;
}

void printTree(const Node* tree)
{
    if (tree == NULL)
    {
        return;
    }
    if (tree->leftSon != NULL && tree->rightSon != 0)
    {
        printf("(");
    }
    if (tree->number != 0)
    {
        printf("%d ", tree->number);
    }
    else if (tree->operand != '\0')
    {
        printf("%c ", tree->operand);
    }

    printTree(tree->leftSon);
    printTree(tree->rightSon);

    if (tree->leftSon != NULL && tree->rightSon != 0)
    {
        printf(") ");
    }
}

int calculateTree(const Node* tree)
{
    if (tree->number != 0)
    {
        return tree->number;
    }

    int firstOperand = calculateTree(tree->leftSon);
    int secondOperand = calculateTree(tree->rightSon);

    if (tree->operand == '+')
    {
        return firstOperand + secondOperand;
    }
    else if (tree->operand == '-')
    {
        return firstOperand - secondOperand;
    }
    else if (tree->operand == '*')
    {
        return firstOperand * secondOperand;
    }
    else if (tree->operand == '/')
    {
        return firstOperand / secondOperand;
    }
}

void deleteTree(Node* tree)
{
    if (tree == NULL)
    {
        return;
    }
    deleteTree(tree->leftSon);
    deleteTree(tree->rightSon);
    free(tree);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    char treeLine[100] = { 0 };
    readLineFromFile("Tree.txt", treeLine, 100);
    Node* tree = createTreeFromLine(treeLine);
    if (tree == NULL)
    {
        printf("Произошла какая-то ошибка или дерево пусто ...\n");
        return 1;
    }

    printf("Распечатанное по файлу дерево: ");
    printTree(tree);
    printf("\n");
    printf("Значение дерева разбора равно: %d\n", calculateTree(tree));

    deleteTree(tree);
}