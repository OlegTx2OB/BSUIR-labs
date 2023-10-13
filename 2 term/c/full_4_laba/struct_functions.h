#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "classes.h"
#pragma once

enum options
{
    ADD = 1, PRINT, UPDATE, KILL, SORT, RETARDED, SEARCH, QUIT,
};

typedef struct Info
{
    struct Info *next;
    struct Info *prev;

    unsigned short int id;
    char full_name[64];
    short int age;
    short class;
    union
    {
        class1 cl1;
        class2 cl2;
        class3 cl3;
        class4 cl4;
    };
    char address[64];
    long long telephone;
} school;

void add (school** p);
void print(school* p);
void update(school** p_curr_pos);
void kill(school** p_curr_pos);
void sort(school** p_curr_pos);
void retarded(school** p_curr_pos);
void search(school** p_curr_pos);

float ave_mark(school** p_curr_pos);

