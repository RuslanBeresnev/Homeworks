#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Рекурсивный алгоритм заметно медленнее итеративного начиная примерно с fib(33)

int recursiveFibonacci(int index)
{
    if (index == 0)
    {
        return 0;
    }
    else if (index == 1)
    {
        return 1;
    }
    else if (index > 1)
    {
        return recursiveFibonacci(index - 1) + recursiveFibonacci(index - 2);
    }
    return -1;
}

int iterativeFibonacci(int index)
{
    if (index < 0)
    {
        return -1;
    }
    int fibonacciNumbers[3] = { 0 };
    fibonacciNumbers[1] = 1;
    for (int i = 2; i <= index; i++)
    {
        fibonacciNumbers[i % 3] = fibonacciNumbers[(i - 1) % 3] + fibonacciNumbers[(i - 2) % 3];
    }
    return fibonacciNumbers[index % 3];
}

bool standardCasesTest()
{
    return iterativeFibonacci(20) == 6765 && recursiveFibonacci(20) == 6765;
}

bool edgeCasesTest()
{
    return iterativeFibonacci(0) == 0 && recursiveFibonacci(0) == 0 && iterativeFibonacci(1) == 1 && recursiveFibonacci(1) == 1;
}

bool crashCasesTest()
{
    return iterativeFibonacci(-10) == -1 && recursiveFibonacci(-10) == -1;
}

bool generalTest()
{
    return standardCasesTest() && edgeCasesTest() && crashCasesTest();
}

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "1") == 0)
    {
        if (generalTest())
        {
            printf("Tests Passed!\n");
            return 0;
        }
        printf("Tests Failed ...\n");
        return 1;
    }

    printf("Input Fibonacci index:\n");
    int index = -1;
    const int input = scanf("%d", &index);
    if (input != 1)
    {
        printf("You entered not a number ...\n");
        return 1;
    }
    printf("Fibonacci(%d) found iteratively: %d\n", index, iterativeFibonacci(index));
    printf("Fibonacci(%d) found recursively: %d\n", index, recursiveFibonacci(index));
}