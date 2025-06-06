#pragma once

#include <gtk/gtk.h>

// gchar *f2i(GObject *obj, gdouble d);

void on_add_text(GtkButton *button, gpointer user_data);
void on_scan_canvas(GtkButton *button, gpointer user_data);
void on_add_btn_clicked(GtkButton *button, gpointer user_data);
void on_mask_clicked(
    GtkGestureClick *gesture,
    int n_press,
    double x,
    double y,
    gpointer user_data);