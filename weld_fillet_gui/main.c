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
#include <conio.h>
#include <cairo-pdf.h>
#include "temp_function.h"

GtkWidget *window_main;
GtkWidget *fixed_all;
GtkWidget *fixed_thick;
GtkWidget *entry_t1;
GtkWidget *entry_t2;
GtkWidget *label_t1;
GtkWidget *label_t2;
GtkWidget *button_calc;
GtkWidget *button_new;
GtkWidget *fixed_tabl;
GtkWidget *katet_tabl1;
GtkWidget *label_result1;
GtkWidget *katet_tabl2;
GtkWidget *label_result2;
GtkWidget *fixed_file;
GtkWidget *frame_thick;
GtkWidget *frame_tabl;
GtkWidget *frame_file;
GtkWidget *button_new_data;
GtkWidget *label_count;
GtkWidget *button_file;
GtkWidget *label_create_file;
GtkWidget *entry_name;
GtkWidget *radiobutton_1;
GtkWidget *radiobutton_2;
GtkWidget *radiobutton_3;
GtkWidget *radiobutton_1_2;
GtkWidget *radiobutton_1_3;
GtkWidget *radiobutton_2_3;
GtkWidget *radiobutton_1_2_3;
GtkBuilder *builder;

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

G_MODULE_EXPORT void on_entry_t1_changed(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t2_changed(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t1_insert_text(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t2_insert_text(GtkEntry *e);
G_MODULE_EXPORT void on_entry_name_focus_in_event(GtkEntry *e);
G_MODULE_EXPORT void on_button_new_data_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_new_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_file_clicked(GtkButton *b);

void work_widgets();
void writing_data_s_list(gint count_result);


int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("resources/weld.glade");
    work_widgets();

    // работа с *.css файлом
    working_css_file();

    gtk_widget_show(window_main);
    gtk_main();

    g_slist_free(list);
    g_free(first);
    g_free(second);
    g_free(third);
    return 0;
}

// Работаем с виджетами
void work_widgets()
{
    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_window_set_title(GTK_WINDOW(window_main), "Минимальный катет шва 1.0");
    gtk_window_set_icon_from_file(GTK_WINDOW(window_main), "resources/ant.gif", NULL);
    gtk_window_set_resizable(GTK_WINDOW(window_main), FALSE);
    g_signal_connect(window_main, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    fixed_all = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_all"));
    fixed_thick = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_thick"));
    entry_t1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_t1"));
    gtk_entry_set_alignment((GtkEntry *) entry_t1, 1); // ввод текста слева
    entry_t2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_t2"));
    gtk_entry_set_alignment((GtkEntry *) entry_t2, 1); // ввод текста слева
    label_t1 = GTK_WIDGET(gtk_builder_get_object(builder, "label_t1"));
    label_t2 = GTK_WIDGET(gtk_builder_get_object(builder, "label_t2"));
    button_calc = GTK_WIDGET(gtk_builder_get_object(builder, "button_calc"));
    fixed_tabl = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_tabl"));
    katet_tabl1 = GTK_WIDGET(gtk_builder_get_object(builder, "katet_tabl1"));
    label_result1 = GTK_WIDGET(gtk_builder_get_object(builder, "label_result1"));
    katet_tabl2 = GTK_WIDGET(gtk_builder_get_object(builder, "katet_tabl2"));
    label_result2 = GTK_WIDGET(gtk_builder_get_object(builder, "label_result2"));
    fixed_file = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_file"));
    button_new = GTK_WIDGET(gtk_builder_get_object(builder, "button_new"));
    button_new_data = GTK_WIDGET(gtk_builder_get_object(builder, "button_new_data"));
    label_count = GTK_WIDGET(gtk_builder_get_object(builder, "label_count"));
    button_file = GTK_WIDGET(gtk_builder_get_object(builder, "button_file"));
    label_create_file = GTK_WIDGET(gtk_builder_get_object(builder, "label_create_file"));
    entry_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry_name"));
    gtk_entry_set_alignment((GtkEntry *) entry_name, 1);  // ввод текста слева
    frame_thick = GTK_WIDGET(gtk_builder_get_object(builder, "frame_thick"));
    frame_tabl = GTK_WIDGET(gtk_builder_get_object(builder, "frame_tabl"));
    frame_file = GTK_WIDGET(gtk_builder_get_object(builder, "frame_file"));
    radiobutton_1 = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_1"));
    radiobutton_2 = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_2"));
    radiobutton_3 = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_3"));
    radiobutton_1_2 = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_1_2"));
    radiobutton_1_3 = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_1_3"));
    radiobutton_2_3 = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_2_3"));
    radiobutton_1_2_3 = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_1_2_3"));
    // Управление активностью кнопок
    gtk_widget_set_sensitive(GTK_WIDGET(button_calc), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(button_new), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(button_file), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(entry_name), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(button_new_data), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_1), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_2), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_3), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_1_2), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_1_3), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_2_3), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_1_2_3), FALSE);
}

