#include "additional_functions.h"

short input_strings_count()
{
    printf("Input count of strings you want to input (from 2 to 100):");
    short strings_count = getshort(2, 100);
    return strings_count;
}
char** input_strings_and_their_count(short strings_count)
{
    printf("Input your text with %hd strings:\n", strings_count);
    char** strings = malloc(sizeof(char*));
    for(int i = 0; i < strings_count; i++)
    {
        strings[i] = malloc(100 * sizeof(char));
        fgets(strings[i], 100, stdin);
    }
    return strings;
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