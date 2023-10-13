#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#define LOWER_BOUND -10000000
#define UPPER_BOUND 10000000
#pragma once

void create_root(node **root, int number, short* nodes_count);
void add_node(node* root, int number, short* nodes_count);

int enter_number_you_want();
int getint(int lower_bound, int upper_bound);

void delete_node_with_one_child(node** root, node* parent, node* child, node* deleted_node);

node *node_for_replacement(node *node_for_replace);
void free_old_tree(node** root);
int recursive_min_search(node *root, int* min_curr, int min_min, int after_right);