#ifndef WELD_FILLET_TERMINAL_TEMP_FUNCTION_H
#define WELD_FILLET_TERMINAL_TEMP_FUNCTION_H

#include <curses.h>

// Создаем таблицу
void draw_table_lines(WINDOW *sub1);

// Заполняем шапку таблицы
void table_header_text(WINDOW *sub1);

// Заполняем таблицу постоянными значениями
void fill_table_text(WINDOW *sub1);

// Работа с окном ввода данных
void data_entry_dialog(WINDOW *sub1, WINDOW *a);

// Удаление строки
void delete_char(WINDOW *w, int row, int column, int count_ch);

// Вывод результата
void output_result(WINDOW *sub1, int thick_first_part, int thick_second_part);

// Обработка не предусмотренных таблицей значений
void not_intend_values(WINDOW *sub1, int thick_first_part, int thick_second_part);

// Подбор катета для толщин 4-5
void from_thick_4_to_5(WINDOW *sub1, int thick_first_part, int thick_second_part);

#endif //WELD_FILLET_TERMINAL_TEMP_FUNCTION_H
