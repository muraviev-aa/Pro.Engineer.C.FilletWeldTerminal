#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget *window_main;
GtkWidget *fixed_all;
GtkWidget *fixed_thick;
GtkWidget *entry_t1;
GtkWidget *entry_t2;
GtkWidget *label_t1;
GtkWidget *label_t2;
GtkWidget *button_calc;
GtkWidget *fixed_tabl;
GtkWidget *katet_tabl1;
GtkWidget *label_result1;
GtkWidget *katet_tabl2;
GtkWidget *label_result2;
GtkWidget *fixed_file;
GtkWidget *frame_thick;
GtkWidget *frame_tabl;
GtkWidget *frame_file;
GtkWidget *button_new;
GtkWidget *button_new_data;
GtkWidget *button_file;
GtkWidget *entry_name;
GtkBuilder *builder;

gint t1 = 0; // толщина первой свариваемой детали
gint t2 = 0; // толщина второй свариваемой детали
gchar *str_calc1 = "   по расчету,\nно не более";
gchar str_calc2[4];
gchar *str_calc3;

G_MODULE_EXPORT void on_entry_t1_changed(GtkEntry *e);
G_MODULE_EXPORT void on_entry_t2_changed(GtkEntry *e);
G_MODULE_EXPORT void on_button_calc_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_new_data_clicked(GtkButton *b);
G_MODULE_EXPORT void on_button_new_clicked(GtkButton *b);


int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("weld.glade");
    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_window_set_title(GTK_WINDOW(window_main), "Минимальный катет шва 1.0");
    gtk_window_set_resizable(GTK_WINDOW(window_main), FALSE);
    g_signal_connect(window_main, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    fixed_all = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_all"));
    fixed_thick = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_thick"));
    entry_t1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_t1"));
    gtk_entry_set_alignment((GtkEntry *) entry_t1, 1);
    entry_t2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_t2"));
    gtk_entry_set_alignment((GtkEntry *) entry_t2, 1);
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
    button_file = GTK_WIDGET(gtk_builder_get_object(builder, "button_file"));
    entry_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry_name"));
    frame_thick = GTK_WIDGET(gtk_builder_get_object(builder, "frame_thick"));
    frame_tabl = GTK_WIDGET(gtk_builder_get_object(builder, "frame_tabl"));
    frame_file = GTK_WIDGET(gtk_builder_get_object(builder, "frame_file"));

    gtk_window_set_icon_from_file(GTK_WINDOW(window_main), "resources/ant.gif", NULL);
    gtk_widget_show(window_main);

    gtk_main();
    return 0;
}

void on_button_calc_clicked(GtkButton *b)
{
    printf("%d\n", t1);
    printf("%d\n", t2);

    if (t1 < t2 && t1 < 0.6 * t2 || 0.6 * t1 > t2 && t1 > t2)
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
        printf("Calculate 1\n");
    } else
    {
        gtk_widget_hide(katet_tabl1);
        gtk_widget_show(label_result1);
        gtk_widget_hide(katet_tabl2);
        gtk_widget_show(label_result2);
        if (t1 > t2 && t1 <= 5 && t1 >= 4 || t1 < t2 && t2 <= 5 && t2 >= 4)
        {
            gtk_label_set_text(GTK_LABEL(label_result1), "3");
            gtk_label_set_text(GTK_LABEL(label_result2), "3");
        } else if (t1 > t2 && t1 <= 10 && t1 >= 6 || t1 < t2 && t2 <= 10 && t2 >= 6)
        {
            gtk_label_set_text(GTK_LABEL(label_result1), "4");
            gtk_label_set_text(GTK_LABEL(label_result2), "5");
        } else if (t1 > t2 && t1 <= 16 && t1 >= 11 || t1 < t2 && t2 <= 16 && t2 >= 11)
        {
            gtk_label_set_text(GTK_LABEL(label_result1), "6");
            gtk_label_set_text(GTK_LABEL(label_result2), "8");
        } else if (t1 > t2 && t1 <= 22 && t1 >= 17 || t1 < t2 && t2 <= 22 && t2 >= 17)
        {
            gtk_label_set_text(GTK_LABEL(label_result1), "10");
            gtk_label_set_text(GTK_LABEL(label_result2), "12");
        } else if (t1 > t2 && t1 <= 32 && t1 >= 23 || t1 < t2 && t2 <= 32 && t2 >= 23)
        {
            gtk_label_set_text(GTK_LABEL(label_result1), "12");
            gtk_label_set_text(GTK_LABEL(label_result2), "16");
        } else if (t1 > t2 && t1 <= 40 && t1 >= 33 || t1 < t2 && t2 <= 40 && t2 >= 33)
        {
            gtk_label_set_text(GTK_LABEL(label_result1), "16");
            gtk_label_set_text(GTK_LABEL(label_result2), "22");
        }
        printf("Calculate 3, 4\n");
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
    gtk_widget_hide(label_result1);
    gtk_widget_show(katet_tabl2);
    gtk_widget_hide(label_result2);
}