#pragma once
#include <iostream>
#include <string>
using namespace std;

class BatteryInfo
{
public:
	void displayInfo();
private:
	void displayIsCharging();
	void displayIsBatterySaverOn();
	void displayBatteryLevel();
	void displayBatteryType();
	void displayBatteryTime();
};