void on_button_calc_clicked(GtkButton *b)
{
    size_weld();
    gtk_widget_set_sensitive(GTK_WIDGET(button_new), TRUE);
    printf("flag is %d\n", flag_result);
    if (flag_result != 1)
        gtk_widget_set_sensitive(GTK_WIDGET(button_new_data), TRUE);
    else
    {
        flag_result = 0;
        printf("flag is %d\n", flag_result);
    }
}

void size_weld()
{
    if (t1 > t2 && t1 < 4 || t1 < t2 && t2 < 4) // вариант, не предусмотренный СП 16.13330.2017
    {
        gtk_button_set_label(GTK_BUTTON(button_calc), "ОШИБКА В ДАННЫХ");
        gtk_entry_set_text(GTK_ENTRY(entry_t1), "????");
        gtk_entry_set_text(GTK_ENTRY(entry_t2), "????");
        gtk_label_set_text(GTK_LABEL(label_t1), " Толщина более толстого из свариваемых");
        gtk_label_set_text(GTK_LABEL(label_t2), "элементов меньше 4 мм не предусмотрена");
        flag_result = 1;
    } else if (t1 < t2 && t2 > 40 || t1 > t2 && t1 > 40) // наиболее толстый элемент толщиной более 40 мм
    {
        gtk_label_set_text(GTK_LABEL(katet_tabl1), str_calc4);
        gtk_label_set_text(GTK_LABEL(katet_tabl2), str_calc4);
        flag_result = 2;
    } else
    {
        if (t1 < t2 && t1 < 0.6 * t2 || 0.6 * t1 > t2 && t1 > t2) // условие t >= 0.6T не выполняется
        {
            gdouble kat_max;
            if (t1 < t2)
                kat_max = 1.2 * t1;
            else
                kat_max = 1.2 * t2;
            sprintf(str_calc2, "%.1f", kat_max);
            str_calc3 = g_strjoin(" ", str_calc1, str_calc2, NULL);
            gtk_label_set_text(GTK_LABEL(katet_tabl1), str_calc3);
            gtk_label_set_text(GTK_LABEL(katet_tabl2), str_calc3);
            flag_result = 3;
        } else
        {
            gtk_widget_hide(katet_tabl1);
            gtk_widget_hide(katet_tabl2);
            if (t1 > t2 && t1 <= 5 && t1 >= 4 || t1 < t2 && t2 <= 5 && t2 >= 4
                || t1 == t2 && t2 <= 5 && t2 >= 4)
            {
                gtk_label_set_text(GTK_LABEL(label_result1), "3");
                gtk_label_set_text(GTK_LABEL(label_result2), "3");
            } else if (t1 > t2 && t1 <= 10 && t1 >= 6 || t1 < t2 && t2 <= 10 && t2 >= 6
                       || t1 == t2 && t2 <= 10 && t2 >= 6)
            {
                gtk_label_set_text(GTK_LABEL(label_result1), "4");
                gtk_label_set_text(GTK_LABEL(label_result2), "5");
            } else if (t1 > t2 && t1 <= 16 && t1 >= 11 || t1 < t2 && t2 <= 16 && t2 >= 11
                       || t1 == t2 && t2 <= 16 && t2 >= 11)
            {
                gtk_label_set_text(GTK_LABEL(label_result1), "6");
                gtk_label_set_text(GTK_LABEL(label_result2), "8");
            } else if (t1 > t2 && t1 <= 22 && t1 >= 17 || t1 < t2 && t2 <= 22 && t2 >= 17
                       || t1 == t2 && t2 <= 22 && t2 >= 17)
            {
                gtk_label_set_text(GTK_LABEL(label_result1), "10");
                gtk_label_set_text(GTK_LABEL(label_result2), "12");
            } else if (t1 > t2 && t1 <= 32 && t1 >= 23 || t1 < t2 && t2 <= 32 && t2 >= 23
                       || t1 == t2 && t2 <= 32 && t2 >= 23)
            {
                gtk_label_set_text(GTK_LABEL(label_result1), "12");
                gtk_label_set_text(GTK_LABEL(label_result2), "16");
            } else if (t1 > t2 && t1 <= 40 && t1 >= 33 || t1 < t2 && t2 <= 40 && t2 >= 33
                       || t1 == t2 && t2 <= 40 && t2 >= 33)
            {
                gtk_label_set_text(GTK_LABEL(label_result1), "16");
                gtk_label_set_text(GTK_LABEL(label_result2), "22");
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
    gtk_label_set_text(GTK_LABEL(label_t1), thick1_enter);
    t1 = strtol(thick1_calc, NULL, 10);
}

void on_entry_t2_changed(GtkEntry *e)
{
    gchar thick2_enter[128];
    const gchar *thick2_calc = gtk_entry_get_text(e);
    sprintf(thick2_enter, "Толщина второго элемента %s мм", thick2_calc);
    gtk_label_set_text(GTK_LABEL(label_t2), (const gchar *) thick2_enter);
    t2 = strtol(thick2_calc, NULL, 10);
}

void on_button_new_data_clicked(GtkButton *b)
{
    button_click_count++;
    printf("*******\n");
    printf("button_click_count is %d\n", button_click_count);
    gchar *count_click = g_strdup_printf("%i", button_click_count);
    gtk_label_set_text(GTK_LABEL(label_count), count_click);

    // Заполнение односвязного списка
    writing_data_s_list(button_click_count);
    gtk_widget_set_sensitive(GTK_WIDGET(button_new_data), FALSE);
}

void writing_data_s_list(gint count_result)
{
    if (count_result == 1)                            // заполнение результатами 1-го узла
    {
        first = (Weld_data *) malloc(sizeof(Weld_data));
        first->position = button_click_count;
        first->thick_t1 = strtol(gtk_entry_get_text(GTK_ENTRY(entry_t1)), NULL, 0);
        first->thick_t2 = strtol(gtk_entry_get_text(GTK_ENTRY(entry_t2)), NULL, 0);
        first->thick_max = MAX(first->thick_t1, first->thick_t2);
        first->max_leg = 1.2 * MIN(first->thick_t1, first->thick_t2);
        first->weld_leg_1 = strtol(gtk_label_get_text(GTK_LABEL(label_result1)), NULL, 0);
        first->weld_leg_2 = strtol(gtk_label_get_text(GTK_LABEL(label_result2)), NULL, 0);
        list = g_slist_append(list, first);
        gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_1), TRUE);
        // Поле ввода имени файла и кнопка его создания активны
        gtk_widget_set_sensitive(GTK_WIDGET(button_file), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(entry_name), TRUE);

    } else if (count_result == 2)                     // заполнение результатами 2-го узла
    {
        second = g_new(Weld_data, 1);
        second->position = button_click_count;
        second->thick_t1 = strtol(gtk_entry_get_text(GTK_ENTRY(entry_t1)), NULL, 0);
        second->thick_t2 = strtol(gtk_entry_get_text(GTK_ENTRY(entry_t2)), NULL, 0);
        second->thick_max = MAX(second->thick_t1, second->thick_t2);
        second->max_leg = 1.2 * MIN(second->thick_t1, second->thick_t2);
        second->weld_leg_1 = strtol(gtk_label_get_text(GTK_LABEL(label_result1)), NULL, 0);
        second->weld_leg_2 = strtol(gtk_label_get_text(GTK_LABEL(label_result2)), NULL, 0);
        list = g_slist_append(list, second);
        gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_2), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_1_2), TRUE);
        // поле ввода имени и кнопка создания файла активны
        gtk_widget_set_sensitive(GTK_WIDGET(button_file), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(entry_name), TRUE);

    } else if (count_result == 3)                     // заполнение результатами 3-го узла
    {
        third = g_new(Weld_data, 1);
        third->position = button_click_count;
        third->thick_t1 = strtol(gtk_entry_get_text(GTK_ENTRY(entry_t1)), NULL, 0);
        third->thick_t2 = strtol(gtk_entry_get_text(GTK_ENTRY(entry_t2)), NULL, 0);
        third->thick_max = MAX(third->thick_t1, third->thick_t2);
        third->max_leg = 1.2 * MIN(third->thick_t1, third->thick_t2);
        third->weld_leg_1 = strtol(gtk_label_get_text(GTK_LABEL(label_result1)), NULL, 0);
        third->weld_leg_2 = strtol(gtk_label_get_text(GTK_LABEL(label_result2)), NULL, 0);
        list = g_slist_append(list, third);
        gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_3), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_1_3), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_2_3), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(radiobutton_1_2_3), TRUE);
        // Окончание ввода данных
        gtk_label_set_text(GTK_LABEL(label_count), ">>>>>");
        gtk_widget_set_sensitive(GTK_WIDGET(button_calc), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(button_new), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(entry_t1), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(entry_t2), FALSE);
    }
}

