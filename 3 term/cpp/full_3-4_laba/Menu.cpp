#include "Menu.h"
void Menu::printAllEvents(list<Event*> eventList, CurrentTime* currTime)
{
    while(!eventList.empty())
    {
        Event *event = eventList.front();
        eventList.pop_front();
        event->getEventName();

        if(event->getEventName() == "Meeting")
        {
            Meeting* m = dynamic_cast<Meeting*>(event);
            m->printEventInfo();
        }
        else if(event->getEventName() == "Reminder")
        {
            Reminder* r = dynamic_cast<Reminder*>(event);
            if(currTime->getTimeInHours() < r->getTimeInHours()) r->printEventInfo();
        }
        else if(event->getEventName() == "Task")
        {
            Task* t = dynamic_cast<Task*>(event);
            t->printEventInfo();
        }
    }
}
void Menu::addEvent(list<Event*> &eventList)
{
    printf("Choose event you want to add:\n"
           "1.meeting   2.reminder   3.task:");
    int choose = getInt("",1, 3);

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
    else if(choose == 2)
    {
        Reminder* reminder = new Reminder(id);
        if(getInt("isRandomTimeInput",0, 1))reminder->setTimeByRandom();
        else reminder->setTimeByHand();
        eventList.push_back(reminder);
    }
    else
    {
        printf("Enter description:");
        string str;
        cin >> str;

        Task* task = new Task(id, str);
        if(getInt("isRandomTimeInput",0, 1))task->setTimeByRandom();
        else task->setTimeByHand();
        eventList.push_back(task);
    }
}
void Menu::getEventById(list<Event*> eventList, CurrentTime* currTime)
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
            m->eventMenu(currTime);
        }
        else if(event->getEventName() == "Reminder")
        {
            Reminder* r = dynamic_cast<Reminder*>(event);
            r->eventMenu(currTime);
        }
        else
        {
            Task* t = dynamic_cast<Task*>(event);
            t->eventMenu(currTime);
        }
    }

}
void Menu::delEventById(list<Event*> eventList)
{
    int id = getInt("id",1000, 9999);
    for (auto it = eventList.begin(); it != eventList.end(); it++)
    {
        if ( (*it)->getId() == id)
        {
            eventList.erase(it);
            break;
        }
    }
}