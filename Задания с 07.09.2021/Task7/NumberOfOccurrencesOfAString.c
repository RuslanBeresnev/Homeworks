#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    char s[100] = { 0 };
    char s1[100] = { 0 };
    int countOfOccurrences = 0;
    printf("Enter the string where you want to find occurrences:\n");
    scanf("%s", &s);
    int sLength = strlen(s);
    printf("Enter the substring you want to find:\n");
    scanf("%s", &s1);
    int s1Length = strlen(s1);
    int enteredLettersCounter = 0;
    for (int i = 0; i < sLength - s1Length + 1; i++)
    {
        if (s[i] == s1[enteredLettersCounter])
        {
            enteredLettersCounter++;
            bool isOccurence = true;
            for (int j = i + 1; j < i + s1Length; j++)
            {
                if (s[j] != s1[enteredLettersCounter])
                {
                    isOccurence = false;
                    enteredLettersCounter = 0;
                    break;
                }
                enteredLettersCounter++;
            }
            if (isOccurence)
            {
                countOfOccurrences++;
            }
        }
        enteredLettersCounter = 0;
    }
    printf("Count of occurrences s1 in s: %d\n", countOfOccurrences);
}