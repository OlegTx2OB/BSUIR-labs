#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void input(char* fname, int int_count);
void output(char* fname, int int_count);
void checking_for_forbidden_filenames(char* fname);

void task1(char* fname, int int_count);
void task2(char* fname, int int_count);
void task3(char* fname, int int_count);
void task4(char* fname, int int_count);
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
    int int_count;
    printf("Enter count of int_count (from 2 to 20):");
    while(!scanf("%d", &int_count) || int_count > 2147483647 || int_count < -2147483648 || getchar() != '\n')
    {
        printf("Wrong input. Please, try again. Enter count of int_count (from 2 to 20):");
        rewind(stdin);
    }
    task1(fname, int_count);
    task2(fname, int_count);
    task3(fname, int_count);
    task4(fname, int_count);
    return 0;
}

void task1(char* fname, int int_count)
{
    FILE* fp = fopen(fname, "wb");
    input(fname, int_count);
    printf("\noutput: ");
    output(fname, int_count);
    fclose(fp);
}
void task2(char* fname, int int_count)
{
    FILE* fp = fopen(fname, "r+b");
    int simple_int_count = 0;
    int var;
    fseek(fp, 0, SEEK_SET);
    for(int i = 0; i < int_count; i++)
    {
        int checkbox = 0;
        fread(&var, sizeof(int), 1, fp);
        for(int j = 2; j < var || var == 2; j++)
        {

            if(var % j == 0) checkbox++;
        }
        if(checkbox == 0 && var > 1) simple_int_count++;
    }
    printf("\ncount of simple_int_count is %d\n", simple_int_count);
    fclose(fp);
}
void task3(char* fname, int int_count)
{
    FILE* fp = fopen(fname, "r+b");
    int buf;
    int i = 0;
    while (1)
    {
        fseek(fp, i * sizeof(int), SEEK_SET);
        fread(&buf, sizeof(int), 1, fp);
        buf = (-1) * buf;
        fseek(fp, -4, SEEK_CUR);

        fwrite(&buf, sizeof(int), 1, fp);
        fflush(fp);
        i++;
        if (i == int_count)
        {
            break;
        }
    }
    printf("\nOutput after sign change: ");
    output(fname, int_count);
    fclose(fp);
}
void task4(char* fname, int int_count)
{
    FILE* fp = fopen(fname, "r+b");
    int int1, int2;
    for (int k=0;k<(int_count-1);k++)
    {
        int min_index = k;
        fseek(fp, k*sizeof(int), SEEK_SET);
        fread(&int1, sizeof(int), 1, fp);
        int buffer = int1;
        if (buffer>0)
        {
            continue;
        }
        for (int j = k + 1; j < int_count; j++)
        {
            fseek(fp, j * sizeof(int), SEEK_SET);
            fread(&int2, sizeof(int), 1, fp);
            if (int2 > 0)
            {
                continue;
            }
            if (int1 < int2)
            {
                min_index = j;
                int1 = int2;
            }
        }
        if (min_index!=k)
        {
            fseek(fp, min_index * sizeof(int), SEEK_SET);
            fwrite(&buffer, sizeof(int), 1, fp);
            fflush(fp);
            fseek(fp, k * sizeof(int), SEEK_SET);
            fwrite(&int1, sizeof(int), 1, fp);
            fflush(fp);

        }
    }
    printf("\nOutput after sort: ");
    output(fname, int_count);
    fclose(fp);
}
void input(char* fname, int int_count)
{
    FILE* fp = fopen(fname, "wb");
    if(fp == NULL)
    {
        return;
    }
    int var;
    for(int i = 0; i < int_count; i++)
    {
        printf("Enter %d-st var:", i + 1);
        while(!scanf("%d", &var) || var > 2147483647 || var < -2147483648 || getchar() != '\n')
        {
            printf("wrong input. try again. Enter %d-st var: ", i + 1);
            rewind(stdin);
        }
        fwrite(&var, sizeof(int), 1, fp);
    }
    fclose(fp);
}
void output(char* fname, int int_count)
{
    FILE* fp = fopen(fname, "rb");
        if(fp == NULL)
        {
            return;
        }
    int var;
    for(int i = 0; i < int_count; i++)
    {
        fread(&var, sizeof(int), 1, fp);
        printf("%d ", var);
    }
    fclose(fp);
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
            printf("Failed to start the program, incorrect filename\n\n");
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