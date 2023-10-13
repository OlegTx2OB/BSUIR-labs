#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_OVERFLOW 1488
#define STACK_UNDERFLOW 1337

#pragma once

typedef struct LIST
{
    char sign;
    int sign_status;
    struct LIST *next;
}stack;

void push(stack **head, char sign);
char pop(stack **head);
int peek_status(stack* head);

