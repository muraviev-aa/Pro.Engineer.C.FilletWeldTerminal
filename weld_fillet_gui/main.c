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
GtkWidget *katet_tabl2;
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
    entry_t2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_t2"));
    label_t1 = GTK_WIDGET(gtk_builder_get_object(builder, "label_t1"));
    label_t2 = GTK_WIDGET(gtk_builder_get_object(builder, "label_t2"));
    button_calc = GTK_WIDGET(gtk_builder_get_object(builder, "button_calc"));
    fixed_tabl = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_tabl"));
    katet_tabl1 = GTK_WIDGET(gtk_builder_get_object(builder, "katet_tabl1"));
    katet_tabl2 = GTK_WIDGET(gtk_builder_get_object(builder, "katet_tabl2"));
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

    if (t1 < t2 && t1 < 0.6 * t2)
    {
        gdouble kat_max = 1.2 * t1;
        sprintf(str_calc2, "%.1f", kat_max);
        str_calc3 = g_strjoin(" ", str_calc1, str_calc2, NULL);
        gtk_label_set_text(GTK_LABEL(katet_tabl1), str_calc3);
        gtk_label_set_text(GTK_LABEL(katet_tabl2), str_calc3);
        printf("Calculate 1\n");
    } else if (0.6 *t1 > t2 && t1 > t2)
    {
        gdouble kat_max = 1.2 * t2;
        sprintf(str_calc2, "%.1f", kat_max);
        str_calc3 = g_strjoin(" ", str_calc1, str_calc2, NULL);
        gtk_label_set_text(GTK_LABEL(katet_tabl1), str_calc3);
        gtk_label_set_text(GTK_LABEL(katet_tabl2), str_calc3);
        printf("Calculate 2\n");
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
}