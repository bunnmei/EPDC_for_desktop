
#include "add_obj.h"
#include "canvas.h"
#include "label_bind.h"

void on_add_btn_clicked(GtkButton *button, gpointer user_data) {
  PopUp *pop_up = (PopUp *)user_data;
  gtk_widget_set_visible(pop_up->mask, TRUE);
  gtk_widget_set_visible(pop_up->pop_up_box, TRUE);
}

void on_scan_canvas(GtkButton *button, gpointer user_data){
  PopUp *pop_up = (PopUp *)user_data;
  GtkWidget *scan_target_canvas = pop_up->app_obj->ope_draw_area;
  int w = gtk_widget_get_width(scan_target_canvas);
  int h = gtk_widget_get_height(scan_target_canvas);

  GtkSnapshot *snapshot = gtk_snapshot_new();
  GdkPaintable  *paintable = gtk_widget_paintable_new(GTK_WIDGET(scan_target_canvas));
  gdk_paintable_snapshot(paintable , snapshot, w, h);

  GskRenderNode *node = gtk_snapshot_free_to_node (snapshot);
  GskRenderer *renderer = gtk_native_get_renderer(gtk_widget_get_native(scan_target_canvas));
  GdkTexture *texture = gsk_renderer_render_texture (renderer,
                                                     node,
                                                     &GRAPHENE_RECT_INIT (0, 0, w, h));

  GdkPixbuf *pixbuf = gdk_pixbuf_get_from_texture(texture);
  guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);
  long int pixels_length = gdk_pixbuf_get_n_channels(pixbuf) * gdk_pixbuf_get_width(pixbuf) * gdk_pixbuf_get_height(pixbuf);

  int size_w = (CANVAS_WIDTH / 3);
  int size_h = (CANVAS_HEIGHT / 3);
  int block = 2;
  // int buf[size_w * size_h];
  int c = 0;
  pop_up->pixels = g_ptr_array_new_with_free_func(g_free);
  pop_up->pixels_red = g_ptr_array_new_with_free_func(g_free);

  GPtrArray *px = pop_up->pixels;
  GPtrArray *px_red = pop_up->pixels_red;
  for (int y = 0; y < size_h; y++)
  {
    for (int x = 0; x < size_w; x++) {
      int count = 0;
      int count_red = 0;
      int i1 = (y * 3) * (size_w * 3) + (x * 3);
      int i2 = (y * 3) * (size_w * 3) + (x * 3) + 1;
      int i3 = (y * 3) * (size_w * 3) + (x * 3) + (size_w * 3);
      int i4 = (y * 3) * (size_w * 3) + (x * 3) + (size_w * 3) + 1;
      int px1_r = pixels[i1 * 4];
      int px1_g = pixels[i1 * 4 + 1];
      int px1_b = pixels[i1 * 4 + 2];
      
      int px2_r = pixels[i2 * 4];
      int px2_g = pixels[i2 * 4 + 1];
      int px2_b = pixels[i2 * 4 + 2];

      int px3_r = pixels[i3 * 4];
      int px3_g = pixels[i3 * 4 + 1];
      int px3_b = pixels[i3 * 4 + 2];

      int px4_r = pixels[i4 * 4];
      int px4_g = pixels[i4 * 4 + 1];
      int px4_b = pixels[i4 * 4 + 2];

      if (px1_r >= 120 && px1_g <= 120 && px1_b <= 120) {
        count_red++;
      } else if (px1_r <= 120 && px1_g <= 120 && px1_b <= 120) {
        count++;
      }
      if (px2_r >= 120 && px2_g <= 120 && px2_b <= 120) {
        count_red++;
      } else if (px2_r <= 120 && px2_g <= 120 && px2_b <= 120) {
        count++;
      }
      if (px3_r >= 120 && px3_g <= 120 && px3_b <= 120 ) {
        count_red++;
      } else if (px3_r <= 120 && px3_g <= 120 && px3_b <= 120) {
        count++;
      }
      if (px4_r >= 120 && px4_g <= 120 && px4_b <= 120) {
        // printf("r %d - g %d - b %d\n", px4_r, px4_g, px4_b);
        count_red++;
      } else if (px4_r <= 120 && px4_g <= 120 && px4_b <= 120) {
        count++;
      }

      if(count >= 2) {
        int *val = g_new(int, 1);
        *val = 0;
        g_ptr_array_add(px, val);
      } else {
        int *val = g_new(int, 1);
        *val = 1;
        g_ptr_array_add(px, val);
      }

      if(count_red >= 2) {
        int *val = g_new(int, 1);
        *val = 0;
        g_ptr_array_add(px_red, val);
      } else {
        int *val = g_new(int, 1);
        *val = 1;
        g_ptr_array_add(px_red, val);
      }
      
      c++;
    }
  }

  c = 0;

  gtk_widget_queue_draw(pop_up->app_obj->preview_draw_area);
}

