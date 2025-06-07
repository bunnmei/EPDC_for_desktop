#include "USB_btn.h"
#include "usb_emit.h"

void on_usb_btn_clicked(GtkButton *button, gpointer user_data) {
    PopUp *pop_up = (PopUp *)user_data;
    bool emited = usb_emit(pop_up->pixels, pop_up);
    if(emited) {
      printf("送信完了\n");
    } else {
      printf("送信失敗\n");
    }
}

GtkWidget *cretate_usb_controller_box(PopUp *pop_up) {
  
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_valign(box, GTK_ALIGN_START);

  GtkWidget *emit_btn = gtk_button_new();
  gtk_widget_set_margin_start(emit_btn, 4);
  gtk_widget_add_css_class(emit_btn, "add-button");
  gtk_widget_set_size_request(emit_btn, 50, 50);

  g_signal_connect(emit_btn, "clicked", G_CALLBACK(on_usb_btn_clicked), pop_up);

  GtkWidget *image_usb = gtk_image_new_from_file("src/icons/usb.svg");
  gtk_widget_set_size_request(image_usb, 24, 24);
  gtk_widget_set_valign(image_usb, GTK_ALIGN_CENTER);
  gtk_button_set_child(GTK_BUTTON(emit_btn), image_usb);
  gtk_box_append(GTK_BOX(box), emit_btn);
  return box;
}