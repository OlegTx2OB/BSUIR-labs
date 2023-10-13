#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "structs.h"
#pragma once

#define KEY_SIZE 64
#define MAX_ARRAY_SIZE 1000
#define SIZEOF_BUF 64

char* key_generate();
array** create_hash_array();
list* create_cache_list();

short dns_is_not_exists_in_cache(list* cache_list, char* dns);

unsigned short hash_calculation(char* dns, char* key);
int getint(int lower_bound, int upper_bound);
char* enter_your_dns();