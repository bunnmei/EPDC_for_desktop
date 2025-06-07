#include "canvas.h"
#include "text_object.h"
#include "draw_canvas.h"
#include "add_obj.h"

GtkWidget *create_canvas(GtkWidget *box, PopUp *pop_up){

  GtkWidget *overlay = gtk_overlay_new();
  gtk_widget_set_hexpand(overlay, TRUE);
  gtk_widget_set_vexpand(overlay, TRUE);
  gtk_box_append(GTK_BOX(box), overlay);

  GtkWidget *canvas_layer = create_canvas_layer(pop_up);
  GtkWidget *mask_layer = create_mask_layer(pop_up);
  GtkWidget *pop_up_layer = create_pop_up_layer(pop_up);
  GtkWidget *btn_layer = create_operate_btns_layer(pop_up);

  gtk_overlay_set_child(GTK_OVERLAY(overlay), canvas_layer);
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), btn_layer);
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), mask_layer);
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), pop_up_layer);

  return overlay;
}

GtkWidget *create_canvas_layer(PopUp *pop_up) {
  GtkWidget *canvas_layer_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_add_css_class(canvas_layer_box, "canvas-layer");
  gtk_widget_set_halign(canvas_layer_box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(canvas_layer_box, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(canvas_layer_box, TRUE);
  gtk_widget_set_vexpand(canvas_layer_box, TRUE);

  GtkWidget *operate_drawing_area = gtk_drawing_area_new();
  pop_up->app_obj->ope_draw_area = operate_drawing_area;
  gtk_widget_set_size_request(operate_drawing_area, CANVAS_WIDTH, CANVAS_HEIGHT);
  gtk_drawing_area_set_draw_func(
    GTK_DRAWING_AREA(operate_drawing_area),
    draw_function,
    pop_up->app_obj, 
    NULL
  );
  gtk_box_append(GTK_BOX(canvas_layer_box), operate_drawing_area);

  GtkWidget *preview_drawing_area = gtk_drawing_area_new();
  pop_up->app_obj->preview_draw_area = preview_drawing_area;
  gtk_widget_set_size_request(preview_drawing_area, CANVAS_WIDTH, CANVAS_HEIGHT);
  gtk_drawing_area_set_draw_func(
    GTK_DRAWING_AREA(preview_drawing_area),
    draw_preview_function,
    pop_up, 
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

  GtkWidget *scan_canvas_btn = gtk_button_new();
  gtk_widget_set_margin_start(scan_canvas_btn, 4);
  gtk_widget_add_css_class(scan_canvas_btn, "add-button");
  gtk_widget_set_size_request(scan_canvas_btn, 50, 50);

  GtkWidget *image_scan_canvas = gtk_image_new_from_file("src/icons/scan.svg");
  gtk_widget_set_size_request(image_scan_canvas, 24, 24);
  gtk_widget_set_valign(image_scan_canvas, GTK_ALIGN_CENTER);
  gtk_button_set_child(GTK_BUTTON(scan_canvas_btn), image_scan_canvas);
  
  gtk_box_append(GTK_BOX(operate_btns_layer_box), add_obj_btn);
  gtk_box_append(GTK_BOX(operate_btns_layer_box), scan_canvas_btn);
  g_signal_connect(add_obj_btn, "clicked", G_CALLBACK(on_add_btn_clicked), pop_up);
  g_signal_connect(scan_canvas_btn, "clicked", G_CALLBACK(on_scan_canvas), pop_up);

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