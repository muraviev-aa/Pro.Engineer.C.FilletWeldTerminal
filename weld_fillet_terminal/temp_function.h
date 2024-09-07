#ifndef WELD_FILLET_TERMINAL_TEMP_FUNCTION_H
#define WELD_FILLET_TERMINAL_TEMP_FUNCTION_H

#include <curses.h>

// Создаем таблицу
void draw_table_lines(WINDOW *sub1);

// Заполняем шапку таблицы
void table_header_text(WINDOW *sub1);

// Заполняем таблицу
void fill_table_text(WINDOW *sub1);

#endif //WELD_FILLET_TERMINAL_TEMP_FUNCTION_H
