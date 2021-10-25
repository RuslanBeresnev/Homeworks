#include "Stack.h"

#include <stdio.h>

bool notEmptyStackTestPassed(void)
{
    StackElement* head = NULL;
    for (int i = 0; i < 10; i++)
    {
        push(&head, i);
    }
    int numbers[10] = { 0 };
    for (int i = 0; i < 10; i++)
    {
        numbers[9 - i] = pop(&head, i);
    }
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
    return pop(&head) == 0;
}

bool isEmptyFunctionTestPassed(void)
{
    StackElement* firstHead = NULL;
    push(&firstHead, 1);
    StackElement* secondHead = NULL;
    return isEmpty(firstHead) == false && isEmpty(secondHead) == true;
}

bool deleteStackFunctionTestPassed(void)
{
    StackElement* head = NULL;
    for (int i = 0; i < 10; i++)
    {
        push(&head, i);
    }
    deleteStack(&head);
    return isEmpty(head) == true;
}

bool generalTest(void)
{
    return notEmptyStackTestPassed() && emptyStackTestPassed() && isEmptyFunctionTestPassed() && deleteStackFunctionTestPassed();
}