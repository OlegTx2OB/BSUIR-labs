#include <thread>
#include "BatteryInfo.h"
#include "PowerManager.h"

bool isProgramWorking = true;

void coutInfo() {
    BatteryInfo batteryInfo = BatteryInfo();
    while (isProgramWorking) {
        batteryInfo.displayInfo();
    }
}

void cinInfo() {
    PowerManager powerManager = PowerManager();
    char option[64];
    while (isProgramWorking) {
        scanf_s("%s", option, (unsigned)_countof(option));
        if ('1' == option[0]) {
            powerManager.goIntoSleepMode();
        }
        else if ('2' == option[0]) {
            powerManager.goIntoHibernationMode();
        }
        else if ('3' == option[0]) {
            isProgramWorking = false;
        }
        else {
            printf("invalid input\n");
        }
    }
}

int main() {
    thread coutThread(coutInfo);
    thread cinThread(cinInfo);

    cinThread.join();
    coutThread.join();

    return 0;
}
