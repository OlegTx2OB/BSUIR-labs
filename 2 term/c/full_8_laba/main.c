#include "main_funcs.h"
#include "structs.h"
#include "secondary_funcs.h"
//todo удаление не производится, если загружено больше 1 строки (не находится)
int main()
{
    char* key = key_generate();
    list* cache_list = create_cache_list();
    array** hash_array = create_hash_array();

    while(1)
    {
        print_cache( cache_list);

        printf("1.LOAD n STRINGS   2.ADD   3.REMOVE BY DNS   4.FIND IP BY DNS   5.EXIT : ");
        short choose = getint(LOAD_n_STRINGS, EXIT);

        if(choose == LOAD_n_STRINGS) load_n_strings(cache_list, hash_array, key);
        else if (choose == ADD) add(cache_list, hash_array, key);
        else if (choose == REMOVE_BY_DNS) remove_by_dns(cache_list, hash_array, key);
        else if (choose == FIND_IP_BY_DNS) find_ip_by_dns(cache_list, hash_array, key);
        else return 0;
    }
}
