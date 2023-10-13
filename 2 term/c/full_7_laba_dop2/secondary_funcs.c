#include "secondary_funcs.h"

char* input_eng_word()
{
    char* str = malloc(64 * sizeof(char));
    fgets(str, 64, stdin);
    return str;
}

void adding_node_to_tree(node** root, char* str)
{
    if((*root) == NULL)
    {
        (*root) = malloc(sizeof(node));
        strcpy((*root)->info, str);

        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if(strcmp(str, (*root)->info) > 0) adding_node_to_tree(&(*root)->right, str);
    else if(strcmp(str, (*root)->info) < 0) adding_node_to_tree(&(*root)->left, str);
}
char* eng_part_of(char* full_string)
{
    char* first_part = calloc(64 * sizeof(char), 1);
    int i = 0;
    for(; full_string[i] != '='; i++)
    {
        first_part[i] = full_string[i];
    }
    first_part[i] = '\n';
    first_part[i + 1] = '\0';
    return first_part;
}
char* rus_part_of(char* full_string)
{
    char* second_part = malloc(64 * sizeof(char));
    short i = 0;
    for(; full_string[i - 1] != '='; i++);
    short j = 0;
    for(;full_string[i] != '\n' && full_string[i] != '\0'; j++, i++)
        second_part[j] = full_string[i];
    second_part[j] = '\n';
    second_part[j + 1] = '\0';
    return second_part;
}
void finding_translation_to_word(node** root, char* str)
{
    if((*root) == NULL) printf("There is no %s", str);
    else if(strcmp(str, eng_part_of((*root)->info)) == 0)printf("Translation is %s\n", rus_part_of((*root)->info));
    else if(strcmp(str, eng_part_of((*root)->info)) > 0) finding_translation_to_word(&(*root)->right, str);
    else if(strcmp(str, eng_part_of((*root)->info)) < 0) finding_translation_to_word(&(*root)->left, str);
}