#include "BatteryInfo.h"

void BatteryInfo::displayInfo() {
    SYSTEM_POWER_STATUS powerStatus;
    if (GetSystemPowerStatus(&powerStatus)) {
        displayClearStrings();
        displayIsCharging(powerStatus);
        displayIsBatterySaverOn(powerStatus);
        displayBatteryTime(powerStatus, true);
        displayBatteryTime(powerStatus, false);
        displayBatteryLevel(powerStatus);
        displayBatteryType();
        displayOptions();
    }
}

void BatteryInfo::displayClearStrings() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void BatteryInfo::displayIsCharging(SYSTEM_POWER_STATUS powerStatus) {
    printf("Is battery changing: %s\n", (powerStatus.ACLineStatus ? "yes" : "no"));
}

void BatteryInfo::displayBatteryLevel(SYSTEM_POWER_STATUS powerStatus) {
    printf("Battery level: %d\n", powerStatus.BatteryLifePercent);
}

void BatteryInfo::displayIsBatterySaverOn(SYSTEM_POWER_STATUS powerStatus) {
    printf("Battery saving mode: %s\n", static_cast<bool>(powerStatus.SystemStatusFlag) ? "yes" : "no");
}

void BatteryInfo::displayBatteryType() {

    /// Получаем список устройств класса батарей
    // DIGCF_PRESENT - выбирает только присутствующие устройства, DIGCF_DEVICEINTERFACE - выбирает интерфейсы устройства
    //enumenator 0 значит, мы не указываем конкретный экземпляр устройства, и функция будет работать для всех устройств указанного класса
    //hwndParent указатель на окно, которое может использоваться в диалогах, отображаемых функцией. Здесь он равен 0, что означает, что окно не требуется и никакие взаимодействия с пользователем через диалоги не планируются.
    HDEVINFO hdev = SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    /// Инициализация структуры данных для интерфейса устройства
    SP_DEVICE_INTERFACE_DATA did = { 0 }; /// Обнуление всех полей структуры
    did.cbSize = sizeof(did);  /// Устанавливаем размер структуры, необходим для корректного вызова API

    /// Получаем первый интерфейс устройства, соответствующий батарее
    // GUID_DEVCLASS_BATTERY - идентификатор класса батареи, 0 - индекс первого устройства
    if (!SetupDiEnumDeviceInterfaces(hdev, 0, &GUID_DEVCLASS_BATTERY, 0, &did))
        return;

    /// Определяем размер буфера, который потребуется для получения подробной информации об интерфейсе
    DWORD cbRequired = 0;
    /// Второй и третий аргументы - это NULL, так как мы пока только запрашиваем размер
    SetupDiGetDeviceInterfaceDetail(hdev, &did, 0, 0, &cbRequired, 0);
    /// Проверяем, что не ошибка недостаточного буфера (ERROR_INSUFFICIENT_BUFFER), иначе выходим
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        SetupDiDestroyDeviceInfoList(hdev);  // Удаляем список информации об устройстве
        return;
    }

    /// Выделяем память для структуры с подробной информацией об интерфейсе устройства
    PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, cbRequired);
    // LPTR - выделяет память и инициализирует нулями
    pdidd->cbSize = sizeof(*pdidd); /// Устанавливаем размер структуры для правильного вызова API

    /// Получаем подробную информацию об интерфейсе устройства
    //hdev — дескриптор набора устройств, полученный с помощью SetupDiGetClassDevs.
    //&did — указатель на структуру SP_DEVICE_INTERFACE_DATA, содержащую информацию о конкретном интерфейсе устройства.
    //pdidd — указатель на структуру SP_DEVICE_INTERFACE_DETAIL_DATA, содержащую путь к устройству (буфер должен быть выделен заранее).
    //cbRequired — размер буфера pdidd.
    //&cbRequired — указатель на переменную для хранения фактического размера данных.
    //0 — указатель на SP_DEVINFO_DATA (здесь равен 0, так как информация об устройстве не требуется).
    if (!SetupDiGetDeviceInterfaceDetail(hdev, &did, pdidd, cbRequired, &cbRequired, 0)) {
        LocalFree(pdidd);  /// Освобождаем память, если произошла ошибка
        SetupDiDestroyDeviceInfoList(hdev);  /// Удаляем список информации об устройстве
        return;
    }

    /// Открываем файл устройства для чтения/записи
    HANDLE hBattery = CreateFile(
            pdidd->DevicePath,          // Путь к устройству, полученный из `pdidd`
            GENERIC_READ | GENERIC_WRITE, // Доступ для чтения и записи
            FILE_SHARE_READ | FILE_SHARE_WRITE, // Разрешаем другим процессам читать и записывать в файл одновременно
            NULL,                       // Без атрибутов безопасности (по умолчанию)
            OPEN_EXISTING,              // Открыть только существующий файл или устройство
            FILE_ATTRIBUTE_NORMAL,      // Атрибуты файла, указывающие на обычный файл
            NULL                        // Файл-шаблон не используется
    );
    LocalFree(pdidd);  // Освобождаем память, так как она больше не нужна
    SetupDiDestroyDeviceInfoList(hdev);  // Удаляем список информации об устройстве

    // Если не удалось открыть устройство, выходим
    if (INVALID_HANDLE_VALUE == hBattery) {
        return;
    }

    // Запрос информации о батарее
    BATTERY_QUERY_INFORMATION bqi = { 0 }; // Обнуление всех полей структуры

    /// Запрашиваем тег батареи. Если запрос не удался или тег равен 0, выходим
    if (!(DeviceIoControl(
                hBattery,                    // Дескриптор устройства, полученный с помощью `CreateFile`
                IOCTL_BATTERY_QUERY_TAG,     // Управляющий код для запроса тега батареи
                0,                                // Указатель на входные данные, здесь не требуется
                0,                              // Размер входных данных, равен 0, так как входные данные не требуются
                &bqi.BatteryTag,                 // Указатель на выходные данные — здесь записывается тег батареи
                sizeof(bqi.BatteryTag),        // Размер выходных данных, равен размеру поля `BatteryTag`
                0,                           // Указатель на переменную для записи количества байт, переданных в `lpOutBuffer` (здесь не требуется)
                0                            // Перекрывающая структура (`OVERLAPPED`), используется только для асинхронного ввода-вывода (здесь не используется)
        ) && bqi.BatteryTag))
        return;

    // Получаем основную информацию о батарее
    BATTERY_INFORMATION bi = { 0 }; // Обнуление всех полей структуры
    bqi.InformationLevel = BatteryInformation; // Устанавливаем уровень информации, которую хотим получить

    // Запрашиваем информацию о батарее. Если запрос не удался, выходим
    if (!DeviceIoControl(
                hBattery,                    // Дескриптор устройства, полученный с помощью `CreateFile`
                IOCTL_BATTERY_QUERY_INFORMATION, // Управляющий код для запроса информации о батарее
                &bqi,                        // Указатель на структуру `BATTERY_QUERY_INFORMATION`, содержащую параметры запроса
                sizeof(bqi),                 // Размер входных данных, равен размеру структуры `bqi`
                &bi,                         // Указатель на структуру `BATTERY_INFORMATION`, в которую будет записана информация о батарее
                sizeof(bi),                  // Размер выходных данных, равен размеру структуры `bi`
                0,                           // Указатель на переменную для записи количества байт, переданных в `lpOutBuffer` (здесь не используется)
                0                            // Перекрывающая структура (`OVERLAPPED`), используется для асинхронного ввода-вывода (здесь не используется)
        ))
        return;

    // Проверяем, является ли устройство системной батареей, а также является ли оно кратковременным (например, буферной батареей)
    // BATTERY_SYSTEM_BATTERY - указывает, что устройство является основной батареей, BATTERY_IS_SHORT_TERM - указывает на временную батарею
    if (!(bi.Capabilities & BATTERY_SYSTEM_BATTERY) && (bi.Capabilities & BATTERY_IS_SHORT_TERM))
        return;

    // Выводим тип батареи (например, "Li-Ion") на экран
    // bi.Chemistry содержит 4-символьный код, представляющий тип батареи
    printf("Battery type: %s\n", string(bi.Chemistry, bi.Chemistry + 4).c_str());
}

