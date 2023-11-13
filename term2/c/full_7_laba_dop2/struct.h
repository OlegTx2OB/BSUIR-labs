#pragma once
typedef struct tree
{
    struct tree* left;
    struct tree* right;
    char info[64];
}
node;