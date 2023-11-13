#include "secondary_funcs.h"

char* key_generate()
{
    srand(time(NULL));
    char* key = malloc(KEY_SIZE * sizeof(char));
    for(int i = 0; i < KEY_SIZE - 1; i++)key[i] = rand() % 94 + 32;
    key[KEY_SIZE - 1] = '\0';
    return key;
}
array** create_hash_array()
{
    array** hash_table = malloc(MAX_ARRAY_SIZE * sizeof(array*));
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        hash_table[i] = malloc(sizeof(array));
        hash_table[i]->head = hash_table[i]->tail = NULL;
    }
    return hash_table;
}

list* create_cache_list()
{
    list* cache_list = malloc(sizeof(list));
    cache_list->head = cache_list->tail = NULL;
    return cache_list;
}

short dns_is_not_exists_in_cache(list* cache_list, char* dns)
{
    cache_struct* node = cache_list->head;
    for(;cache_list->head && node != NULL;node = node->next)if(strcmp(dns, node->dns) == 0) return 0;
    return 1;
}
unsigned short hash_calculation(char* dns, char* key)
{
    unsigned long hash = 0;

    for(int i = 0; i < strlen(dns); i++)hash += dns[i] * i + key[i];
    return (hash % MAX_ARRAY_SIZE);
}

int getint(int lower_bound, int upper_bound)
{
    int d;
    while (!scanf("%d", &d) || d < lower_bound || d > upper_bound || getchar() != '\n')
    {
        printf("invalid input\n");
        rewind(stdin);
    }
    return d;
}

char* enter_your_dns()
{
    unsigned char* dns = malloc(SIZEOF_BUF * sizeof(char));
    printf("Enter your dns: ");
    fgets(dns, SIZEOF_BUF,stdin);
    return dns;
}