#pragma warning (disable: 4996 5045 6328 6387)

#define MAX_ROW_LENGTH 30
#define MAX_COMMENT_LENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

int inputDFSTableFromFile(const char fileName[], int dfsTable[MAX_ROW_LENGTH][MAX_ROW_LENGTH][2])
{
    FILE* dfsFile = fopen(fileName, "r");
    if (dfsFile == NULL)
    {
        return 1;
    }

    int statesCount = 0;
    const int statesCountInput = fscanf(dfsFile, "%d", &statesCount);
    if (statesCountInput != 1)
    {
        fclose(dfsFile);
        return 1;
    }

    for (int i = 0; i < statesCount; i++)
    {
        int stateNumber = 0;
        const int stateNumberInput = fscanf(dfsFile, "%d", &stateNumber);
        if (stateNumberInput != 1)
        {
            fclose(dfsFile);
            return 1;
        }

        int transitionsCount = 0;
        const int transitionsCountInput = fscanf(dfsFile, "%d", &transitionsCount);
        if (transitionsCountInput != 1)
        {
            fclose(dfsFile);
            return 1;
        }

        for (int j = 0; j < transitionsCount; j++)
        {
            fgetc(dfsFile);
            char transitionSymbol = '\0';
            const int symbolInput = fscanf(dfsFile, "%c", &transitionSymbol);
            dfsTable[stateNumber][j][0] = transitionSymbol;
            if (symbolInput != 1)
            {
                fclose(dfsFile);
                return 1;
            }
            const int nextStateNumberInput = fscanf(dfsFile, "%d", &dfsTable[stateNumber][j][1]);
            if (nextStateNumberInput != 1)
            {
                fclose(dfsFile);
                return 1;
            }
        }
    }

    fclose(dfsFile);
    return 0;
}

int getCommentsFromFile(const char fileName[], const int dfsTable[MAX_ROW_LENGTH][MAX_ROW_LENGTH][2], char* comments[])
{
    FILE* codeFile = fopen(fileName, "r");
    if (codeFile == NULL)
    {
        return 1;
    }

    int state = 0;

    int commentsCount = 0;
    char currentComment[MAX_COMMENT_LENGTH] = { '\0' };
    int symbolPositionInComment = 0;

    while (!feof(codeFile))
    {
        char currentSymbol = (char)getc(codeFile);

        if (state == 2 || state == 3)
        {
            if (currentComment[0] == NULL)
            {
                currentComment[0] = '/';
                currentComment[1] = '*';
                symbolPositionInComment += 2;
            }
            currentComment[symbolPositionInComment] = currentSymbol;
            symbolPositionInComment++;
        }

        if (state == 4)
        {
            char* currentCommentCopy = calloc(MAX_COMMENT_LENGTH, sizeof(char));
            strcpy(currentCommentCopy, currentComment);
            comments[commentsCount] = currentCommentCopy;
            commentsCount++;

            symbolPositionInComment = 0;
            for (int i = 0; i < MAX_COMMENT_LENGTH; i++)
            {
                currentComment[i] = '\0';
            }
        }

        for (int i = 0; i < MAX_ROW_LENGTH; i++)
        {
            if (dfsTable[state][i][0] == currentSymbol || dfsTable[state][i][0] == '!')
            {
                state = dfsTable[state][i][1];
                break;
            }
        }
    }

    return commentsCount;
}

void printComments(const char* comments[], const int commentsCount)
{
    for (int i = 0; i < commentsCount; i++)
    {
        printf("%s", comments[i]);
    }
}

bool compareTwoStringArrays(const char* firstArray[], const char* secondArray[], const int length)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(firstArray[i], secondArray[i]) != 0)
        {
            return false;
        }
    }
    return true;
}

bool generalTestPassed(void)
{
    int DFSTable[MAX_ROW_LENGTH][MAX_ROW_LENGTH][2];
    const int errorCode = inputDFSTableFromFile("DFS.txt", DFSTable);
    if (errorCode != 0)
    {
        return false;
    }

    char* commentsArray[MAX_ROW_LENGTH] = { NULL };
    getCommentsFromFile("Test Input.txt", DFSTable, commentsArray);

    char* correctCommentsArray[10] = {"/*disables warnings*/", "/**/", "/*The main function in programm*/", "/*comment*/", "/*comment2**/"};
    bool verdict = compareTwoStringArrays(commentsArray, correctCommentsArray, 5);

    for (int i = 0; i < 5; i++)
    {
        free(commentsArray[i]);
    }

    return verdict;
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");

    int DFSTable[MAX_ROW_LENGTH][MAX_ROW_LENGTH][2];
    const int errorCode = inputDFSTableFromFile("DFS.txt", DFSTable);
    if (errorCode != 0)
    {
        printf("Файл не найден или произошла какая-то ошибка ...\n");
        return 1;
    }

    char* comments[MAX_ROW_LENGTH] = { NULL };
    const int commentsCount = getCommentsFromFile("Input.txt", DFSTable, comments);

    printf("Все строки комментариев из файла с кодом:\n\n");
    printComments(comments, commentsCount);
    printf("\n");

    for (int i = 0; i < commentsCount; i++)
    {
        free(comments[i]);
    }
}