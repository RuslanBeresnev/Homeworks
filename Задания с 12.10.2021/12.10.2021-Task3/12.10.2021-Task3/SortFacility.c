#pragma warning (disable: 4996 4464)

#include "../../Stack/Stack/Stack.h"

#include <stdio.h>
#include <locale.h>

void sortFacility(char sequence[], char toInput[])
{
    StackElement* head = NULL;
    int sequencePosition = 0;
    int toInputPosition = 0;
    int attachmentsCount = 0;
    while (sequence[sequencePosition] != '\n')
    {
        if (sequence[sequencePosition] == '+' || sequence[sequencePosition] == '-' || sequence[sequencePosition] == '*' ||
            sequence[sequencePosition] == '/' || sequence[sequencePosition] == '(')
        {
            push(&head, (int)sequence[sequencePosition]);
        }
        else
        {
            if (sequence[sequencePosition] != ' ' && sequence[sequencePosition] != ')')
            {
                toInput[toInputPosition] = sequence[sequencePosition];
                toInput[toInputPosition + 1] = ' ';
                toInputPosition += 2;
            }
        }
        if (sequence[sequencePosition] == '(')
        {
            attachmentsCount++;
        }
        else if (sequence[sequencePosition] == ')' && attachmentsCount > 0)
        {
            char topElement = (char)pop(&head);
            while (topElement != '(' && topElement != 0)
            {
                toInput[toInputPosition] = topElement;
                toInput[toInputPosition + 1] = ' ';
                toInputPosition += 2;
                topElement = (char)pop(&head);
            }
            if (!isEmpty(head))
            {
                toInput[toInputPosition] = (char)pop(&head);
                toInput[toInputPosition + 1] = ' ';
                toInputPosition += 2;
            }
            attachmentsCount--;
        }
        sequencePosition++;
    }
    if (attachmentsCount == 0)
    {
        while (!isEmpty(head))
        {
            toInput[toInputPosition] = (char)pop(&head);
            toInput[toInputPosition + 1] = ' ';
            toInputPosition += 2;
        }
    }
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    printf("Введите выражение в инфиксной форме:\n");
    char sequence[100] = { 0 };
    fgets(sequence, 100, stdin);
    char postfixNotation[100] = { 0 };
    sortFacility(sequence, postfixNotation);
    printf("Выражение в постфиксной форме: %s\n", postfixNotation);
}