#include <stdio.h>
#include <stdbool.h>

int main()
{
    char bracketsSequence[101] = { 0 };
    printf("Enter bracket sequence:\n");
    int input = scanf("%100s", &bracketsSequence);
    const int stringLength = strlen(bracketsSequence);
    if (input != 1)
    {
        printf("Oh, something went wrong ...\n");
        return 1;
    }
    int balanceCounter = 0;
    bool sequenceIsRight = true;
    for (int i = 0; i < stringLength; i++)
    {
        if (bracketsSequence[i] != '(' && bracketsSequence[i] != ')')
        {
            printf("Unfortunately, this is not a bracket sequence ...\n");
            return 1;
        }
        if (bracketsSequence[i] == '(')
        {
            balanceCounter++;
        }
        else if (bracketsSequence[i] == ')')
        {
            balanceCounter--;
        }
        if (balanceCounter < 0)
        {
            sequenceIsRight = false;
            break;
        }
    }
    if (sequenceIsRight && balanceCounter == 0)
    {
        printf("The bracket sequence is correct )\n");
    }
    else
    {
        printf("The bracket sequence is incorrect (\n");
    }
}