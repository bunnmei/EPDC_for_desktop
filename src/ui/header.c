#include "header.h"

static void on_header_buttons(GtkWidget *widget, gpointer data) {
  GtkWindow *window = GTK_WINDOW(data);
  const char *button_name = gtk_widget_get_name(GTK_WIDGET(widget)); 
  if (g_strcmp0(button_name, "h-close") == 0) {
    gtk_window_close(window);
  } else if (g_strcmp0(button_name, "h-expand") == 0) {
    if (gtk_window_is_maximized(window)) {
      gtk_window_unmaximize(window);
    } else {
      gtk_window_maximize(window);
    }
  } else if (g_strcmp0(button_name, "h-window-min") == 0) {
     gtk_window_minimize(window);
  }
}

void create_header(GtkWidget *win) {
  
  GtkWidget *label = gtk_label_new("");
  GtkWidget *header_bar = gtk_header_bar_new();
  gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header_bar), label);
  gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header_bar), FALSE);

  gtk_window_set_titlebar(GTK_WINDOW(win), header_bar);

  GtkWidget *image = gtk_image_new_from_file("src/icons/close.svg");
  gtk_widget_set_size_request(image, 18, 18);
  gtk_widget_set_valign(image, GTK_ALIGN_CENTER);
  
  GtkWidget *image_square = gtk_image_new_from_file("src/icons/square.svg");
  gtk_widget_set_size_request(image_square, 18, 18);
  gtk_widget_set_valign(image_square, GTK_ALIGN_CENTER);

  GtkWidget *image_minimize = gtk_image_new_from_file("src/icons/minimize.svg");
  gtk_widget_set_size_request(image_minimize, 18, 18);
  gtk_widget_set_valign(image_minimize, GTK_ALIGN_CENTER);

  GtkWidget *button_close = gtk_button_new();
  gtk_button_set_child(GTK_BUTTON(button_close), image);
  gtk_widget_add_css_class(button_close, "header-bar-button");
  gtk_widget_add_css_class(button_close, "close-button");
  gtk_widget_set_name(button_close, "h-close");
  gtk_widget_set_valign(button_close, GTK_ALIGN_FILL);
  gtk_widget_set_size_request(button_close, 50, 40);
  g_signal_connect(button_close, "clicked", G_CALLBACK(on_header_buttons), win);
  gtk_header_bar_pack_end (GTK_HEADER_BAR (header_bar), button_close);
  
  GtkWidget *button_expand = gtk_button_new();
  gtk_button_set_child(GTK_BUTTON(button_expand), image_square);
  gtk_widget_add_css_class(button_expand, "header-bar-button");
  gtk_widget_add_css_class(button_expand, "expand-button");
  gtk_widget_set_name(button_expand, "h-expand");
  gtk_widget_set_valign(button_expand, GTK_ALIGN_FILL);
  gtk_widget_set_size_request(button_expand, 50, 40);
  g_signal_connect(button_expand, "clicked", G_CALLBACK(on_header_buttons), win);
  gtk_header_bar_pack_end (GTK_HEADER_BAR (header_bar), button_expand);
  
  GtkWidget *button_window_min = gtk_button_new();
  gtk_button_set_child(GTK_BUTTON(button_window_min), image_minimize);
  gtk_widget_set_name(button_window_min, "h-window-min");
  gtk_widget_add_css_class(button_window_min, "header-bar-button");
  gtk_widget_add_css_class(button_window_min, "window-min-button");
  gtk_widget_set_valign(button_window_min, GTK_ALIGN_FILL);
  gtk_widget_set_size_request(button_window_min, 50, 40);
  g_signal_connect(button_window_min, "clicked", G_CALLBACK(on_header_buttons), win);
  gtk_header_bar_pack_end (GTK_HEADER_BAR (header_bar), button_window_min);

}