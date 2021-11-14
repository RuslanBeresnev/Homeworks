#pragma warning (disable: 4996 4464)

#include "../../Stack/Stack/Stack.h"

#include <stdio.h>
#include <locale.h>
#include <string.h>

bool isCorrectInputSequence(const char sequence[])
{
    int position = 0;
    while (sequence[position] != '\n')
    {
        const int token = sequence[position];
        bool isDigit = false;
        for (int i = 0; i <= 9; i++)
        {
            if (token == i + 48)
            {
                isDigit = true;
                break;
            }
        }
        if (isDigit)
        {
            position++;
            continue;
        }
        if (token != '(' && token != ')' && token != '+' && token != '-' && token != '*' && token != '/' && token != ' ')
        {
            return false;
        }
        position++;
    }
    return true;
}

int shuntingYard(const char sequence[], char toOutput[])
{
    if (!isCorrectInputSequence(sequence))
    {
        return 1;
    }

    StackElement* head = NULL;
    int sequencePosition = 0;
    int toOutputPosition = 0;
    while (sequence[sequencePosition] != '\n')
    {
        char token = sequence[sequencePosition];

        if (token == ' ')
        {
            sequencePosition++;
            continue;
        }
        if (token != '(' && token != ')' && token != '+' && token != '-' && token != '*' && token != '/')
        {
            toOutput[toOutputPosition] = token;
            toOutput[toOutputPosition + 1] = ' ';
            toOutputPosition += 2;
        }
        else if (token == '(')
        {
            push(&head, (int)token);
        }
        else if (token == ')')
        {
            while (true)
            {
                bool correctWorking = true;
                char topElement = (char)pop(&head, &correctWorking);
                if (!correctWorking)
                {
                    return 1;
                }
                if (topElement != '(')
                {
                    toOutput[toOutputPosition] = topElement;
                    toOutput[toOutputPosition + 1] = ' ';
                    toOutputPosition += 2;
                    continue;
                }
                break;
            }
        }
        else
        {
            bool correctWorking = true;
            if (token == '*' || token == '/')
            {
                while ((char)top(&head, &correctWorking) == '*' || (char)top(&head, &correctWorking) == '/')
                {
                    toOutput[toOutputPosition] = (char)top(&head, &correctWorking);
                    toOutput[toOutputPosition + 1] = ' ';
                    toOutputPosition += 2;
                }
            }
            else if (token == '+' || token == '-')
            {
                while ((char)top(&head, &correctWorking) == '*' || (char)top(&head, &correctWorking) == '/'
                    || (char)top(&head, &correctWorking) == '+' || (char)top(&head, &correctWorking) == '-')
                {
                    toOutput[toOutputPosition] = (char)pop(&head, &correctWorking);
                    toOutput[toOutputPosition + 1] = ' ';
                    toOutputPosition += 2;
                }
            }
            push(&head, (int)token);
        }
        sequencePosition++;
    }
    bool correctWorking = true;
    while (!isEmpty(head))
    {
        if ((char)top(&head, &correctWorking) == '(')
        {
            return 1;
        }
        toOutput[toOutputPosition] = (char)pop(&head, &correctWorking);
        toOutput[toOutputPosition + 1] = ' ';
        toOutputPosition += 2;
    }
    return 0;
}

bool standardExpressionTestPassed(void)
{
    char postfixNotation[100] = { 0 };
    const int errorCode = shuntingYard("1 * 2 + 3\n", postfixNotation);
    return errorCode == 0 && strcmp(postfixNotation, "1 2 * 3 + ") == 0;
}

bool expressionWithBracketsTestPassed(void)
{
    char postfixNotation[100] = { 0 };
    const int errorCode = shuntingYard("3 + (1 * 2)\n", postfixNotation);
    return errorCode == 0 && strcmp(postfixNotation, "3 1 2 * + ") == 0;
}

bool incompleteExpressionTestPassed(void)
{
    char postfixNotation[100] = { 0 };
    const int errorCode = shuntingYard("+ 4\n", postfixNotation);
    return errorCode == 0 && strcmp(postfixNotation, "4 + ") == 0;
}

bool nestingExpressionTestPassed(void)
{
    char postfixNotation[100] = { 0 };
    const int errorCode = shuntingYard("(1 + (3 - 4 * (6 / 3)) * 2) * 3 + 5\n", postfixNotation);
    return errorCode == 0 && strcmp(postfixNotation, "1 3 4 6 3 / * - 2 * + 3 * 5 + ") == 0;
}

bool incorrectExpressionTestPassed(void)
{
    char postfixNotation[100] = { 0 };
    return shuntingYard("4 + 5 efef e/ ewd\n", postfixNotation) != 0;
}

bool generalTest(void)
{
    return standardExpressionTestPassed() && expressionWithBracketsTestPassed() && incompleteExpressionTestPassed()
        && nestingExpressionTestPassed() && incorrectExpressionTestPassed();
}

int main(void)
{
    if (!generalTest())
    {
        printf("Tests Failed ...\n");
        return 1;
    }
    setlocale(LC_ALL, "Russian");
    printf("Введите выражение в инфиксной форме:\n");
    char sequence[100] = { 0 };
    fgets(sequence, 100, stdin);
    char postfixNotation[100] = { 0 };
    const int errorCode = shuntingYard(sequence, postfixNotation);
    if (errorCode != 0)
    {
        printf("В выражении допущена ошибка ...\n");
        return 1;
    }
    printf("Выражение в постфиксной форме: %s\n", postfixNotation);
}