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


void on_rect_prop(GtkButton *button, gpointer user_data){
  const char *button_name = gtk_widget_get_name(GTK_WIDGET(button));
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  g_print("rect prop btnが押されたよ\n");
  if (g_strcmp0(button_name, "prop_rect_x_btn_minus") == 0) {
      g_object_set(app_obj->obj_rect, "x", app_obj->obj_rect->x -= 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_rect_x_btn_plus") == 0) {
    g_object_set(app_obj->obj_rect, "x", app_obj->obj_rect->x += 10.0, NULL);
  }  
  else if (g_strcmp0(button_name, "prop_rect_y_btn_minus") == 0) {
    g_object_set(app_obj->obj_rect, "y", app_obj->obj_rect->y -= 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_rect_y_btn_plus") == 0) {
    g_object_set(app_obj->obj_rect, "y", app_obj->obj_rect->y += 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_rect_w_btn_minus") == 0) {
    g_object_set(app_obj->obj_rect, "w", app_obj->obj_rect->w -= 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_rect_w_btn_plus") == 0) {
    g_object_set(app_obj->obj_rect, "w", app_obj->obj_rect->w += 10.0, NULL);
  }
 
  else if (g_strcmp0(button_name, "prop_rect_h_btn_minus") == 0) {
    g_object_set(app_obj->obj_rect, "h", app_obj->obj_rect->h -= 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_rect_h_btn_plus") == 0) {
    g_object_set(app_obj->obj_rect, "h", app_obj->obj_rect->h += 10.0, NULL);
  }
  
  else if (g_strcmp0(button_name, "prop_rect_degree_btn_minus") == 0) {
    g_object_set(app_obj->obj_rect, "degree", app_obj->obj_rect->degree -= 10.0, NULL);
  }
  else if (g_strcmp0(button_name, "prop_rect_degree_btn_plus") == 0) {
    g_object_set(app_obj->obj_rect, "degree", app_obj->obj_rect->degree += 10.0, NULL);
  }
  gtk_widget_queue_draw(app_obj->ope_draw_area);
}