#include "collatz.h"

unsigned long long int collatz_conjecture(unsigned long long int value)
{
    if (value % 2 == 0)
    {
        value /= 2;
    }
    else
    {
        value = 3 * value + 1;
    }
    return value;
}

unsigned long long int collatz_conjecture_wrapper(unsigned long long int value)
{
    unsigned long long int steps = 0;
    while (value != 1 && value > 0)
    {
        steps++;
        value = collatz_conjecture(value);
    }
    return steps;
}