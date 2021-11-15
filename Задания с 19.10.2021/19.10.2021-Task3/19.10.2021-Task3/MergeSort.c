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
        addToHead(phoneBook, note);
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

void shiftFirstElement(List* source, Position** sourcePosition, List* destination, Position** destinationPosition)
{
    if (getLength(source) == 0 || isLast(*sourcePosition))
    {
        return;
    }
    if (getLength(destination) == 0)
    {
        addToHead(destination, getData(*sourcePosition));
        Position* copyOfDestinationPosition = *destinationPosition;
        *destinationPosition = getFirstElement(destination);
        deletePosition(copyOfDestinationPosition);
    }
    else
    {
        addAfter(destination, *destinationPosition, getData(*sourcePosition));
        next(*destinationPosition);
    }
    next(*sourcePosition);
    deleteFirstElement(source);
}

List* merge(List* firstHalf, List* secondHalf, const Option option)
{
    List* mergedList = createList();
    Position* mergedListPointer = getFirstElement(mergedList);
    Position* firstHalfPointer = getFirstElement(firstHalf);
    Position* secondHalfPointer = getFirstElement(secondHalf);

    while (getLength(firstHalf) != 0 && getLength(secondHalf) != 0)
    {
        if (comparePointers(firstHalf, secondHalf, option) <= 0)
        {
            shiftFirstElement(firstHalf, &firstHalfPointer, mergedList, &mergedListPointer);
        }
        else
        {
            shiftFirstElement(secondHalf, &secondHalfPointer, mergedList, &mergedListPointer);
        }
    }

    while (getLength(firstHalf) > 0)
    {
        shiftFirstElement(firstHalf, &firstHalfPointer, mergedList, &mergedListPointer);
    }
    while (getLength(secondHalf) > 0)
    {
        shiftFirstElement(secondHalf, &secondHalfPointer, mergedList, &mergedListPointer);
    }

    deletePosition(firstHalfPointer);
    deletePosition(secondHalfPointer);
    deletePosition(mergedListPointer);
    return mergedList;
}

List* mergeSort(List* list, const Option option)
{
    const int listLength = getLength(list);
    if (listLength == 1)
    {
        List* newList = createList();
        addToHead(newList, getData(getFirstElement(list)));
        return newList;
    }

    Position* listPosition = getFirstElement(list);
    List* firstHalf = createList();
    List* secondHalf = createList();
    while (getLength(firstHalf) != listLength / 2)
    {
        addToHead(firstHalf, getData(listPosition));
        next(listPosition);
    }
    while (getLength(secondHalf) != listLength - listLength / 2)
    {
        addToHead(secondHalf, getData(listPosition));
        next(listPosition);
    }

    List* sortedFirstHalf = mergeSort(firstHalf, option);
    List* sortedSecondHalf = mergeSort(secondHalf, option);
    List* sortedList = merge(sortedFirstHalf, sortedSecondHalf, option);

    deleteList(firstHalf);
    deleteList(secondHalf);
    deleteList(sortedFirstHalf);
    deleteList(sortedSecondHalf);
    deletePosition(listPosition);

    return sortedList;
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

    List* sortedPhoneBook = NULL;
    if (option == 1)
    {
        sortedPhoneBook = mergeSort(phoneBook, SORT_BY_NAME);
    }
    else if (option == 2)
    {
        sortedPhoneBook = mergeSort(phoneBook, SORT_BY_PHONENUMBER);
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

    printList(sortedPhoneBook);
    deleteList(sortedPhoneBook);
    deleteList(phoneBook);
}