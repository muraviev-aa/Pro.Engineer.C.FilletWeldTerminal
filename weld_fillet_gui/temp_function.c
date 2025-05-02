
#include "temp_function.h"

void working_css_file()
{
    GtkCssProvider *provider;
    GFile *file;
    GdkScreen *screen;
    screen = gdk_screen_get_default();
    gchar *path;
    path = g_build_filename("resources/style.css", NULL);
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

    if (((Weld_data *) g_slist_nth(list, serial_number)->data)->weld_leg_1 == 0)  // условие не выполнено
    {
        gdouble max_leg_thin = ((Weld_data *) g_slist_nth(list, serial_number)->data)->max_leg;
        char str[10];                                                   // максимальный катет по наименьшей толщине
        sprintf(str, "%.1f", max_leg_thin);
        cairo_move_to(cr, 387, 153 + shift_value);
        cairo_show_text(cr, "по расчету, но не более");
        cairo_move_to(cr, 427, 170 + shift_value);
        cairo_show_text(cr, g_strjoin(" ", str, "мм", NULL));
        cairo_move_to(cr, 387, 202 + shift_value);
        cairo_show_text(cr, "по расчету, но не более");
        cairo_move_to(cr, 427, 219 + shift_value);
        cairo_show_text(cr, g_strjoin(" ", str, "мм", NULL));

    } else                                                                           // условие выполнено
    {
        sprintf(leg_1_1, "%d", ((Weld_data *) g_slist_nth(list, serial_number)->data)->weld_leg_1);
        sprintf(leg_2_1, "%d", ((Weld_data *) g_slist_nth(list, serial_number)->data)->weld_leg_2);
        cairo_move_to(cr, 444, 160 + shift_value);
        cairo_show_text(cr, leg_1_1);                  // записываем катет 1 в табл.
        cairo_move_to(cr, 444, 210 + shift_value);
        cairo_show_text(cr, leg_2_1);                  // записываем катет 2 в табл.
    }

    cairo_move_to(cr, 63, 45 + shift_value);
    cairo_show_text(cr, g_strjoin(position_1, "№", ".", NULL));
    cairo_move_to(cr, 85, 45 + shift_value);
    cairo_show_text(cr,
                    g_strjoin(" ", "Толщина первого свариваемого элемента",
                              g_strjoin(" ", tick_1, "мм", NULL), NULL));   // записываем толщину t1 в табл.
    cairo_move_to(cr, 85, 60 + shift_value);
    cairo_show_text(cr,
                    g_strjoin(" ", "Толщина второго свариваемого элемента",
                              g_strjoin(" ", tick_2, "мм", NULL), NULL));   // записываем толщину t2 в табл.
    cairo_move_to(cr, 70, 80 + shift_value);
    cairo_show_text(cr, "Таблица 38 СП 16.13330.2017 изм. № 2, 3");

    // толщина линии таблицы
    //cairo_set_line_width(cr, 0.6);

    // 1-й столбец
    cairo_move_to(cr, 94, 110 + shift_value);
    cairo_show_text(cr, "Тип соединения");
    cairo_move_to(cr, 74, 145 + shift_value);
    cairo_show_text(cr, "Тавровое с");
    cairo_move_to(cr, 74, 155 + shift_value);
    cairo_show_text(cr, "двусторонними угловыми");
    cairo_move_to(cr, 74, 165 + shift_value);
    cairo_show_text(cr, "швами; нахлесточное и");
    cairo_move_to(cr, 74, 175 + shift_value);
    cairo_show_text(cr, "угловое");
    cairo_move_to(cr, 74, 200 + shift_value);
    cairo_show_text(cr, "Угловое и тавровое с");
    cairo_move_to(cr, 74, 210 + shift_value);
    cairo_show_text(cr, "односторонними");
    cairo_move_to(cr, 74, 220 + shift_value);
    cairo_show_text(cr, "угловыми швами");
    // 2-й столбец
    cairo_move_to(cr, 239, 110 + shift_value);
    cairo_show_text(cr, "Вид сварки");
    cairo_move_to(cr, 229, 170 + shift_value);
    cairo_show_text(cr, "Ручная дуговая,");
    cairo_move_to(cr, 224, 180 + shift_value);
    cairo_show_text(cr, "автоматическая и");
    cairo_move_to(cr, 222, 190 + shift_value);
    cairo_show_text(cr, "механизированная");
    // 3-й столбец
    cairo_move_to(cr, 344, 100 + shift_value);
    cairo_show_text(cr, "Минимальный катет шва kf, мм, при толщине");
    cairo_move_to(cr, 335, 110 + shift_value);
    cairo_show_text(cr, "более толстого из свариваемых элементов Т, мм");
    cairo_move_to(cr, 440, 120 + shift_value);
    cairo_show_text(cr, thick_max);                // записываем макс. значение в табл.
}

