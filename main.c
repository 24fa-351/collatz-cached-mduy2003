#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "collatz.h"

int main(int argc, char *argv[])
{
    unsigned long long int num_of_values;
    unsigned long long int min;
    unsigned long long int max;
    char *cache_policy;
    int cache_size;
    FILE *file = fopen("results.csv", "w+");

    sscanf(argv[1], "%llu", &num_of_values);
    sscanf(argv[2], "%llu", &min);
    sscanf(argv[3], "%llu", &max);
    sscanf(argv[4], "%s", cache_policy);
    sscanf(argv[5], "%d", &cache_size);

    srand(time(NULL));

    fprintf(file, "Number, Number of Steps\n");
    for (size_t current_value = 0; current_value < num_of_values; ++current_value)
    {
        unsigned long long int random_number = rand() % (max - min + 1) + min;
        unsigned long long int num_of_steps = collatz_conjecture_wrapper(random_number);
        fprintf(file, "%llu, %llu\n", random_number, num_of_steps);
    }
    fclose(file);

    return 0;
}