#include "Menu.h"

int Menu::getInt(string str, int lowerBound, int upperBound)
{
    if (!str.empty()) cout << "Enter " << str << " (" << lowerBound << " - " << upperBound << "): ";

    int d;
    while (!scanf("%d", &d) || d < lowerBound || d > upperBound)
    {
        cout << "invalid input" << endl;
        rewind(stdin);
    }
    return d;
}