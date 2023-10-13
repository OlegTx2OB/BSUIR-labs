#pragma once

typedef struct Info
{
    char full_name[64];
    long long cost;
    struct tm *date;
}info;

typedef struct Queue
{
    struct Queue *next;
    struct Info *info;
}queue;

typedef struct Ring
{
    struct Ring *next;
    struct Ring *prev;
    struct Info *info;
}ring;