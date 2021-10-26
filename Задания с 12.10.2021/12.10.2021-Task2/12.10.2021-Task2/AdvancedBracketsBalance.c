#pragma warning (disable: 4996 4464)

#include "../../Stack/Stack/Stack.h"

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

bool checkBracketsBalance(char sequence[])
{
    StackElement* head = NULL;
    int position = 0;
    char topElement = 0;
    while (sequence[position] != '\0')
    {
        if (sequence[position] == ')' || sequence[position] == ']' || sequence[position] == '}')
        {
            topElement = (char)pop(&head);
        }
        switch (sequence[position])
        {
        case ')':
            if (topElement != '(')
            {
                return false;
            }
            break;
        case ']':
            if (topElement != '[')
            {
                return false;
            }
            break;
        case '}':
            if (topElement != '{')
            {
                return false;
            }
            break;
        default:
            push(&head, (int)sequence[position]);
            break;
        }
        position++;
    }
    if (!isEmpty(head))
    {
        return false;
    }
    return true;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    printf("Введите скобочную последовательность:\n");
    char sequence[100] = { 0 };
    const int input = scanf("%s", &sequence);
    if (input == 0)
    {
        printf("Введены некорректные данные ...\n");
        return 1;
    }
    bool verdict = checkBracketsBalance(sequence);
    if (verdict)
    {
        printf("Это правильная скобочная последовательность }])\n");
    }
    else
    {
        printf("Это неправильная скобочная последовательность {[(\n");
    }
}