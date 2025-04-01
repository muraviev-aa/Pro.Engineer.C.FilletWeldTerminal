
#ifndef WELD_FILLET_GUI_TEMP_FUNCTION_H
#define WELD_FILLET_GUI_TEMP_FUNCTION_H

#include <gtk/gtk.h>

// Структура под данные подбора катета
typedef struct
{
    char *position;
    gint thick_t1;
    gint thick_t2;
    const char *weld_leg_1;
    const char *weld_leg_2;
} Weld_data;

#endif //WELD_FILLET_GUI_TEMP_FUNCTION_H
