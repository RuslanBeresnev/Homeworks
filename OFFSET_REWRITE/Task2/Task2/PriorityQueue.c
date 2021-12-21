#pragma warning (disable: 6011 28182)

#include "PriorityQueue.h"

#include <stdlib.h>

typedef struct QueueElement
{
    int value;
    int priority;
    struct QueueElement* next;
} QueueElement;

typedef struct PriorityQueue
{
    QueueElement* head;
} PriorityQueue;

PriorityQueue* createPriorityQueue(void)
{
    return calloc(1, sizeof(PriorityQueue));
}

void enqueue(PriorityQueue* queue, int value, int priority)
{
    QueueElement* newElement = calloc(1, sizeof(QueueElement));
    newElement->value = value;
    newElement->priority = priority;
    newElement->next = queue->head;
    queue->head = newElement;
}

bool isEmpty(PriorityQueue* queue)
{
    return queue->head == NULL;
}

QueueElement* getElementWithMaxPriority(PriorityQueue* queue)
{
    QueueElement* position = queue->head;
    int maxPriority = -1000000000;
    QueueElement* requiredElement = NULL;

    while (position != NULL)
    {
        if (position->priority >= maxPriority)
        {
            maxPriority = position->priority;
            requiredElement = position;
        }
        position = position->next;
    }

    return requiredElement;
}

QueueElement* getPreviousElement(PriorityQueue* queue, QueueElement* element)
{
    QueueElement* position = queue->head;
    QueueElement* requiredElement = NULL;

    while (true)
    {
        if (position->next == element)
        {
            requiredElement = position;
            return requiredElement;
        }
        position = position->next;
    }
}

int dequeue(PriorityQueue* queue)
{
    if (isEmpty(queue))
    {
        return -1;
    }

    QueueElement* requiredElement = getElementWithMaxPriority(queue);
    const int value = requiredElement->value;
    if (requiredElement == queue->head)
    {
        queue->head = requiredElement->next;
    }
    else
    {
        QueueElement* previousElement = getPreviousElement(queue, requiredElement);
        previousElement->next = requiredElement->next;
    }

    free(requiredElement);
    return value;
}

void deletePriorityQueue(PriorityQueue* queue)
{
    QueueElement* position = queue->head;

    while (!isEmpty(queue))
    {
        QueueElement* nextElement = position->next;
        free(position);
        position = nextElement;
    }

    free(queue);
}