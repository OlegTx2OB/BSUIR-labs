#include "stack.h"

void push(stack **head, char sign)
{
    stack *sample = malloc(sizeof(stack));
    if (sample == NULL) exit(STACK_OVERFLOW);

    sample->next = (*head);
    sample->sign = sign;
    sample->sign_status = 0;

    (*head) = sample;
}
char pop(stack **head)
{
    if (*head == NULL) exit(STACK_UNDERFLOW);
    stack* sample = *head;
    *head = (*head)->next;
     char sign = sample->sign;
    free(sample);
    return sign;
}
int peek_status(stack* head)
{
    if (head == NULL) exit(STACK_UNDERFLOW);
    return head->sign_status;
}