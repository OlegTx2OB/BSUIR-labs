#include "struct.h"
#include "secondary_funcs.h"
#pragma once

enum options
{
    NEW = 1, NODES_COUNT, PRINT, SEARCH, UPDATE, TRANSFORMATION, REMOVE, QUIT
};
void new(node** root, int number, short* nodes_count);
void print(node* root);
node* search(node* root, int number);
void delete(node **root, int number, short* nodes_count);
void transformation(node **root, node** new_root, int interval, int min_min, int after_right);
