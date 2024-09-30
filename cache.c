#include <stdlib.h>

#include "cache.h"

LRUCache *create_lru_cache(int capacity)
{
    LRUCache *cache = (LRUCache *)malloc(sizeof(LRUCache));
    cache->entries = (CacheEntry *)malloc(sizeof(CacheEntry) * capacity);
    cache->size = 0;
    cache->capacity = capacity;
    return cache;
}

FIFOCache *create_fifo_cache(int capacity)
{
    FIFOCache *cache = (FIFOCache *)malloc(sizeof(FIFOCache));
    cache->entries = (CacheEntry *)malloc(sizeof(CacheEntry) * capacity);
    cache->size = 0;
    cache->capacity = capacity;
    cache->front = 0;
    cache->rear = -1;
    return cache;
}

unsigned long long int get_from_lru_cache(LRUCache *cache, unsigned long long int key, int *cache_hits, int *cache_accesses)
{
    (*cache_accesses)++;
    for (int ix = 0; ix < cache->size; ix++)
    {
        if (cache->entries[ix].key == key)   // If key is found, move it to the front of the cache
        {
            (*cache_hits)++; 
            CacheEntry entry = cache->entries[ix]; 
            for (int jx = ix; jx > 0; jx--) 
            {
                cache->entries[jx] = cache->entries[jx - 1]; 
            }
            cache->entries[0] = entry; 
            return entry.value;
        }
    }
    return 0; // Not found
}

void put_in_lru_cache(LRUCache *cache, unsigned long long int key, unsigned long long int value)
{
    if (cache->size < cache->capacity) // If cache is not full, add the new element to the front of the cache
    {
        for (int ix = cache->size; ix > 0; ix--)
        {
            cache->entries[ix] = cache->entries[ix - 1];
        }
        cache->entries[0].key = key; 
        cache->entries[0].value = value;
        cache->size++;
    }
    else  // If cache is full, remove the last element and shift all elements to the right
    {
        for (int ix = cache->capacity - 1; ix > 0; ix--)
        {
            cache->entries[ix] = cache->entries[ix - 1];
        }
        cache->entries[0].key = key; 
        cache->entries[0].value = value;
    }
}

unsigned long long int get_from_fifo_cache(FIFOCache *cache, unsigned long long int key, int *cache_hits, int *cache_accesses)
{
    (*cache_accesses)++;
    for (int ix = 0; ix < cache->size; ix++) // Searches for key and returns value if found
    {
        if (cache->entries[(cache->front + ix) % cache->capacity].key == key) 
        {
            (*cache_hits)++;
            return cache->entries[(cache->front + ix) % cache->capacity].value;
        }
    }
    return 0; // Not found
}

void put_in_fifo_cache(FIFOCache *cache, unsigned long long int key, unsigned long long int value) 
{
    cache->rear = (cache->rear + 1) % cache->capacity; // Add the new element to the rear of the cache
    cache->entries[cache->rear].key = key; 
    cache->entries[cache->rear].value = value; 
    if (cache->size < cache->capacity)
    {
        cache->size++;
    }
    else // If cache is full, remove the front element
    {
        cache->front = (cache->front + 1) % cache->capacity;
    }
}