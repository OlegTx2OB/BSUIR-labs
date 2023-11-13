#include "struct_functions.h"
#include "functions.h"
int main()
{
    school* p_curr_pos = NULL;
    while(1)
    {
        printf("|----------------------------------|\n"
               "| 1. Add pupil                     |\n"
               "| 2. Print all pupils              |\n"
               "| 3. Update information about pupil|\n"
               "| 4. Remove pupil                  |\n"
               "| 5. Sort pupils by ave mark       |\n"
               "| 6. Find retarded pupil(-s)       |\n"
               "| 7. Search pupils by class        |\n"
               "| 8. Quit                          |\n"
               "|----------------------------------|\n");
        short choose = getshort(1, 8);
        if (choose == ADD)
        {
            if(p_curr_pos == NULL)
            {
                p_curr_pos = malloc(sizeof(school));
                add(&p_curr_pos);
                p_curr_pos->prev = NULL;
                p_curr_pos->next = NULL;
            }
            else
            {
                move_to_last(&p_curr_pos);
                school* p_new = malloc(sizeof(school));
                add(&p_new);
                p_new->next = NULL;
                p_curr_pos->next = p_new;
                p_new->prev = p_curr_pos;
            }

            printf("\n * New pupil has been added * \n");
        }
        else if (choose == PRINT)
        {
            if(p_curr_pos == NULL) printf(" * List of pupils is clear \n");
            else
            {
                move_to_last(&p_curr_pos);

                print(p_curr_pos);
                while(p_curr_pos->prev != NULL)
                {
                    p_curr_pos = p_curr_pos->prev;
                    print(p_curr_pos);
                }
            }
        }
        else if (choose == UPDATE) update(&p_curr_pos);
        else if (choose == KILL) kill(&p_curr_pos);
        else if (choose == SORT) sort(&p_curr_pos);
        else if (choose == RETARDED) retarded(&p_curr_pos);
        else if (choose == SEARCH) search(&p_curr_pos);
        else if (choose == QUIT) return 0;
    }
}
