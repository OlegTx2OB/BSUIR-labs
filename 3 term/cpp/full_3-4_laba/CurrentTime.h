#pragma once
#include <iostream>
#include <limits>

using namespace std;

class CurrentTime
{
private:
    int hours;
    int day;
    int month;
    int year;

public:
    CurrentTime(int hours = 0, int day = 1, int month = 1, int year = 1900)
                : hours(hours), day(day), month(month), year(year){}

    void printTime();
    void setTimeByHand();
    void setTimeByRandom();

    int getTimeInHours();

    int getHours(){ return hours; }
    int getDay(){ return day; }
    int getMonth(){ return month; }
    int getYear(){ return year; }
    void setHours(int _hours) { this->hours = _hours; }
    void setDay(int _day) { this->day = _day; }
    void setMonth(int _month) { this->month = _month; }
    void setYear(int _year) { this->year = _year; }
};