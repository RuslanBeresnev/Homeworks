#pragma warning (disable: 4996 5045 4668 4710 6031)

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    char name[50];
    char phoneNumber[30];
} Note;

int initializeMemory(Note phoneBook[], const char fileName[])
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
        if (note.name[0] == 0)
        {
            break;
        }
        int position = 0;
        while (note.name[position] != ':')
        {
            position++;
        }
        note.name[position] = 0;
        phoneBook[notesRead] = note;
        notesRead++;
    }
    fclose(database);
    return notesRead;
}

void addNote(const char name[], const char phoneNumber[], Note phoneBook[], const int currentIndex)
{
    strcpy(phoneBook[currentIndex].name, name);
    strcpy(phoneBook[currentIndex].phoneNumber, phoneNumber);
}

void printAllNotes(const Note phoneBook[], const int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%s %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
    }
}

void findPhoneNumber(const char name[], char phoneNumber[], const Note phoneBook[], const int length)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(name, phoneBook[i].name) == 0)
        {
            strcpy(phoneNumber, phoneBook[i].phoneNumber);
            break;
        }
    }
}

void findName(const char phoneNumber[], char name[], const Note phoneBook[], const int length)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(phoneNumber, phoneBook[i].phoneNumber) == 0)
        {
            strcpy(name, phoneBook[i].name);
            break;
        }
    }
}

int saveData(const char fileName[], const Note phoneBook[], const int notesCount)
{
    FILE* database = fopen(fileName, "w");
    if (database == NULL)
    {
        return 1;
    }
    for (int i = 0; i < notesCount; i++)
    {
        fprintf(database, "%s: ", phoneBook[i].name);
        fprintf(database, "%s\n", phoneBook[i].phoneNumber);
    }
    fclose(database);
    return 0;
}

void readLineWithoutLineBreak(char line[], int maxLength)
{
    fgets(line, maxLength, stdin);
    int counter = 0;
    while (line[counter] != '\n')
    {
        counter++;
    }
    line[counter] = '\0';
}

void clearFile(const char fileName[])
{
    FILE* file = fopen(fileName, "w");
    fclose(file);
}

bool saveDataTestPassed(void)
{
    Note phoneBook[100] = { 0 };
    addNote("RazbeR", "+7??????????", phoneBook, 0);
    addNote("RRB3", "+7??????????", phoneBook, 1);
    saveData("Test Database.txt", phoneBook, 2);
    initializeMemory(phoneBook, "Test Database.txt");
    return strcmp(phoneBook[0].name, "RazbeR") == 0 && strcmp(phoneBook[0].phoneNumber, "+7??????????") == 0 &&
        strcmp(phoneBook[1].name, "RRB3") == 0 && strcmp(phoneBook[1].phoneNumber, "+7??????????") == 0;
}

bool addNoteTestPassed(void)
{
    Note phoneBook[100] = { 0 };
    addNote("Vanya Akakievich", "+79876543210", phoneBook, 0);
    addNote("Petr Gvidonovich", "+71234872092", phoneBook, 1);
    return strcmp(phoneBook[0].name, "Vanya Akakievich") == 0 && strcmp(phoneBook[0].phoneNumber, "+79876543210") == 0 &&
        strcmp(phoneBook[1].name, "Petr Gvidonovich") == 0 && strcmp(phoneBook[1].phoneNumber, "+71234872092") == 0;
}

bool findPhoneNumberTestPassed(void)
{
    Note phoneBook[100] = { 0 };
    const int length = initializeMemory(phoneBook, "Test Database.txt");
    char phoneNumber[30] = { 0 };
    findPhoneNumber("RazbeR", phoneNumber, phoneBook, length);
    return strcmp(phoneNumber, "+7??????????") == 0;
}

bool findNameTestPassed(void)
{
    Note phoneBook[100] = { 0 };
    const int length = initializeMemory(phoneBook, "Test Database.txt");
    char name[50] = { 0 };
    findName("+7??????????", name, phoneBook, length);
    return strcmp(name, "RazbeR") == 0;
}

bool generalTestPassed(void)
{
    return saveDataTestPassed() && findPhoneNumberTestPassed() && findNameTestPassed() && addNoteTestPassed();
}

int main(int argc, char* argv[])
{
    clearFile("Test Database.txt");
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

    setlocale(LC_ALL, "Russian");
    Note phoneBook[100] = { 0 };
    int notesCount = initializeMemory(phoneBook, "Database.txt");
    int notesCountBeforeSaving = notesCount;

    while (true)
    {
        printf("Введите одну из следующих команд:\n");
        printf("\n");
        printf("0 - Выйти\n");
        printf("1 - Добавить новую запись\n");
        printf("2 - Распечатать все имеющиеся записи\n");
        printf("3 - Найти телефон по имени\n");
        printf("4 - Найти имя по телефону\n");
        printf("5 - Сохранить текущие данные в файл\n");

        int selectedCommand = 0;
        const int commandInput = scanf("%d", &selectedCommand);
        while (getchar() != '\n');
        if (commandInput != 1)
        {
            printf("Кажется, вы ввели недопустимые данные, поэтому программа завершает работу ...\n");
            return 1;
        }

        if (selectedCommand == 0)
        {
            return 0;
        }
        else if (selectedCommand == 1)
        {
            if (notesCount == 100)
            {
                printf("Телефонный справочник переполнен. Больше нельзя добавлять записи.\n");
            }
            else
            {
                printf("Введите имя пользователя на английском языке:\n");
                char name[50] = { 0 };
                readLineWithoutLineBreak(name, 50);
                printf("Введите номер телефона:\n");
                char phoneNumber[30] = { 0 };
                readLineWithoutLineBreak(phoneNumber, 30);

                addNote(name, phoneNumber, phoneBook, notesCountBeforeSaving);
                notesCountBeforeSaving++;
                printf("Запись добавлена\n");
            }
        }
        else if (selectedCommand == 2)
        {
            if (notesCountBeforeSaving == 0)
            {
                printf("В справочнике пока нет записей, но вы можете их добавить\n");
            }
            else
            {
                printf("Все имеющиеся в справочнике записи:\n");
                printAllNotes(phoneBook, notesCountBeforeSaving);
            }
        }
        else if (selectedCommand == 3)
        {
            printf("Введите имя пользователя:\n");
            char name[50] = { 0 };
            readLineWithoutLineBreak(name, 50);
            char phoneNumber[30] = { 0 };
            findPhoneNumber(name, phoneNumber, phoneBook, notesCountBeforeSaving);
            if (phoneNumber[0] == 0)
            {
                printf("Кажется, данного пользователя нет в телефонном справочнике ...\n");
            }
            else
            {
                printf("Номер телефона пользователя %s: %s\n", name, phoneNumber);
            }
        }
        else if (selectedCommand == 4)
        {
            printf("Введите номер телефона:\n");
            char phoneNumber[30] = { 0 };
            readLineWithoutLineBreak(phoneNumber, 30);
            char name[50] = { 0 };
            findName(phoneNumber, name, phoneBook, notesCountBeforeSaving);
            if (name[0] == 0)
            {
                printf("Кажется данный номер телефона отсутствует в справочнике ...\n");
            }
            else
            {
                printf("Имя пользователя с номером телефона %s: %s\n", phoneNumber, name);
            }
        }
        else if (selectedCommand == 5)
        {
            const int errorCode = saveData("Database.txt", phoneBook, notesCountBeforeSaving);
            if (errorCode != 0)
            {
                printf("Что-то пошло не так ...\n");
                return 1;
            }
            notesCount = notesCountBeforeSaving;
            printf("Данные сохранены\n");
        }
    }
}