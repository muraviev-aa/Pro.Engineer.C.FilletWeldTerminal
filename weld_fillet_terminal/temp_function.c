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

    // Левая вертикальная линия
    for (int i = 2; i < 7; i++)
    {
        wmove(sub1, i, 1);
        waddch(sub1, ACS_VLINE); // вертикальная линия
    }
    wmove(sub1, 4, 1);
    waddch(sub1, ACS_LTEE); // левый разделитель
    for (int i = 7; i < 25; i++)
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
    waddch(sub1, ACS_RTEE); // правый разделитель
    for (int i = 7; i < 25; i++)
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
    for (int i = 5; i < 25; i++)
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
    for (int i = 5; i < 25; i++)
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