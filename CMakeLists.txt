cmake_minimum_required(VERSION 3.9.0)
project(webbrowser)

#cmake_policy(SET CMP0084 NEW)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Xml
)

add_compile_options(-std=c++17 -g)

include_directories(parser)

add_subdirectory(parser)
add_subdirectory(src)

