cmake_minimum_required(VERSION 3.28)
project(lab1)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)

# Добавляем исполняемый файл
add_executable(lab1
        MySleepHibernateMode.cpp
        MySleepHibernateMode.h
        Battery.cpp
        MyBatteryInformation.cpp
        MyBatteryInformation.h
)

# Линкуем необходимые библиотеки
target_link_libraries(lab1 PRIVATE
        setupapi   # Для работы с SetupAPI
        PowrProf   # Для работы с SetSuspendState
)
