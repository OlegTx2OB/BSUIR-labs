#pragma once
#include <iostream>
#include <limits>
#include "List.h"

using namespace std;
class Menu
{
public:
    Menu(){}

    void chooseListTypeMenu()
    {
        while(true)
        {
            cout << "\n===| Enter tree type |==============\n"
                    "1.int   2.float   3.string   4.quit:";
            int choose = getInt("", 1, 4);
            if(choose == 1)
            {
                List<int> list;
                workWithListMenu(list);
            }
            else if(choose == 2)
            {
                List<float> list;
                workWithListMenu(list);
            }
            else if(choose == 3)
            {
                List<string> list;
                workWithListMenu(list);
            }
            else if(choose == 4) break;
        }
    }
    template<typename T>
    void workWithListMenu(List<T>& list)
    {
        while(true)
        {
            cout << "\n===| List menu |=========================================================\n"
                    "1.addNode   2.isEmpty   3.print   4.deleteAll   5.deleteByValue   6.quit:";
            int choose = getInt("", 1, 6);
            if(choose == 1) list.addNode();
            else if(choose == 2) list.isEmpty();
            else if(choose == 3) list.print();
            else if(choose == 4) list.deleteAll();
            else if(choose == 5) list.deleteByValue();
            else if(choose == 6) break;
        }
    }
    int getInt(string str, int lowerBound, int upperBound);
};

