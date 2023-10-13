#include "main_funcs.h"
#include "struct.h"
#include "secondary_funcs.h"

int main()
{
    node* root = NULL;
    short nodes_count = 0;
    while(1)
    {
        printf("1.NEW   2.NODES_COUNT   3.PRINT   4.SEARCH   5.UPDATE   6.TRANSFORMATION   7.REMOVE   8.QUIT : ");
        short choose = getint(NEW, QUIT);

        if(choose == NEW) new(&root, enter_number_you_want(), &nodes_count);
        else if (choose == NODES_COUNT) printf("Nodes count is %d\n", nodes_count);
        else if (choose == PRINT) print(root);
        else if (choose == SEARCH)
        {
            if(search(root, enter_number_you_want()) == NULL) printf("Node NOT founded\n");
            else printf("Node founded\n");
        }
        else if (choose == UPDATE)
        {
            delete(&root, enter_number_you_want(), &nodes_count);
            new(&root, enter_number_you_want(), &nodes_count);
        }
        else if (choose == TRANSFORMATION)
        {
            int i = 1;
            for(;powf(2, i) - 1 < nodes_count; i++);
            node* new_root = NULL;
            if(powf(2, i) - 1 == nodes_count)
            {
                transformation(&root, &new_root, nodes_count, LOWER_BOUND - 1, LOWER_BOUND - 1);
                free_old_tree(&root);
                root = new_root;
            }
            else printf("Your binary tree can't be transformed to a FULL binary tree\n");
        }
        else if (choose == REMOVE) delete(&root, enter_number_you_want(), &nodes_count);
        else if (choose == QUIT)return 0;
    }
}
