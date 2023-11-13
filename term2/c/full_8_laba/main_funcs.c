#include "main_funcs.h"
#include "funcs_with_nodes.h"
void print_cache(list* cache_list)
{
    cache_struct* node = cache_list->head;
    for(; node; node = node->next)
    {
        printf("%s%d\n\n", node->dns, node->ip);
    }
}

void load_n_strings(list* cache_list, array** hash_array, char* key)
{
    FILE *fp = fopen("db.txt", "r");
    if(fp == NULL)
    {
        printf("DB is not founded\n");
        exit(1);
    }

    printf("enter number of strings you want to load:");
    int n = getint(1, 20);
    for(int i = 0; i < n && n < 25; i++)
    {
        unsigned char* dns = malloc(SIZEOF_BUF * sizeof(char));
        fgets(dns, SIZEOF_BUF, fp);
        adding_node(cache_list, hash_array, dns, key);
    }
    fclose(fp);
}

void add(list* cache_list, array** hash_array, char* key)
{
    unsigned char* dns = enter_your_dns();
    adding_node(cache_list, hash_array, dns, key);
}

void remove_by_dns(list* cache_list, array** hash_array, char* key)
{
    unsigned char* dns = enter_your_dns();
    short hash = hash_calculation(dns, key);

    if(hash_array[hash]->head == NULL) printf("Node is not founded in hash_array\n");
    else
    {
        hash_struct* hash_node = hash_array[hash]->head;
        cache_struct* cache_node = malloc(sizeof(cache_struct));
        int node_has_been_founded = 0;
        for (;!node_has_been_founded && hash_node; hash_node = hash_node->next)
        {
            cache_node = *hash_node->node;
            if (strcmp(cache_node->dns, dns) == 0) node_has_been_founded = 1;
        }
        if(node_has_been_founded)
        {
            deleting_line_in_hash(hash_array, hash_node, hash);
            deleting_line_in_cache(cache_list, cache_node);
            printf("Node has been deleted\n");
        }
        else printf("Node is not founded in hash_array\n");
    }
}

void find_ip_by_dns(list* cache_list, array** hash_array, char* key)
{
    unsigned char* dns = enter_your_dns();
    short hash = hash_calculation(dns, key);

    hash_struct* hash_node = hash_array[hash]->head;
    int equal_dns_is_exists_in_hash = 0;
    for(; !equal_dns_is_exists_in_hash && hash_node; hash_node = hash_node->next)
    {
        cache_struct* node = *hash_node->node;
        if (strcmp(dns, node->dns) == 0)
        {
            printf("Your IP is %d\n", node->ip);
            equal_dns_is_exists_in_hash = 1;
        }
    }
    if(!equal_dns_is_exists_in_hash) printf("equal dns isn't founded in hash_struct\n");
}