#include "ope_prop.h"
#include "change_prop.h"

GtkWidget *create_prop_stack(EPDC_App_Obj *app_obj) {
  GtkWidget *stack = gtk_stack_new();
  gtk_widget_add_css_class(stack, "stack");
  gtk_widget_set_valign(stack, GTK_ALIGN_FILL);

  GtkWidget *select_none = create_none_select_box();
  GtkWidget *text_prop_box = create_text_prop_box(app_obj);
  GtkWidget *rect_prop_box = create_rect_prop_box(app_obj);

  gtk_stack_add_named(GTK_STACK(stack), select_none, "none");
  gtk_stack_add_named(GTK_STACK(stack), text_prop_box, "text");
  gtk_stack_add_named(GTK_STACK(stack), rect_prop_box, "rect");
  
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "none");
  return stack;
}

GtkWidget *create_none_select_box() {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *none_label = gtk_label_new("None");
  gtk_box_append(GTK_BOX(box), none_label);
  return box;
}

void on_dropdown_changed(GtkDropDown *dropdown, GParamSpec *pspec, gpointer user_data) {
  // 選択された項目（GtkStringObject）を取得
  g_print("on_dropdown_changedが呼ばれたよ\n");
  GtkStringObject *selected_item = gtk_drop_down_get_selected_item(dropdown);
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  if(app_obj->obj_mode == TEXT) {
    if (selected_item) {
      // GtkStringObject から文字列を取得
      const char *selected_text = gtk_string_object_get_string(selected_item);
      if(g_strcmp0(selected_text, "BLACK") == 0) {
        g_object_set(app_obj->obj_text, "color", BLACK,  NULL);
        
      } else if(g_strcmp0(selected_text, "RED") == 0) {
        g_object_set(app_obj->obj_text, "color", RED, NULL);
        // g_object_set(app_obj->obj_text, "color", RED,  NULL);
      }
      // g_print("選択された項目: %s\n", selected_text);
    } else {
        g_print("何も選択されていません\n");
    }
  } else if(app_obj->obj_mode == RECT_OBJMode) {
    if (selected_item) {
      // GtkStringObject から文字列を取得
      const char *selected_rect = gtk_string_object_get_string(selected_item);
      if(g_strcmp0(selected_rect, "BLACK") == 0) {
        g_object_set(app_obj->obj_rect, "color", BLACK,  NULL);
        
      } else if(g_strcmp0(selected_rect, "RED") == 0) {
        g_object_set(app_obj->obj_rect, "color", RED, NULL);
        // g_object_set(app_obj->obj_text, "color", RED,  NULL);
      }
      // g_print("選択された項目: %s\n", selected_text);
    } else {
        g_print("何も選択されていません\n");
    }
  }

  g_print("再描画\n");
  gtk_widget_queue_draw(app_obj->ope_draw_area);
}

void on_entry_changed(GtkEntry *entry, gpointer user_data) {
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  const char *text = gtk_editable_get_text(GTK_EDITABLE(entry));
  g_object_set(app_obj->obj_text, "text", text,  NULL);
  gtk_widget_queue_draw(app_obj->ope_draw_area);
}

GtkWidget *create_text_prop_box(EPDC_App_Obj *app_obj){
  GtkWidget *text_prop_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *x = create_prop("x", app_obj);
  GtkWidget *btn_x = gtk_widget_get_first_child(x); // 子要素の取得キモイ
  GtkWidget *label_x = gtk_widget_get_next_sibling(btn_x);
  app_obj->text_labels->x = label_x;
  
  GtkWidget *y = create_prop("y", app_obj);
  GtkWidget *btn_y = gtk_widget_get_first_child(y);
  GtkWidget *label_y = gtk_widget_get_next_sibling(btn_y);
  app_obj->text_labels->y = label_y;
  
  GtkWidget *font_size = create_prop("font_size", app_obj);
  GtkWidget *btn_font_size = gtk_widget_get_first_child(font_size);
  GtkWidget *label_font_size = gtk_widget_get_next_sibling(btn_font_size);
  app_obj->text_labels->font_size = label_font_size;

  //color drop_down_menu
  GtkWidget *drop_down_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(drop_down_box, "drop-down-box");
  GtkWidget *color_label = gtk_label_new("Color: ");
  gtk_widget_add_css_class(color_label, "prop-label");
  gtk_label_set_xalign(GTK_LABEL(color_label), 0.1); 
  const char *options[] = {"BLACK", "RED", NULL};
  GtkStringList *string_list = gtk_string_list_new(options);
  GtkWidget *drop_down = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
  app_obj->select_color = drop_down;
  gtk_widget_set_hexpand(drop_down, TRUE);
  gtk_drop_down_set_selected(GTK_DROP_DOWN(drop_down), 0);
  g_signal_connect(drop_down, "notify::selected-item", G_CALLBACK(on_dropdown_changed), app_obj);
  gtk_box_append(GTK_BOX(drop_down_box), color_label);
  gtk_box_append(GTK_BOX(drop_down_box), drop_down);

  GtkWidget *entry_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(entry_box, "entry-box");
  GtkWidget *entry_label = gtk_label_new("Text: ");
  gtk_widget_add_css_class(entry_label, "prop-label");
  gtk_label_set_xalign(GTK_LABEL(entry_label), 0.1); // 左寄せ

  GtkWidget *entry = gtk_entry_new();
  gtk_widget_set_hexpand(entry, TRUE);
  app_obj->text_labels->entry = entry;
  g_signal_connect(entry, "changed", G_CALLBACK(on_entry_changed), app_obj);
  gtk_box_append(GTK_BOX(entry_box), entry_label);
  gtk_box_append(GTK_BOX(entry_box), entry);

  gtk_box_append(GTK_BOX(text_prop_box), x);
  gtk_box_append(GTK_BOX(text_prop_box), y);
  gtk_box_append(GTK_BOX(text_prop_box), font_size);
  gtk_box_append(GTK_BOX(text_prop_box), drop_down_box);
  gtk_box_append(GTK_BOX(text_prop_box), entry_box);
  return text_prop_box;
}

