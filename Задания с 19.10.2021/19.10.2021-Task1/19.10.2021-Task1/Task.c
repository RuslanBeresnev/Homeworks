#pragma warning (disable: 4996 4710 5045)

#include "SortedList.h"

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

bool standardAddRemoveTestPassed(void)
{
    List* list = createList();

    addNumberToList(list, 10);
    addNumberToList(list, 8);
    addNumberToList(list, 12);
    addNumberToList(list, 10);
    addNumberToList(list, 1);

    Position* position = first(list);
    int correctSequence[5] = { 1, 8, 10, 10, 12 };
    for (int i = 0; i < 5; i++)
    {
        if (get(position) != correctSequence[i])
        {
            return false;
        }
        next(position);
    }
    deletePosition(position);

    position = first(list);
    deleteElementAfterPosition(position);
    deleteElementAfterPosition(position);
    deleteElementAfterPosition(position);
    deleteFirstElement(list);
    deletePosition(position);
    
    position = first(list);
    const int value = get(position);
    deleteList(list);
    deletePosition(position);
    return value == 12;
}

bool deletionFromEmptyListTestPassed(void)
{
    List* list = createList();
    bool successfulDeletion = deleteFirstElement(list);
    deleteList(list);
    return !successfulDeletion;
}

bool generalTestPassed(void)
{
    return standardAddRemoveTestPassed() && deletionFromEmptyListTestPassed();
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    List* list = createList();

    while (true)
    {
        setlocale(LC_ALL, "Russian");
        printf("\n");
        printf("¬ведите одну из следующих команд:\n");
        printf("\n");
        printf("0 Ц выйти\n");
        printf("1 Ц добавить значение в сортированный список\n");
        printf("2 Ц удалить значение из списка\n");
        printf("3 Ц распечатать список\n");
        printf("\n");

        int selectedCommand = 0;
        const int commandInput = scanf("%d", &selectedCommand);
        if (commandInput != 1)
        {
            printf("„то-то пошло не так ...\n");
            deleteList(list);
            return 1;
        }

        switch (selectedCommand)
        {
        case 0:
        {
            deleteList(list);
            return 0;
        }
        case 1:
        {
            printf("¬ведите число: ");
            int number = 0;
            const int numberInput = scanf("%d", &number);
            if (numberInput != 1)
            {
                printf("„то-то пошло не так ...\n");
                deleteList(list);
                return 1;
            }
            addNumberToList(list, number);
            printf("„исло добавлено в список\n");
            break;
        }
        case 2:
        {
            printf("¬ведите индекс элемента (слева-направо), который хотите удалить: ");
            int index = 0;
            const int indexInput = scanf("%d", &index);
            if (indexInput != 1)
            {
                printf("„то-то пошло не так ...\n");
                deleteList(list);
                return 1;
            }
            if (removeNumberFromList(list, index))
            {
                printf("Ёлемент удалЄн\n");
            }
            else
            {
                printf("„то-то пошло не так ... Ёлемент не удалЄн\n");
            }
            break;
        }
        case 3:
        {
            printf("–аспечатанный сортированный список:\n");
            printList(list);
            break;
        }
        default:
        {
            printf("“акой команды пока ещЄ нет ...\n");
            break;
        }
        }
    }
}