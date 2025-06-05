#include "change_prop.h"

void on_prop(GtkButton *button, gpointer user_data){
  const char *button_name = gtk_widget_get_name(GTK_WIDGET(button));
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  g_print("prop btnが押されたよ\n");
  if (g_strcmp0(button_name, "prop_text_x_btn_minus") == 0) {
      g_object_set(app_obj->obj_text, "x", app_obj->obj_text->x -= 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_text_x_btn_plus") == 0) {
    g_object_set(app_obj->obj_text, "x", app_obj->obj_text->x += 10.0, NULL);
  }  
  else if (g_strcmp0(button_name, "prop_text_y_btn_minus") == 0) {
    g_object_set(app_obj->obj_text, "y", app_obj->obj_text->y -= 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_text_y_btn_plus") == 0) {
    g_object_set(app_obj->obj_text, "y", app_obj->obj_text->y += 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_text_font_size_btn_minus") == 0) {
    g_object_set(app_obj->obj_text, "font_size", app_obj->obj_text->font_size -= 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_text_font_size_btn_plus") == 0) {
    g_object_set(app_obj->obj_text, "font_size", app_obj->obj_text->font_size += 10.0, NULL);
  }
  
  gtk_widget_queue_draw(app_obj->ope_draw_area);
}