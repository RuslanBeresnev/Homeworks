#include <stdio.h>

int main()
{
    int sums[29] = { 0 };
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                sums[i + j + k]++;
            }
        }
    }
    int countOfLuckyTickets = 0;
    for (int a = 0; a < 28; a++)
    {
        countOfLuckyTickets += sums[a] * sums[a];
    }
    printf("Count of lucky tickets: %d\n", countOfLuckyTickets);
}