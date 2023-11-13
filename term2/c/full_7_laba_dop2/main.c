#include "secondary_funcs.h"
#include "struct.h"
#include "main_funcs.h"

int main()
{
    node* root = NULL;
    load_data_from_dictionary(&root);
    while(1)translate(&root);
}
