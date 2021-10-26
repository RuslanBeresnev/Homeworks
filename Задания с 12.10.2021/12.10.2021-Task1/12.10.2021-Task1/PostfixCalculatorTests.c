#include "PostfixCalculatorTests.h"

bool standardSequenceTestPassed(void)
{
    return postfixCalculator("5 5 3 2 * + - 3 /\n") == -2;
}

bool emptySequenceTestPassed(void)
{
    return postfixCalculator("\n") == 0;
}

bool generalTestPassed(void)
{
    return standardSequenceTestPassed() && emptySequenceTestPassed();
}