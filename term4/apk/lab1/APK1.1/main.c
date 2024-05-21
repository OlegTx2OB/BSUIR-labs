#include <stdio.h>
#include <windows.h>
#include <io.h>

char* filename = "COM6";
int main() {

    FILE *file_pointer;
    file_pointer = fopen(filename, "r");

    if (file_pointer == NULL) {
        printf("not opened\n");
        return 1;
    }

    char word[101], *it = word;
    int retVal, size;

    while (1)
    {
        retVal = _read(_fileno(file_pointer), it, 1);
        it += sizeof(char);

        if (retVal < 1 || *(it - 1) == '\n')
            break;
    }
    if (retVal >= 0)
    {
        size = it - word;
        for (int i = 0; i < size; i++)
            printf("%c", word[i]);
    }
    else
        printf("error\n");

    fclose(file_pointer);
    return 0;
}




