#pragma warning (disable: 4996 4464)

#include "../../Stack/Stack/Stack.h"

#include <stdio.h>
#include <locale.h>

int postfixCalculator(char sequence[])
{
    StackElement* head = NULL;
    int position = 0;
    int firstNumber = 0;
    int secondNumber = 0;
    while (sequence[position] != '\n')
    {
        if (sequence[position] == '+' || sequence[position] == '-' || sequence[position] == '*' || sequence[position] == '/')
        {
            secondNumber = pop(&head);
            firstNumber = pop(&head);
        }
        switch (sequence[position])
        {
        case ' ':
            position++;
            continue;
        case '+':
            push(&head, firstNumber + secondNumber);
            break;
        case '-':
            push(&head, firstNumber - secondNumber);
            break;
        case '*':
            push(&head, secondNumber * firstNumber);
            break;
        case '/':
            push(&head, firstNumber / secondNumber);
            break;
        default:
            push(&head, sequence[position] - '0');
            break;
        }
        position++;
    }
    return pop(&head);
}

bool standardSequenceTestPassed(void)
{
    return postfixCalculator("5 5 3 2 * + - 3 /\n") == -2;
}

bool emptySequenceTestPassed(void)
{
    return postfixCalculator("\n") == 0;
}

bool generalTestPassed(void)
{
    return standardSequenceTestPassed() && emptySequenceTestPassed();
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }
    setlocale(LC_ALL, "Russian");
    printf("Введите последовательность арифметических операций с помощью постфиксной записи:\n");
    char sequence[100] = { 0 };
    fgets(sequence, 100, stdin);
    const int result = postfixCalculator(sequence);
    printf("Полученный результат: %d", result);
    printf("\n");
}