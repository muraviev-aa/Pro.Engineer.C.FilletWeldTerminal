#include <curses.h>
#include "temp_function.h"
#include <stdio.h>

int main(void)
{
    WINDOW *sub1, *a;
    int maxx, maxy;

    initscr();

    // Создание цветовых пар
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_WHITE);     // окно sub1 - базовый белый
    init_pair(2, COLOR_WHITE, COLOR_BLUE);     // окно a - базовый синий

    // Базовое окно терминала
    bkgd(COLOR_PAIR(1));
    refresh();

    // Определяем размеры и положение доп. окон
    getmaxyx(stdscr, maxy, maxx);

    // Создаем доп. окна
    sub1 = subwin(stdscr, maxy - 4, maxx - 2, 3, 1);
    a = subwin(stdscr, LINES - 28, COLS - 2, 1, 1);

    if (sub1 == NULL || a == NULL)
    {
        endwin();
        puts("Unable to create subwindow");
        return (1);
    }
    wbkgd(a, COLOR_PAIR(2));

    draw_table_lines(sub1);       // рисуем таблицу
    table_header_text(sub1);      // заполняем шапку таблицы
    fill_table_text(sub1);        // заполняем таблицу постоянными значениями
    data_entry_dialog(sub1, a);   // работа с окном ввода данных

    wrefresh(sub1);
    wrefresh(a);
    refresh();

    getch();
    endwin();

    return 0;
}
