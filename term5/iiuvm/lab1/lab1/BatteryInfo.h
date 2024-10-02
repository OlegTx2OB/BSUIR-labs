#pragma once
#include <iostream>
#include <string>
#include <iostream>
#include <windows.h>
#include <powrprof.h>
#include <devguid.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <poclass.h>
#include <setupapi.h>

using namespace std;

class BatteryInfo
{
public:
    void displayInfo();
private:
    void displayIsCharging(SYSTEM_POWER_STATUS powerStatus);
    void displayBatteryLevel(SYSTEM_POWER_STATUS powerStatus);
    void displayIsBatterySaverOn(SYSTEM_POWER_STATUS powerStatus);
    void displayBatteryType();
    void displayBatteryTime(SYSTEM_POWER_STATUS powerStatus, bool isFullBatteryTime);

    string mapSecondsTimeIntoString(int timeInSeconds);
    void displayOptions();
    void displayClearStrings();
};
