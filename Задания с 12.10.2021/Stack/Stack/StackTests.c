#pragma warning (disable: 5045)

#include "Stack.h"

#include <stdio.h>

bool notEmptyStackTestPassed(void)
{
    StackElement* head = NULL;
    for (int i = 0; i < 10; i++)
    {
        const int errorCode = push(&head, i);
        if (errorCode != 0)
        {
            return false;
        }
    }
    int numbers[10] = { 0 };
    for (int i = 0; i < 10; i++)
    {
        bool correctWorking = true;
        numbers[9 - i] = pop(&head, &correctWorking);
        if (!correctWorking)
        {
            return false;
        }
    }
    deleteStack(&head);
    for (int i = 0; i < 10; i++)
    {
        if (numbers[i] != i)
        {
            return false;
        }
    }
    return true;
}

bool emptyStackTestPassed(void)
{
    StackElement* head = NULL;
    bool correctWorking = true;
    pop(&head, &correctWorking);
    return !correctWorking;
}

bool topFunctionTestPassed(void)
{
    StackElement* head = NULL;
    push(&head, 1);
    push(&head, 2);
    bool correctWorking = true;
    return top(&head, &correctWorking) == 2;
}

bool isEmptyFunctionTestPassed(void)
{
    StackElement* firstHead = NULL;
    const int errorCode = push(&firstHead, 1);
    if (errorCode != 0)
        return false;
    StackElement* secondHead = NULL;
    bool result = !isEmpty(firstHead) && isEmpty(secondHead);
    deleteStack(&firstHead);
    return result;
}

bool deleteStackFunctionTestPassed(void)
{
    StackElement* head = NULL;
    for (int i = 0; i < 10; i++)
    {
        const int errorCode = push(&head, i);
        if (errorCode != 0)
        {
            return false;
        }
    }
    deleteStack(&head);
    return isEmpty(head);
}

bool generalTest(void)
{
    return notEmptyStackTestPassed() && emptyStackTestPassed() && isEmptyFunctionTestPassed()
        && deleteStackFunctionTestPassed() && topFunctionTestPassed();
}