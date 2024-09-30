#ifndef CACHE_H
#define CACHE_H

typedef struct {
    unsigned long long int key;
    unsigned long long int value;
} CacheEntry;

typedef struct {
    CacheEntry *entries;
    int size;
    int capacity;
} LRUCache;

typedef struct {
    CacheEntry *entries;
    int size;
    int capacity;
    int front;
    int rear;
} FIFOCache;

LRUCache* create_lru_cache(int capacity);

FIFOCache* create_fifo_cache(int capacity);

unsigned long long int get_from_lru_cache(LRUCache *cache, unsigned long long int key, int *cache_hits, int *cache_accesses);

void put_in_lru_cache(LRUCache *cache, unsigned long long int key, unsigned long long int value);

unsigned long long int get_from_fifo_cache(FIFOCache *cache, unsigned long long int key, int *cache_hits, int *cache_accesses);

void put_in_fifo_cache(FIFOCache *cache, unsigned long long int key, unsigned long long int value);
#endif