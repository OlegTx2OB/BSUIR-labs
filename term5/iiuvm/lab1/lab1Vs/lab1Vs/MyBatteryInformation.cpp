#include "MyBatteryInformation.h"

wstring MyBatteryInformation::getDeviceName() {
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get device info set: " << GetLastError() << std::endl;
        return L"";
    }

    SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
    deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
    std::wstring devicePath = L"";

    for (int i = 0; SetupDiEnumDeviceInterfaces(deviceInfoSet, NULL, &GUID_DEVCLASS_BATTERY, i, &deviceInterfaceData); ++i) {
        DWORD requiredSize = 0;
        SetupDiGetDeviceInterfaceDetail(deviceInfoSet, &deviceInterfaceData, NULL, 0, &requiredSize, NULL);

        SP_DEVICE_INTERFACE_DETAIL_DATA* deviceInterfaceDetailData = (SP_DEVICE_INTERFACE_DETAIL_DATA*)malloc(requiredSize);
        deviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        if (SetupDiGetDeviceInterfaceDetail(deviceInfoSet, &deviceInterfaceData, deviceInterfaceDetailData, requiredSize, NULL, NULL)) {
            devicePath = deviceInterfaceDetailData->DevicePath;
        }

        free(deviceInterfaceDetailData);
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
    return devicePath;
}

void MyBatteryInformation::batteryInformation() {
    HANDLE hDevice = CreateFile(
        getDeviceName().c_str(),
        GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    SYSTEM_POWER_STATUS spsPwr;
    BATTERY_QUERY_INFORMATION bqi;
    BATTERY_INFORMATION bi;
    DWORD bytesReturned;

    int lastACLineStatus = 0;
    int lastBatteryFlag = 0;
    int lastBatteryLifePercent = 0;
    int lastSystemStatusFlag = 0;
    int lastBatteryLifeTime = 0;
    int lastBatteryFullLifeTime = 0;


    bqi.BatteryTag = 0;
    bqi.InformationLevel = BatteryInformation;

    DeviceIoControl(hDevice, IOCTL_BATTERY_QUERY_TAG, NULL, 0, &bqi.BatteryTag, sizeof(bqi.BatteryTag), &bytesReturned, NULL);
    DeviceIoControl(hDevice, IOCTL_BATTERY_QUERY_INFORMATION, &bqi, sizeof(bqi), &bi, sizeof(bi), &bytesReturned, NULL);
    CloseHandle(hDevice);

    while (1) {
        GetSystemPowerStatus(&spsPwr);

        if (lastACLineStatus != static_cast<int>(spsPwr.ACLineStatus) ||
            lastBatteryFlag != static_cast<int>(spsPwr.BatteryFlag) ||
            lastBatteryLifePercent != static_cast<int>(spsPwr.BatteryLifePercent) ||
            lastSystemStatusFlag != static_cast<int>(spsPwr.SystemStatusFlag) ||
            lastBatteryLifeTime != static_cast<int>(spsPwr.BatteryLifeTime) ||
            lastBatteryFullLifeTime != static_cast<int>(spsPwr.BatteryFullLifeTime)) {

            system("cls");

            wcout << "DeviceName: " << getDeviceName();
            cout << "\nChemistry: " << bi.Chemistry;
            cout << "\nDesignedCapacity: " << bi.DesignedCapacity;
            cout << "\nFullChargedCapacity: " << bi.FullChargedCapacity;
            cout << "\nAC Status : " << static_cast<int>(spsPwr.ACLineStatus);             //charging 1 yes 0 no
            cout << "\nBattery Status : " << static_cast<int>(spsPwr.BatteryFlag);         //1 Hight 2 Low 4 Critical 8 Charging 128 No buttery 255 unable to read
            cout << "\nBattery Life % : " << static_cast<int>(spsPwr.BatteryLifePercent);  //% battery
            cout << "\nSystem Status Flag : " << static_cast<int>(spsPwr.SystemStatusFlag);//1 Buttery saver on 0 Buttery saver off

            if (static_cast<int>(spsPwr.BatteryLifeTime) == -1) {
                cout << "\nBattery is charging : " << static_cast<int>(spsPwr.BatteryLifeTime);
            }
            else {
                int hours = static_cast<int>(spsPwr.BatteryLifeTime) / 3600;
                int minutes = (static_cast<int>(spsPwr.BatteryLifeTime) - (hours * 3600)) / 60;
                int seconds = static_cast<int>(spsPwr.BatteryLifeTime) - (hours * 3600) - (minutes * 60);
                cout << "\nBattery Life Time : " << hours << "h " << minutes << "m " << seconds << "s";
            }

            if (static_cast<int>(spsPwr.BatteryFullLifeTime) == -1) {
                cout << "\nBattery is charging : " << static_cast<int>(spsPwr.BatteryFullLifeTime);
            }
            else {
                int hours = static_cast<int>(spsPwr.BatteryFullLifeTime) / 3600;
                int minutes = (static_cast<int>(spsPwr.BatteryFullLifeTime) - (hours * 3600)) / 60;
                int seconds = static_cast<int>(spsPwr.BatteryFullLifeTime) - (hours * 3600) - (minutes * 60);
                cout << "\nBattery Full Life Time : " << hours << "h " << minutes << "m " << seconds << "s";
            }
        }

        lastACLineStatus = static_cast<int>(spsPwr.ACLineStatus);
        lastBatteryFlag = static_cast<int>(spsPwr.BatteryFlag);
        lastBatteryLifePercent = static_cast<int>(spsPwr.BatteryLifePercent);
        lastSystemStatusFlag = static_cast<int>(spsPwr.SystemStatusFlag);
        lastBatteryLifeTime = static_cast<int>(spsPwr.BatteryLifeTime);
        lastBatteryFullLifeTime = static_cast<int>(spsPwr.BatteryFullLifeTime);
    }
}