#include "ISA_IO.h"
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

struct VendorInfo {
    std::string vendorName;
    std::map<unsigned int, std::string> devices; // Map для хранения Device ID -> Device Name
};

std::map<unsigned int, VendorInfo> pciDatabase;

void search(unsigned int vendorId, unsigned int deviceId) {
    auto vendorIt = pciDatabase.find(vendorId);
    if (vendorIt != pciDatabase.end()) {
        std::cout << std::left << std::setw(35) << vendorIt->second.vendorName;
        auto deviceIt = vendorIt->second.devices.find(deviceId);
        if (deviceIt != vendorIt->second.devices.end()) {
            std::cout << std::left << std::setw(30) << deviceIt->second << std::endl;
        }
        else {
            std::cout << "Device ID не найдено для данного Vendor ID." << std::endl;
        }
    }
    else {
        std::cout << "Vendor ID не найдено." << std::endl;
    }
}

int parcing() {
    std::ifstream pciFile("pci.ids");
    if (!pciFile.is_open()) {
        std::cerr << "Не удалось открыть файл pci.ids!" << std::endl;
        return 1;
    }
    std::string line;
    unsigned int currentVendorId = 0; // Переменная для хранения текущего Vendor ID

    // Чтение файла построчно
    while (std::getline(pciFile, line)) {
        // Игнорируем комментарии
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Проверяем, содержит ли строка Vendor ID (без отступа)
        if (line[0] != '\t') {
            std::istringstream ss(line);
            unsigned int vendorId;
            std::string vendorName;

            // Читаем Vendor ID и имя
            ss >> std::hex >> vendorId; // Читаем Vendor ID в шестнадцатеричном формате
            std::getline(ss, vendorName); // Читаем имя вендора (оставшаяся часть строки)
            vendorName.erase(0, vendorName.find_first_not_of(" \t")); // Удаляем лишние пробелы и табуляции

            // Сохраняем Vendor ID и имя
            pciDatabase[vendorId] = { vendorName, {} };
            currentVendorId = vendorId;
        }
            // Если строка начинается с табуляции, то это Device ID
        else if (currentVendorId != 0) {
            std::istringstream ss(line);
            unsigned int deviceId;
            std::string deviceName;

            // Читаем Device ID и название устройства
            ss >> std::hex >> deviceId; // Читаем Device ID в шестнадцатеричном формате
            std::getline(ss, deviceName); // Читаем название устройства
            deviceName.erase(0, deviceName.find_first_not_of(" \t")); // Удаляем лишние пробелы и табуляции

            // Сохраняем Device ID и его название для текущего Vendor ID
            pciDatabase[currentVendorId].devices[deviceId] = deviceName;
        }
    }

    // Закрываем файл
    pciFile.close();
    return 0;
}

int getDevices() {
    unsigned int count = 1;
    HANDLE hDevice = CreateFileW(
            L"\\\\?\\ISA-IO",  // ваш путь к устройству
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
    );

    if (hDevice == INVALID_HANDLE_VALUE) {
        std::cout << "Не удалось открыть устройство!" << std::endl;
        return 1;
    }

    // Перебор всех шин, устройств и функций
    for (unsigned int bus = 0; bus < 256; bus++) {
        for (unsigned int device = 0; device < 32; device++) {
            for (unsigned int func = 0; func < 8; func++) {
                // Формируем адрес в формате для порта 0xCF8
                IsaIoRequestWrite request_write;

                // Формируем запрос для PCI Configuration Address
                request_write.port = 0xCF8;
                request_write.value = (1 << 31) | (bus << 16) | (device << 11) | (func << 8);

                // Записываем в порт 0xCF8
                DeviceIoControl(hDevice, IOCTL_ISA_WRITE_32, &request_write, sizeof(request_write), NULL, 0, NULL, NULL);


                // Читаем данные с порта 0xCFC (32 бита)
                IsaIoRequestRead request_read;
                request_read.port = 0xCFC;
                IsaIoResponse response = { 0 };
                DeviceIoControl(hDevice, IOCTL_ISA_READ_32, &request_read, sizeof(request_read), &response, sizeof(response), NULL, NULL);

                unsigned int result = response.value;

                // Извлекаем Device ID и Vendor ID
                unsigned int vendorId = result & 0xFFFF;         // Нижние 16 бит
                unsigned int deviceId = (result >> 16) & 0xFFFF; // Верхние 16 бит

                // Проверяем, если Vendor ID равен 0xFFFF, значит устройство отсутствует
                if (vendorId != 0xFFFF) {
                    std::cout << std::left
                              << std::setw(8) << std::dec << count++   // Номер строки
                              << std::setw(12) << std::hex << std::uppercase << vendorId  // Vendor ID
                              << std::setw(12) << std::hex << std::uppercase << deviceId;
                    search(vendorId, deviceId);
                    std::cout << std::endl;
                }

                // Если func == 0 и это не многофункциональное устройство, можно прекратить поиск других функций
                if (func == 0) {
                    IsaIoRequestWrite request_write_multi;
                    request_write_multi.port = 0xCF8;
                    request_write_multi.value = (1 << 31) | (bus << 16) | (device << 11) | (func << 8); // Offset для Header Type

                    DeviceIoControl(hDevice, IOCTL_ISA_WRITE_32, &request_write_multi, sizeof(request_write_multi), NULL, 0, NULL, NULL);

                    IsaIoRequestRead request_read_multi;
                    request_read_multi.port = 0xCFC;
                    IsaIoResponse response_multi = { 0 };
                    DeviceIoControl(hDevice, IOCTL_ISA_READ_32, &request_read_multi, sizeof(request_read_multi), &response_multi, sizeof(response_multi), NULL, NULL);

                    unsigned int headerType = (response_multi.value >> 16) & 0xFF;

                    // Если бит 7 в Header Type равен 0, то это однофункциональное устройство
                    if ((headerType & 0x80) == 0) {
                        break;
                    }
                }
            }
        }
    }

    CloseHandle(hDevice);
    return 0;
}

int main() {
    setlocale(0, "");

    if (parcing())
        return 1;

    std::cout << std::left
              << std::setw(8) << "Number"
              << std::setw(12) << "Vendor ID"
              << std::setw(12) << "Device ID"
              << std::setw(35) << "Vendor Name"
              << std::setw(30) << "Device Name"
              << std::endl;
    std::cout << std::string(92, '-') << std::endl;

    if (getDevices())
        return 1;

    unsigned int a = (0x0C & 0xFC);
    std::cout << a << std::endl;
    return 0;
}