void on_button_new_clicked(GtkButton *b)
{
    gtk_editable_delete_text(GTK_EDITABLE(entry_t1), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(entry_t2), 0, -1);
    gtk_label_set_text(GTK_LABEL(label_t1), "Введите толщину первого элемента, мм");
    gtk_label_set_text(GTK_LABEL(label_t2), "Введите толщину второго элемента, мм");
    gtk_label_set_text(GTK_LABEL(katet_tabl1), "Введите исходные\n          данные");
    gtk_label_set_text(GTK_LABEL(katet_tabl2), "Введите исходные\n          данные");
    gtk_widget_show(katet_tabl1);
    gtk_label_set_text(GTK_LABEL(label_result1), " ");
    gtk_widget_show(katet_tabl2);
    gtk_label_set_text(GTK_LABEL(label_result2), " ");
    gtk_button_set_label(GTK_BUTTON(button_calc), "Вычислить");
    gtk_widget_set_sensitive(GTK_WIDGET(button_calc), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(button_new_data), FALSE);
}

void on_entry_t1_insert_text(GtkEntry *e)
{
    if (gtk_entry_get_text_length(GTK_ENTRY(entry_t2)))
        gtk_widget_set_sensitive(GTK_WIDGET(button_calc), TRUE);
}

void on_entry_t2_insert_text(GtkEntry *e)
{
    if (gtk_entry_get_text_length(GTK_ENTRY(entry_t1)))
        gtk_widget_set_sensitive(GTK_WIDGET(button_calc), TRUE);
}

