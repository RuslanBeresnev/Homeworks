#pragma warning (disable: 4996 4710 5045)

#include "List.h"

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

void addNumberToList(List* list, const int number)
{
    Position* position = first(list);
    if (last(position))
    {
        addToStart(list, number);
        return;
    }
    if (get(position) >= number)
    {
        addToStart(list, number);
        deletePosition(position);
        return;
    }
    while (!(last(next(position))) && get(next(position)) < number)
    {
        position = next(position);
    }
    addAfter(position, number);
    deletePosition(position);
}

bool removeNumberFromList(List* list, const int index)
{
    if (index == 0)
    {
        return deleteFirstElement(list);
    }
    Position* position = first(list);
    for (int i = 0; i < index - 1; i++)
    {
        if (last(position))
        {
            break;
        }
        position = next(position);
    }
    const bool successedRemove = deleteElementAfterPosition(position);
    deletePosition(position);
    return successedRemove;
}

void printList(List* list)
{
    Position* position = first(list);
    while (!last(position))
    {
        printf("%d ", get(position));
        position = next(position);
    }
    printf("\n");
    deletePosition(position);
}

int main(void)
{
    List* list = createList();

    while (true)
    {
        setlocale(LC_ALL, "Russian");
        printf("\n");
        printf("Введите одну из следующих команд:\n");
        printf("\n");
        printf("0 – выйти\n");
        printf("1 – добавить значение в сортированный список\n");
        printf("2 – удалить значение из списка\n");
        printf("3 – распечатать список\n");
        printf("\n");

        int selectedCommand = 0;
        const int commandInput = scanf("%d", &selectedCommand);
        if (commandInput != 1)
        {
            printf("Что-то пошло не так ...\n");
            deleteList(list);
            return 1;
        }

        if (selectedCommand == 0)
        {
            deleteList(list);
            break;
        }
        else if (selectedCommand == 1)
        {
            printf("Введите число: ");
            int number = 0;
            const int numberInput = scanf("%d", &number);
            if (numberInput != 1)
            {
                printf("Что-то пошло не так ...\n");
                deleteList(list);
                return 1;
            }
            addNumberToList(list, number);
            printf("Число добавлено в список\n");
        }
        else if (selectedCommand == 2)
        {
            printf("Введите индекс элемента (слева-направо), который хотите удалить: ");
            int index = 0;
            const int indexInput = scanf("%d", &index);
            if (indexInput != 1)
            {
                printf("Что-то пошло не так ...\n");
                deleteList(list);
                return 1;
            }
            if (removeNumberFromList(list, index))
            {
                printf("Элемент удалён\n");
            }
            else
            {
                printf("Что-то пошло не так ... Элемент не удалён\n");
            }
        }
        else if (selectedCommand == 3)
        {
            printf("Распечатанный сортированный список:\n");
            printList(list);
        }
        else
        {
            printf("Такой команды пока ещё нет ...\n");
        }
    }
}