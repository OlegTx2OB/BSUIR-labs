#include "options_funcs.h"
#include "funcs.h"
#include "structs.h"
//todo сортировку доработать


int main()
{
    ring* r_head = NULL;
    queue* q_head = NULL;

    while(1)
    {
        printf("\t\t\t|-----------------------|------------------------------------|"
               "-------------------------------|---------|\n"
               "\t\t\t| 1. Add pupil to queue "
               "| 2. Move clients from queue to ring "
               "| 3. Print all pupils from ring "
               "| 4. Quit |\n"
               "\t\t\t|-----------------------|------------------------------------|"
               "-------------------------------|---------|\n");
        short choose = getshort(1, 4);
        if (choose == ADD)add(&q_head);
        else if (choose == MOVE_CLIENTS)move_clients(&q_head, &r_head);
        else if (choose == PRINT)print(r_head);
        else if (choose == QUIT) return 0;
    }
}
