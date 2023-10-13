#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#pragma once

enum options
{
    ADD = 1, MOVE_CLIENTS, PRINT, QUIT
};

void add(queue** q_head);
void add_info(info * info_new);

void print(ring* r_head);
void print_ring(ring* r_cycle);

void move_clients(queue** q, ring** r_head);
