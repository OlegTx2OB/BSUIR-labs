#pragma once
#include <iostream>
#include <limits>
#include "CurrentTime.h"
#include "SecondaryFunctions.h"

using namespace std;

class Event : public CurrentTime
{
private:
    int eventId;
    bool isCompleted;

public:
    Event(int eventId, int hours = 0, int day = 1, int month = 1, int year = 1900)
    : eventId(eventId), CurrentTime(hours, day, month, year){}

    virtual string getEventName() = 0;
    virtual void eventMenu(CurrentTime* currTime) = 0;
    virtual void printEventInfo() = 0;

    int getId() { return eventId; }
    void setEventId(int _eventId) { this->eventId = _eventId; }

};

class Meeting : public Event
{
private:
    bool isCompleted;
    int durationInHours;

public:
    Meeting(int eventId, int durationInHours, bool isCompleted = false, int hours = 0, int day = 1, int month = 1, int year = 1900)
    : Event(eventId, hours, day, month, year), isCompleted(isCompleted), durationInHours(durationInHours){}

    void eventMenu(CurrentTime* currTime) override
    {
        while(true)
        {
            printEventInfo();
            printf("1.Change time   2.Change durationInHours   3.Change isCompleted   4.QUIT:");
            int choose = getInt("", 1, 3);
            if (choose == 1) this->setTimeByHand();
            else if (choose == 2) setDurationInHours(getInt("durationInHours", 0, 100));
            else if(choose == 3)
            {
                if(currTime->getTimeInHours() >= this->getTimeInHours() + this->getDurationInHours())
                    setIsCompleted(getInt("isCompleted", 0, 1));
                else printf("You can't change this parameter\n");
            }
            else break;
        }
    }

    void printEventInfo() override;
    string getEventName() override {return "Meeting";}


    int getDurationInHours() { return durationInHours; }
    bool getIsCompleted() { return isCompleted; }
    void setDurationInHours(int _durationInHours) { durationInHours = _durationInHours; }
    void setIsCompleted(bool _isCompleted) { isCompleted = _isCompleted; }
};

class Reminder : public Event
{
public:
    Reminder(int eventId, int hours = 0, int day = 1, int month = 1, int year = 1900)
            : Event(eventId, hours, day, month, year){}

    void eventMenu(CurrentTime* currTime) override
    {
        while(true)
        {
            printEventInfo();
            printf("1.Change time   2.QUIT:");
            int choose = getInt("", 1, 2);
            if (choose == 1) this->setTimeByHand();
            else break;
        }
    }
    void printEventInfo() override;
    string getEventName() override {return "Reminder";}
};

class Task : public Event
{
private:
    string description;
public:
    Task(int eventId, string description = "", int hours = 0, int day = 1, int month = 1, int year = 1900)
            : Event(eventId, hours, day, month, year), description(description){}

    void eventMenu(CurrentTime* currTime) override
    {
        while(true)
        {
            printEventInfo();
            printf("1.Change time   2.Change description   3.QUIT:");
            int choose = getInt("", 1, 3);
            if (choose == 1) this->setTimeByHand();
            else if (choose == 2) cin >> description;
            else break;
        }
    }
    void printEventInfo() override;
    string getEventName() override {return "Task";}

    string getDescription(){ return description; }
    void setDescription(string _description){ description = _description;}

};
