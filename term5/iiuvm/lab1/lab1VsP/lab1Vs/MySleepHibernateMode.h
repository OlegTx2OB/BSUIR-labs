#pragma once
#include <iostream>
#include <windows.h>
#include <powrprof.h>
#include <string>

class MySleepHibernateMode
{
private:
    static void enterSleepMode();
    static void enterHibernateMode();
    static bool hasConsoleUpdated(CONSOLE_SCREEN_BUFFER_INFO& lastInfo);
    static void rewrite();

public:
    static void enterMode();
    static void handleCommands();
};

