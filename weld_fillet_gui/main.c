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
GtkBuilder *builder;

gint t1 = 0; // толщина первой свариваемой детали
gint t2 = 0; // толщина второй свариваемой детали
gint button_click_count = 0;
gchar *str_calc1 = "   по расчету,\nно не более";
gchar str_calc2[4];
gchar *str_calc3;
gchar *str_calc4 = "   по расчету";
GSList *list = NULL; // односвязный список
gint flag_result = 0;

G_MODULE_EXPORT void on_entry_t1_changed(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t2_changed(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t1_insert_text(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t2_insert_text(GtkEntry *e);
G_MODULE_EXPORT void on_entry_name_focus_in_event(GtkEntry *e);
G_MODULE_EXPORT void on_button_calc_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_new_data_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_new_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_file_clicked(GtkButton *b);

void work_widgets();
void size_weld();
void writing_data_s_list(gint count_result);
void working_css_file();

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("weld.glade");
    work_widgets();

    // работа с *.css файлом
    working_css_file();

    gtk_widget_show(window_main);
    gtk_main();

    return 0;
}

void working_css_file()
{
    GtkCssProvider *provider;
    GFile *file;
    GdkScreen *screen;
    screen = gdk_screen_get_default();
    gchar *path;
    path = g_build_filename("style.css", NULL);
    file = g_file_new_for_path(path);

    g_free(path);
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_file(provider, file, NULL);
    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_reset_widgets(screen);
    g_object_unref(provider);
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
    // Управление активностью кнопок
    gtk_widget_set_sensitive(GTK_WIDGET(button_calc), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(button_new), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(button_file), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(entry_name), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(button_new_data), FALSE);
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
        printf("flag is %d\n", flag_result);
    } else if (t1 < t2 && t2 > 40 || t1 > t2 && t1 > 40) // наиболее толстый элемент толщиной более 40 мм
    {
        gtk_label_set_text(GTK_LABEL(katet_tabl1), str_calc4);
        gtk_label_set_text(GTK_LABEL(katet_tabl2), str_calc4);
        flag_result = 2;
        printf("flag is %d\n", flag_result);
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
            printf("flag is %d\n", flag_result);
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
            printf("flag is %d\n", flag_result);
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


}

void writing_data_s_list(gint count_result)
{

    if (count_result == 1) // 1 часть
    {
        Weld_data *first = (Weld_data *) malloc(sizeof(Weld_data));
        first->position = button_click_count;
        first->thick_t1 = gtk_entry_get_text(GTK_ENTRY(entry_t1));
        first->thick_t2 = gtk_entry_get_text(GTK_ENTRY(entry_t2));
        first->weld_leg_1 = gtk_label_get_text(GTK_LABEL(label_result1));
        first->weld_leg_2 = gtk_label_get_text(GTK_LABEL(label_result2));
        list = g_slist_append(list, first);
        printf("- - - - - - - - - -\n");
        printf("part_1\n");
        printf("1 number is %d\n", ((Weld_data *) list->data)->position);
        printf("t1 = %s\n", ((Weld_data *) list->data)->thick_t1);
        printf("t2 = %s\n", ((Weld_data *) list->data)->thick_t2);
        printf("weld_leg1 = %s\n", ((Weld_data *) list->data)->weld_leg_1);
        printf("weld_leg2 = %s\n", ((Weld_data *) list->data)->weld_leg_2);
    } else if (count_result == 2) // 2 часть
    {
        Weld_data *second = g_new(Weld_data, 1);
        second->position = button_click_count;
        second->thick_t1 = gtk_entry_get_text(GTK_ENTRY(entry_t1));
        second->thick_t2 = gtk_entry_get_text(GTK_ENTRY(entry_t2));
        second->weld_leg_1 = gtk_label_get_text(GTK_LABEL(label_result1));
        second->weld_leg_2 = gtk_label_get_text(GTK_LABEL(label_result2));
        list = g_slist_append(list, second);
        printf("- - - - - - - - - -\n");
        printf("part_2\n");
        printf("2 number is %d\n", second->position);
        printf("t1 = %s\n", second->thick_t1);
        printf("t2 = %s\n", second->thick_t2);
        printf("weld_leg1 = %s\n", second->weld_leg_1);
        printf("weld_leg2 = %s\n", second->weld_leg_2);
    } else if (count_result == 3) // 3 часть
    {
        Weld_data *third = g_new(Weld_data, 1);
        third->position = button_click_count;
        third->thick_t1 = gtk_entry_get_text(GTK_ENTRY(entry_t1));
        third->thick_t2 = gtk_entry_get_text(GTK_ENTRY(entry_t2));
        third->weld_leg_1 = gtk_label_get_text(GTK_LABEL(label_result1));
        third->weld_leg_2 = gtk_label_get_text(GTK_LABEL(label_result2));
        list = g_slist_append(list, third);
        printf("- - - - - - - - - -\n");
        printf("part_3\n");
        printf("3 number is %d\n", third->position);
        printf("t1 = %s\n", third->thick_t1);
        printf("t2 = %s\n", third->thick_t2);
        printf("weld_leg1 = %s\n", third->weld_leg_1);
        printf("weld_leg2 = %s\n", third->weld_leg_2);
    } else if (count_result == 4) // 4 часть, конец формирования списка
    {
        Weld_data *third = g_new(Weld_data, 1);
        third->position = button_click_count;
        third->thick_t1 = gtk_entry_get_text(GTK_ENTRY(entry_t1));
        third->thick_t2 = gtk_entry_get_text(GTK_ENTRY(entry_t2));
        third->weld_leg_1 = gtk_label_get_text(GTK_LABEL(label_result1));
        third->weld_leg_2 = gtk_label_get_text(GTK_LABEL(label_result2));
        list = g_slist_append(list, third);

        gtk_button_set_label(GTK_BUTTON(button_new_data), "ОТЧЕТ СФОРМИРОВАН");
        gtk_label_set_text(GTK_LABEL(label_count), "  --->>>");

        // ввод имени и создание файла активно
        gtk_widget_set_sensitive(GTK_WIDGET(button_file), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(entry_name), TRUE);

        printf("- - - - - - - - - -\n");
        printf("part_4\n");
        printf("4 number is %d\n", third->position);
        printf("t1 = %s\n", third->thick_t1);
        printf("t2 = %s\n", third->thick_t2);
        printf("weld_leg1 = %s\n", third->weld_leg_1);
        printf("weld_leg2 = %s\n", third->weld_leg_2);
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
    {
        gtk_widget_set_sensitive(GTK_WIDGET(button_calc), TRUE);
    }
}

void on_entry_t2_insert_text(GtkEntry *e)
{
    if (gtk_entry_get_text_length(GTK_ENTRY(entry_t1)))
    {
        gtk_widget_set_sensitive(GTK_WIDGET(button_calc), TRUE);
    }

}

void on_button_file_clicked(GtkButton *b)
{
    gchar *file_name = NULL;
    const gchar *first_size = ((Weld_data *) list->data)->weld_leg_1;  // катет вар.1
    const gchar *second_size = ((Weld_data *) list->data)->weld_leg_2; // катет вар.2
    cairo_surface_t *surface;
    cairo_t *cr;
    const gchar *file_name_assigned = gtk_entry_get_text(GTK_ENTRY(entry_name));
    // Имя файла задано или используется по умолчанию
    if (g_str_equal(file_name_assigned, "        Введите имя файла"))
        file_name = "text.pdf";
    else
        file_name = g_strjoin(".", file_name_assigned, "pdf", NULL);

    surface = cairo_pdf_surface_create(file_name, 597.6, 842.4);
    cr = cairo_create(surface);

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

    cairo_set_font_size(cr, 12.0);
    cairo_move_to(cr, 200, 25);
    cairo_show_text(cr, "Минимальные катеты сварных угловых швов ");

    char result[5];
    sprintf(result, "%d", ((Weld_data *)list->data)->position); // порядковый номер
    printf("%s", result);
    cairo_set_font_size(cr, 10.0);
    cairo_move_to(cr, 48, 45);
    cairo_show_text(cr, g_strjoin(result, "№", ".", NULL));

    cairo_move_to(cr, 70, 45);
    cairo_show_text(cr, g_strjoin(" ", "Толщина первого свариваемого элемента",
                                  g_strjoin(" ", ((Weld_data *) list->data)->thick_t1, "мм", NULL), NULL));
    cairo_move_to(cr, 70, 60);
    cairo_show_text(cr, g_strjoin(" ", "Толщина второго свариваемого элемента",
                                  g_strjoin(" ", ((Weld_data *) list->data)->thick_t2, "мм", NULL), NULL));
    cairo_move_to(cr, 60, 80);
    cairo_show_text(cr, "Таблица 38 СП 16.13330.2017 изм. № 2, 3");

    // толщина линии таблицы
    cairo_set_line_width(cr, 0.4);
    // наружная рамка таблицы
    cairo_rectangle(cr, 60, 85, 510, 145);
    // 1-й столбец
    cairo_move_to(cr, 90, 110);
    cairo_show_text(cr, "Тип соединения");
    cairo_move_to(cr, 70, 145);
    cairo_show_text(cr, "Тавровое с");
    cairo_move_to(cr, 70, 155);
    cairo_show_text(cr, "двусторонними угловыми");
    cairo_move_to(cr, 70, 165);
    cairo_show_text(cr, "швами; нахлесточное и");
    cairo_move_to(cr, 70, 175);
    cairo_show_text(cr, "угловое");
    cairo_move_to(cr, 70, 200);
    cairo_show_text(cr, "Угловое и тавровое с");
    cairo_move_to(cr, 70, 210);
    cairo_show_text(cr, "односторонними");
    cairo_move_to(cr, 70, 220);
    cairo_show_text(cr, "угловыми швами");
    // 2-й столбец
    cairo_move_to(cr, 235, 110);
    cairo_show_text(cr, "Вид сварки");
    cairo_move_to(cr, 225, 170);
    cairo_show_text(cr, "Ручная дуговая,");
    cairo_move_to(cr, 220, 180);
    cairo_show_text(cr, "автоматическая и");
    cairo_move_to(cr, 218, 190);
    cairo_show_text(cr, "механизированная");
    // 3-й столбец
    cairo_move_to(cr, 340, 100);
    cairo_show_text(cr, "Минимальный катет шва kf, мм, при толщине");
    cairo_move_to(cr, 331, 110);
    cairo_show_text(cr, "более толстого из свариваемых элементов Т, мм");
    cairo_move_to(cr, 440, 120);
    if (t1 > t2 || t1 == t2)
        cairo_show_text(cr, ((Weld_data *) list->data)->thick_t1);
    else
        cairo_show_text(cr, ((Weld_data *) list->data)->thick_t2);
    cairo_move_to(cr, 440, 160);
    cairo_show_text(cr, first_size);
    cairo_move_to(cr, 440, 210);
    cairo_show_text(cr, second_size);
    // Первая вертикальная линия
    cairo_move_to(cr, 200.0, 85.0);
    cairo_line_to(cr, 200.0, 230.0);
    // Вторая вертикальная линия
    cairo_move_to(cr, 320.0, 85.0);
    cairo_line_to(cr, 320.0, 230.0);
    // Первая горизонтальная линия
    cairo_move_to(cr, 60.0, 130.0);
    cairo_line_to(cr, 570.0, 130.0);
    // Вторая горизонтальная линия
    cairo_move_to(cr, 60.0, 185.0);
    cairo_line_to(cr, 200.0, 185.0);
    cairo_move_to(cr, 320, 185.0);
    cairo_line_to(cr, 570.0, 185.0);

    // 2-я таблица

    cairo_stroke(cr);
    cairo_fill(cr);

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    g_slist_free(list);
}

// Очищаем entry от существующего текста
void on_entry_name_focus_in_event(GtkEntry *e)
{
    gtk_entry_set_text(GTK_ENTRY(entry_name), " ");
}
