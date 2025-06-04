#include "ope_prop.h"

static void on_prop(GtkButton *button, gpointer user_data){
  const char *button_name = gtk_widget_get_name(GTK_WIDGET(button));
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  g_print("prop btnが押されたよ\n");
  if (g_strcmp0(button_name, "prop_text_x_btn_minus") == 0) {
      g_print("prop x -\n");
  }
  else if (g_strcmp0(button_name, "prop_text_x_btn_plus") == 0)
  {
    g_print("prop x +\n");
    g_object_set(app_obj->obj_text, "x", app_obj->obj_text->x += 10.0, NULL);
  }
  gtk_widget_queue_draw(app_obj->ope_draw_area);
}

GtkWidget *create_prop_stack(EPDC_App_Obj *app_obj) {
  GtkWidget *stack = gtk_stack_new();
  gtk_widget_add_css_class(stack, "stack");
  gtk_widget_set_valign(stack, GTK_ALIGN_FILL);

  GtkWidget *select_none = create_none_select_box();
  GtkWidget *text_prop_box = create_text_prop_box(app_obj);

  gtk_stack_add_named(GTK_STACK(stack), select_none, "none");
  gtk_stack_add_named(GTK_STACK(stack), text_prop_box, "text");
  
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "none");
  return stack;
}

GtkWidget *create_none_select_box() {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *none_label = gtk_label_new("None");
  gtk_box_append(GTK_BOX(box), none_label);
  return box;
}

GtkWidget *create_text_prop_box(EPDC_App_Obj *app_obj){
  GtkWidget *text_prop_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *x = create_prop("x", app_obj);

  gtk_box_append(GTK_BOX(text_prop_box), x);
  return text_prop_box;
}

GtkWidget *create_prop(char *id, EPDC_App_Obj *app_obj){
  char id_name[32];
  GtkWidget *prop_box_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(prop_box_h, "prop_box");
  gtk_widget_set_valign(prop_box_h, GTK_ALIGN_START);
  
  snprintf(id_name, sizeof(id_name), "prop_text_%s_btn_minus", id);
  GtkWidget *prop_btn_minus = gtk_button_new();
  gtk_widget_set_name(prop_btn_minus, id_name);
  gtk_widget_add_css_class(prop_btn_minus, "prop_btn");
  gtk_widget_set_valign(prop_btn_minus, GTK_ALIGN_CENTER);

  GtkWidget *prop_label = gtk_label_new("");
  gtk_widget_set_hexpand(prop_label, TRUE);
  
  snprintf(id_name, sizeof(id_name), "prop_text_%s_btn_plus", id);
  GtkWidget *prop_btn_plus = gtk_button_new();
  gtk_widget_set_name(prop_btn_plus, id_name);
  gtk_widget_set_valign(prop_btn_plus, GTK_ALIGN_CENTER);
  gtk_widget_add_css_class(prop_btn_plus, "prop_btn");

  g_signal_connect(prop_btn_minus, "clicked", G_CALLBACK(on_prop), app_obj);
  g_signal_connect(prop_btn_plus, "clicked", G_CALLBACK(on_prop), app_obj);

  gtk_box_append(GTK_BOX(prop_box_h), prop_btn_minus);
  gtk_box_append(GTK_BOX(prop_box_h), prop_label);
  gtk_box_append(GTK_BOX(prop_box_h), prop_btn_plus);

  return prop_box_h;
}