void create_table(cairo_t *cr, gint shift_value)
{
    // наружная рамка таблицы
    cairo_rectangle(cr, 64, 85 + shift_value, 510, 145);
    // Первая вертикальная линия
    cairo_move_to(cr, 204.0, 85.0 + shift_value);
    cairo_line_to(cr, 204.0, 230.0 + shift_value);
    // Вторая вертикальная линия
    cairo_move_to(cr, 324.0, 85.0 + shift_value);
    cairo_line_to(cr, 324.0, 230.0 + shift_value);
    // Первая горизонтальная линия
    cairo_move_to(cr, 64.0, 130.0 + shift_value);
    cairo_line_to(cr, 574.0, 130.0 + shift_value);
    // Вторая горизонтальная линия
    // 1-я линия
    cairo_move_to(cr, 64.0, 185.0 + shift_value);
    cairo_line_to(cr, 204.0, 185.0 + shift_value);
    // 2-я линия
    cairo_move_to(cr, 324, 185.0 + shift_value);
    cairo_line_to(cr, 574.0, 185.0 + shift_value);
    cairo_stroke(cr);  // рисуем линии
}

void insert_png(cairo_t *cr, GSList *list, gint shift_value, gint serial_number)
{
    if (((Weld_data *) g_slist_nth(list, serial_number)->data)->weld_leg_1 == 0)
    {
        cairo_surface_t *image = cairo_image_surface_create_from_png("resources/condition_not_met.png");
        if (cairo_surface_status(image) != CAIRO_STATUS_SUCCESS) {
            fprintf(stderr, "Failed to load image.png\n");
        }
        cairo_set_source_surface(cr, image, 380, 38 + shift_value);
        cairo_paint(cr);
    } else
    {
        cairo_surface_t *image = cairo_image_surface_create_from_png("resources/condition_met.png");
        if (cairo_surface_status(image) != CAIRO_STATUS_SUCCESS) {
            fprintf(stderr, "Failed to load image.png\n");
        }
        cairo_set_source_surface(cr, image, 380, 38 + shift_value);
        cairo_paint(cr);
    }
}

void work_dates(cairo_t *cr)
{
    time_t now = time(NULL);              // получаем текущее время
    struct tm *local = localtime(&now);
    // Извлекаем день, месяц и год
    gint day = local->tm_mday;
    gint month = local->tm_mon + 1;            // месяцы начинаются с 0
    gint year = local->tm_year + 1900;         // годы начинаются с 1900
    gchar current_day[2];
    gchar current_month[2];
    gchar current_year[5];
    sprintf(current_day, "%d", day);
    sprintf(current_month, "%d", month);
    sprintf(current_year, "%d", year);

    cairo_move_to(cr, 450, 25);
    if (day < 10)
        cairo_show_text(cr, g_strjoin("", "0", current_day, NULL));
    else
        cairo_show_text(cr, current_day);
    cairo_move_to(cr, 461, 25);
    cairo_show_text(cr, ".");
    cairo_move_to(cr, 464, 25);
    if (month < 10)
        cairo_show_text(cr, g_strjoin("", "0", current_month, NULL));
    else
        cairo_show_text(cr, current_month);
    cairo_move_to(cr, 475, 25);
    cairo_show_text(cr, g_strjoin("", ".", current_year, NULL));
}

void set_widget_alignment(GtkEntry *entry) {
    gtk_entry_set_alignment(entry, 1);
}

GtkWidget *get_widget(GtkBuilder *builder, const char *name)
{
    return GTK_WIDGET(gtk_builder_get_object(builder, name));
}

void set_widgets_sensitive(GtkWidget **widgets, int count, gboolean sensitive)
{
    for (int i = 0; i < count; i++)
        gtk_widget_set_sensitive(widgets[i], sensitive);
}
