
#ifndef WELD_FILLET_GUI_TEMP_FUNCTION_H
#define WELD_FILLET_GUI_TEMP_FUNCTION_H

#include <gtk/gtk.h>

// Структура под данные подбора катета
typedef struct
{
    gint position;
    const char *thick_t1;   // толщина первой свариваемой детали
    const char *thick_t2;   // толщина второй свариваемой детали
    const char *weld_leg_1; // катет вар.1
    const char *weld_leg_2; // катет вар.2
} Weld_data;

#endif //WELD_FILLET_GUI_TEMP_FUNCTION_H
