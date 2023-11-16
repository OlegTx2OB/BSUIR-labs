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
void Menu::divideTwoFloats()
{
    float f1;
    float f2;


    cout << "input f1:";
    while (!scanf("%f", &f1))
    {
        cout << "invalid input. enter float:";
        rewind(stdin);
    }

    cout << "input f2:";
    while (!scanf("%f", &f2))
    {
        cout << "invalid input. enter float:";
        rewind(stdin);
    }

    try
    {
        cout << "\nYour answer:"<< f1/f2;
    }
    catch(...)
    {
        cout << "You can't divide by 0\n";
    }
}


