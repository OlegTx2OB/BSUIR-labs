#include "MyBatteryInformation.h"
#include "MySleepHibernateMode.h"
#include <thread>

using namespace std;

int main() {
    thread batteryThread(MyBatteryInformation::batteryInformation);
    thread enterThread(MySleepHibernateMode::enterMode);
    thread inputThread(MySleepHibernateMode::handleCommands);

    batteryThread.join();
    enterThread.join();
    inputThread.join();

    return 0;
}