
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

// Работаем с *.css файлом
void working_css_file();

// Определение минимального катета сварного шва
void size_weld();

// Работа с датой
void work_dates(cairo_t *cr);

// Сбор данных для печати
void data_collection(cairo_t *cr, GSList *list, gint shift_value, gint serial_number);

// Печать таблицы
void create_table(cairo_t *cr, gint shift_value);

// Вставка *.png выполнения условия
void insert_png(cairo_t *cr, GSList *list, gint shift_value, gint serial_number);

// Ввод текста слева
void set_widget_alignment(GtkEntry *entry);

// Получение виджетов из builder
GtkWidget *get_widget(GtkBuilder *builder, const char *name);

// Управление состоянием нескольких виджетов
void set_widgets_sensitive(GtkWidget **widgets, int count, gboolean sensitive);

// Обработчик события кнопки button_calc
G_MODULE_EXPORT void on_button_calc_clicked(GtkButton *b);

#endif //WELD_FILLET_GUI_TEMP_FUNCTION_H
