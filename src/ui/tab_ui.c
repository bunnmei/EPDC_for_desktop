#include "tab_ui.h"
#include "text_object.h"
#include "ope_prop.h"
#include "obj_list.h"
#include "USB_btn.h"

GtkWidget *create_tab_ui(GtkWidget *box, PopUp *pop_up) {
  GtkWidget *note_book = gtk_notebook_new();
  gtk_widget_set_size_request(note_book, 300, 0);
  gtk_box_append(GTK_BOX(box), note_book);

  GtkWidget *label1, *label2, *label3;
  GtkWidget *page1_content, *page2_content, *page3_content;
  
  label1 = gtk_label_new("プロパティ");
  gtk_widget_set_hexpand(label1, TRUE);
  label2 = gtk_label_new("オブジェクト");
  gtk_widget_set_hexpand(label2, TRUE);
  label3 = gtk_label_new("USB");
  gtk_widget_set_hexpand(label3, TRUE);
  
  page1_content = create_prop_stack(pop_up->app_obj);
  pop_up->app_obj->stack = page1_content;
  page2_content = create_obj_list_box(pop_up->app_obj);
  page3_content = cretate_usb_controller_box(pop_up);
  gtk_notebook_append_page(GTK_NOTEBOOK(note_book), page1_content, label1);
  gtk_notebook_append_page(GTK_NOTEBOOK(note_book), page2_content, label2);
  gtk_notebook_append_page(GTK_NOTEBOOK(note_book), page3_content, label3);

  return note_book;
}

// GtkWidget 