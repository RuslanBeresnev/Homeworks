#pragma warning (disable: 4996 4464)

#include "../../Stack/Stack/Stack.h"

#include <stdio.h>
#include <locale.h>

//void shuntingYard(char sequence[], char toInput[])
//{
//    StackElement* head = NULL;
//    int sequencePosition = 0;
//    int toInputPosition = 0;
//    int attachmentsCount = 0;
//    while (sequence[sequencePosition] != '\n')
//    {
//        if (sequence[sequencePosition] == '+' || sequence[sequencePosition] == '-' || sequence[sequencePosition] == '*' ||
//            sequence[sequencePosition] == '/' || sequence[sequencePosition] == '(')
//        {
//            push(&head, (int)sequence[sequencePosition]);
//        }
//        else
//        {
//            if (sequence[sequencePosition] != ' ' && sequence[sequencePosition] != ')')
//            {
//                toInput[toInputPosition] = sequence[sequencePosition];
//                toInput[toInputPosition + 1] = ' ';
//                toInputPosition += 2;
//            }
//        }
//        if (sequence[sequencePosition] == '(')
//        {
//            attachmentsCount++;
//        }
//        else if (sequence[sequencePosition] == ')' && attachmentsCount > 0)
//        {
//            bool correctWorking = true;
//            char topElement = (char)pop(&head, &correctWorking);
//            if (!correctWorking)
//            {
//                attachmentsCount--;
//                continue;
//            }
//            while (topElement != '(')
//            {
//                toInput[toInputPosition] = topElement;
//                toInput[toInputPosition + 1] = ' ';
//                toInputPosition += 2;
//                correctWorking = true;
//                topElement = (char)pop(&head, &correctWorking);
//                if (!correctWorking)
//                {
//                    break;
//                }
//            }
//            if (!isEmpty(head))
//            {
//                correctWorking = true;
//                toInput[toInputPosition] = (char)pop(&head, &correctWorking);
//                toInput[toInputPosition + 1] = ' ';
//                toInputPosition += 2;
//            }
//            attachmentsCount--;
//        }
//        sequencePosition++;
//    }
//    if (attachmentsCount == 0)
//    {
//        while (!isEmpty(head))
//        {
//            bool correctWorking = true;
//            toInput[toInputPosition] = (char)pop(&head, &correctWorking);
//            toInput[toInputPosition + 1] = ' ';
//            toInputPosition += 2;
//        }
//    }
//}

int shuntingYard(const char sequence[], char toOutput[])
{
    StackElement* head = NULL;
    int sequencePosition = 0;
    int toOutputPosition = 0;
    while (sequence[sequencePosition] != '\n')
    {
        char token = sequence[sequencePosition];

        if (token != '(' && token != ')' && token != '+' && token != '-' && token != '*' && token != '/')
        {
            push(&head, (int)token);
        }
        else if (token == '(')
        {
            push(&head, token);
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
                    continue;
                }
                break;
            }
        }
        else
        {
            if (token == '*' || token == '/')
            {
                while ()
                {

                }
            }
            else if (token == '+' || token == '-')
            {
                while ()
                {

                }
            }
        }
    }
    // Не забыть return 0
}

int main(void)
{
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