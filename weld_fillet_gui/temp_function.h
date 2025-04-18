
#ifndef WELD_FILLET_GUI_TEMP_FUNCTION_H
#define WELD_FILLET_GUI_TEMP_FUNCTION_H

#include <gtk/gtk.h>

// Структура под данные подбора катета
typedef struct
{
    gint position;     // порядковый номер расчета
    gint thick_t1;     // толщина первой свариваемой детали
    gint thick_t2;     // толщина второй свариваемой детали
    gint thick_max;    // максимальная толщина
    gdouble max_leg;   // максимальный катет по наименьшей толщине
    gint weld_leg_1;   // катет вар.1
    gint weld_leg_2;   // катет вар.2
} Weld_data;

#endif //WELD_FILLET_GUI_TEMP_FUNCTION_H
