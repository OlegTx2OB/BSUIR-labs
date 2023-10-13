#include <iostream>
#include <list>
#include "CurrentTime.h"
#include "Event.h"
#include "SecondaryFunctions.h"

using namespace std;

class Menu
{
public:
    Menu(){}

    void MainMenu()
    {
        CurrentTime* currTime = new CurrentTime();
        currTime->printTime();

        list<Event*> eventList;

        while(true)
        {
            cout << "===== Main Menu =====================================================================================================\n"
                    "1.Get curr time   2.Set curr time   3.Print all events   4.add event   5.Get event by id   6.del event by id   7.QUIT\n"
                    "=====================================================================================================================\n";
            int choose = getInt("",1, 7);
            if(choose == 1) currTime->printTime();
            else if(choose == 2) currTime->setTimeByHand();
            else if(choose == 3) this->printAllEvents(eventList);
            else if(choose == 4) this->addEvent(eventList);
            else if(choose == 5) this->getEventById(eventList);
            else if(choose == 6) this->delEventById(eventList);
            else if(choose == 7) break;
        }
        delete currTime;
    }

    void printAllEvents(list<Event*> eventList);
    void addEvent(list<Event*> &eventList);
    void getEventById(list<Event*> eventList);
    void delEventById(list<Event*> eventList);
};