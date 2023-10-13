#include <iostream>
#include <list>
#include "CurrentTime.h"
#include "Event.h"

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

    void printAllEvents(list<Event*> eventList)
    {
        Event *event = eventList.front();
        eventList.pop_front();
        event->getEventName();

        if(event->getEventName() == "Meeting")
        {
            Meeting* m = dynamic_cast<Meeting*>(event);
            m->printEventInfo();
        }
    }
    void addEvent(list<Event*> &eventList)
    {
        printf("Choose event you want to add:\n"
               "1.meeting   2TODO:");
        int choose = getInt("",1, 2);

        srand(time(nullptr));
        int id = (rand() % 9000) + 1000;

        if(choose == 1)
        {
            int durationInHours = getInt("duration in hours",1, 100);
            Meeting* meeting = new Meeting(id, durationInHours);
            if(getInt("isRandomTimeInput",0, 1))meeting->setTimeByRandom();
            else meeting->setTimeByHand();
            eventList.push_back(meeting);
        }
    }
    void getEventById(list<Event*> eventList)
    {
        int id = getInt("id",1000, 9999);

        Event* event = nullptr;
        for(Event *e : eventList)
        {
            if (e->getId() == id)
            {
                event = e;
                break;
            }
        }

        if(event == nullptr) printf("Event is not founded");
        else
        {
            if(event->getEventName() == "Meeting")
            {
                Meeting* m = dynamic_cast<Meeting*>(event);
                m->eventMenu();
            }
        }

    }
    void delEventById(list<Event*> eventList)
    {

    }


    static int getInt(string str, int lowerBound, int upperBound);
};