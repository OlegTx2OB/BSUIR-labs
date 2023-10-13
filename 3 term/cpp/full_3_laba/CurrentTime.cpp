#include "CurrentTime.h"
#include "Menu.h"


int CurrentTime::getTimeInHours()
{
    return ((( (this->year * 12) + this->month) * 31) + this->day) * 24 + this->hours;
}

void CurrentTime::printTime()
{
    printf("Time: YYYY:%d MM:%d DD:%d hr:%d\n\n",
           this->getYear(), this->getMonth(), this->getDay(), this->getHours());
}
void CurrentTime::setTimeByHand()
{
    this->setYear(Menu::getInt("year", 1900, 2100));
    this->setMonth(Menu::getInt("month", 1, 12));
    this->setDay(Menu::getInt("day", 1, 31));
    this->setHours(Menu::getInt("hours", 0, 23));
}
void CurrentTime::setTimeByRandom()
{
    srand(time(nullptr));

    this->setYear((rand() % 201) + 1900);
    this->setMonth((rand() % 12) + 1);
    this->setDay((rand() % 31) + 1);
    this->setHours(rand() % 24);
}