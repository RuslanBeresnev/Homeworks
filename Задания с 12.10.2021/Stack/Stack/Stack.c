#pragma warning (disable: 4047)

#include "Stack.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct StackElement
{
    int value;
    struct StackElement* next;
} StackElement;

int push(StackElement** head, int number)
{
    StackElement* newStackElement = calloc(1, sizeof(StackElement));
    if (newStackElement == NULL)
    {
        return 1;
    }
    newStackElement->value = number;
    newStackElement->next = *head;
    *head = newStackElement;
    return 0;
}

int pop(StackElement** head)
{
    if (head == NULL || *head == NULL)
    {
        return NULL;
    }
    StackElement* temporary = *head;
    int value = temporary->value;
    *head = (*head)->next;
    free(temporary);
    return value;
}

bool isEmpty(StackElement* head)
{
    return head == NULL;
}

void deleteStack(StackElement** head)
{
    while (!isEmpty(*head))
    {
        pop(head);
    }
}