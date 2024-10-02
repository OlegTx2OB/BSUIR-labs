#pragma comment(lib, "PowrProf.lib")
#pragma comment (lib, "setupapi.lib")

#include <iostream>
#include <Windows.h>
#include "winbase.h"
#include "ioapiset.h"
#include "powrprof.h"
#include <thread>   
#include "conio.h"
#include <Poclass.h>
#include <Setupapi.h>
#include <devguid.h>
#include <sstream>
#include <string>

bool run = true;

bool getBatteryChemistry() {
    HDEVINFO hdev = SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (hdev == INVALID_HANDLE_VALUE)
        return false;

    SP_DEVICE_INTERFACE_DATA did = { 0 };
    did.cbSize = sizeof(did);

    if (!SetupDiEnumDeviceInterfaces(hdev, 0, &GUID_DEVCLASS_BATTERY, 0, &did))
        return false;

    DWORD cbRequired = 0;
    SetupDiGetDeviceInterfaceDetail(hdev, &did, 0, 0, &cbRequired, 0);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        SetupDiDestroyDeviceInfoList(hdev);
        return INVALID_HANDLE_VALUE;
    }

    PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, cbRequired);
    if (!pdidd) {
        SetupDiDestroyDeviceInfoList(hdev);
        return false;
    }

    pdidd->cbSize = sizeof(*pdidd);
    if (!SetupDiGetDeviceInterfaceDetail(hdev, &did, pdidd, cbRequired, &cbRequired, 0)) {
        LocalFree(pdidd);
        SetupDiDestroyDeviceInfoList(hdev);
        return false;
    }

    HANDLE hBattery = CreateFile(pdidd->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (INVALID_HANDLE_VALUE == hBattery) {
        LocalFree(pdidd);
        SetupDiDestroyDeviceInfoList(hdev);
        return false;
    }

    LocalFree(pdidd);
    SetupDiDestroyDeviceInfoList(hdev);

    BATTERY_QUERY_INFORMATION bqi = { 0 };

    if (!(DeviceIoControl(hBattery, IOCTL_BATTERY_QUERY_TAG, 0, 0, &bqi.BatteryTag, sizeof(bqi.BatteryTag), 0, 0) && bqi.BatteryTag))
        return false;

    BATTERY_INFORMATION bi = { 0 };
    bqi.InformationLevel = BatteryInformation;

    if (!DeviceIoControl(hBattery, IOCTL_BATTERY_QUERY_INFORMATION, &bqi, sizeof(bqi), &bi, sizeof(bi), 0, 0))
        return false;

    if (!(bi.Capabilities & BATTERY_SYSTEM_BATTERY) && (bi.Capabilities & BATTERY_IS_SHORT_TERM))
        return false;

    std::cout << std::string(bi.Chemistry, bi.Chemistry + 4) << std::endl;
}

void getBatteryInfo() {
    SYSTEM_POWER_STATUS sys_inf;
    GetSystemPowerStatus(&sys_inf);


    int ACLineStatus = sys_inf.ACLineStatus;
    std::cout << "Charging status: ";
    if (ACLineStatus)
        std::cout << "charging" << std::endl;
    else
        std::cout << "not charging" << std::endl;

    int BatteryLifePercent = sys_inf.BatteryLifePercent;
    std::cout << "Battery level: " << BatteryLifePercent << "%" << std::endl;


    int SystemStatusFlag = sys_inf.SystemStatusFlag;
    if (SystemStatusFlag)
        std::cout << "Battery saver is on" << std::endl;
    else
        std::cout << "Battery saver is off" << std::endl;

    getBatteryChemistry();

    int BatteryLifeTime = sys_inf.BatteryLifeTime;
    if (BatteryLifeTime != -1) {
        std::cout << "Time remaining: " << BatteryLifeTime / 3600 << " h " << BatteryLifeTime % 60 << " min" << std::endl;
        int batteryMaxTime = 100 * BatteryLifeTime / BatteryLifePercent;
        std::cout << "Max time: " << batteryMaxTime / 3600 << " h " << batteryMaxTime % 60 << " min" << std::endl;
    }

}
void monitorBatteryInfo() {
    while (true) {
        getBatteryInfo();
        int a;
        std::string input;
        while (true) {
            std::getline(std::cin, input);
            std::stringstream ss(input);


            if (ss >> a && ss.eof()) {
                if (a < 4 && a >= 0)
                    break;
                std::cout << "Error" << std::endl;
            }
            else {
                std::cout << "Error" << std::endl;
            }
        }
        if (a == 1)
            SetSuspendState(1, 1, 0);
        else if (a == 2)
            SetSuspendState(0, 1, 0);
        else if (a == 0) {
            run = false;
            return;
        }
        else
            std::cout << "Error" << std::endl;
    }
}
void realTimeRefresh() {
    while (run) {
        system("cls");
        getBatteryInfo();
        std::cout << "1. Hibernation" << std::endl << "2. Sleep" << std::endl << "0. Stop program" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::thread batteryThread(realTimeRefresh);
    monitorBatteryInfo();
    batteryThread.join();
    return 0;
}
