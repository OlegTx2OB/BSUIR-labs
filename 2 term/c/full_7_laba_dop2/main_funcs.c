#include "main_funcs.h"

void load_data_from_dictionary(node** root)
{
    FILE* fp = fopen( "dictionary.txt", "a+");
    short count = 0;
    while(!feof(fp))
    {
        char* str = malloc(64);
        fscanf(fp, "%s", str);
        adding_node_to_tree(root, str);
        count++;
    }
    printf("Loaded %d pairs of words\n\n", count);
    fclose(fp);
}

void translate(node** root)
{
    printf("Enter word you want to translate:");
    char* eng_part = input_eng_word();
    finding_translation_to_word(root, eng_part);
}


