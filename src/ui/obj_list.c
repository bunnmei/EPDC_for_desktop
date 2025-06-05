

#include "obj_list.h"

void on_button_clicked(GtkButton *button, gpointer user_data)
{
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  GtkListItem *list_item = g_object_get_data(G_OBJECT(button), "list-item");
  GObject *model_item = gtk_list_item_get_item(list_item);
  TextObject *rm_obj = TEXT_OBJECT(model_item);
  if(g_strcmp0(rm_obj->uuid, app_obj->obj_text->uuid) == 0) {
    app_obj->obj_text = NULL;
    app_obj->obj_mode = NONE;
    gtk_stack_set_visible_child_name(GTK_STACK(app_obj->stack), "none");
  }
  if (TEXT_IS_OBJECT(model_item)){
    g_print("TextObjectです\n");
  }
  if (list_item)
  {
    // app_obj->obj_text = NULL;
    guint position = gtk_list_item_get_position(list_item);
    g_list_store_remove(app_obj->text_store, position);
    gpointer ptr = g_ptr_array_remove_index(app_obj->text_objs, position);
    if (ptr) {
      g_print("Successfully removed from GPtrArray.\n");
  } else {
      g_print("Warning: Object not found in GPtrArray.\n");
  }
    gtk_widget_queue_draw(app_obj->ope_draw_area);
    g_print("Button clicked at position: %u\n", position);
  }
}


static void setup_list_item(GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data){
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *label = gtk_label_new("");
  GtkWidget *button = gtk_button_new();
  gtk_box_append(GTK_WIDGET(box), label);
  gtk_box_append(GTK_WIDGET(box), button);
  gtk_label_set_xalign(GTK_LABEL(label), 0.0); // 左寄せ
  g_object_set_data(G_OBJECT(button), "list-item", list_item);
  g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), app_obj);
  gtk_list_item_set_child(list_item, box);
}

static void bind_list_item(GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data){
  TextObject *item_data = TEXT_OBJECT(gtk_list_item_get_item(list_item));
  GtkWidget *box = gtk_list_item_get_child(list_item);
  GtkWidget *label = gtk_widget_get_first_child(box);
  // GtkWidget *label = gtk_list_item_get_child(list_item);

  GtkExpression *ex = gtk_property_expression_new(TEXT_TYPE_OBJECT, NULL, "text");
  gtk_expression_bind(ex, label, "label", item_data);
}

static void on_item_selected(GtkSingleSelection *selection, GParamSpec *pspec, gpointer user_data)
{
  // g_print("clickされたよ");
  EPDC_App_Obj *app_obj = (EPDC_App_Obj *)user_data;
  gpointer selected_item = gtk_single_selection_get_selected_item(selection);
  TextObject *item_data = TEXT_OBJECT(selected_item);

  guint selected_index = gtk_single_selection_get_selected(selection);
  g_print("n番目 %d\n", selected_index);

  // if (selected_item) {
  //   // Cast the selected item to TextObject*

  //   // Now you can access the data within item_data, for example:
  //   g_print("Selected item text: %s\n", item_data->uuid); // Assuming you have a getter for the text property
  // }


}

GtkWidget *create_obj_list_box(EPDC_App_Obj *app_obj){
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GListStore *store = g_list_store_new(TEXT_TYPE_OBJECT);
  app_obj->text_store = store;

  GtkSingleSelection *selection = gtk_single_selection_new(G_LIST_MODEL(store));
  g_signal_connect(selection, "notify::selected", G_CALLBACK(on_item_selected), NULL);

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