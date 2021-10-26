#pragma warning (disable: 4996 4464)

#include "../../Stack/Stack/Stack.h"

#include <stdio.h>
#include <locale.h>

int addToInputTopElement(char sequence[], int currentPosition, StackElement* headOfStack)
{
    sequence[currentPosition] = (char)pop(&headOfStack);
    sequence[currentPosition + 1] = ' ';
    currentPosition += 2;
    return currentPosition + 2;
}

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
               toInputPosition = addToInputTopElement(toInput, toInputPosition, head);
            }
        }
        if (sequence[sequencePosition] == '(')
        {
            attachmentsCount++;
        }
        else if (sequence[sequencePosition] == ')' && attachmentsCount > 0)
        {
            char topElement = 0;
            while (topElement != '(')
            {
                topElement = (char)pop(&head);
                toInputPosition = addToInputTopElement(toInput, toInputPosition, head);
            }
            attachmentsCount--;
            toInputPosition = addToInputTopElement(toInput, toInputPosition, head);
        }
        sequencePosition++;
    }
    while (!isEmpty(head))
    {
        toInputPosition = addToInputTopElement(toInput, toInputPosition, head);
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