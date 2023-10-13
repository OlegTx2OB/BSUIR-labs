#include "additional_functions.h"

void findMaxSubstring(char** strings, int strings_count, char* max_founded_substring)
{
    int max_length = 0;
    int first_string_length = (int)strlen(strings[0]);
    for (int i = 0; i < first_string_length; i++)
    {
        for (int j = i + 1; j <= first_string_length; j++)
        {
            char current_substring[120];
            strncpy(current_substring, &strings[0][i], j - i);
            current_substring[j - i] = '\0';
            int check_found_In_all = 1;

            for (int k = 1; k < strings_count; k++)
            {
                if (strstr(strings[k], current_substring) == NULL)
                {
                    check_found_In_all = 0;
                    break;
                }
            }
            if (check_found_In_all && (j - i) > max_length)
            {
                max_length = j - i;
                strcpy(max_founded_substring, current_substring);
            }
        }
    }
}
int main()
{
    short strings_count = input_strings_count();
    char** strings = input_strings_and_their_count(strings_count);
    char maxSubstring[100];

    findMaxSubstring(strings, strings_count, maxSubstring);

    if (strlen(maxSubstring) > 0)printf("max string in all strings: %s\n", maxSubstring);
    else printf("In your text there is no general part\n");

    return 0;
}