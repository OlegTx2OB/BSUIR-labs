#include "Menu.h"


int Menu::getInt(string str, int lowerBound, int upperBound)
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

//void Menu::printAllEvents(list<Event*> eventList)
//{
//    while(!eventList.empty())
//    {
//        Event *event = eventList.front();
//        eventList.pop_front();
//        event->getEventName();
//
//        if(event->getEventName() == "Meeting")
//        {
//            Meeting* m = dynamic_cast<Meeting*>(event);
//            m->printEventInfo();
//        }
//    }
//}
//void Menu::addEvent(list<Event*> &eventList)
//{
//    printf("Choose event you want to add:\n"
//           "1.meeting   2TODO:");
//    int choose = getInt("",1, 2);
//
//    srand(time(nullptr));
//    int id = (rand() % 9000) + 1000;
//
//    if(choose == 1)
//    {
//        int durationInHours = getInt("duration in hours",1, 100);
//        Meeting* meeting = new Meeting(id, durationInHours);
//        if(getInt("isRandomTimeInput",0, 1))meeting->setTimeByRandom();
//        else meeting->setTimeByHand();
//        eventList.push_back(meeting);
//    }
//}
//void Menu::getEventById(list<Event*> eventList)
//{
//    int id = getInt("id",1000, 9999);
//
//    Event* event = nullptr;
//    for(Event *e : eventList)
//    {
//        if (e->getId() == id)
//        {
//            event = e;
//            break;
//        }
//    }
//
//    if(event == nullptr) printf("Event is not founded");
//    else
//    {
//        if(event->getEventName() == "Meeting")
//        {
//            Meeting* m = dynamic_cast<Meeting*>(event);
//            m->eventMenu();
//        }
//    }
//
//}
//void Menu::delEventById(list<Event*> eventList)
//{
//
//}