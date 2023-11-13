#include "structs.h"
#include "secondary_funcs.h"
#pragma once

enum options
{
    LOAD_n_STRINGS = 1, ADD, REMOVE_BY_DNS, FIND_IP_BY_DNS, EXIT
};
void print_cache(list* cache_list);

void load_n_strings(list* cache_list, array** hash_array, char* key);
void add(list* cache_list, array** hash_array, char* key);
void remove_by_dns(list* cache_list, array** hash_array, char* key);
void find_ip_by_dns(list* cache_list, array** hash_array, char* key);