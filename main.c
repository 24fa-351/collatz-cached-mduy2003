#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#include "cache.h"
#include "collatz.h"

#define POLICY_STRING_LENGTH 10

int main(int argc, char *argv[]) {
    unsigned long long int num_of_values;
    unsigned long long int min;
    unsigned long long int max;
    char cache_policy[POLICY_STRING_LENGTH];
    int cache_size;
    FILE *file = fopen("results.csv", "w+");

    sscanf(argv[1], "%llu", &num_of_values);
    sscanf(argv[2], "%llu", &min);
    sscanf(argv[3], "%llu", &max);
    sscanf(argv[4], "%s", cache_policy);
    sscanf(argv[5], "%d", &cache_size);

    srand(time(NULL));

    LRUCache *lruCache = create_lru_cache(cache_size);
    FIFOCache *fifoCache = create_fifo_cache(cache_size);

    int cache_hits = 0;
    int cache_accesses = 0;

    fprintf(file, "Number, Number of Steps\n");
    for (size_t current_value = 0; current_value < num_of_values; ++current_value) {
        unsigned long long int random_number = rand() % (max - min + 1) + min;
        unsigned long long int num_of_steps = collatz_conjecture_wrapper(random_number, lruCache, fifoCache, cache_policy, &cache_hits, &cache_accesses);
        fprintf(file, "%llu, %llu\n", random_number, num_of_steps);
    }
    fclose(file);

    double cache_hit_percentage = ((double)cache_hits / cache_accesses) * 100;
    printf("Cache Hit Percentage: %.2f%%, %d, %d\n", cache_hit_percentage, cache_accesses, cache_hits);

    free(lruCache->entries);
    free(lruCache);
    free(fifoCache->entries);
    free(fifoCache);

    return 0;
}