#include "functions.h"
void move_to_first(school** p_curr_pos)
{
    while((*p_curr_pos)->prev != NULL) (*p_curr_pos) = (*p_curr_pos)->prev;
}
void move_to_last(school** p_curr_pos)
{
    while((*p_curr_pos)->next != NULL) (*p_curr_pos) = (*p_curr_pos)->next;
}
void check_and_kill_by_id_the_only(school** p_curr_pos, unsigned short id, short* check_equal_id)
{
    if(id == (*p_curr_pos)->id)
    {
        writing_log_by_the_first_parameter(REMOVED, (*p_curr_pos)->id, (*p_curr_pos)->full_name, (*p_curr_pos)->age, (*p_curr_pos)->class,
                                           ave_mark(p_curr_pos), (*p_curr_pos)->address, (*p_curr_pos)->telephone);
        free(*p_curr_pos);
        (*p_curr_pos) = NULL;
        (*check_equal_id) = 1;
    }
}

void kill_the_first(school** p_curr_pos, short* check_equal_id)
{
    school* p_next = (*p_curr_pos)->next;
    free(*p_curr_pos);
    (*p_curr_pos) = p_next;
    (*p_curr_pos)->prev = NULL;
    (*check_equal_id) = 1;
}
int count_of_nodes(school **p_curr_pos)
{

    move_to_first(p_curr_pos);
    int count = 1;
    for(; (*p_curr_pos)->next != NULL; (*p_curr_pos) = (*p_curr_pos)->next, count++);
    return count;
}

void check_and_kill_by_id_the_mid(school** p_curr_pos, unsigned short id, short* check_equal_id)
{
    while((*p_curr_pos)->next != NULL)
    {
        if(id == (*p_curr_pos)->id)
        {
            school* p_prev = (*p_curr_pos)->prev;
            school* p_next = (*p_curr_pos)->next;
            writing_log_by_the_first_parameter(REMOVED, (*p_curr_pos)->id, (*p_curr_pos)->full_name, (*p_curr_pos)->age, (*p_curr_pos)->class,
                                               ave_mark(p_curr_pos), (*p_curr_pos)->address, (*p_curr_pos)->telephone);
            free(*p_curr_pos);
            p_prev->next = p_next;
            p_next->prev = p_prev;
            *p_curr_pos = p_prev;

            (*check_equal_id) = 1;
        }
        (*p_curr_pos) = (*p_curr_pos)->next;
    }
}
void kill_the_last(school** p_curr_pos, short* check_equal_id)
{
    school* p_prev = (*p_curr_pos)->prev;
    free(*p_curr_pos);
    (*p_curr_pos) = p_prev;
    (*p_curr_pos)->next = NULL;
    (*check_equal_id) = 1;
}

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
float getfloat(short lower_bound, short upper_bound)
{
    float f;
    while (!scanf("%f", &f) || f < lower_bound || f > upper_bound || getchar() != '\n')
    {
        printf("invalid input\n");
        rewind(stdin);
    }
    return f;
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

void writing_log_by_the_first_parameter(short parameter, unsigned short id, char* full_name, short age, short class,
                                        float av_mark, char* address, long long telephone)
{
    FILE* fp = fopen("data.log", "a+");
    char *first_word = NULL;
    if(parameter == ADDED) first_word = "added";
    else if(parameter == REMOVED)first_word = "removed";
    else if(parameter == UPDATED)first_word = "updated to";

    fseek(fp, 0,SEEK_END);
    fprintf(fp, "%s id.%hd full_name.%s age.%hd class.%hd av_mark.%.3f address.%s telephone.%lld\n\n",
            first_word, id, full_name, age, class, av_mark, address, telephone);
    fclose(fp);
}