#include "SecondaryFunctions.h"
int getInt(string str, int lowerBound, int upperBound)
{
    if (str != "") printf("Enter %s (%d - %d):", str.c_str(), lowerBound, upperBound);
    int d;
    while (!scanf_s("%d", &d) || d < lowerBound || d > upperBound || getchar() != '\n')
    {
        printf("invalid input\n");
        cin.ignore();
    }
    return d;
}