#include "secondary_funcs.h"

void adding_node(list* cache_list, array** hash_array, char* dns, char* key);
void push_in_cache(list *cache_list, char* dns);
void push_in_hash(array** hash_array, list* cache_list, short hash);

void deleting_line_in_hash(array** hash_array, hash_struct* hash_node, short hash);
void deleting_line_in_cache(list* cache_list, cache_struct* cache_node);