void on_button_file_clicked(GtkButton *b)
{
    gchar *file_name = NULL;
    cairo_surface_t *surface;
    cairo_t *cr;
    const gchar *file_name_assigned = gtk_entry_get_text(GTK_ENTRY(entry_name));

    // Проверка задано имя файла или используется по умолчанию
    if (g_str_equal(file_name_assigned, "        Введите имя файла"))
        file_name = "text.pdf";
    else
        file_name = g_strjoin(".", file_name_assigned, "pdf", NULL);

    surface = cairo_pdf_surface_create(file_name, 595, 842); // А4 in points
    cr = cairo_create(surface);

    // Вставка png
    // печатаем картинку 1 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_1))
    {
        insert_png(cr, list, 0, 0);
    }
    // печатаем картинку 2 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_2))
    {
        insert_png(cr, list, 0, 1);
    }
    // печатаем картинку 3 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_3))
    {
        insert_png(cr, list, 0, 2);
    }
    // печатаем картинку 1, 2 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_1_2))
    {
        insert_png(cr, list, 0, 0);
        insert_png(cr, list, 215, 1);
    }
    // печатаем картинку 1, 3 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_1_3))
    {
        insert_png(cr, list, 0, 0);
        insert_png(cr, list, 215, 2);
    }
    // печатаем картинку 2, 3 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_2_3))
    {
        insert_png(cr, list, 0, 1);
        insert_png(cr, list, 215, 2);
    }
    // печатаем картинку 1, 2, 3 результата
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_1_2_3))
    {
        insert_png(cr, list, 0, 0);
        insert_png(cr, list, 215, 1);
        insert_png(cr, list, 430, 2);
    }

    // Проверяем создан ли файл
    if (surface == NULL)
    {
        printf("cairo_pdf_surface_create %s file is BREAK\n", file_name);
        gtk_label_set_text(GTK_LABEL(label_create_file), "Ошибка создания файла");
        puts("Press any key to exit...");
        getch(); // считывает символ из входного потока, но не выводит на экран
        exit(1);
    } else
    {
        gtk_label_set_text(GTK_LABEL(label_create_file), "Файл создан");
        printf("cairo_pdf_surface_create %s file is DONE\n", file_name);
    }

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12.0);    // размер шрифта заголовка
    cairo_move_to(cr, 200, 25);
    cairo_show_text(cr, "Минимальные катеты сварных угловых швов ");
    // печатаем 1 результат
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_1))
    {
        // Сбор данных для печати 1-го результата
        data_collection(cr, list, 0, 0);
        // Рисуем таблицу с 1-ым результатом
        create_table(cr, 0);
    }
    // печатаем 2 результат
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_2))
    {
        // Сбор данных для печати 2-го результата
        data_collection(cr, list, 0, 1);
        // Рисуем таблицу со 2-ым результатом
        create_table(cr, 0);
    }
    // печатаем 3 результат
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_3))
    {
        // Сбор данных для печати 3-го результата
        data_collection(cr, list, 0, 2);
        // Рисуем таблицу с 3-им результатом
        create_table(cr, 0);
    }
    // печатаем 1, 2 результаты
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_1_2))
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
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_1_3))
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
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_2_3))
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
    if (gtk_toggle_button_get_active((GtkToggleButton *) radiobutton_1_2_3))
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
    gtk_entry_set_text(GTK_ENTRY(entry_name), " ");
    gtk_label_set_text(GTK_LABEL(label_create_file), " ");
}
