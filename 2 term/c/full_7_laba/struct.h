#pragma once
typedef struct tree
{
    struct tree* p;
    struct tree* l;
    struct tree* r;

    int number;
}
node;