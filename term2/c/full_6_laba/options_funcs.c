#include "options_funcs.h"
#include "funcs.h"

void add(queue** q_head)
{
    info *info_new = malloc(sizeof(info));
    add_info(info_new);
    queue* q_new = malloc(sizeof(queue));
    q_new->info = info_new;
    push_to_q(q_head, &q_new);
}

void add_info(info * info_new)
{
//full_name
    printf(" * Enter full name of this child (to 64 symbols):");
    fgets(info_new->full_name, 64, stdin);
    rewind(stdin);
//cost
    printf(" * Enter cost: ");
    info_new->cost = getlonglong(1, 9223372036854775807);
//date
    time_t my_time = time(NULL);
    info_new->date = localtime(&my_time);
    clear_screen_after_enter();
}

void print(ring* r_head)
{
    if (r_head == NULL)
    {
        printf(" * There is no added clients\n");
        clear_screen_after_enter();
    }
    else
    {
        ring* r_cycle = r_head;
        do
        {
            print_ring(r_cycle);
            r_cycle = r_cycle->next;
        }
        while(r_cycle != r_head);
        clear_screen_after_enter();
    }
}
void print_ring(ring* r_cycle)
{
    printf("    |------------------------------\n"
           "    | 1. full name: %s"
           "    | 2. cost: %lld\n"
           "    | 3. date: %d.%d.%d\n"
           "    | 4. time: %d:%d:%d\n"
           "    |------------------------------\n", r_cycle->info->full_name, r_cycle->info->cost,
           r_cycle->info->date->tm_mday, r_cycle->info->date->tm_mon + 1, r_cycle->info->date->tm_year + 1900,
           r_cycle->info->date->tm_hour, r_cycle->info->date->tm_min, r_cycle->info->date->tm_sec);
}

void move_clients(queue** q_head, ring** r_head)
{
    if ((*q_head) == NULL)
    {
        printf(" * Sorry, queue is empty\n");
        clear_screen_after_enter();
    }
    else
    {
        while ((*q_head) != NULL)
        {
//if head is clear
            if ((*r_head) == NULL) push_to_empty_r(r_head, q_head);
//if head is 1 element
            else if ((*r_head)->next == (*r_head))push_to_1_element_r(r_head, q_head);
//2+
            else
            {
                ring* r_curr = (*r_head);
                ring* r_next = (*r_head)->next;
                while(1)
                {
                    if(r_next->info->cost >= r_curr->info->cost)
                    {
                        if(peek_node_form_q_and_return_info(q_head)->cost <= r_next->info->cost
                           && peek_node_form_q_and_return_info(q_head)->cost >= r_curr->info->cost)
                        {
                            push_to_full_r(q_head, &r_next, &r_curr);
                            break;
                        }
                        r_curr = r_curr->next;
                        r_next = r_next->next;
                    }
                    else
                    {
                        if(peek_node_form_q_and_return_info(q_head)->cost <= r_next->info->cost
                           || peek_node_form_q_and_return_info(q_head)->cost >= r_curr->info->cost)
                        {
                            push_to_full_r(q_head, &r_next, &r_curr);
                            break;
                        }
                        r_curr = r_curr->next;
                        r_next = r_next->next;
                    }
                }
            }
        }
    }
    printf(" * Moving has been successful\n");
    clear_screen_after_enter();
}