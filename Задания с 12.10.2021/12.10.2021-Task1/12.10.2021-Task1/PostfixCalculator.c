#pragma warning (disable: 4996)

#include "../../Stack/Stack/Stack.h"
#include "PostfixCalculatorTests.h"

#include <stdio.h>
#include <locale.h>

float postfixCalculator(char sequence[])
{
    StackElement* head = NULL;
    int position = 0;
    float firstNumber = 0;
    float secondNumber = 0;
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
            push(&head, (float)firstNumber / secondNumber);
            break;
        default:
            push(&head, sequence[position] - '0');
            break;
        }
        position++;
    }
    return pop(&head);
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
    const float result = postfixCalculator(sequence);
    printf("Полученный результат: %f", result);
    printf("\n");
}