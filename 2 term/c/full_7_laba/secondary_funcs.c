#include "secondary_funcs.h"

void create_root(node **root, int number, short* nodes_count)
{
    (*root) = malloc(sizeof(node));
    (*root)->number = number;
    (*root)->p = (*root)->l = (*root)->r = NULL;
    printf("New %hd-st node has been added\n", ++(*nodes_count));
}
void add_node(node* root, int number, short* nodes_count)
{
    node* added_node = root;
    node* parent_of_added_node = root;

    short equality_of_nodes = 0;
    while(added_node != NULL)
    {
        parent_of_added_node = added_node;
        if(number > added_node->number) added_node = added_node->r;
        else if (number < added_node->number) added_node = added_node->l;
        else
        {
            equality_of_nodes = 1;
            break;
        }
    }

    if(equality_of_nodes == 0)
    {
        added_node = malloc(sizeof(node));
        added_node->number = number;
        added_node->l = NULL, added_node->r = NULL, added_node->p = parent_of_added_node;
        if(number > parent_of_added_node->number) parent_of_added_node->r = added_node;
        else parent_of_added_node->l = added_node;

        printf("New %hd-st node has been added\n", ++(*nodes_count));
    }
    else printf("Node with %hd number already exists\n", number);
}
int enter_number_you_want()
{
    printf("Enter number you want:");
    int number = getint(LOWER_BOUND, UPPER_BOUND);
    return number;
}
int getint(int lower_bound, int upper_bound)
{
    int d;
    while (!scanf("%d", &d) || d < lower_bound || d > upper_bound || getchar() != '\n')
    {
        printf("invalid input\n");
        rewind(stdin);
    }
    return d;
}

void delete_node_with_one_child(node** root, node* parent, node* child, node* deleted_node)
{
    if (parent && deleted_node->number > parent->number) parent->r = child;
    else if (parent) parent->l = child;
    else (*root) = child;
    free(deleted_node);
    child->p = parent;
}

node *node_for_replacement(node *node_for_replace)
{
    while(node_for_replace->l != NULL) node_for_replace = node_for_replace->l;
    return node_for_replace;
}
void free_old_tree(node** root)
{
    if (*root)
    {
        free_old_tree(&(*root)->l);
        free_old_tree(&(*root)->r);

        free(*root);
        (*root) = NULL;
    }
}
int recursive_min_search(node *root, int* min_curr, int min_min, int after_right)
{
    if (root)
    {
        if((root->number < (*min_curr)) && (min_min < root->number) && (after_right < root->number)) (*min_curr) = root->number;
        recursive_min_search(root->l, min_curr, min_min, after_right);
        recursive_min_search(root->r, min_curr, min_min, after_right);
    }
    return (*min_curr);
}