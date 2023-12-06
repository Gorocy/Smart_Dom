cmake_minimum_required(VERSION 3.12)
project(YourProjectName)

# Ustawienie ścieżki do pliku toolchain od vcpkg
set(CMAKE_TOOLCHAIN_FILE "./opt/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Ustawienie standardu C++
set(CMAKE_CXX_STANDARD 11)

# Ustawienie CMAKE_PREFIX_PATH na katalog z asio (zmień na swoją ścieżkę)
set(CMAKE_PREFIX_PATH "./opt/vcpkg/installed/x64-linux/share/boost-asio" ${CMAKE_PREFIX_PATH})

# Pobranie listy pakietów z vcpkg (dodaj asio do tej listy)
find_package(Boost REQUIRED COMPONENTS system thread regex)

# Dodanie źródeł projektu
add_executable(serwerbin
        main.cpp
        smart_home_logic.cpp
        door.cpp
        gate_and_garage.cpp
        pet_feeder.cpp
        roller_shutter.cpp
        thermostat.cpp
        monitoring.cpp)


# Podłączenie bibliotek asio do twojego projektu
target_link_libraries(serwerbin PRIVATE Boost::boost Boost::system Boost::thread Boost::regex)

