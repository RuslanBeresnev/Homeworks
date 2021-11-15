#pragma warning (disable: 4710 4996 5045 6031)

#include "PhoneBookList.h"

#include <stdio.h>
#include <locale.h>
#include <string.h>

typedef enum
{
    SORT_BY_NAME,
    SORT_BY_PHONENUMBER
} Option;

int initializeList(List* phoneBook, const char fileName[])
{
    FILE* database = fopen(fileName, "r");
    if (database == NULL)
    {
        database = fopen(fileName, "w");
        fclose(database);
        return 0;
    }

    int notesRead = 0;
    while (!feof(database))
    {
        Note note = { 0 };
        fscanf(database, "%s%s", note.name, note.phoneNumber);
        if (note.name[0] == '\0')
        {
            break;
        }
        int position = 0;
        while (note.name[position] != ':')
        {
            if (position == 50)
            {
                break;
            }
            position++;
        }
        if (position == 0)
        {
            continue;
        }
        if (position != 50)
        {
            note.name[position] = '\0';
        }
        addToStart(phoneBook, note);
        notesRead++;
    }
    fclose(database);
    return notesRead;
}

int comparePointers(const Position* pointer1, const Position* pointer2, const Option option)
{
    if (option == SORT_BY_NAME)
    {
        return strcmp(getData(pointer1).name, getData(pointer2).name);
    }
    else if (option == SORT_BY_PHONENUMBER)
    {
        return strcmp(getData(pointer1).phoneNumber, getData(pointer2).phoneNumber);
    }
}

void merge(List* list, const Option option, const int startPosition, const int middlePosition, const int endPosition)
{
    List* mergedList = createList();
    int leftCursor = startPosition;
    int rightCursor = middlePosition + 1;
    while (leftCursor <= middlePosition && rightCursor <= endPosition)
    {
        Position* leftPointer = getPositionByIndex(list, leftCursor);
        Position* rightPointer = getPositionByIndex(list, rightCursor);
        Position* mergedListPointer = getLastElement(mergedList);
        int resultOfCompare = 0;

        if (option == SORT_BY_NAME)
        {
            resultOfCompare = comparePointers(leftPointer, rightPointer, SORT_BY_NAME);
        }
        else if (option == SORT_BY_PHONENUMBER)
        {
            resultOfCompare = comparePointers(leftPointer, rightPointer, SORT_BY_PHONENUMBER);
        }

        if (resultOfCompare <= 0)
        {
            if (isEmptyData(mergedListPointer))
            {
                addToStart(mergedList, getData(leftPointer));
            }
            else
            {
                addAfter(mergedListPointer, getData(leftPointer));
            }
            leftCursor++;
        }
        else
        {
            if (isEmptyData(mergedListPointer))
            {
                addToStart(mergedList, getData(rightPointer));
            }
            else
            {
                addAfter(mergedListPointer, getData(rightPointer));
            }
            rightCursor++;
        }

        deletePosition(leftPointer);
        deletePosition(rightPointer);
        deletePosition(mergedListPointer);
    }

    Position* mergedListPointer = getLastElement(mergedList);
    while (leftCursor <= middlePosition)
    {
        Position* leftCursorPointer = getPositionByIndex(list, leftCursor);
        addAfter(mergedListPointer, getData(leftCursorPointer));
        Position* mergedListPointerCopy = mergedListPointer;
        mergedListPointer = next(mergedListPointer);
        leftCursor++;
        deletePosition(mergedListPointerCopy);
        deletePosition(leftCursorPointer);
    }
    while (rightCursor <= endPosition)
    {
        Position* rightCursorPointer = getPositionByIndex(list, rightCursor);
        addAfter(mergedListPointer, getData(rightCursorPointer));
        Position* mergedListPointerCopy = mergedListPointer;
        mergedListPointer = next(mergedListPointer);
        rightCursor++;
        deletePosition(mergedListPointerCopy);
        deletePosition(rightCursorPointer);
    }
    deletePosition(mergedListPointer);
    mergedListPointer = getFirstElement(mergedList);
    for (int listCursor = startPosition; listCursor <= endPosition; listCursor++)
    {
        Position* listPointer = getPositionByIndex(list, listCursor);
        setData(listPointer, getData(mergedListPointer));
        Position* mergedListPointerCopy = mergedListPointer;
        mergedListPointer = next(mergedListPointer);
        deletePosition(mergedListPointerCopy);
        deletePosition(listPointer);
    }
    deleteList(mergedList);
}

void mergeSort(List* list, const Option option, const int startPosition, const int endPosition)
{
    if (endPosition == startPosition)
    {
        return;
    }
    const int middlePosition = startPosition + (endPosition - startPosition) / 2;
    mergeSort(list, option, startPosition, middlePosition);
    mergeSort(list, option, middlePosition + 1, endPosition);
    merge(list, option, startPosition, middlePosition, endPosition);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    List* phoneBook = createList();
    const int length = initializeList(phoneBook, "Database.txt");
    if (length == 0)
    {
        printf("Файл пуст ...\n");
        return 1;
    }

    printf("Введите один из следующих способов сортировки записей:\n");
    printf("1 - по имени пользователя\n");
    printf("2 - по номеру телефона\n");

    int option = 0;
    const int input = scanf("%d", &option);
    if (input != 1 || (option != 1 && option != 2))
    {
        printf("Вы ввели некорректные данные ...\n");
        return 1;
    }

    if (option == 1)
    {
        mergeSort(phoneBook, SORT_BY_NAME, 0, length - 1);
    }
    else if (option == 2)
    {
        mergeSort(phoneBook, SORT_BY_PHONENUMBER, 0, length - 1);
    }

    printf("\n");
    if (option == 1)
    {
        printf("Отсортированные по имени пользователя записи в телефонной книге:\n");
    }
    else if (option == 2)
    {
        printf("Отсортированные по номеру телефона записи в телефонной книге:\n");
    }
    printf("\n");
    printList(phoneBook);
    deleteList(phoneBook);
}