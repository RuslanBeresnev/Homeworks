#pragma warning (disable: 4996 4710 5045)

#include "LoopList.h"

#include <stdio.h>
#include <locale.h>

int counting(const int warriorsCount, const int alternationLength)
{
    if (warriorsCount == 1)
    {
        return warriorsCount;
    }
    List* warriors = createLoopList();
    Position* currentWarrior = getFirstElement(warriors);
    for (int i = 0; i < warriorsCount; i++)
    {
        addAfter(warriors, currentWarrior);
        next(currentWarrior);
    }
    deletePosition(currentWarrior);
    currentWarrior = getFirstElement(warriors);
    for (int i = 0; i < alternationLength - 2; i++)
    {
        next(currentWarrior);
    }
    if (alternationLength == 1)
    {
        deletePosition(currentWarrior);
        currentWarrior = getLastElement(warriors);
    }
    while (!oneElementLoopList(warriors))
    {
        deleteAfter(warriors, currentWarrior);
        for (int i = 0; i < alternationLength - 1; i++)
        {
            next(currentWarrior);
        }
    }
    const int remainingWarriorNumber = getNumber(currentWarrior);
    deleteLoopList(warriors);
    deletePosition(currentWarrior);
    return remainingWarriorNumber;
}

bool standardTestPassed(void)
{
    return counting(5, 3) == 4;
}

bool killingEveryoneTestPassed(void)
{
    return counting(10, 1) == 10;
}

bool oneWarriorTestPassed(void)
{
    return counting(1, 1) == 1;
}

bool generalTestPassed(void)
{
    return standardTestPassed() && killingEveryoneTestPassed() && oneWarriorTestPassed();
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");
    printf("Введите количество воинов в кругу: ");
    int warriorsCount = 0;
    const int warriorsCountInput = scanf("%d", &warriorsCount);
    if (warriorsCountInput != 1 || warriorsCount <= 0)
    {
        printf("Вы ввели некорректные данные ...\n");
        return 1;
    }
    printf("Введите длину чередования: ");
    int alternationLength = 0;
    const int alternationLengthInput = scanf("%d", &alternationLength);
    if (alternationLengthInput != 1 || alternationLength <= 0)
    {
        printf("Вы ввели некорректные данные ...\n");
        return 1;
    }
    printf("Воин с номером %d должен будет совершить felony ...\n", counting(warriorsCount, alternationLength));
}