void on_add_text(GtkButton *button, gpointer user_data) {
  PopUp *pop_up = (PopUp *)user_data;
  gtk_widget_set_visible(pop_up->mask, FALSE);
  gtk_widget_set_visible(pop_up->pop_up_box, FALSE);
  TextObject *new_obj = text_object_new("dammy", g_uuid_string_random(), 50.0, 150.0, 100.0, BLACK);
  pop_up->app_obj->obj_mode = TEXT;
  pop_up->app_obj->obj_text = new_obj;

  // label_bind_double("x", pop_up->app_obj->text_labels->x, pop_up->app_obj->obj_text);
  // label_bind_double("y", pop_up->app_obj->text_labels->y, pop_up->app_obj->obj_text);
  // label_bind_double("font_size", pop_up->app_obj->text_labels->font_size, pop_up->app_obj->obj_text);

  //同じ文字列をセットするとキャッシュされているため違う文字を代入　仮　GtkEntryBufferを使う？.　
  // gchar *dset = g_strdup_printf("%s%d", new_obj->text, pop_up->app_obj->text_objs->len);
  // gtk_editable_set_text(GTK_EDITABLE(pop_up->app_obj->text_labels->entry), "");
  // gtk_editable_set_text(GTK_EDITABLE(pop_up->app_obj->text_labels->entry), new_obj->text);

  g_list_store_append(pop_up->app_obj->text_store, new_obj);
  guint last_item_index = g_list_model_get_n_items(G_LIST_MODEL(pop_up->app_obj->text_store)) - 1;
  gtk_single_selection_set_selected(pop_up->app_obj->rect_selection, GTK_INVALID_LIST_POSITION);
  gtk_single_selection_set_selected(pop_up->app_obj->text_selection, last_item_index);

  // 何も選択しない状態にする
  // gtk_single_selection_set_selected(pop_up->app_obj->text_selection, GTK_INVALID_LIST_POSITION);
  gtk_stack_set_visible_child_name(GTK_STACK(pop_up->app_obj->stack), "text");
  g_ptr_array_add(pop_up->app_obj->text_objs, new_obj);
  gtk_widget_queue_draw(pop_up->app_obj->ope_draw_area);
}


void on_add_rect(GtkButton *button, gpointer user_data) {
  PopUp *pop_up = (PopUp *)user_data;

  gtk_widget_set_visible(pop_up->mask, FALSE);
  gtk_widget_set_visible(pop_up->pop_up_box, FALSE);

  RectObject *new_obj = rect_object_new(g_uuid_string_random(), 50.0, 150.0, 100.0, 100.0, 0.0, BLACK);
  pop_up->app_obj->obj_mode = RECT_OBJMode;
  pop_up->app_obj->obj_rect = new_obj;

  g_list_store_append(pop_up->app_obj->rect_store, new_obj);
  guint last_item_index = g_list_model_get_n_items(G_LIST_MODEL(pop_up->app_obj->rect_store)) - 1;
  gtk_single_selection_set_selected(pop_up->app_obj->text_selection, GTK_INVALID_LIST_POSITION);
  gtk_single_selection_set_selected(pop_up->app_obj->rect_selection, last_item_index);

  gtk_stack_set_visible_child_name(GTK_STACK(pop_up->app_obj->stack), "rect");
  g_ptr_array_add(pop_up->app_obj->rect_objs, new_obj);
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