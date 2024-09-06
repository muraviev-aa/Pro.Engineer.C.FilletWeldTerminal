cmake_minimum_required(VERSION 3.28)
project(weld_fillet_terminal C)

set(CMAKE_C_STANDARD 11)
set(CURSES_INCLUDE_PATH "C:/tools/PDCurses-3.9")
set(CURSES_LIBRARY "C:/tools/PDCurses-3.9/wincon/pdcurses.a")

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIR} )

set(CMAKE_C_STANDARD 11)

add_executable(weld_fillet_terminal main.c
        temp_function.h
        temp_function.c)

target_link_libraries( weld_fillet_terminal ${CURSES_LIBRARIES} )
