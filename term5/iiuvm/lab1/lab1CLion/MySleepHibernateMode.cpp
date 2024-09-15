#include "MySleepHibernateMode.h"

void MySleepHibernateMode::enterSleepMode() {
    SetSuspendState(FALSE, FALSE, FALSE);
}

void MySleepHibernateMode::enterHibernateMode() {
    SetSuspendState(TRUE, FALSE, FALSE);
}

bool MySleepHibernateMode::hasConsoleUpdated(CONSOLE_SCREEN_BUFFER_INFO& lastInfo) {
    CONSOLE_SCREEN_BUFFER_INFO currentInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!GetConsoleScreenBufferInfo(hConsole, &currentInfo)) {
        std::cerr << "Failed to get console buffer info." << std::endl;
        return false;
    }

    // Check if the console has been cleared by comparing cursor position and window size
    bool cleared = (currentInfo.dwCursorPosition.X == 0 && currentInfo.dwCursorPosition.Y == 0) &&
                   (currentInfo.dwSize.X == lastInfo.dwSize.X && currentInfo.dwSize.Y == lastInfo.dwSize.Y);

    lastInfo = currentInfo; // Update the last known info
    return cleared;
}

void MySleepHibernateMode::rewrite() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;

    coord.X = 0;
    coord.Y = 11;

    SetConsoleCursorPosition(hConsole, coord);
    std::cout << "Enter '--sleep' for Sleep Mode, '--hibernate' for Hibernate Mode:                          " << std::flush;

    coord.X = 66;
    coord.Y = 11;

    SetConsoleCursorPosition(hConsole, coord);
}

void MySleepHibernateMode::enterMode() {
    int count = 0;

    CONSOLE_SCREEN_BUFFER_INFO lastInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &lastInfo);

    while (1) {
        if (hasConsoleUpdated(lastInfo))
        {
            Sleep(100);
            std::cout << "\n\nEnter '--sleep' for Sleep Mode, '--hibernate' for Hibernate Mode: ";
        }
    }
}

void MySleepHibernateMode::handleCommands() {
    std::string input;

    while (1) {
        getline(std::cin, input);
        rewrite();

        if (input == "--sleep") {
            enterSleepMode();
        }
        else if (input == "--hibernate") {
            enterHibernateMode();
        }
    }
}