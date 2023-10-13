#include "struct_functions.h"
#include "functions.h"

void add (school** p)
{
//id
    (*p)->id = time(NULL);
//full name
    printf(" * Enter full name of this child (to 63 symbols) (Please, write in correct form):");
    fgets((*p)->full_name, 64, stdin);
    rewind(stdin);
//age
    printf(" * Enter age of this child (from 0 to to 100):");
    (*p)->age = getshort(0, 100);

//choose class
    printf(" * Enter class of this child:");
    (*p)->class = getshort(1, 4);

//average marks for every subject
    short class_size = 0;
    if((*p)->class == CLASS1)class_size = sizeof((*p)->cl1);
    else if((*p)->class == CLASS2)class_size = sizeof((*p)->cl2);
    else if((*p)->class == CLASS3)class_size = sizeof((*p)->cl3);
    else if((*p)->class == CLASS4)class_size = sizeof((*p)->cl4);

    float* p_subject = (float*)(&(*p)->cl1 + 1);
    for(int i = 0; i < class_size/sizeof(float); i++)
    {
        printf("        Enter average mark for the %d-st subject of the %d-st class: ", i+1, (*p)->class);
        float average_mark = getfloat(0, 10);
        *(++p_subject - 4) = average_mark;
    }
//char* address
    printf(" * Enter address of this child (to 63 symbols):");
    rewind(stdin);
    fgets((*p)->address, 64, stdin);
    rewind(stdin);
//telephone
    printf(" * Enter telephone of this child:");
    (*p)->telephone = getlonglong(1, 9223372036854775807);
//logs
    writing_log_by_the_first_parameter(ADDED, (*p)->id, (*p)->full_name, (*p)->age, (*p)->class,
                                       ave_mark(p), (*p)->address, (*p)->telephone);
}
void print(school* p)
{
    printf("    |------------------------------\n"
           "    | 1. id: %d\n"
           "    | 2. full name: %s"
           "    | 3. age: %d\n"
           "    | 4. class: %hd\n"
           "    | 5. average mark: %.3f\n"
           "    | 6. address: %s"
           "    | 7. telephone: %lld\n"
           "    |------------------------------\n", p->id, p->full_name, p->age,
           p->class, ave_mark(&p), p->address, p->telephone);
}
void update(school** p_curr_pos)
{
    if ((*p_curr_pos) == NULL) printf(" * No one pupil added\n");
    else
    {
        printf(" * Enter id of this pupil: ");
        unsigned short int id = (unsigned short) getlonglong(0, 65535);
        move_to_last(p_curr_pos);

        short check_update = 0;
        if(id == (*p_curr_pos)->id)
        {
            add(p_curr_pos);
            check_update = 1;
        }
        while((*p_curr_pos)->prev != NULL && check_update == 0)
        {
            (*p_curr_pos) = (*p_curr_pos)->prev;
            if(id == (*p_curr_pos)->id)
            {
                add(p_curr_pos);
                check_update = 1;
            }
        }
        writing_log_by_the_first_parameter(UPDATED, (*p_curr_pos)->id, (*p_curr_pos)->full_name, (*p_curr_pos)->age, (*p_curr_pos)->class,
                                           ave_mark(p_curr_pos), (*p_curr_pos)->address, (*p_curr_pos)->telephone);
    }
}
void kill(school** p_curr_pos)
{
    short check_equal_id = 0;

//0 pupils
    if ((*p_curr_pos) == NULL) printf(" * No one pupil added\n");
    else
    {
        printf(" * Enter id of this pupil: ");
        unsigned short int id = (unsigned short) getlonglong(0, 65535);
        move_to_first(p_curr_pos);
//1 pupil
        if((*p_curr_pos)->next == NULL) check_and_kill_by_id_the_only(p_curr_pos, id, &check_equal_id);
//2+ pupils
        else
        {
            if(id == (*p_curr_pos)->id)
            {
                writing_log_by_the_first_parameter(REMOVED, (*p_curr_pos)->id, (*p_curr_pos)->full_name, (*p_curr_pos)->age, (*p_curr_pos)->class,
                                                   ave_mark(p_curr_pos), (*p_curr_pos)->address, (*p_curr_pos)->telephone);
                kill_the_first(p_curr_pos, &check_equal_id);
            }
            else
            {
                (*p_curr_pos) = (*p_curr_pos)->next;
                check_and_kill_by_id_the_mid(p_curr_pos, id, &check_equal_id);
            }

            if((check_equal_id == 0) && ((*p_curr_pos)->id == id))
            {
                writing_log_by_the_first_parameter(REMOVED, (*p_curr_pos)->id, (*p_curr_pos)->full_name, (*p_curr_pos)->age, (*p_curr_pos)->class,
                                                   ave_mark(p_curr_pos), (*p_curr_pos)->address, (*p_curr_pos)->telephone);
                kill_the_last(p_curr_pos, &check_equal_id);
            }
        }
    }

    if(check_equal_id == 1) printf(" * Pupil has been removed\n");
    else printf(" * Pupil is not found\n");
}
void sort(school** p_curr_pos)
{
    if ((*p_curr_pos) == NULL)
    {
        printf(" * No one pupil added\n");
    }
    else
    {
        move_to_first(p_curr_pos);

        if ((*p_curr_pos)->next == NULL) printf(" * Too few pupils. Please, try next time\n");
        else
        {
            for(int i = count_of_nodes(p_curr_pos) - 1; i >= 0; i--)
            {
                move_to_first(p_curr_pos);
                for(int node_num_of_p_curr_pos = 0; node_num_of_p_curr_pos < i ;node_num_of_p_curr_pos++)
                {
                    school *p_next = (*p_curr_pos)->next;
                    if (ave_mark(&p_next) > ave_mark(p_curr_pos))
                    {
                        if ((*p_curr_pos)->prev != NULL)
                        {
                            school *curr_prev = (*p_curr_pos)->prev;
                            curr_prev->next = p_next;
                            p_next->prev = curr_prev;
                        }
                        else p_next->prev = NULL;

                        if (p_next->next != NULL)
                        {
                            school *next_next = p_next->next;
                            next_next->prev = (*p_curr_pos);
                            (*p_curr_pos)->next = next_next;
                        }
                        else (*p_curr_pos)->next = NULL;

                        (*p_curr_pos)->prev = p_next;
                        p_next->next = (*p_curr_pos);

                    }
                    else (*p_curr_pos) = (*p_curr_pos)->next;
                }
            }
            printf(" * Pupils have been sorted\n");

        }
    }
}
void retarded(school** p_curr_pos)
{
    if ((*p_curr_pos) == NULL) printf(" * No one pupil added\n");
    else
    {
        printf("\n * Enter minimum of normal gpa :");
        float gpa = getfloat(0, 10);

        move_to_last(p_curr_pos);
        printf("\n * Retarded people:\n");

        if (gpa > ave_mark(p_curr_pos)) print(*p_curr_pos);
        while ((*p_curr_pos)->prev != NULL)
        {
            (*p_curr_pos) = (*p_curr_pos)->prev;
            if (gpa > ave_mark(p_curr_pos)) print(*p_curr_pos);
        }
    }
}
void search(school** p_curr_pos)
{
    if ((*p_curr_pos) == NULL) printf(" * No one pupil added\n");
    else
    {
        printf("\n * Enter class of pupils:");
        short class_number = getshort(1, 4);

        move_to_last(p_curr_pos);
        printf("\n * pupils with %hd class:\n", class_number);

        if (class_number == (*p_curr_pos)->class) print(*p_curr_pos);
        while ((*p_curr_pos)->prev != NULL)
        {
            (*p_curr_pos) = (*p_curr_pos)->prev;
            if (class_number == (*p_curr_pos)->class) print(*p_curr_pos);
        }
    }
}

float ave_mark(school** p_curr_pos)
{
    short class_size = 0;
    if((*p_curr_pos)->class == CLASS1)class_size = sizeof((*p_curr_pos)->cl1);
    else if((*p_curr_pos)->class == CLASS2)class_size = sizeof((*p_curr_pos)->cl2);
    else if((*p_curr_pos)->class == CLASS3)class_size = sizeof((*p_curr_pos)->cl3);
    else if((*p_curr_pos)->class == CLASS4)class_size = sizeof((*p_curr_pos)->cl4);
    float average_mark = 0;
    float* p_subject = (float*)(&(*p_curr_pos)->cl1 + 1);
    for(int i = 0; i < class_size/sizeof(float); i++)
    {
        average_mark += *(++p_subject - 4) / (class_size/sizeof(float));
    }
    return average_mark;
}
