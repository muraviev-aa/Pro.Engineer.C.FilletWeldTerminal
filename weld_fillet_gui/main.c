#include <stdio.h>
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
GtkWidget *button_new_data;
GtkWidget *button_file;
GtkWidget *entry_name;
GtkBuilder *builder;

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("weld.glade");
    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_window_set_title(GTK_WINDOW(window_main), "Минимальный катет шва");
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
