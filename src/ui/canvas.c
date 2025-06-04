#include "canvas.h"
#include "text_object.h"

static void
draw_function(GtkDrawingArea *drawing_area,
              cairo_t *cr,
              int width,
              int height,
              gpointer user_data)
{
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
  cairo_paint(cr);

  for (guint i = 0; i < app_obj->text_objs->len ; i++) {
    TextObject *text_obj = (TextObject *)g_ptr_array_index(app_obj->text_objs, i);
    g_print("canvas rand = %s\n", text_obj->uuid
    );
    if(text_obj->color == BLACK) {
      cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    } else if(text_obj->color == RED) {
      cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    }
    cairo_move_to(cr, text_obj->x, text_obj->y);
    cairo_set_font_size(cr, text_obj->font_size);
    cairo_show_text(cr, text_obj->text);
  }
  
}

static void on_add_btn_clicked(GtkButton *button, gpointer user_data) {
  PopUp *pop_up = (PopUp *)user_data;
  gtk_widget_set_visible(pop_up->mask, TRUE);
  gtk_widget_set_visible(pop_up->pop_up_box, TRUE);
}

static void on_add_text(GtkButton *button, gpointer user_data) {
  PopUp *pop_up = (PopUp *)user_data;
  gtk_widget_set_visible(pop_up->mask, FALSE);
  gtk_widget_set_visible(pop_up->pop_up_box, FALSE);
  TextObject *new_obj = text_object_new("dammy", g_uuid_string_random(), 50.0, 150.0, 100.0, BLACK);
  pop_up->app_obj->obj_mode = TEXT;
  pop_up->app_obj->obj_text = new_obj;
  gtk_stack_set_visible_child_name(GTK_STACK(pop_up->app_obj->stack), "text");
  g_ptr_array_add(pop_up->app_obj->text_objs, new_obj);
  gtk_widget_queue_draw(pop_up->app_obj->ope_draw_area);
}

static void on_mask_clicked(
  GtkGestureClick *gesture,
  int n_press,
  double x,
  double y,
  gpointer user_data) {

  PopUp *pop_up = (PopUp *)user_data;
  gtk_widget_set_visible(pop_up->mask, FALSE);
  gtk_widget_set_visible(pop_up->pop_up_box, FALSE);
}

GtkWidget *create_canvas(GtkWidget *box, EPDC_App_Obj *app_obj){
  PopUp *pop_up = g_new0(PopUp, 1);
  pop_up->mask = NULL;
  pop_up->pop_up_box = NULL;
  pop_up->app_obj = app_obj;

  GtkWidget *overlay = gtk_overlay_new();
  gtk_widget_set_hexpand(overlay, TRUE);
  gtk_widget_set_vexpand(overlay, TRUE);
  gtk_box_append(GTK_BOX(box), overlay);

  GtkWidget *canvas_layer = create_canvas_layer(app_obj);
  GtkWidget *mask_layer = create_mask_layer(pop_up);
  GtkWidget *pop_up_layer = create_pop_up_layer(pop_up);
  GtkWidget *btn_layer = create_operate_btns_layer(pop_up);
  gtk_overlay_set_child(GTK_OVERLAY(overlay), canvas_layer);
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), btn_layer);
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), mask_layer);
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), pop_up_layer);

  return overlay;
}

GtkWidget *create_canvas_layer(EPDC_App_Obj *app_obj) {
  GtkWidget *canvas_layer_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_add_css_class(canvas_layer_box, "canvas-layer");
  gtk_widget_set_halign(canvas_layer_box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(canvas_layer_box, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(canvas_layer_box, TRUE);
  gtk_widget_set_vexpand(canvas_layer_box, TRUE);

  GtkWidget *operate_drawing_area = gtk_drawing_area_new();
  app_obj->ope_draw_area = operate_drawing_area;
  gtk_widget_set_size_request(operate_drawing_area, CANVAS_WIDTH, CANVAS_HEIGHT);
  gtk_drawing_area_set_draw_func(
    GTK_DRAWING_AREA(operate_drawing_area),
    draw_function,
    app_obj, 
    NULL
  );
  gtk_box_append(GTK_BOX(canvas_layer_box), operate_drawing_area);

  GtkWidget *preview_drawing_area = gtk_drawing_area_new();
  app_obj->ope_draw_area = preview_drawing_area;
  gtk_widget_set_size_request(preview_drawing_area, CANVAS_WIDTH, CANVAS_HEIGHT);
  gtk_drawing_area_set_draw_func(
    GTK_DRAWING_AREA(preview_drawing_area),
    draw_function,
    app_obj, 
    NULL
  );
  gtk_box_append(GTK_BOX(canvas_layer_box), preview_drawing_area);

  return canvas_layer_box;
}

GtkWidget *create_operate_btns_layer(PopUp *pop_up) {
  GtkWidget *operate_btns_layer_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(operate_btns_layer_box, GTK_ALIGN_END);

  GtkWidget *add_obj_btn = gtk_button_new();
  gtk_widget_set_margin_start(add_obj_btn, 4);
  gtk_widget_add_css_class(add_obj_btn, "add-button");
  gtk_widget_set_size_request(add_obj_btn, 50, 50);

  GtkWidget *image_add = gtk_image_new_from_file("src/icons/add.svg");
  gtk_widget_set_size_request(image_add, 24, 24);
  gtk_widget_set_valign(image_add, GTK_ALIGN_CENTER);
  gtk_button_set_child(GTK_BUTTON(add_obj_btn), image_add);
  
  gtk_box_append(GTK_BOX(operate_btns_layer_box), add_obj_btn);
  g_signal_connect(add_obj_btn, "clicked", G_CALLBACK(on_add_btn_clicked), pop_up);

  return operate_btns_layer_box;
}

GtkWidget *create_mask_layer(PopUp *pop_up) {
  GtkWidget *mask_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); //mask.
  gtk_widget_add_css_class(mask_box, "mask");
  gtk_widget_set_vexpand(mask_box, TRUE);
  gtk_widget_set_visible(mask_box, FALSE);
  pop_up->mask = mask_box;
  
  GtkGesture *click_controller = gtk_gesture_click_new();
  g_signal_connect(click_controller, "pressed", G_CALLBACK(on_mask_clicked), pop_up);
  gtk_widget_add_controller(mask_box, GTK_EVENT_CONTROLLER(click_controller));
  
  return mask_box;
}

GtkWidget *create_pop_up_layer(PopUp *pop_up) {
  GtkWidget *add_obj_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(add_obj_list_box, TRUE);
  gtk_widget_set_halign(add_obj_list_box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(add_obj_list_box, GTK_ALIGN_CENTER);
  gtk_widget_add_css_class(add_obj_list_box, "add-obj-list-box");
  gtk_widget_set_size_request(add_obj_list_box, 300, 400);
  gtk_widget_set_visible(add_obj_list_box, FALSE);
  pop_up->pop_up_box = add_obj_list_box;
  GtkWidget *add_text_btn = gtk_button_new();
  gtk_box_append(GTK_BOX(add_obj_list_box), add_text_btn);
  g_signal_connect(add_text_btn, "clicked", G_CALLBACK(on_add_text), pop_up);

  return add_obj_list_box;
}