#include "funcs_with_nodes.h"

void adding_node(list* cache_list, array** hash_array, char* dns, char* key)
{
    if(dns_is_not_exists_in_cache(cache_list, dns))
    {
        push_in_cache(cache_list, dns);
        short hash = hash_calculation(dns, key);
        push_in_hash(hash_array, cache_list, hash);
    }
    else printf("line has been added before\n");
}
void push_in_cache(list* cache_list, char* dns)
{
    srand(time(NULL));
    cache_struct* cache_node = malloc(sizeof(cache_struct));
    cache_node->dns = dns;
    cache_node->ip = time(NULL);
    cache_node->next = cache_node->prev = NULL;

    if(cache_list->tail == NULL) cache_list->tail = cache_node;
    else
    {
        cache_node->next = cache_list->head;
        cache_list->head->prev = cache_node;
    }
    cache_list->head = cache_node;
}

void push_in_hash(array** hash_array, list* cache_list, short hash)
{
    hash_struct* hash_node = malloc(sizeof(hash_struct));
    hash_node->node = &cache_list->head;
    hash_node->next = hash_node->prev = NULL;

    if(hash_array[hash]->tail == NULL) hash_array[hash]->tail = hash_node;
    else
    {
        hash_node->next = hash_array[hash]->head;
        hash_array[hash]->head->prev = hash_node;
    }
    hash_array[hash]->head = hash_node;
}

void deleting_line_in_hash(array** hash_array, hash_struct* hash_node, short hash)
{
//1
    if(hash_array[hash]->head == hash_array[hash]->tail) hash_array[hash]->head = hash_array[hash]->tail = NULL;
//head
    else if(hash_array[hash]->head == hash_node)
    {
        hash_struct* next_node = hash_array[hash]->head = hash_node->next;
        next_node->prev = NULL;
    }
//tail
    else if(hash_array[hash]->tail == hash_node)
    {
        hash_struct* prev_node = hash_array[hash]->tail = hash_node->prev;
        prev_node->next = NULL;
    }
//centre
    else
    {
        hash_struct* next_node = hash_node->next;
        hash_struct* prev_node = hash_node->prev;
        next_node->prev = prev_node;
        prev_node->next = next_node;
    }
    free(hash_node);
}
void deleting_line_in_cache(list* cache_list, cache_struct* cache_node)
{
//1
    if(cache_list->head == cache_list->tail) cache_list->head = cache_list->tail = NULL;
//head
    else if(cache_list->head == cache_node)
    {
        cache_struct* next_node = cache_list->head = cache_node->next;
        next_node->prev = NULL;
    }
//tail
    else if(cache_list->tail == cache_node)
    {
        cache_struct* prev_node = cache_list->tail = cache_node->prev;
        prev_node->next = NULL;
    }
//centre
    else
    {
        cache_struct* next_node = cache_node->next;
        cache_struct* prev_node = cache_node->prev;
        next_node->prev = prev_node;
        prev_node->next = next_node;
    }
    free(cache_node);
}