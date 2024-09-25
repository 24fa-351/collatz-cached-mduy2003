#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long int collatz_conjecture(unsigned long long int value)
{
    unsigned long long int steps = 0;
    while (value != 1 && value > 0)
    {
        steps++;
        if (value % 2 == 0)
        {
            value /= 2;
        }
        else
        {   
            value = 3 * value + 1;
        }
    }
    return steps;
}

int main(int argc, char *argv[])
{
    unsigned long long int num_of_values;
    unsigned long long int min;
    unsigned long long int max;
    FILE *file = fopen("results.csv", "w+");

    unsigned long long int nuv_input = sscanf(argv[1], "%llu", &num_of_values);
    unsigned long long int min_input = sscanf(argv[2], "%llu", &min);
    unsigned long long int max_input = sscanf(argv[3], "%llu", &max);

    srand(time(NULL));

    fprintf(file, "Number, Number of Steps\n");
    for (size_t ix = 0; ix < num_of_values; ++ix)
    {
        unsigned long long int random_number = rand() % (max - min + 1) + min;
        unsigned long long int result = collatz_conjecture(random_number);
        fprintf(file, "%llu, %llu\n", random_number, result);
    }
    fclose(file);

    return 0;
}