#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void checking_for_forbidden_filenames(char* fname);
int file_len(char* fname);
int letter(char c);
void start_and_end_of_st_word(char* fname, int* n_start, int* n_end, int n);
void finding_min_word(char* fname, int* min_word_start_pos, int* min_word_end_pos);
void print_min_word(char* fname, int min_word_start_pos, int min_word_end_pos);
void reversing_part(char* fname, int start, int end)
{
    FILE *fp = fopen(fname, "r+");
    char ci, c_end_j;
    {
        for(int i = start, j = 0; i < ((end + start) * 0.5 + 0.5); i++, j++)
        {
            fseek(fp, i, SEEK_SET);
            ci = fgetc(fp);                     //start

            fseek(fp, end - j, SEEK_SET);
            c_end_j = fgetc(fp);                     //end

            fseek(fp, end - j, SEEK_SET);
            fputc(ci, fp);

            fseek(fp, i, SEEK_SET);
            fputc(c_end_j, fp);


        }
    }
    fclose(fp);
}
void output(char* fname)
{
    FILE *fp = fopen(fname, "r");
    printf("\n");
    for (int i = 0;  i < file_len(fname); i++)
    {
        char c = fgetc(fp);
        printf("%c", c);
    }
    fclose(fp);
}


void task1(char* fname);
void task2(char* fname);
void task3(char* fname);
int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("/-------------------------------------------------------------------------\\\n"
               "|Failed to start the program. Please, try again and write only 2 arguments|\n"
               "\\-------------------------------------------------------------------------/\n");
        exit(-1);
    }
    char* fname = argv[1];

    checking_for_forbidden_filenames(fname);

    //char* fname = "mama.txt";
    task1(fname);
    task2(fname);
    task3(fname);
    return 0;
}

void task1(char* fname)
{
    FILE* fp = fopen(fname, "w+");
    char* str = malloc(255);
    int i = 0;
    char c;
    printf("Please, enter what you want in your file:\n");

    while((c = getchar() )!='\n')
    {
        str[i]=c;
        fputc(c, fp);
        i++;
    }
    fputc('\0', fp);
    fclose(fp);

}
void task2(char* fname)
{
    int min_word_start_pos;
    int min_word_end_pos;
    start_and_end_of_st_word(fname, &min_word_start_pos, &min_word_end_pos, 1);
    finding_min_word(fname, &min_word_start_pos, &min_word_end_pos);
    print_min_word(fname, min_word_start_pos, min_word_end_pos);

}