void BatteryInfo::displayBatteryTime(SYSTEM_POWER_STATUS powerStatus, bool isFullBatteryTime) {
    string fullTimeStr;

    if (powerStatus.BatteryLifeTime == -1) {
        fullTimeStr = "N/A";
    } else if (isFullBatteryTime) {
        fullTimeStr = mapSecondsTimeIntoString(static_cast<int>(powerStatus.BatteryLifeTime)
                                               * 100 / static_cast<int>(powerStatus.BatteryLifePercent));
    } else {
        fullTimeStr = mapSecondsTimeIntoString(static_cast<int>(powerStatus.BatteryLifeTime));
    }
    printf("%s: %s\n",
           (isFullBatteryTime ? "Current battery time" : "Full battery time"), fullTimeStr.c_str());
}

string BatteryInfo::mapSecondsTimeIntoString(int timeInSeconds) {
    int timeInMinutes = timeInSeconds / 60;
    timeInSeconds -= timeInMinutes * 60;
    int timeInHours = timeInMinutes / 60;
    timeInMinutes -= timeInHours * 60;

    return to_string(timeInHours) + "h " +
                       to_string(timeInMinutes) + "m " + to_string(timeInSeconds) + "s ";
}

void BatteryInfo::displayOptions() {
    printf("\n 1 Sleep mode\n 2 Hibernation mode\n 3 Exit\n");
}