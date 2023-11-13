#pragma once

typedef struct cache
{
    char* dns;
    int ip;

    struct cache* next;
    struct cache* prev;
}cache_struct;

typedef struct
{
    cache_struct* head;
    cache_struct* tail;
}list;

typedef struct hash
{
    cache_struct** node;

    struct hash* next;
    struct hash* prev;
}hash_struct;

typedef struct
{
    hash_struct* head;
    hash_struct* tail;
}array;