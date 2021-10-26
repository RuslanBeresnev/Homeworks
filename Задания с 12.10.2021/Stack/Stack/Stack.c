#include "Stack.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct StackElement
{
    float value;
    struct StackElement* next;
}StackElement;

void push(StackElement** head, float number)
{
    StackElement* newStackElement = calloc(1, sizeof(StackElement));
    if (newStackElement == NULL)
    {
        return NULL;
    }
    newStackElement->value = number;
    newStackElement->next = *head;
    *head = newStackElement;
}
float pop(StackElement** head)
{
    if (*head == NULL || head == NULL)
    {
        return 0;
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