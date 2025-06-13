#include "obj_list.h"

void on_button_clicked(GtkButton *button, gpointer user_data)
{
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  GtkListItem *list_item = g_object_get_data(G_OBJECT(button), "list-item");
  GObject *model_item = gtk_list_item_get_item(list_item);
  TextObject *rm_obj = TEXT_OBJECT(model_item);
  
  if (TEXT_IS_OBJECT(model_item)){
    g_print("TextObjectです\n");
    g_print("rm_obj %s\n", rm_obj->text);
  }

  if (list_item)
  {
    printf("ppp %p\n", list_item);
    guint position = gtk_list_item_get_position(list_item);
    printf("position %d\n", position);
    g_list_store_remove(app_obj->text_store, position);
    gboolean result = g_ptr_array_remove(app_obj->text_objs, rm_obj);
    gtk_widget_queue_draw(app_obj->ope_draw_area);

    if(g_strcmp0(rm_obj->uuid, app_obj->obj_text->uuid) == 0) {
      app_obj->obj_text = NULL;
      app_obj->obj_mode = NONE;
      gtk_stack_set_visible_child_name(GTK_STACK(app_obj->stack), "none");

      guint last_item_index = g_list_model_get_n_items(G_LIST_MODEL(app_obj->text_store)) - 1;
      if(last_item_index >= 0) {
        gtk_single_selection_set_selected(app_obj->text_selection, last_item_index);
      }
    }
    // gtk_stack_set_visible_child_name(GTK_STACK(app_obj->stack), "none");
    // gtk_single_selection_set_selected(app_obj->text_selection, GTK_INVALID_LIST_POSITION);

    // gpointer ptr = g_ptr_array_remove_index(app_obj->text_objs, position);
    // printf("rm position %d\n", position);
    // g_list_store_remove(app_obj->text_store, position);
    // if (result) {
    //   g_print("Successfully removed from GPtrArray.\n");
    // } else {
    //   g_print("Warning: Object not found in GPtrArray.\n");
    // }
    // g_print("Button clicked at position: %u\n", position);
  }
}


static void setup_list_item(GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data){
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(box, "list-box");
  
  GtkWidget *label = gtk_label_new("");
  gtk_widget_add_css_class(label, "list-label");
  
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_hexpand(spacer, TRUE);
  
  GtkWidget *button = gtk_button_new();
  gtk_widget_add_css_class(button, "list-btn");
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_vexpand(button, FALSE);
  gtk_widget_set_size_request(button, 40, 40);

  GtkWidget *image_delete = gtk_image_new_from_file("src/icons/delete.svg");
  gtk_widget_set_size_request(image_delete, 24, 24);
  gtk_widget_set_valign(image_delete, GTK_ALIGN_CENTER);
  gtk_button_set_child(GTK_BUTTON(button), image_delete);

  gtk_box_append(GTK_BOX(box), label);
  gtk_box_append(GTK_BOX(box), spacer);
  gtk_box_append(GTK_BOX(box), button);
  gtk_label_set_xalign(GTK_LABEL(label), 0.0); // 左寄せ
  g_object_set_data(G_OBJECT(button), "list-item", list_item);
  g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), app_obj);
  gtk_list_item_set_child(list_item, box);
}

static void bind_list_item(GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data){
  printf("bild_list_item\n");
  gpointer obj_ptr = gtk_list_item_get_item(list_item);
  if(obj_ptr == NULL) {
    printf("bind_list_obj_ptr is NULL");
  }
  TextObject *item_data = TEXT_OBJECT(obj_ptr);
  GtkWidget *box = gtk_list_item_get_child(list_item);
  GtkWidget *label = gtk_widget_get_first_child(box);
  // GtkWidget *label = gtk_list_item_get_child(list_item);
  GtkExpression *ex = gtk_property_expression_new(TEXT_TYPE_OBJECT, NULL, "text");
  gtk_expression_bind(ex, label, "label", item_data);
}


static void on_item_selected(GtkSingleSelection *selection, GParamSpec *pspec, gpointer user_data)
{
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  
  // if(item_data) {
  //   printf("null TextObject\n");
  // }
  guint selected_index = gtk_single_selection_get_selected(selection);
  gpointer selected_item = gtk_single_selection_get_selected_item(selection);
  TextObject *item_data = TEXT_OBJECT(selected_item);
  g_print("on_item_selected - n番目 %d\n", selected_index);
  // if(item_data == NULL) {
  //   printf("TextObject is NULL\n");
  // }
  // item_data != NULLはlistの要素削除ににも"bind"のコールバック関数が呼ばれるため
  if(selected_index >= 0 && item_data != NULL) {
    app_obj->obj_mode = TEXT;
    app_obj->obj_text = item_data;
  
    label_bind_double("x", app_obj->text_labels->x, app_obj->obj_text);
    label_bind_double("y", app_obj->text_labels->y, app_obj->obj_text);
    label_bind_double("font_size", app_obj->text_labels->font_size,app_obj->obj_text);

    gtk_drop_down_set_selected(GTK_DROP_DOWN(app_obj->select_color), app_obj->obj_text->color);
  
    GtkEntry *entry = GTK_ENTRY(app_obj->text_labels->entry);
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
    gtk_entry_buffer_set_text(buffer, app_obj->obj_text->text, -1);
  }

}

GtkWidget *create_obj_list_box(EPDC_App_Obj *app_obj){
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GListStore *store = g_list_store_new(TEXT_TYPE_OBJECT);
  app_obj->text_store = store;

  GtkSingleSelection *selection = gtk_single_selection_new(G_LIST_MODEL(store));
  g_signal_connect(selection, "notify::selected", G_CALLBACK(on_item_selected), app_obj);
  app_obj->text_selection = selection;

  GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
  g_signal_connect(factory, "setup", G_CALLBACK(setup_list_item), app_obj);
  g_signal_connect(factory, "bind", G_CALLBACK(bind_list_item), NULL);

  GtkWidget *scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

  GtkWidget *list_view = gtk_list_view_new(GTK_SELECTION_MODEL(selection), factory);
  gtk_list_view_set_show_separators(GTK_LIST_VIEW(list_view), TRUE);
  gtk_widget_set_vexpand(list_view, TRUE);

  gtk_box_append(GTK_BOX(box), list_view);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);

  return scrolled_window;
}