
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

// Виджеты окон
typedef struct
{
    GtkWidget *fixed_all;
    GtkWidget *alig_1;
    GtkWidget *fixed_thick;
    GtkWidget *label_1;
    GtkWidget *entry_t1;
    GtkWidget *entry_t2;
    GtkWidget *label_t1;
    GtkWidget *label_t2;
    GtkWidget *button_calc;
    GtkWidget *alig_2;
    GtkWidget *fixed_tabl;
    GtkWidget *label_2_1;
    GtkWidget *label_2_2;
    GtkWidget *label_2_3;
    GtkWidget *label_2_4;
    GtkWidget *label_2_5;
    GtkWidget *label_2_6;
    GtkWidget *label_2_7;
    GtkWidget *separator_1;
    GtkWidget *separator_2;
    GtkWidget *separator_3;
    GtkWidget *separator_4;
    GtkWidget *separator_5;
    GtkWidget *separator_6;
    GtkWidget *separator_7;
    GtkWidget *separator_8;
    GtkWidget *separator_9;
    GtkWidget *separator_10;
    GtkWidget *separator_11;
    GtkWidget *alig_3;
    GtkWidget *label_name;
    GtkWidget *label_text;
    GtkWidget *katet_tabl1;
    GtkWidget *label_result1;
    GtkWidget *katet_tabl2;
    GtkWidget *label_result2;
    GtkWidget *fixed_file;
    GtkWidget *button_new;
    GtkWidget *button_new_data;
    GtkWidget *label_count;
    GtkWidget *button_file;
    GtkWidget *label_create_file;
    GtkWidget *label_without_frame;
    GtkWidget *label_frame;
    GtkWidget *button_form;
    GtkWidget *entry_name;
    GtkWidget *frame_thick;
    GtkWidget *frame_tabl;
    GtkWidget *frame_file;
    GtkWidget *radiobutton_1;
    GtkWidget *radiobutton_2;
    GtkWidget *radiobutton_3;
    GtkWidget *radiobutton_1_2;
    GtkWidget *radiobutton_1_3;
    GtkWidget *radiobutton_2_3;
    GtkWidget *radiobutton_1_2_3;
    GtkWidget *radio_without_frame;
    GtkWidget *radio_frame;
    GtkWidget *label_forma;
    GtkWidget *fixed_forma2;
    GtkWidget *image_forma2;
    GtkWidget *tree_forma2;
    GtkWidget *entry_code;
    GtkWidget *entry_developer;
    GtkWidget *entry_inspector;
    GtkWidget *entry_norm_contr;
    GtkWidget *entry_approver;
    GtkWidget *entry_name1;
    GtkWidget *entry_name2;
    GtkWidget *entry_name3;
    GtkWidget *entry_sheet;
    GtkWidget *entry_sheets;
    GtkWidget *entry_organization;
    GtkWidget *record_button;
} WidgetContainer;

// Столбцы таблицы БД
enum
{
    COL_ID,
    COL_PROJECT_NAME1,
    COL_PROJECT_NAME2,
    COL_PROJECT_NAME3,
    COL_PROJECT_CODE,
    COL_PROJECT_SHEET,
    COL_PROJECT_SHEETS,
    COL_DEVELOPER,
    COL_INSPECTOR,
    COL_NORM_CONTR,
    COL_APPROVER,
    NUM_COLS
};

// Работаем с *.css файлом
void apply_css(void);

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

// Управление состоянием активности нескольких виджетов
void set_widgets_sensitive(GtkWidget **widgets, int count, gboolean sensitive);

// Универсальное получение виджетов
void get_and_check_widget(GtkBuilder *erector, const char *widget_name, GtkWidget **widget);

// Обработчик события кнопки button_calc
G_MODULE_EXPORT void on_button_calc_clicked(GtkButton *b);

#endif //WELD_FILLET_GUI_TEMP_FUNCTION_H
