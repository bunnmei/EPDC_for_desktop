#include "main_content.h"

GtkWidget *create_main_content_box(GtkWidget *win){
  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_window_set_child(GTK_WINDOW(win), main_box);

  return main_box;
}

GtkWidget *create_content_left_box(GtkWidget *box){
  GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_add_css_class(left_box, "left-box");
  gtk_widget_set_halign(left_box, GTK_ALIGN_FILL); //box verticalを立ていっぱいに広げる.
  gtk_widget_set_hexpand(left_box, TRUE);  //box verticalを立ていっぱいに広げる.
  gtk_box_append(GTK_BOX(box), left_box);

  return left_box;
}

GtkWidget *create_content_right_box(GtkWidget *box){
  GtkWidget *right_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_size_request(right_box, 300, 0);
  gtk_widget_add_css_class(right_box, "right-box");
  gtk_box_append(GTK_BOX(box), right_box);
  
  return right_box;
}