GtkWidget *create_rect_prop_box(EPDC_App_Obj *app_obj){
  GtkWidget *rect_prop_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *x = create_rect_prop("x", app_obj);
  GtkWidget *btn_x = gtk_widget_get_first_child(x); // 子要素の取得キモイ
  GtkWidget *label_x = gtk_widget_get_next_sibling(btn_x);
  app_obj->rect_labels->x = label_x;
  
  GtkWidget *y = create_rect_prop("y", app_obj);
  GtkWidget *btn_y = gtk_widget_get_first_child(y);
  GtkWidget *label_y = gtk_widget_get_next_sibling(btn_y);
  app_obj->rect_labels->y = label_y;
  
  GtkWidget *w = create_rect_prop("w", app_obj);
  GtkWidget *btn_w = gtk_widget_get_first_child(w);
  GtkWidget *label_w = gtk_widget_get_next_sibling(btn_w);
  app_obj->rect_labels->w = label_w;

  GtkWidget *h = create_rect_prop("h", app_obj);
  GtkWidget *btn_h = gtk_widget_get_first_child(h);
  GtkWidget *label_h = gtk_widget_get_next_sibling(btn_h);
  app_obj->rect_labels->h = label_h;

  GtkWidget *degree = create_rect_prop("degree", app_obj);
  GtkWidget *btn_degree = gtk_widget_get_first_child(degree);
  GtkWidget *label_degree = gtk_widget_get_next_sibling(btn_degree);
  app_obj->rect_labels->degree = label_degree;

  //color drop_down_menu
  GtkWidget *drop_down_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(drop_down_box, "drop-down-box");
  GtkWidget *color_label = gtk_label_new("Color: ");
  gtk_widget_add_css_class(color_label, "prop-label");
  gtk_label_set_xalign(GTK_LABEL(color_label), 0.1); 
  const char *options[] = {"BLACK", "RED", NULL};
  GtkStringList *string_list = gtk_string_list_new(options);
  GtkWidget *drop_down = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
  app_obj->select_color_rect = drop_down;
  gtk_widget_set_hexpand(drop_down, TRUE);
  gtk_drop_down_set_selected(GTK_DROP_DOWN(drop_down), 0);
  g_signal_connect(drop_down, "notify::selected-item", G_CALLBACK(on_dropdown_changed), app_obj);
  gtk_box_append(GTK_BOX(drop_down_box), color_label);
  gtk_box_append(GTK_BOX(drop_down_box), drop_down);

  gtk_box_append(GTK_BOX(rect_prop_box), x);
  gtk_box_append(GTK_BOX(rect_prop_box), y);
  gtk_box_append(GTK_BOX(rect_prop_box), w);
  gtk_box_append(GTK_BOX(rect_prop_box), h);
  gtk_box_append(GTK_BOX(rect_prop_box), degree);
  gtk_box_append(GTK_BOX(rect_prop_box), drop_down_box);
  return rect_prop_box;
}

