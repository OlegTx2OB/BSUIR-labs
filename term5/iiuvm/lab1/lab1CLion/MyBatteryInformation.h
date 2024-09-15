#pragma once
#include <iostream>
#include <windows.h>
#include <batclass.h>
#include <devguid.h>
#include <setupapi.h>
#include <powrprof.h>

using namespace std;
#pragma comment(lib, "setupapi.lib")

class MyBatteryInformation
{
public:
    static void batteryInformation();
private:
    static wstring getDeviceName();
};

