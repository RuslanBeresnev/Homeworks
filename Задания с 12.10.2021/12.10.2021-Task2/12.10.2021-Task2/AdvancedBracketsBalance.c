#pragma warning (disable: 4996 4464)

#include "../../Stack/Stack/Stack.h"

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

bool checkBracketsBalance(const char sequence[])
{
    StackElement* head = NULL;
    int position = 0;
    char topElement = 0;
    while (sequence[position] != '\0')
    {
        if (sequence[position] == ')' || sequence[position] == ']' || sequence[position] == '}')
        {
            bool correctWorking = true;
            topElement = (char)pop(&head, &correctWorking);
            if (!correctWorking)
            {
                return false;
            }
        }
        switch (sequence[position])
        {
        case ')':
            if (topElement != '(')
            {
                deleteStack(&head);
                return false;
            }
            break;
        case ']':
            if (topElement != '[')
            {
                deleteStack(&head);
                return false;
            }
            break;
        case '}':
            if (topElement != '{')
            {
                deleteStack(&head);
                return false;
            }
            break;
        default:
            push(&head, (int)sequence[position]);
            break;
        }
        position++;
    }
    return isEmpty(head);
}

bool correctSequenceTestPassed(void)
{
    return checkBracketsBalance("[({([{}])})]");
}

bool wrongSequenceTestPassed(void)
{
    return !checkBracketsBalance("{[({)}])");
}

bool leftAntisymmetricSequenceTestPassed(void)
{
    return !checkBracketsBalance("(((((((((((((())))");
}

bool rightAntisymmetricSequenceTestPassed(void)
{
    return !checkBracketsBalance("((()))))))))))))))");
}

bool negativeSequenceTestPassed(void)
{
    return !checkBracketsBalance("}])([{");
}

bool oneElementSequenceTestPassed(void)
{
    return !checkBracketsBalance("(");
}

bool generalTestPassed(void)
{
    return correctSequenceTestPassed() && wrongSequenceTestPassed() && leftAntisymmetricSequenceTestPassed()
        && rightAntisymmetricSequenceTestPassed() && negativeSequenceTestPassed() && oneElementSequenceTestPassed();
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }
    setlocale(LC_ALL, "Russian");
    printf("Введите скобочную последовательность:\n");
    char sequence[100] = { 0 };
    const int input = scanf("%s", &sequence);
    if (input == 0)
    {
        printf("Введены некорректные данные ...\n");
        return 1;
    }
    const bool verdict = checkBracketsBalance(sequence);
    if (verdict)
    {
        printf("Это правильная скобочная последовательность }])\n");
    }
    else
    {
        printf("Это неправильная скобочная последовательность {[(\n");
    }
}