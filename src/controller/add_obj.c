
#include "add_obj.h"
#include "canvas.h"

gchar* f2i(GObject *obj, gdouble d) {
  return g_strdup_printf("X: %d", (int)d);
}

void on_add_btn_clicked(GtkButton *button, gpointer user_data) {
  PopUp *pop_up = (PopUp *)user_data;
  gtk_widget_set_visible(pop_up->mask, TRUE);
  gtk_widget_set_visible(pop_up->pop_up_box, TRUE);
}

void on_add_text(GtkButton *button, gpointer user_data) {
  PopUp *pop_up = (PopUp *)user_data;
  gtk_widget_set_visible(pop_up->mask, FALSE);
  gtk_widget_set_visible(pop_up->pop_up_box, FALSE);
  TextObject *new_obj = text_object_new("dammy", g_uuid_string_random(), 50.0, 150.0, 100.0, BLACK);
  pop_up->app_obj->obj_mode = TEXT;
  pop_up->app_obj->obj_text = new_obj;

  GtkExpression *params_x[1];
  params_x[0] = gtk_property_expression_new(TEXT_TYPE_OBJECT, NULL, "x");
  GtkExpression *format_ex_x = gtk_cclosure_expression_new(G_TYPE_STRING, NULL, 1, params_x, G_CALLBACK(f2i), NULL, NULL);
  gtk_expression_bind(format_ex_x, pop_up->app_obj->text_labels->x, "label", pop_up->app_obj->obj_text);
  
  GtkExpression *params_y[1];
  params_y[0] = gtk_property_expression_new(TEXT_TYPE_OBJECT, NULL, "y");
  GtkExpression *format_ex_y = gtk_cclosure_expression_new(G_TYPE_STRING, NULL, 1, params_y, G_CALLBACK(f2i), NULL, NULL);
  gtk_expression_bind(format_ex_y, pop_up->app_obj->text_labels->y, "label", pop_up->app_obj->obj_text);

  GtkExpression *params_font_size[1];
  params_font_size[0] = gtk_property_expression_new(TEXT_TYPE_OBJECT, NULL, "font_size");
  GtkExpression *format_ex_font_size = gtk_cclosure_expression_new(G_TYPE_STRING, NULL, 1, params_font_size, G_CALLBACK(f2i), NULL, NULL);
  gtk_expression_bind(format_ex_font_size, pop_up->app_obj->text_labels->font_size, "label", pop_up->app_obj->obj_text);

//同じ文字列をセットするとキャッシュされているため違う文字を代入　仮　GtkEntryBufferを使う？.　
  gchar *dset = g_strdup_printf("%s%d", new_obj->text, pop_up->app_obj->text_objs->len);
  gtk_editable_set_text(GTK_EDITABLE(pop_up->app_obj->text_labels->entry), dset);

  g_list_store_append(pop_up->app_obj->text_store, new_obj);

  gtk_stack_set_visible_child_name(GTK_STACK(pop_up->app_obj->stack), "text");
  g_ptr_array_add(pop_up->app_obj->text_objs, new_obj);
  gtk_widget_queue_draw(pop_up->app_obj->ope_draw_area);
}

void on_mask_clicked(
  GtkGestureClick *gesture,
  int n_press,
  double x,
  double y,
  gpointer user_data) {

  PopUp *pop_up = (PopUp *)user_data;
  gtk_widget_set_visible(pop_up->mask, FALSE);
  gtk_widget_set_visible(pop_up->pop_up_box, FALSE);
}