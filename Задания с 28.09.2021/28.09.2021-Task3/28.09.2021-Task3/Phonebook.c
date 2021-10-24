#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#pragma warning (disable: 4996 5045 6001 4090 6385 6386 4189)

typedef struct
{
    char name[50];
    char phoneNumber[30];
} Note;

int initializeMemory(Note phoneBook[], char fileName[])
{
    FILE* database = fopen(fileName, "r");
    if (database == NULL)
    {
        database = fopen(fileName, "w");
        return 0;
    }
    int notesRead = 0;
    int position = 0;
    bool nameReaded = false;
    Note note;
    while (!feof(database))
    {
        if (!nameReaded)
        {
            const int charReading = fscanf(database, "%c", &note.name[position]);
            if (charReading < 0)
            {
                fclose(database);
                return notesRead;
            }
        }
        else
        {
            const int charReading = fscanf(database, "%c", &note.phoneNumber[position]);
            if (charReading < 0)
            {
                fclose(database);
                note.phoneNumber[position] = '\0';
                phoneBook[notesRead] = note;
                notesRead++;
                return notesRead;
            }
        }
        if (note.name[position] == ':')
        {
            nameReaded = true;
            note.name[position] = '\0';
            position = -1;
            char backspace = '0';
            const int backspaceReading = fscanf(database, "%c", &backspace);
        }
        if (note.phoneNumber[position] == '\n')
        {
            nameReaded = false;
            note.phoneNumber[position] = '\0';
            phoneBook[notesRead] = note;
            position = -1;
            notesRead++;
        }
        position++;
    }
    return notesRead;
}

void addNote(const char name[], const char phoneNumber[], Note phoneBook[], const int currentIndex)
{
    Note note;
    strcpy(note.name, name);
    strcpy(note.phoneNumber, phoneNumber);
    phoneBook[currentIndex] = note;
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

int saveData(const Note phoneBook[], const int length)
{
    FILE* database = fopen("Database.txt", "w");
    if (database == NULL)
    {
        return 1;
    }
    for (int i = 0; i < length; i++)
    {
        fprintf(database, "%s: ", phoneBook[i].name);
        fprintf(database, "%s\n", phoneBook[i].phoneNumber);
    }
    fclose(database);
    return 0;
}

bool findPhoneNumberTestPassed(void)
{
    Note phoneBook[100] = { 0 };
    const int length = initializeMemory(phoneBook, "Test Database.txt");
    char phoneNumber[30] = { 0 };
    findPhoneNumber("Петя", phoneNumber, phoneBook, length);
    const char correctPhoneNumber[13] = "+78995677430";
    return strcmp(phoneNumber, correctPhoneNumber) == 0;
}

bool findNameTestPassed(void)
{
    Note phoneBook[100] = { 0 };
    const int length = initializeMemory(phoneBook, "Test Database.txt");
    char name[50] = { 0 };
    findName("+78995677430", name, phoneBook, length);
    const char correctName[5] = "Петя";
    return strcmp(name, correctName) == 0;
}

bool generalTestPassed(void)
{
    return findPhoneNumberTestPassed() && findNameTestPassed();
}

int main(void)
{
    if (!generalTestPassed())
    {
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
            printf("Кажется, вы не ввели недопустимые данные, поэтому программа завершает работу ...\n");
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
                fgets(name, 50, stdin);
                int counter = 0;
                while (name[counter] != '\n')
                {
                    counter++;
                }
                name[counter] = '\0';

                printf("Введите номер телефона:\n");
                char phoneNumber[30] = { 0 };
                fgets(phoneNumber, 30, stdin);
                counter = 0;
                while (phoneNumber[counter] != '\n')
                {
                    counter++;
                }
                phoneNumber[counter] = '\0';

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
            fgets(name, 50, stdin);
            int counter = 0;
            while (name[counter] != '\n')
            {
                counter++;
            }
            name[counter] = '\0';

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
            char phoneNumber[50] = { 0 };
            fgets(phoneNumber, 50, stdin);
            int counter = 0;
            while (phoneNumber[counter] != '\n')
            {
                counter++;
            }
            phoneNumber[counter] = '\0';

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
            const int errorCode = saveData(phoneBook, notesCountBeforeSaving);
            if (errorCode != 0)
            {
                printf("Что-то пошло не так ...\n");
                return 1;
            }
            notesCount = notesCountBeforeSaving;
            printf("Данные сохранены\n");
        }
    }
    return 0;
}