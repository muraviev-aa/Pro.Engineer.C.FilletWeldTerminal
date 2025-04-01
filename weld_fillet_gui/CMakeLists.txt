cmake_minimum_required(VERSION 3.28)
project(weld_fillet_gui C)

set(CMAKE_C_STANDARD 11)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
pkg_check_modules(Cairo REQUIRED cairo)
#pkg_check_modules(Cairo REQUIRED IMPORTED_TARGET cairo)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
link_libraries(${GTK_LIBRARIES})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(weld_fillet_gui main.c
        temp_function.c
        temp_function.h)
