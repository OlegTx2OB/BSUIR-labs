#include <stdio.h>
#include <stdlib.h>
#include "struct_functions.h"
#pragma once

enum log_parameter
{
    ADDED = 1, REMOVED, UPDATED,
};
void move_to_first(school **p_curr_pos);
void move_to_last(school **p_curr_pos);
int count_of_nodes(school **p_curr_pos);

void check_and_kill_by_id_the_only(school** p_curr_pos, unsigned short id, short* check_equal_id);
void kill_the_first(school** p_curr_pos, short* check_equal_id);
void check_and_kill_by_id_the_mid(school** p_curr_pos, unsigned short id, short* check_equal_id);
void kill_the_last(school** p_curr_pos, short* check_equal_id);

short getshort(short lower_bound, short upper_bound);
float getfloat(short lower_bound, short upper_bound);
long long getlonglong(short lower_bound, long long upper_bound);

void writing_log_by_the_first_parameter(short parameter, unsigned short id, char* full_name, short age, short class,
                                        float av_mark, char* address, long long telephone);