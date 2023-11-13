#include "funcs.h"
#include <windows.h>

short getshort(short lower_bound, short upper_bound)
{
    short hd;
    while (!scanf("%hd", &hd) || hd < lower_bound || hd > upper_bound || getchar() != '\n')
    {
        printf("invalid input\n");
        rewind(stdin);
    }
    return hd;
}
long long getlonglong(short lower_bound, long long upper_bound)
{
    long long lld;
    while (!scanf("%lld", &lld) || lld < lower_bound || lld > upper_bound || getchar() != '\n')
    {
        printf("invalid input\n");
        rewind(stdin);
    }
    return lld;
}

void push_to_q(queue** q_head, queue** q_new)
{
    if(q_head == NULL)
    {
        (*q_head) = malloc(sizeof(queue));
        (*q_head) = (*q_new);
        (*q_head)->next = NULL;
    }
    else
    {
        (*q_new)->next = (*q_head);
        (*q_head) = (*q_new);
    }
}
info* pop_node_from_q_and_return_info(queue** q_head)
{
    queue* q_popped = (*q_head);
    for(;q_popped->next != NULL; q_popped = q_popped->next);

    queue* q_penult = (*q_head);
    for(;q_penult->next != q_popped && q_penult != q_popped; q_penult = q_penult->next);

    q_penult->next = NULL;
    info* info = q_popped->info;
    if(q_popped == (*q_head))
    {
        free((*q_head));
        (*q_head) = NULL;
    }
    else free(q_popped);

    return info;
}
info* peek_node_form_q_and_return_info(queue** q_head)
{
    queue* q_popped = (*q_head);
    for(; q_popped->next != NULL; q_popped = q_popped->next);
    info* info = q_popped->info;
    return info;
}
void push_to_empty_r(ring** r_head, queue** q_head)
{
    (*r_head) = malloc(sizeof(ring));
    (*r_head)->info = pop_node_from_q_and_return_info(q_head);
    (*r_head)->next = (*r_head);
    (*r_head)->prev = (*r_head);
}
void push_to_1_element_r(ring** r_head, queue** q_head)
{
    ring* r_new = malloc(sizeof(ring));
    r_new->info = pop_node_from_q_and_return_info(q_head);

    (*r_head)->next = r_new;
    (*r_head)->prev = r_new;
    r_new->next = (*r_head);
    r_new->prev = (*r_head);
}
void push_to_full_r(queue** q_head, ring** r_next, ring** r_curr)
{
    ring* r_new = malloc(sizeof(ring));
    r_new->info = pop_node_from_q_and_return_info(q_head);

    r_new->next = (*r_next);
    r_new->prev = (*r_curr);
    (*r_curr)->next = r_new;
    (*r_next)->prev = r_new;
}
void clear_screen_after_enter()
{
    printf(" Press ENTER to CONTINUE");
    getchar();
    rewind(stdin);
    system("cls");
}