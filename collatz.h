#ifndef COLLATZ_H
#define COLLATZ_H

#include "cache.h"

unsigned long long int collatz_conjecture(unsigned long long int value);

unsigned long long int collatz_conjecture_wrapper(unsigned long long int value, LRUCache *lruCache, FIFOCache *fifoCache,
                                                  const char *cache_policy, int *cache_hits, int *cache_accesses);
#endif