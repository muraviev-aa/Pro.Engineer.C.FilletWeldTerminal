/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * @version 1.0
  * @author Aleksei Muraviev
  * @contact muraviev_aa@yandex.ru
  *
  *  Program for determining the minimum legs of corner welds
  *
  ******************************************************************************
  */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sqlite3.h>
#include <conio.h>
#include <cairo-pdf.h>
#include "temp_function.h"

sqlite3 *db;
GtkBuilder *builder;
GtkWidget *window_main = NULL;
GtkWidget *window_forma2 = NULL;

WidgetContainer widgets; // для хранения всех виджетов
gint t1 = 0; // толщина первой свариваемой детали
gint t2 = 0; // толщина второй свариваемой детали
gint button_click_count = 0;
gchar *str_calc1 = "   по расчету,\nно не более";
gchar str_calc2[4];
gchar *str_calc3;
gchar *str_calc4 = "   по расчету";
GSList *list = NULL; // односвязный список
Weld_data *first = NULL;
Weld_data *second = NULL;
Weld_data *third = NULL;
gint flag_result = 0;
gint flag_frame = 0;

G_MODULE_EXPORT void on_entry_t1_changed(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t2_changed(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t1_insert_text(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t2_insert_text(GtkEntry *e);
G_MODULE_EXPORT void on_entry_name_focus_in_event(GtkEntry *e);
G_MODULE_EXPORT void on_button_new_data_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_new_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_file_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_form_clicked(GtkButton *b);
G_MODULE_EXPORT void on_window_main_destroy(GtkWidget *main_win);
G_MODULE_EXPORT gboolean on_window_forma2_delete_event(GtkWidget *child_win);

void work_widgets();
void writing_data_s_list(gint count_result);

int main(int argc, char **argv)
{
    if (sqlite3_open("resources/forma_2.db", &db))
    {
        g_printerr("Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else
        printf("sqlite3_open\n");

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "resources/weld.glade", NULL))
    {
        g_printerr("Error loading weld.glade file\n");
        return 1;
    }

    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_window_set_title(GTK_WINDOW(window_main), "Минимальный катет шва 1.0");
    gtk_window_set_icon_from_file(GTK_WINDOW(window_main), "resources/ant.gif", NULL);
    gtk_window_set_resizable(GTK_WINDOW(window_main), FALSE);
    if (!window_main)
    {
        g_error("Failed to get window_main from builder\n");
        return 1;
    }

    window_forma2 = GTK_WIDGET(gtk_builder_get_object(builder, "window_forma2"));
    gtk_window_set_title(GTK_WINDOW(window_forma2), "Форма 2. Заполнение");
    gtk_window_set_icon_from_file(GTK_WINDOW(window_forma2), "resources/ant.gif", NULL);
    gtk_window_set_resizable(GTK_WINDOW(window_forma2), FALSE);
    if (!window_forma2)
    {
        g_error("Failed to get window_forma2 from builder\n");
        return 1;
    }
    gtk_builder_connect_signals(builder, NULL);
    work_widgets();

    // работа с *.css файлом
    apply_css();

    gtk_widget_show_all(window_main);
    gtk_main();

    g_slist_free(list);
    g_free(first);
    g_free(second);
    g_free(third);
    g_object_unref(builder);
    sqlite3_close(db);
    return 0;
}

gboolean on_window_forma2_delete_event(GtkWidget *child_win)
{
    gtk_widget_hide(window_forma2); // скрываем window_forma2
    gtk_widget_show(window_main);
    return TRUE;
}

void on_window_main_destroy(GtkWidget *main_win)
{
    gtk_main_quit(); // завершаем главный цикл GTK
}

void on_button_form_clicked(GtkButton *b)
{
    if (window_forma2 == NULL)
    {
        window_forma2 = GTK_WIDGET(gtk_builder_get_object(builder, "window_forma2"));
        gtk_window_set_title(GTK_WINDOW(window_forma2), "Форма 2. Заполнение");
        gtk_window_set_icon_from_file(GTK_WINDOW(window_forma2), "resources/ant.gif", NULL);
        gtk_window_set_resizable(GTK_WINDOW(window_forma2), FALSE);
        if (!window_forma2)
            g_error("Failed to get window_forma2 from builder");
        g_signal_connect(window_forma2, "delete_event", G_CALLBACK(on_window_forma2_delete_event), NULL);
        printf("Window forma2 created and signals connected.\n");
    }
    // Показываем окно
    gtk_widget_show_all(window_forma2);
    printf("Window forma2 shown\n");
    gtk_widget_hide(window_main);
}

void get_and_check_widget(GtkBuilder *erector, const char *widget_name, GtkWidget **widget)
{
    *widget = get_widget(erector, widget_name);
    if (!*widget)
        g_warning("Widget '%s' not found", widget_name);
}

void work_widgets()
{
    // Получаем виджеты window_main
    get_and_check_widget(builder, "fixed_all", &widgets.fixed_all);
    get_and_check_widget(builder, "alig_1", &widgets.alig_1);
    get_and_check_widget(builder, "fixed_thick", &widgets.fixed_thick);
    get_and_check_widget(builder, "label_1", &widgets.label_1);
    get_and_check_widget(builder, "entry_t1", &widgets.entry_t1);
    set_widget_alignment((GtkEntry *) widgets.entry_t1);    // заполнение текстом справа
    get_and_check_widget(builder, "entry_t2", &widgets.entry_t2);
    set_widget_alignment((GtkEntry *) widgets.entry_t2);    // заполнение текстом справа
    get_and_check_widget(builder, "label_t1", &widgets.label_t1);
    get_and_check_widget(builder, "label_t2", &widgets.label_t2);
    get_and_check_widget(builder, "button_calc", &widgets.button_calc);
    get_and_check_widget(builder, "alig_2", &widgets.alig_2);
    get_and_check_widget(builder, "fixed_tabl", &widgets.fixed_tabl);
    get_and_check_widget(builder, "label_2_1", &widgets.label_2_1);
    get_and_check_widget(builder, "label_2_2", &widgets.label_2_2);
    get_and_check_widget(builder, "label_2_3", &widgets.label_2_3);
    get_and_check_widget(builder, "label_2_4", &widgets.label_2_4);
    get_and_check_widget(builder, "label_2_5", &widgets.label_2_5);
    get_and_check_widget(builder, "label_2_6", &widgets.label_2_6);
    get_and_check_widget(builder, "label_2_7", &widgets.label_2_7);
    get_and_check_widget(builder, "separator_1", &widgets.separator_1);
    get_and_check_widget(builder, "separator_2", &widgets.separator_2);
    get_and_check_widget(builder, "separator_3", &widgets.separator_3);
    get_and_check_widget(builder, "separator_4", &widgets.separator_4);
    get_and_check_widget(builder, "separator_5", &widgets.separator_5);
    get_and_check_widget(builder, "separator_6", &widgets.separator_6);
    get_and_check_widget(builder, "separator_7", &widgets.separator_7);
    get_and_check_widget(builder, "separator_8", &widgets.separator_8);
    get_and_check_widget(builder, "separator_9", &widgets.separator_9);
    get_and_check_widget(builder, "separator_10", &widgets.separator_10);
    get_and_check_widget(builder, "separator_11", &widgets.separator_11);
    get_and_check_widget(builder, "alig_3", &widgets.alig_3);
    get_and_check_widget(builder, "label_name", &widgets.label_name);
    get_and_check_widget(builder, "label_text", &widgets.label_text);
    get_and_check_widget(builder, "katet_tabl1", &widgets.katet_tabl1);
    get_and_check_widget(builder, "label_result1", &widgets.label_result1);
    get_and_check_widget(builder, "katet_tabl2", &widgets.katet_tabl2);
    get_and_check_widget(builder, "label_result2", &widgets.label_result2);
    get_and_check_widget(builder, "fixed_file", &widgets.fixed_file);
    get_and_check_widget(builder, "button_new", &widgets.button_new);
    get_and_check_widget(builder, "button_new_data", &widgets.button_new_data);
    get_and_check_widget(builder, "label_count", &widgets.label_count);
    get_and_check_widget(builder, "button_file", &widgets.button_file);
    get_and_check_widget(builder, "label_create_file", &widgets.label_create_file);
    get_and_check_widget(builder, "label_without_frame", &widgets.label_without_frame);
    get_and_check_widget(builder, "label_frame", &widgets.label_frame);
    get_and_check_widget(builder, "button_form", &widgets.button_form);
    get_and_check_widget(builder, "entry_name", &widgets.entry_name);
    set_widget_alignment((GtkEntry *) widgets.entry_name);      // заполнение текстом справа
    get_and_check_widget(builder, "frame_thick", &widgets.frame_thick);
    get_and_check_widget(builder, "frame_tabl", &widgets.frame_tabl);
    get_and_check_widget(builder, "frame_file", &widgets.frame_file);
    get_and_check_widget(builder, "radiobutton_1", &widgets.radiobutton_1);
    get_and_check_widget(builder, "radiobutton_2", &widgets.radiobutton_2);
    get_and_check_widget(builder, "radiobutton_3", &widgets.radiobutton_3);
    get_and_check_widget(builder, "radiobutton_1_2", &widgets.radiobutton_1_2);
    get_and_check_widget(builder, "radiobutton_1_3", &widgets.radiobutton_1_3);
    get_and_check_widget(builder, "radiobutton_2_3", &widgets.radiobutton_2_3);
    get_and_check_widget(builder, "radiobutton_1_2_3", &widgets.radiobutton_1_2_3);
    get_and_check_widget(builder, "radio_without_frame", &widgets.radio_without_frame);
    get_and_check_widget(builder, "radio_frame", &widgets.radio_frame);

    // Получаем виджеты window_forma2
    get_and_check_widget(builder, "label_forma", &widgets.label_forma);
    get_and_check_widget(builder, "fixed_forma2", &widgets.fixed_forma2);
    get_and_check_widget(builder, "image_forma2", &widgets.image_forma2);
    get_and_check_widget(builder, "tree_forma2", &widgets.tree_forma2);
    get_and_check_widget(builder, "entry_code", &widgets.entry_code);
    get_and_check_widget(builder, "entry_developer", &widgets.entry_developer);
    get_and_check_widget(builder, "entry_inspector", &widgets.entry_inspector);
    get_and_check_widget(builder, "entry_norm_contr", &widgets.entry_norm_contr);
    get_and_check_widget(builder, "entry_approver", &widgets.entry_approver);
    get_and_check_widget(builder, "entry_name1", &widgets.entry_name1);
    get_and_check_widget(builder, "entry_name2", &widgets.entry_name2);
    get_and_check_widget(builder, "entry_name3", &widgets.entry_name3);
    get_and_check_widget(builder, "entry_sheet", &widgets.entry_sheet);
    get_and_check_widget(builder, "entry_sheets", &widgets.entry_sheets);
    get_and_check_widget(builder, "entry_organization", &widgets.entry_organization);
    get_and_check_widget(builder, "record_button", &widgets.record_button);

    GtkWidget *sensitive_widgets_false[] =
            {
                    widgets.button_calc,
                    widgets.button_new,
                    widgets.button_file,
                    widgets.entry_name,
                    widgets.button_new_data,
                    widgets.radiobutton_1,
                    widgets.radiobutton_2,
                    widgets.radiobutton_3,
                    widgets.radiobutton_1_2,
                    widgets.radiobutton_1_3,
                    widgets.radiobutton_2_3,
                    widgets.radiobutton_1_2_3,
                    widgets.radio_without_frame,
                    widgets.radio_frame,
                    widgets.button_form,
                    widgets.label_without_frame,
                    widgets.label_frame
            };

    set_widgets_sensitive(sensitive_widgets_false,
                          sizeof(sensitive_widgets_false) / sizeof(sensitive_widgets_false[0]), FALSE);
}

void on_button_calc_clicked(GtkButton *b)
{
    size_weld();
    gtk_widget_set_sensitive(GTK_WIDGET(widgets.button_new), TRUE);
    printf("flag is %d\n", flag_result);
    if (flag_result != 1)
        gtk_widget_set_sensitive(GTK_WIDGET(widgets.button_new_data), TRUE);
    else
    {
        flag_result = 0;
        printf("flag is %d\n", flag_result);
    }
}

void size_weld()
{
    if (((t1 > t2) && (t1 < 4)) || ((t1 < t2) && (t2 < 4))) // вариант, не предусмотренный СП 16.13330.2017
    {
        gtk_button_set_label(GTK_BUTTON(widgets.button_calc), "ОШИБКА В ДАННЫХ");
        gtk_entry_set_text(GTK_ENTRY(widgets.entry_t1), "????");
        gtk_entry_set_text(GTK_ENTRY(widgets.entry_t2), "????");
        gtk_label_set_text(GTK_LABEL(widgets.label_t1), " Толщина более толстого из свариваемых");
        gtk_label_set_text(GTK_LABEL(widgets.label_t2), "элементов меньше 4 мм не предусмотрена");
        flag_result = 1;
    } else if (((t1 < t2) && (t2 > 40)) || ((t1 > t2) && (t1 > 40))) // наиболее толстый элемент толщиной более 40 мм
    {
        gtk_label_set_text(GTK_LABEL(widgets.katet_tabl1), str_calc4);
        gtk_label_set_text(GTK_LABEL(widgets.katet_tabl2), str_calc4);
        flag_result = 2;
    } else
    {
        if (((t1 < t2) && (t1 < 0.6 * t2)) || ((0.6 * t1 > t2) && (t1 > t2))) // условие t >= 0.6T не выполняется
        {
            gdouble kat_max = (t1 < t2) ? 1.2 * t1 : 1.2 * t2;
            sprintf(str_calc2, "%.1f", kat_max);
            str_calc3 = g_strjoin(" ", str_calc1, str_calc2, NULL);
            gtk_label_set_text(GTK_LABEL(widgets.katet_tabl1), str_calc3);
            gtk_label_set_text(GTK_LABEL(widgets.katet_tabl2), str_calc3);
            g_free(str_calc3);
            flag_result = 3;
        } else
        {
            gtk_widget_hide(widgets.katet_tabl1);
            gtk_widget_hide(widgets.katet_tabl2);
            if (((t1 > t2) && (t1 <= 5) && (t1 >= 4)) || ((t1 < t2) && (t2 <= 5) && (t2 >= 4))
                || ((t1 == t2) && (t2 <= 5) && (t2 >= 4)))
            {
                gtk_label_set_text(GTK_LABEL(widgets.label_result1), "3");
                gtk_label_set_text(GTK_LABEL(widgets.label_result2), "3");
            } else if (((t1 > t2) && (t1 <= 10) && (t1 >= 6)) || ((t1 < t2) && (t2 <= 10) && (t2 >= 6))
                       || ((t1 == t2) && (t2 <= 10) && (t2 >= 6)))
            {
                gtk_label_set_text(GTK_LABEL(widgets.label_result1), "4");
                gtk_label_set_text(GTK_LABEL(widgets.label_result2), "5");
            } else if (((t1 > t2) && (t1 <= 16) && (t1 >= 11)) || ((t1 < t2) && (t2 <= 16) && (t2 >= 11))
                       || ((t1 == t2) && (t2 <= 16) && (t2 >= 11)))
            {
                gtk_label_set_text(GTK_LABEL(widgets.label_result1), "6");
                gtk_label_set_text(GTK_LABEL(widgets.label_result2), "8");
            } else if (((t1 > t2) && (t1 <= 22) && (t1 >= 17)) || ((t1 < t2) && (t2 <= 22) && (t2 >= 17))
                       || ((t1 == t2) && (t2 <= 22) && (t2 >= 17)))
            {
                gtk_label_set_text(GTK_LABEL(widgets.label_result1), "10");
                gtk_label_set_text(GTK_LABEL(widgets.label_result2), "12");
            } else if (((t1 > t2) && (t1 <= 32) && (t1 >= 23)) || ((t1 < t2) && (t2 <= 32) && (t2 >= 23))
                       || ((t1 == t2) && (t2 <= 32) && (t2 >= 23)))
            {
                gtk_label_set_text(GTK_LABEL(widgets.label_result1), "12");
                gtk_label_set_text(GTK_LABEL(widgets.label_result2), "16");
            } else if (((t1 > t2) && (t1 <= 40) && (t1 >= 33)) || ((t1 < t2) && (t2 <= 40) && (t2 >= 33))
                       || ((t1 == t2) && (t2 <= 40) && (t2 >= 33)))
            {
                gtk_label_set_text(GTK_LABEL(widgets.label_result1), "16");
                gtk_label_set_text(GTK_LABEL(widgets.label_result2), "22");
            }
            flag_result = 4;
        }
    }
}

void on_entry_t1_changed(GtkEntry *e)
{
    gchar thick1_enter[128];
    const gchar *thick1_calc = gtk_entry_get_text(e);
    sprintf(thick1_enter, "Толщина первого элемента %s мм", thick1_calc);
    gtk_label_set_text(GTK_LABEL(widgets.label_t1), thick1_enter);
    t1 = strtol(thick1_calc, NULL, 10);
}

void on_entry_t2_changed(GtkEntry *e)
{
    gchar thick2_enter[128];
    const gchar *thick2_calc = gtk_entry_get_text(e);
    sprintf(thick2_enter, "Толщина второго элемента %s мм", thick2_calc);
    gtk_label_set_text(GTK_LABEL(widgets.label_t2), (const gchar *) thick2_enter);
    t2 = strtol(thick2_calc, NULL, 10);
}

void on_button_new_data_clicked(GtkButton *b)
{
    button_click_count++;
    printf("*******\n");
    printf("button_click_count is %d\n", button_click_count);
    gchar *count_click = g_strdup_printf("%i", button_click_count);
    gtk_label_set_text(GTK_LABEL(widgets.label_count), count_click);

    // Заполнение односвязного списка
    writing_data_s_list(button_click_count);
    gtk_widget_set_sensitive(GTK_WIDGET(widgets.button_new_data), FALSE);
}

void writing_data_s_list(gint count_result)
{
    if (count_result == 1)                            // заполнение результатами 1-го узла
    {
        first = (Weld_data *) malloc(sizeof(Weld_data));
        first->position = button_click_count;
        first->thick_t1 = strtol(gtk_entry_get_text(GTK_ENTRY(widgets.entry_t1)), NULL, 0);
        first->thick_t2 = strtol(gtk_entry_get_text(GTK_ENTRY(widgets.entry_t2)), NULL, 0);
        first->thick_max = MAX(first->thick_t1, first->thick_t2);
        first->max_leg = 1.2 * MIN(first->thick_t1, first->thick_t2);
        first->weld_leg_1 = strtol(gtk_label_get_text(GTK_LABEL(widgets.label_result1)), NULL, 0);
        first->weld_leg_2 = strtol(gtk_label_get_text(GTK_LABEL(widgets.label_result2)), NULL, 0);
        list = g_slist_append(list, first);
        GtkWidget *sensitive_widgets_true[] =
                {
                        widgets.radiobutton_1,
                        widgets.button_file,
                        widgets.entry_name,
                        widgets.radio_without_frame,
                        widgets.radio_frame,
                        widgets.label_without_frame,
                        widgets.button_form,
                        widgets.label_frame
                };
        set_widgets_sensitive(sensitive_widgets_true,
                              sizeof(sensitive_widgets_true) / sizeof(sensitive_widgets_true[0]), TRUE);
    } else if (count_result == 2)                     // заполнение результатами 2-го узла
    {
        second = g_new(Weld_data, 1);
        second->position = button_click_count;
        second->thick_t1 = strtol(gtk_entry_get_text(GTK_ENTRY(widgets.entry_t1)), NULL, 0);
        second->thick_t2 = strtol(gtk_entry_get_text(GTK_ENTRY(widgets.entry_t2)), NULL, 0);
        second->thick_max = MAX(second->thick_t1, second->thick_t2);
        second->max_leg = 1.2 * MIN(second->thick_t1, second->thick_t2);
        second->weld_leg_1 = strtol(gtk_label_get_text(GTK_LABEL(widgets.label_result1)), NULL, 0);
        second->weld_leg_2 = strtol(gtk_label_get_text(GTK_LABEL(widgets.label_result2)), NULL, 0);
        list = g_slist_append(list, second);
        GtkWidget *sensitive_widgets[] =
                {
                        widgets.radiobutton_2,
                        widgets.radiobutton_1_2
                };
        set_widgets_sensitive(sensitive_widgets,
                              sizeof(sensitive_widgets) / sizeof(sensitive_widgets[0]), TRUE);
    } else if (count_result == 3)                     // заполнение результатами 3-го узла
    {
        third = g_new(Weld_data, 1);
        third->position = button_click_count;
        third->thick_t1 = strtol(gtk_entry_get_text(GTK_ENTRY(widgets.entry_t1)), NULL, 0);
        third->thick_t2 = strtol(gtk_entry_get_text(GTK_ENTRY(widgets.entry_t2)), NULL, 0);
        third->thick_max = MAX(third->thick_t1, third->thick_t2);
        third->max_leg = 1.2 * MIN(third->thick_t1, third->thick_t2);
        third->weld_leg_1 = strtol(gtk_label_get_text(GTK_LABEL(widgets.label_result1)), NULL, 0);
        third->weld_leg_2 = strtol(gtk_label_get_text(GTK_LABEL(widgets.label_result2)), NULL, 0);
        list = g_slist_append(list, third);
        GtkWidget *sensitive_widgets_true[] =
                {
                        widgets.radiobutton_3,
                        widgets.radiobutton_1_3,
                        widgets.radiobutton_2_3,
                        widgets.radiobutton_1_2_3
                };
        set_widgets_sensitive(sensitive_widgets_true,
                              sizeof(sensitive_widgets_true) / sizeof(sensitive_widgets_true[0]),
                              TRUE);
        // Окончание ввода данных
        gtk_label_set_text(GTK_LABEL(widgets.label_count), ">>>>>");
        GtkWidget *sensitive_widgets_false[] =
                {
                        widgets.button_calc,
                        widgets.button_new,
                        widgets.entry_t1,
                        widgets.entry_t2
                };
        set_widgets_sensitive(sensitive_widgets_false,
                              sizeof(sensitive_widgets_false) / sizeof(sensitive_widgets_false[0]),
                              FALSE);
    }
}

void on_button_new_clicked(GtkButton *b)
{
    gtk_editable_delete_text(GTK_EDITABLE(widgets.entry_t1), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(widgets.entry_t2), 0, -1);
    gtk_label_set_text(GTK_LABEL(widgets.label_t1), "Введите толщину первого элемента, мм");
    gtk_label_set_text(GTK_LABEL(widgets.label_t1), "Введите толщину второго элемента, мм");
    gtk_label_set_text(GTK_LABEL(widgets.katet_tabl1), "Введите исходные\n          данные");
    gtk_label_set_text(GTK_LABEL(widgets.katet_tabl2), "Введите исходные\n          данные");
    gtk_widget_show(widgets.katet_tabl1);
    gtk_label_set_text(GTK_LABEL(widgets.label_result1), " ");
    gtk_widget_show(widgets.katet_tabl2);
    gtk_label_set_text(GTK_LABEL(widgets.label_result2), " ");
    gtk_button_set_label(GTK_BUTTON(widgets.button_calc), "Вычислить");
    gtk_widget_set_sensitive(GTK_WIDGET(widgets.button_calc), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(widgets.button_new_data), FALSE);
}

void on_entry_t1_insert_text(GtkEntry *e)
{
    if (gtk_entry_get_text_length(GTK_ENTRY(widgets.entry_t2)))
        gtk_widget_set_sensitive(GTK_WIDGET(widgets.button_calc), TRUE);
}

void on_entry_t2_insert_text(GtkEntry *e)
{
    if (gtk_entry_get_text_length(GTK_ENTRY(widgets.entry_t1)))
        gtk_widget_set_sensitive(GTK_WIDGET(widgets.button_calc), TRUE);
}

void on_button_file_clicked(GtkButton *b)
{
    gchar *file_name = NULL;
    double left_margin = (20.0 / 25.4) * 72;  // Левый отступ (20 мм)
    double top_margin = (5.0 / 25.4) * 72;    // Верхний отступ (5 мм)
    double right_margin = (5.0 / 25.4) * 72;  // Правый отступ (5 мм)
    double bottom_margin = (5.0 / 25.4) * 72; // Нижний отступ (5 мм)
    // Вычисляем размеры рамки
    double width = (210.0 / 25.4) * 72 - left_margin - right_margin;
    double height = (297.0 / 25.4) * 72 - top_margin - bottom_margin;
    cairo_surface_t *surface;
    cairo_t *cr;
    const gchar *file_name_assigned = gtk_entry_get_text(GTK_ENTRY(widgets.entry_name));

    // Проверка задано имя файла или используется по умолчанию
    if (g_str_equal(file_name_assigned, "        Введите имя файла"))
        file_name = "text.pdf";
    else
        file_name = g_strjoin(".", file_name_assigned, "pdf", NULL);

    surface = cairo_pdf_surface_create(file_name, (210 / 25.4) * 72,
                                       (297.5 / 25.4) * 72); // А4 in points
    cr = cairo_create(surface);

    // Проверяем создан ли файл
    if (surface == NULL)
    {
        printf("cairo_pdf_surface_create %s file is BREAK\n", file_name);
        gtk_label_set_text(GTK_LABEL(widgets.label_create_file), "Ошибка создания файла");
        puts("Press any key to exit...");
        getch(); // считывает символ из входного потока, но не выводит на экран
        exit(1);
    } else
    {
        gtk_label_set_text(GTK_LABEL(widgets.label_create_file), "Файл создан");
        printf("cairo_pdf_surface_create %s file is DONE\n", file_name);
    }

    // Вставка png
    // печатаем картинку 1 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_1))
    {
        insert_png(cr, list, 0, 0);
    }
    // печатаем картинку 2 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_2))
    {
        insert_png(cr, list, 0, 1);
    }
    // печатаем картинку 3 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_3))
    {
        insert_png(cr, list, 0, 2);
    }
    // печатаем картинку 1, 2 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_1_2))
    {
        insert_png(cr, list, 0, 0);
        insert_png(cr, list, 215, 1);
    }
    // печатаем картинку 1, 3 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_1_3))
    {
        insert_png(cr, list, 0, 0);
        insert_png(cr, list, 215, 2);
    }
    // печатаем картинку 2, 3 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_2_3))
    {
        insert_png(cr, list, 0, 1);
        insert_png(cr, list, 215, 2);
    }
    // печатаем картинку 1, 2, 3 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_1_2_3))
    {
        insert_png(cr, list, 0, 0);
        insert_png(cr, list, 215, 1);
        insert_png(cr, list, 430, 2);
    }

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12.0);    // размер шрифта заголовка
    cairo_move_to(cr, 170, 25);
    cairo_show_text(cr, "Минимальные катеты сварных угловых швов ");
    cairo_set_font_size(cr, 10.0);   // размер шрифта pdf документа

    // Работаем с датой
    cairo_set_font_size(cr, 10.0);
    work_dates(cr);

    // Рамка на формате А4, толщина линии
    cairo_set_line_width(cr, 0.8);

    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radio_without_frame))
        flag_frame = 1;
    else
    {
        flag_frame = 2;
        cairo_rectangle(cr, left_margin, top_margin, width, height);
    }

    /*cairo_rectangle(cr, left_margin, top_margin, width, height);
    // Штамп (форма 2)
    // горизонтальные основные линии
    cairo_move_to(cr, (20.0 / 25.4) * 72, (252.0 / 25.4) * 72);
    cairo_line_to(cr, (205.0 / 25.4) * 72, (252.0 / 25.4) * 72);    // первая
    cairo_move_to(cr, (20.0 / 25.4) * 72, (262.0 / 25.4) * 72);
    cairo_line_to(cr, (85.0 / 25.4) * 72, (262.0 / 25.4) * 72);     // вторая
    cairo_move_to(cr, (20.0 / 25.4) * 72, (267.0 / 25.4) * 72);
    cairo_line_to(cr, (205.0 / 25.4) * 72, (267.0 / 25.4) * 72);    // третья
    cairo_move_to(cr, (155.0 / 25.4) * 72, (272.0 / 25.4) * 72);
    cairo_line_to(cr, (205.0 / 25.4) * 72, (272.0 / 25.4) * 72);    // четвертая
    cairo_move_to(cr, (155.0 / 25.4) * 72, (277.0 / 25.4) * 72);
    cairo_line_to(cr, (205.0 / 25.4) * 72, (277.0 / 25.4) * 72);    // пятая
    // вертикальные основные линии
    cairo_move_to(cr, (27.0 / 25.4) * 72, (252.0 / 25.4) * 72);
    cairo_line_to(cr, (27.0 / 25.4) * 72, (267.0 / 25.4) * 72);    // первая
    cairo_move_to(cr, (37.0 / 25.4) * 72, (252.0 / 25.4) * 72);
    cairo_line_to(cr, (37.0 / 25.4) * 72, (292.0 / 25.4) * 72);    // вторая
    cairo_move_to(cr, (60.0 / 25.4) * 72, (252.0 / 25.4) * 72);
    cairo_line_to(cr, (60.0 / 25.4) * 72, (292.0 / 25.4) * 72);    // третья
    cairo_move_to(cr, (75.0 / 25.4) * 72, (252.0 / 25.4) * 72);
    cairo_line_to(cr, (75.0 / 25.4) * 72, (292.0 / 25.4) * 72);    // четвертая
    cairo_move_to(cr, (85.0 / 25.4) * 72, (252.0 / 25.4) * 72);
    cairo_line_to(cr, (85.0 / 25.4) * 72, (292.0 / 25.4) * 72);    // пятая
    cairo_move_to(cr, (155.0 / 25.4) * 72, (267.0 / 25.4) * 72);
    cairo_line_to(cr, (155.0 / 25.4) * 72, (292.0 / 25.4) * 72);    // шестая
    cairo_move_to(cr, (170.0 / 25.4) * 72, (267.0 / 25.4) * 72);
    cairo_line_to(cr, (170.0 / 25.4) * 72, (277.0 / 25.4) * 72);    // седьмая
    cairo_move_to(cr, (185.0 / 25.4) * 72, (267.0 / 25.4) * 72);
    cairo_line_to(cr, (185.0 / 25.4) * 72, (277.0 / 25.4) * 72);    // восьмая
    cairo_stroke(cr);  // рисуем основные линии
    cairo_set_line_width(cr, 0.3);
    // горизонтальные тонкие линии
    cairo_move_to(cr, (20.0 / 25.4) * 72, (257.0 / 25.4) * 72);
    cairo_line_to(cr, (85.0 / 25.4) * 72, (257.0 / 25.4) * 72);    // первая
    cairo_move_to(cr, (20.0 / 25.4) * 72, (272.0 / 25.4) * 72);
    cairo_line_to(cr, (85.0 / 25.4) * 72, (272.0 / 25.4) * 72);    // вторая
    cairo_move_to(cr, (20.0 / 25.4) * 72, (277.0 / 25.4) * 72);
    cairo_line_to(cr, (85.0 / 25.4) * 72, (277.0 / 25.4) * 72);    // третья
    cairo_move_to(cr, (20.0 / 25.4) * 72, (282.0 / 25.4) * 72);
    cairo_line_to(cr, (85.0 / 25.4) * 72, (282.0 / 25.4) * 72);    // четвертая
    cairo_move_to(cr, (20.0 / 25.4) * 72, (287.0 / 25.4) * 72);
    cairo_line_to(cr, (85.0 / 25.4) * 72, (287.0 / 25.4) * 72);    // пятая
    // вертикальные тонкие линии
    cairo_move_to(cr, (160.0 / 25.4) * 72, (272.0 / 25.4) * 72);
    cairo_line_to(cr, (160.0 / 25.4) * 72, (277.0 / 25.4) * 72);    // первая
    cairo_move_to(cr, (165.0 / 25.4) * 72, (272.0 / 25.4) * 72);
    cairo_line_to(cr, (165.0 / 25.4) * 72, (277.0 / 25.4) * 72);    // вторая
    // текст штампа
    cairo_set_font_size(cr, 8.0);   // размер шрифта штампа
    cairo_move_to(cr, (20.5 / 25.4) * 72, (265.5 / 25.4) * 72);
    cairo_show_text(cr, "Изм.");
    cairo_move_to(cr, (29 / 25.4) * 72, (265.5 / 25.4) * 72);
    cairo_show_text(cr, "Лист");
    cairo_move_to(cr, (42 / 25.4) * 72, (265.5 / 25.4) * 72);
    cairo_show_text(cr, "№ докум.");
    cairo_move_to(cr, (63.5 / 25.4) * 72, (265.5 / 25.4) * 72);
    cairo_show_text(cr, "Подп.");
    cairo_move_to(cr, (77 / 25.4) * 72, (265.5 / 25.4) * 72);
    cairo_show_text(cr, "Дата");
    cairo_move_to(cr, (21 / 25.4) * 72, (271 / 25.4) * 72);
    cairo_show_text(cr, "Разраб.");
    cairo_move_to(cr, (21 / 25.4) * 72, (276 / 25.4) * 72);
    cairo_show_text(cr, "Пров.");
    cairo_move_to(cr, (21 / 25.4) * 72, (286 / 25.4) * 72);
    cairo_show_text(cr, "Н. контр.");
    cairo_move_to(cr, (21 / 25.4) * 72, (291 / 25.4) * 72);
    cairo_show_text(cr, "Утв.");
    cairo_move_to(cr, (160.0 / 25.4) * 72, (270.5 / 25.4) * 72);
    cairo_show_text(cr, "Лит.");
    cairo_move_to(cr, (174.5 / 25.4) * 72, (270.5 / 25.4) * 72);
    cairo_show_text(cr, "Лист");
    cairo_move_to(cr, (190.0 / 25.4) * 72, (270.5 / 25.4) * 72);
    cairo_show_text(cr, "Листов");*/

    cairo_set_font_size(cr, 10.0); // размер шрифта расчетной части
    // печатаем 1 результат
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_1))
    {
        // Сбор данных для печати 1-го результата
        data_collection(cr, list, 0, 0);
        // Рисуем таблицу с 1-ым результатом
        create_table(cr, 0);
    }
    // печатаем 2 результат
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_2))
    {
        // Сбор данных для печати 2-го результата
        data_collection(cr, list, 0, 1);
        // Рисуем таблицу со 2-ым результатом
        create_table(cr, 0);
    }
    // печатаем 3 результат
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_3))
    {
        // Сбор данных для печати 3-го результата
        data_collection(cr, list, 0, 2);
        // Рисуем таблицу с 3-им результатом
        create_table(cr, 0);
    }
    // печатаем 1, 2 результаты
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_1_2))
    {
        // Сбор данных для печати 1-го результата
        data_collection(cr, list, 0, 0);
        // Рисуем таблицу с 1-ым результатом
        create_table(cr, 0);
        // Сбор данных для печати 2-го результата
        data_collection(cr, list, 215, 1);
        // Рисуем таблицу со 2-ым результатом
        create_table(cr, 215);
    }
    // печатаем 1, 3 результаты
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_1_3))
    {
        // Сбор данных для печати 1-го результата
        data_collection(cr, list, 0, 0);
        // Рисуем таблицу с 1-ым результатом
        create_table(cr, 0);
        // Сбор данных для печати 3-го результата
        data_collection(cr, list, 215, 2);
        // Рисуем таблицу с 3-им результатом
        create_table(cr, 215);
    }
    // печатаем 2, 3 результаты
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_2_3))
    {
        // Сбор данных для печати 2-го результата
        data_collection(cr, list, 0, 1);
        // Рисуем таблицу со 2-ым результатом
        create_table(cr, 0);
        // Сбор данных для печати 3-го результата
        data_collection(cr, list, 215, 2);
        // Рисуем таблицу с 3-им результатом
        create_table(cr, 215);
    }
    // печатаем 1, 2, 3 результаты
    if (gtk_toggle_button_get_active((GtkToggleButton *) widgets.radiobutton_1_2_3))
    {
        // Сбор данных для печати 1-го результата
        data_collection(cr, list, 0, 0);
        // Рисуем таблицу с 1-ым результатом
        create_table(cr, 0);
        // Сбор данных для печати 2-го результата
        data_collection(cr, list, 215, 1);
        // Рисуем таблицу со 2-ым результатом
        create_table(cr, 215);
        // Сбор данных для печати 3-го результата
        data_collection(cr, list, 430, 2);
        // Рисуем таблицу с 3-им результатом
        create_table(cr, 430);
    }
    cairo_stroke(cr);
    cairo_fill(cr);

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

// Очищаем entry от существующего текста
void on_entry_name_focus_in_event(GtkEntry *e)
{
    gtk_entry_set_text(GTK_ENTRY(widgets.entry_name), " ");
    gtk_label_set_text(GTK_LABEL(widgets.label_create_file), " ");
}


