#pragma once
#include <iostream>
#include <vector>
#include "Structure.h"
#include "BinFile.h"
#include "TxtFile.h"

using namespace std;
class MenuClass
{
public:
    void menu()
    {
        vector<int> idVector;
        while(true)
        {
            cout << "\n====| Choose option |====\n"
                    "1.add note  2.change note  3.quit: ";
            int choose = getInt("", 1, 3);
            if(choose == 1)
            {
                idVector = addNotesIntoFile();
                mixFiles();
            }
            else if(choose == 2) changeNotesIntoFile(idVector);
            else break;
        }
    }
    vector<int> addNotesIntoFile();
    void changeNotesIntoFile(vector<int> idVector);
    void mixFiles();
    void changeNoteById(int id);


    int getInt(string str, int lowerBound, int upperBound);
};