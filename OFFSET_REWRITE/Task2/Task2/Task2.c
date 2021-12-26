#pragma warning (disable: 4996)

#include "PriorityQueue.h"

#include <stdio.h>
#include <stdbool.h>

bool standardQueueTestPassed(void)
{
    PriorityQueue* queue = createPriorityQueue();

    enqueue(queue, 1, 10);
    enqueue(queue, 2, 20);
    enqueue(queue, 3, 5);
    enqueue(queue, 4, 30);
    enqueue(queue, 5, 1);

    const int value1 = dequeue(queue);
    const int value2 = dequeue(queue);
    const int value3 = dequeue(queue);
    const int value4 = dequeue(queue);
    const int value5 = dequeue(queue);

    bool verdict = false;
    if (value1 == 4 && value2 == 2 && value3 == 1 && value4 == 3 && value5 == 5)
    {
        verdict = true;
    }

    deletePriorityQueue(queue);
    return verdict;
}

bool queueWithSamePriorityElementsTestPassed(void)
{
    PriorityQueue* queue = createPriorityQueue();

    enqueue(queue, 1, 1);
    enqueue(queue, 2, 1);
    enqueue(queue, 3, 1);

    const int value1 = dequeue(queue);
    const int value2 = dequeue(queue);
    const int value3 = dequeue(queue);

    bool verdict = false;
    if (value1 == 1 && value2 == 2 && value3 == 3)
    {
        verdict = true;
    }

    deletePriorityQueue(queue);
    return verdict;
}

bool emptyQueueTestPassed(void)
{
    PriorityQueue* queue = createPriorityQueue();

    const int value = dequeue(queue);

    bool verdict = false;
    if (value == -1 && isEmpty(queue))
    {
        verdict = true;
    }

    deletePriorityQueue(queue);
    return verdict;
}

bool generalTestPassed(void)
{
    return standardQueueTestPassed() && queueWithSamePriorityElementsTestPassed() && emptyQueueTestPassed();
}

int main(void)
{
    if (generalTestPassed())
    {
        printf("Tests Passed !\n");
        return 0;
    }

    printf("Tests Failed ...\n");
    return 1;
}