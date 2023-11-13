#include <iostream>
#include <regex>
#include <iomanip>
#pragma inline
using namespace std;
#define arraySize 10

void arrayInput(double array[arraySize]) 
                                             
{
    regex regFloat("^[-]?[0-9]*[.]?[0-9]+$");
    string buffer;
    for (int i = 0; i < arraySize; i++)
    {
        cout << "Input " << i + 1 << " element: ";
        getline(cin, buffer);
        while (!regex_match(buffer, regFloat))
        {
            cout << "Wrong input. Enter again" << endl;
            rewind(stdin);
            cin.clear();
            getline(cin, buffer);
        }
        array[i] = stod(buffer);
    }
}
int main()
{
    //R0-R7(ST(0) - ST(7))
    //SR, CR, TW, FIP, FDP
    
    //Управления сопроцессором, пересылки данных, базовой арифметики, сравнения, операций над ST0, записи констант
    double sum = 0;
    double average = 0;
    double sizeR = 10;
    
    double array[arraySize];
    arrayInput(array);
    __asm 
    {
        FINIT
        XOR esi, esi
        MOV ecx, arraySize

        FLD sum


        loopArray:
            FLD array[esi]
            FADDP ST(1), ST(0)
            ADD esi, 8
        LOOP loopArray

        FLD sizeR
        FDIVP ST(1), ST(0)
        FSTP average

        FWAIT
    }
    cout << "average is: " << average << setw(5);
    return 0;
}