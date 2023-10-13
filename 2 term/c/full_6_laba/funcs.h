#include <stdio.h>
#include <stdlib.h>
#include "options_funcs.h"
#pragma once

short getshort(short lower_bound, short upper_bound);
long long getlonglong(short lower_bound, long long upper_bound);

void push_to_q(queue** q_head, queue** q_new);
info* pop_node_from_q_and_return_info(queue** q_head);
info* peek_node_form_q_and_return_info(queue** q_head);
void push_to_empty_r(ring** r_head, queue** q_head);
void push_to_1_element_r(ring** r_head, queue** q_head);
void push_to_full_r(queue** q_head, ring** r_next, ring** r_curr);
void clear_screen_after_enter();