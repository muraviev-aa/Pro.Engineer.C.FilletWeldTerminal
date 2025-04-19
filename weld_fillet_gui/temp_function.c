
#include "temp_function.h"

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
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_reset_widgets(screen);
    g_object_unref(provider);
}

void data_collection(cairo_t *cr, GSList *list, gint shift_value, gint serial_number)
{
    char position_1[5];   // порядковый номер расчета
    sprintf(position_1, "%d", ((Weld_data *) g_slist_nth(list, serial_number)->data)->position);
    char tick_1[5];       // толщина первого элемента
    sprintf(tick_1, "%d", ((Weld_data *) g_slist_nth(list, serial_number)->data)->thick_t1);
    char tick_2[5];       // толщина второго элемента
    sprintf(tick_2, "%d", ((Weld_data *) g_slist_nth(list, serial_number)->data)->thick_t2);
    gchar thick_max[5];   // максимальная толщина элемента
    sprintf(thick_max, "%d", ((Weld_data *) g_slist_nth(list, serial_number)->data)->thick_max);
    gchar leg_1_1[5];     // катет 1
    gchar leg_2_1[5];     // катет 2

    if (((Weld_data *) g_slist_nth(list, serial_number)->data)->weld_leg_1 == 0)  // если условие не выполнено
    {
        gdouble max_leg_thin = ((Weld_data *) g_slist_nth(list, serial_number)->data)->max_leg;
        char str[10];                                                   // максимальный катет по наименьшей толщине
        sprintf(str, "%.1f", max_leg_thin);
        cairo_move_to(cr, 380, 153 + shift_value);
        cairo_show_text(cr, "по расчету, но не более");
        cairo_move_to(cr, 417, 170 + shift_value);
        cairo_show_text(cr, g_strjoin(" ", str, "мм", NULL));
        cairo_move_to(cr, 380, 202 + shift_value);
        cairo_show_text(cr, "по расчету, но не более");
        cairo_move_to(cr, 417, 219 + shift_value);
        cairo_show_text(cr, g_strjoin(" ", str, "мм", NULL));
    } else
    {
        sprintf(leg_1_1, "%d", ((Weld_data *) g_slist_nth(list, serial_number)->data)->weld_leg_1);
        sprintf(leg_2_1, "%d", ((Weld_data *) g_slist_nth(list, serial_number)->data)->weld_leg_2);
        cairo_move_to(cr, 440, 160 + shift_value);
        cairo_show_text(cr, leg_1_1);                  // записываем катет 1 в табл.
        cairo_move_to(cr, 440, 210 + shift_value);
        cairo_show_text(cr, leg_2_1);                  // записываем катет 2 в табл.
    }

    cairo_set_font_size(cr, 10.0);   // размер шрифта pdf документа
    cairo_move_to(cr, 48, 45 + shift_value);
    cairo_show_text(cr, g_strjoin(position_1, "№", ".", NULL));
    cairo_move_to(cr, 70, 45 + shift_value);
    cairo_show_text(cr,
                    g_strjoin(" ", "Толщина первого свариваемого элемента",
                              g_strjoin(" ", tick_1, "мм", NULL), NULL));   // записываем толщину t1 в табл.
    cairo_move_to(cr, 70, 60 + shift_value);
    cairo_show_text(cr,
                    g_strjoin(" ", "Толщина второго свариваемого элемента",
                              g_strjoin(" ", tick_2, "мм", NULL), NULL));   // записываем толщину t2 в табл.
    cairo_move_to(cr, 60, 80 + shift_value);
    cairo_show_text(cr, "Таблица 38 СП 16.13330.2017 изм. № 2, 3");

    // толщина линии таблицы
    cairo_set_line_width(cr, 0.6);

    // 1-й столбец
    cairo_move_to(cr, 90, 110 + shift_value);
    cairo_show_text(cr, "Тип соединения");
    cairo_move_to(cr, 70, 145 + shift_value);
    cairo_show_text(cr, "Тавровое с");
    cairo_move_to(cr, 70, 155 + shift_value);
    cairo_show_text(cr, "двусторонними угловыми");
    cairo_move_to(cr, 70, 165 + shift_value);
    cairo_show_text(cr, "швами; нахлесточное и");
    cairo_move_to(cr, 70, 175 + shift_value);
    cairo_show_text(cr, "угловое");
    cairo_move_to(cr, 70, 200 + shift_value);
    cairo_show_text(cr, "Угловое и тавровое с");
    cairo_move_to(cr, 70, 210 + shift_value);
    cairo_show_text(cr, "односторонними");
    cairo_move_to(cr, 70, 220 + shift_value);
    cairo_show_text(cr, "угловыми швами");
    // 2-й столбец
    cairo_move_to(cr, 235, 110 + shift_value);
    cairo_show_text(cr, "Вид сварки");
    cairo_move_to(cr, 225, 170 + shift_value);
    cairo_show_text(cr, "Ручная дуговая,");
    cairo_move_to(cr, 220, 180 + shift_value);
    cairo_show_text(cr, "автоматическая и");
    cairo_move_to(cr, 218, 190 + shift_value);
    cairo_show_text(cr, "механизированная");
    // 3-й столбец
    cairo_move_to(cr, 340, 100 + shift_value);
    cairo_show_text(cr, "Минимальный катет шва kf, мм, при толщине");
    cairo_move_to(cr, 331, 110 + shift_value);
    cairo_show_text(cr, "более толстого из свариваемых элементов Т, мм");
    cairo_move_to(cr, 440, 120 + shift_value);

    cairo_show_text(cr, thick_max);                // записываем макс. значение в табл.
}

void create_table(cairo_t *cr, gint shift_value)
{
    // наружная рамка таблицы
    cairo_rectangle(cr, 60, 85 + shift_value, 510, 145);
    // Первая вертикальная линия
    cairo_move_to(cr, 200.0, 85.0 + shift_value);
    cairo_line_to(cr, 200.0, 230.0 + shift_value);
    // Вторая вертикальная линия
    cairo_move_to(cr, 320.0, 85.0 + shift_value);
    cairo_line_to(cr, 320.0, 230.0 + shift_value);
    // Первая горизонтальная линия
    cairo_move_to(cr, 60.0, 130.0 + shift_value);
    cairo_line_to(cr, 570.0, 130.0 + shift_value);
    // Вторая горизонтальная линия
    // 1-я
    cairo_move_to(cr, 60.0, 185.0 + shift_value);
    cairo_line_to(cr, 200.0, 185.0 + shift_value);
    // 2-я
    cairo_move_to(cr, 320, 185.0 + shift_value);
    cairo_line_to(cr, 570.0, 185.0 + shift_value);
}