void task3(char* fname)
{
    int first_start_pos, first_end_pos;
    int second_start_pos, second_end_pos;
    start_and_end_of_st_word(fname, &first_start_pos, &first_end_pos, 1);
    start_and_end_of_st_word(fname, &second_start_pos, &second_end_pos, 2);

    reversing_part(fname, first_start_pos, second_end_pos - 1);

    start_and_end_of_st_word(fname, &first_start_pos, &first_end_pos, 1);
    reversing_part(fname, first_start_pos, first_end_pos - 1);

    start_and_end_of_st_word(fname, &second_start_pos, &second_end_pos, 2);
    reversing_part(fname, second_start_pos, second_end_pos - 1);

    reversing_part(fname, first_end_pos, second_start_pos - 1);

    output(fname);
}
void checking_for_forbidden_filenames(char* fname)
{
    char *b3 = malloc(5 * sizeof(char));
    char *b4 = malloc(6 * sizeof(char));
    b3[4] = '\0';
    b4[5] = '\0';

    for (int i = 0; i < sizeof(fname); i++)
    {
        if (fname[i] == '"' || fname[i] == '\'' || fname[i] == '/' ||
            fname[i] == '\\' || fname[i] == ':' || fname[i] == '|')
        {
            free(b3);
            free(b4);
            printf("Failed to start the program, incorrect filename\n");
            exit(-1);
        }


        if (i < 4)
        {
            b3[i] = fname[i];
            if (b3[i] >= 'a' && b3[i] <= 'z') b3[i] -= 32;
        }
        if (i < 5)
        {
            b4[i] = fname[i];
            if (b4[i] >= 'a' && b4[i] <= 'z') b4[i] -= 32;
        }
    }
    if ( strcmp(b3, "CON.")  == 0 || strcmp(b3, "PRX.") == 0  || strcmp(b3, "NUL.") == 0  || strcmp(b3, "AUX.") == 0  ||
         strcmp(b4, "COM0.") == 0 || strcmp(b4, "COM1.") == 0 || strcmp(b4, "COM2.") == 0 || strcmp(b4, "COM3.") == 0 ||
         strcmp(b4, "COM4.") == 0 || strcmp(b4, "COM5.") == 0 || strcmp(b4, "COM6.") == 0 || strcmp(b4, "COM7.") == 0 ||
         strcmp(b4, "COM8.") == 0 || strcmp(b4, "COM9.") == 0 || strcmp(b4, "LPT0.") == 0 || strcmp(b4, "LPT1.") == 0 ||
         strcmp(b4, "LPT2.") == 0 || strcmp(b4, "LPT3.") == 0 || strcmp(b4, "LPT4.") == 0 || strcmp(b4, "LPT5.") == 0 ||
         strcmp(b4, "LPT6.") == 0 || strcmp(b4, "LPT7.") == 0 || strcmp(b4, "LPT8.") == 0 || strcmp(b4, "LPT9.") == 0)
    {
        free(b3);
        free(b4);
        printf("Failed to start the program, incorrect filename\n");
        exit (-1);
    }
    free(b3);
    free(b4);
    printf("The new file has been created\n\n");
}
void start_and_end_of_st_word(char* fname, int* n_start, int* n_end, int n)
{
    FILE* fp = fopen(fname, "r+");
    char c_1, c;
    int start_count = 0;
    int end_count = 0;
    int len = file_len(fname);

    for(int i = 0; i <= len; i++)
    {
        c = fgetc(fp);
        if(i != 0)
        {
            fseek(fp, -2, SEEK_CUR);
            c_1 = fgetc(fp);
            fseek(fp, 1, SEEK_CUR);
        }

        if((i!= 0 && !letter(c_1) && letter(c)) || (i == 0 && letter(c) ))           //start
        {
            start_count++;
            if(start_count == n) (*n_start) = i;
        }
        else if ( i!= 0 && !letter(c) && letter(c_1))           //end
        {
            end_count++;
            if(end_count == n) (*n_end) = i;
        }
    }
    fclose(fp);
}
void print_min_word(char* fname, int min_word_start_pos, int min_word_end_pos)
{
    FILE* fp = fopen(fname, "r");
    fseek(fp, min_word_start_pos, SEEK_SET);
    char c;
    printf("\nMin word is: ");
    for(int i = 0; i < min_word_end_pos - min_word_start_pos; i++)
    {
        c = fgetc(fp);
        printf("%c", c);
    }
    fclose(fp);
}
void finding_min_word(char* fname, int* min_word_start_pos, int* min_word_end_pos)
{
    FILE* fp = fopen(fname, "r+");
    char c, c_1;
    int len = file_len(fname);
    int cur_word_start_pos;
    int cur_word_end_pos;
    for(int i = 0; i <= len; i++)
    {
        c = fgetc(fp);
        if(i != 0)
        {
            fseek(fp, -2, SEEK_CUR);
            c_1 = fgetc(fp);
            fseek(fp, 1, SEEK_CUR);
        }

        if((i!= 0 && !letter(c_1) && letter(c)) || (i == 0 && letter(c) ))           //start
        {
            cur_word_start_pos = i;
        }
        else if ( i!= 0 && !letter(c) && letter(c_1))           //end
        {
            cur_word_end_pos = i;
            if((cur_word_end_pos - cur_word_start_pos) < ((*min_word_end_pos) - (*min_word_start_pos) ))
            {
                (*min_word_start_pos) = cur_word_start_pos;
                (*min_word_end_pos) = cur_word_end_pos;
            }
        }

    }
    fclose(fp);
}
int file_len(char* fname)
{
    FILE* fp = fopen(fname, "r");
    int i = 0;
    char c;
    while((c = fgetc(fp)) != '\0' && c != '\n' && c != EOF) i++;
    fclose(fp);
    return i;
}
int letter(char c)
{
    if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1;
    return 0;
}