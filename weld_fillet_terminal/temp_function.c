#include "temp_function.h"
#include <stdlib.h>

void draw_table_lines(WINDOW *sub1)
{
    // Верхняя горизонтальная линия
    wmove(sub1, 1, 1);
    waddch(sub1, ACS_ULCORNER); // верхний левый угол
    for (int i = 2; i < 60; i++)
    {
        wmove(sub1, 1, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    wmove(sub1, 1, 60);
    waddch(sub1, ACS_TTEE);  // начало средней разделит. линии 1
    for (int i = 61; i < 90; i++)
    {
        wmove(sub1, 1, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    wmove(sub1, 1, 90);
    waddch(sub1, ACS_TTEE);  // начало средней разделит. линии 2
    for (int i = 91; i < 116; i++)
    {
        wmove(sub1, 1, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    wmove(sub1, 1, 116);
    waddch(sub1, ACS_URCORNER); // верхний правый угол

    // Средняя горизонтальная линия
    for (int i = 2; i < 60; i++)
    {
        wmove(sub1, 4, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 61; i < 90; i++)
    {
        wmove(sub1, 4, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 91; i < 116; i++)
    {
        wmove(sub1, 4, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }

    // Третья горизонтальная линия (разделители 1 и 3 столбцов)
    for (int i = 1; i < 60; i++)
    {
        wmove(sub1, 14, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия (1 столбец)
    }
    for (int i = 91; i < 116; i++)
    {
        wmove(sub1, 14, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия (3 столбец)
    }

    // Левая вертикальная линия
    for (int i = 2; i < 7; i++)
    {
        wmove(sub1, i, 1);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }
    wmove(sub1, 4, 1);
    waddch(sub1, ACS_LTEE); // левый разделитель
    for (int i = 7; i < 14; i++)
    {
        wmove(sub1, i, 1);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }
    wmove(sub1, 14, 1);
    waddch(sub1, ACS_LTEE);  // разделитель 1 столбца
    for (int i = 15; i < 25; i++)
    {
        wmove(sub1, i, 1);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }

    // Правая вертикальная линия
    for (int i = 2; i < 7; i++)
    {
        wmove(sub1, i, 116);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }
    wmove(sub1, 4, 116);
    waddch(sub1, ACS_RTEE); // правый верхний разделитель
    for (int i = 7; i < 14; i++)
    {
        wmove(sub1, i, 116);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }
    wmove(sub1, 14, 116);
    waddch(sub1, ACS_RTEE); // разделитель 3 столбца
    for (int i = 15; i < 25; i++)
    {
        wmove(sub1, i, 116);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }

    // Средняя вертикальная линия 2
    for (int i = 2; i < 4; i++)
    {
        wmove(sub1, i, 90);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }
    wmove(sub1, 4, 60);
    waddch(sub1, ACS_PLUS);  // крест 1 средней гор. линии таблицы
    wmove(sub1, 4, 90);
    waddch(sub1, ACS_PLUS);  // крест 2 средней гор. линии таблицы
    for (int i = 5; i < 14; i++)
    {
        wmove(sub1, i, 90);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }
    wmove(sub1, 14, 90);
    waddch(sub1, ACS_LTEE);  // разделитель 3 столбца
    for (int i = 15; i < 25; i++)
    {
        wmove(sub1, i, 90);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }

    // Средняя вертикальная линия 1
    for (int i = 2; i < 4; i++)
    {
        wmove(sub1, i, 60);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }
    for (int i = 5; i < 14; i++)
    {
        wmove(sub1, i, 60);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }
    wmove(sub1, 14, 60);
    waddch(sub1, ACS_RTEE);  // разделитель 1 столбца
    for (int i = 15; i < 25; i++)
    {
        wmove(sub1, i, 60);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }

    // Нижняя горизонтальная линия
    wmove(sub1, 25, 1);
    waddch(sub1, ACS_LLCORNER); // левый нижний угол
    for (int i = 2; i < 60; i++)
    {
        wmove(sub1, 25, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 61; i < 90; i++)
    {
        wmove(sub1, 25, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    wmove(sub1, 25, 60);
    waddch(sub1, ACS_BTEE);  // начало средней разделит. линии 1
    wmove(sub1, 25, 90);
    waddch(sub1, ACS_BTEE);  // начало средней разделит. линии 2
    for (int i = 91; i < 116; i++)
    {
        wmove(sub1, 25, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    wmove(sub1, 25, 116);
    waddch(sub1, ACS_LRCORNER);// правый нижний угол
}

void table_header_text(WINDOW *sub1)
{
    // Шапка первый столбец
    wmove(sub1, 2, 26);
    wprintw(sub1, "Connection");
    wmove(sub1, 3, 29);
    wprintw(sub1, "type");
    // Шапка второй столбец
    wmove(sub1, 2, 71);
    wprintw(sub1, "Type of");
    wmove(sub1, 3, 71);
    wprintw(sub1, "welding");
    // Шапка третий столбец
    wmove(sub1, 2, 100);
    wprintw(sub1, "Minimum");
    wmove(sub1, 3, 100);
    wprintw(sub1, "weld leg");
}

void fill_table_text(WINDOW *sub1)
{
    // Название таблицы
    wmove(sub1, 0, 92);
    waddstr(sub1, "Tabl.38 SP 16.13330.2017");
    /* 1 строка первого столбца таблицы */
    wmove(sub1, 8, 18);
    wprintw(sub1, "T-shaped with double-sided");
    wmove(sub1, 9, 25);
    wprintw(sub1, "fillet welds;");
    wmove(sub1, 10, 24);
    wprintw(sub1, "lap and corner");
    /* 2 строка первого столбца таблицы */
    wmove(sub1, 18, 21);
    wprintw(sub1, "Corner and t-shaped");
    wmove(sub1, 19, 24);
    wprintw(sub1, "with one-sided");
    wmove(sub1, 20, 25);
    wprintw(sub1, "fillet welds");
    /* 2 столбец таблицы */
    wmove(sub1, 13, 71);
    wprintw(sub1, "Manual arc,");
    wmove(sub1, 14, 69);
    wprintw(sub1, "automatic and");
    wmove(sub1, 15, 71);
    wprintw(sub1, "mechanized");
    wrefresh(sub1);
}

void data_entry_dialog(WINDOW *sub1, WINDOW *a)
{
    int thick_first_part;
    int thick_second_part;
    char info_thick_first_part[3];
    char info_thick_second_part[3];
    char ch;
    // Ввод толщины первой детали
    do
    {
        wclear(a);
        wbkgd(a, COLOR_PAIR(3));
        wmove(a, 0, 2);
        waddstr(a, "1.Enter the thickness of the first part (mm): ");
        wgetnstr(a, info_thick_first_part, 2);
        thick_first_part = atoi(info_thick_first_part);
        wmove(a, 1, 4);
        wprintw(a,
                "Thickness of the first part is %d mm. If the information is correct then press 'y', if incorrect press 'n' ",
                thick_first_part);
        ch = (char) wgetch(a);
        if (ch == 'n')
            delete_char(a, 1, 1, 95);
    } while (ch != 'y');
    // Вывод результата ввода толщины первого элемента
    wmove(sub1, 0, 2);
    wprintw(sub1, "Data: thickness of the first part is %d mm,", thick_first_part);
    wrefresh(sub1);
    // Ввод толщины второй детали
    do
    {
        wclear(a);
        wbkgd(a, COLOR_PAIR(4));
        wmove(a, 0, 2);
        waddstr(a, "2.Enter the thickness of the second part (mm): ");
        wgetnstr(a, info_thick_second_part, 2);
        thick_second_part = atoi(info_thick_second_part);
        wmove(a, 1, 4);
        wprintw(a,
                "Thickness of the second part is %d mm. If the information is correct then press 'y', if incorrect press 'n' ",
                thick_second_part);
        ch = (char) wgetch(a);
        if (ch == 'n')
            delete_char(a, 1, 1, 95);
    } while (ch != 'y');
    // Вывод результата ввода толщины второго элемента
    wmove(sub1, 0, 45);
    wprintw(sub1, " second part is %d mm", thick_second_part);
    wrefresh(sub1);
    if (thick_first_part > thick_second_part && (0.6 * thick_first_part) > thick_second_part)
    {
        wbkgd(sub1, COLOR_PAIR(5));
        wmove(sub1, 8, 96);
        wprintw(sub1, "by calculation,");
        wmove(sub1, 10, 96);
        wprintw(sub1, "but no more %.1f", 1.2 * thick_second_part);
        wmove(sub1, 18, 96);
        wprintw(sub1, "by calculation,");
        wmove(sub1, 20, 96);
        wprintw(sub1, "but no more %.1f", 1.2 * thick_second_part);
        wrefresh(sub1);
    } else if (thick_first_part < thick_second_part && thick_first_part < (0.6 * thick_second_part))
    {
        wbkgd(sub1, COLOR_PAIR(5));
        wmove(sub1, 8, 96);
        wprintw(sub1, "by calculation,");
        wmove(sub1, 10, 96);
        wprintw(sub1, "but no more %.1f", 1.2 * thick_first_part);
        wmove(sub1, 18, 96);
        wprintw(sub1, "by calculation,");
        wmove(sub1, 20, 96);
        wprintw(sub1, "but no more %.1f", 1.2 * thick_first_part);
        wrefresh(sub1);
    } else
    {
        wmove(sub1, 8, 100);
        wprintw(sub1, "TEST_1");
        wmove(sub1, 9, 100);
        wprintw(sub1, "TEST_2");
    }
}

void delete_char(WINDOW *w, int row, int column, int count_ch)
{
    for (int i = 0; i < count_ch; i++)
    {
        wmove(w, row, column++);
        waddrawch(w, ' ');
        wrefresh(w);
    }
}