GtkWidget *create_prop(char *id, EPDC_App_Obj *app_obj){
  char id_name[32];
  GtkWidget *prop_box_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(prop_box_h, "prop-box");
  gtk_widget_set_valign(prop_box_h, GTK_ALIGN_START);
  
  snprintf(id_name, sizeof(id_name), "prop_text_%s_btn_minus", id);
  GtkWidget *prop_btn_minus = gtk_button_new();
  gtk_widget_set_name(prop_btn_minus, id_name);
  gtk_widget_add_css_class(prop_btn_minus, "prop-btn");
  gtk_widget_set_valign(prop_btn_minus, GTK_ALIGN_CENTER);

  GtkWidget *minus_img = gtk_image_new_from_file("src/icons/remove.svg");
  gtk_widget_set_size_request(minus_img, 24, 24);
  gtk_widget_set_valign(minus_img, GTK_ALIGN_CENTER);
  gtk_button_set_child(GTK_BUTTON(prop_btn_minus), minus_img);

  snprintf(id_name, sizeof(id_name), "prop_text_%s_label", id);
  GtkWidget *prop_label = gtk_label_new("");
  gtk_widget_set_name(prop_label, id_name);
  gtk_widget_set_hexpand(prop_label, TRUE);

  snprintf(id_name, sizeof(id_name), "prop_text_%s_btn_plus", id);
  GtkWidget *prop_btn_plus = gtk_button_new();
  gtk_widget_set_name(prop_btn_plus, id_name);
  gtk_widget_set_valign(prop_btn_plus, GTK_ALIGN_CENTER);
  gtk_widget_add_css_class(prop_btn_plus, "prop-btn");

  GtkWidget *plus_img = gtk_image_new_from_file("src/icons/add.svg");
  gtk_widget_set_size_request(plus_img, 24, 24);
  gtk_widget_set_valign(plus_img, GTK_ALIGN_CENTER);
  gtk_button_set_child(GTK_BUTTON(prop_btn_plus), plus_img);

  g_signal_connect(prop_btn_minus, "clicked", G_CALLBACK(on_prop), app_obj);
  g_signal_connect(prop_btn_plus, "clicked", G_CALLBACK(on_prop), app_obj);

  gtk_box_append(GTK_BOX(prop_box_h), prop_btn_minus);
  gtk_box_append(GTK_BOX(prop_box_h), prop_label);
  gtk_box_append(GTK_BOX(prop_box_h), prop_btn_plus);

  return prop_box_h;
}

GtkWidget *create_rect_prop(char *id, EPDC_App_Obj *app_obj){
  char id_name[32];
  GtkWidget *prop_box_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(prop_box_h, "prop-box");
  gtk_widget_set_valign(prop_box_h, GTK_ALIGN_START);
  
  snprintf(id_name, sizeof(id_name), "prop_rect_%s_btn_minus", id);
  GtkWidget *prop_btn_minus = gtk_button_new();
  gtk_widget_set_name(prop_btn_minus, id_name);
  gtk_widget_add_css_class(prop_btn_minus, "prop-btn");
  gtk_widget_set_valign(prop_btn_minus, GTK_ALIGN_CENTER);

  GtkWidget *minus_img = gtk_image_new_from_file("src/icons/remove.svg");
  gtk_widget_set_size_request(minus_img, 24, 24);
  gtk_widget_set_valign(minus_img, GTK_ALIGN_CENTER);
  gtk_button_set_child(GTK_BUTTON(prop_btn_minus), minus_img);

  snprintf(id_name, sizeof(id_name), "prop_rect_%s_label", id);
  GtkWidget *prop_label = gtk_label_new("");
  gtk_widget_set_name(prop_label, id_name);
  gtk_widget_set_hexpand(prop_label, TRUE);

  snprintf(id_name, sizeof(id_name), "prop_rect_%s_btn_plus", id);
  GtkWidget *prop_btn_plus = gtk_button_new();
  gtk_widget_set_name(prop_btn_plus, id_name);
  gtk_widget_set_valign(prop_btn_plus, GTK_ALIGN_CENTER);
  gtk_widget_add_css_class(prop_btn_plus, "prop-btn");

  GtkWidget *plus_img = gtk_image_new_from_file("src/icons/add.svg");
  gtk_widget_set_size_request(plus_img, 24, 24);
  gtk_widget_set_valign(plus_img, GTK_ALIGN_CENTER);
  gtk_button_set_child(GTK_BUTTON(prop_btn_plus), plus_img);

  g_signal_connect(prop_btn_minus, "clicked", G_CALLBACK(on_rect_prop), app_obj);
  g_signal_connect(prop_btn_plus, "clicked", G_CALLBACK(on_rect_prop), app_obj);

  gtk_box_append(GTK_BOX(prop_box_h), prop_btn_minus);
  gtk_box_append(GTK_BOX(prop_box_h), prop_label);
  gtk_box_append(GTK_BOX(prop_box_h), prop_btn_plus);

  return prop_box_h;
}
