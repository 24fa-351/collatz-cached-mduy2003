#include <string.h>

#include "collatz.h"
#include "cache.h"

unsigned long long int collatz_conjecture(unsigned long long int value)
{
    unsigned long long int steps = 0;
    while (value != 1 && value > 0)
    {
        if (value % 2 == 0)
        {
            value = value / 2;
        }
        else
        {
            value = 3 * value + 1;
        }
        steps++;
    }
    return steps;
}

unsigned long long int collatz_conjecture_wrapper(unsigned long long int value, LRUCache *lruCache, FIFOCache *fifoCache,
                                                  const char *cache_policy, int *cache_hits, int *cache_accesses)
{
    unsigned long long int steps = 0;
    if (strcmp(cache_policy, "LRU") == 0)
    {
        steps = get_from_lru_cache(lruCache, value, cache_hits, cache_accesses);
        if (steps == 0)
        {
            steps = collatz_conjecture(value);
            put_in_lru_cache(lruCache, value, steps);
        }
    }
    else if (strcmp(cache_policy, "FIFO") == 0)
    {
        steps = get_from_fifo_cache(fifoCache, value, cache_hits, cache_accesses);
        if (steps == 0)
        {
            steps = collatz_conjecture(value);
            put_in_fifo_cache(fifoCache, value, steps);
        }
    }
    else
    {
        steps = collatz_conjecture(value);
    }
    return steps;
}