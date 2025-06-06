
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

  int size_w = (CANVAS_WIDTH / 2);
  int size_h = (CANVAS_WIDTH / 2);
  int block = 2;
  int buf[size_w * size_h];
  int c = 0;
  pop_up->pixels = g_ptr_array_new_with_free_func(g_free);
  GPtrArray *px = pop_up->pixels;
  for (int y = 0; y < size_h; y++)
  {
    for (int x = 0; x < size_w; x++) {
      int count = 0;
      int i = (y * 2) * (size_w * 2) + (x * 2);
      int i2 = (y * 2) * (size_w * 2) + (x * 2) + 1;
      int i3 = (y * 2) * (size_w * 2) + (x * 2) + (size_w * 2);
      int i4 = (y * 2) * (size_w * 2) + (x * 2) + (size_w * 2) + 1;
      // printf("i: %d, i2: %d, i3: %d, i4: %d\n", i, i2, i3, i4);
      if(pixels[i*4] > 128) {
        count++;
      }
      if(pixels[i2*4] > 128) {
        count++;
      }
      if(pixels[i3*4] > 128) {
        count++;
      }
      if(pixels[i4*4] > 128) {
        count++;
      }

      if(count >= 2) {
        int *val = g_new(int, 1);
        *val = 0;
        buf[c] = 0;
        g_ptr_array_add(px, val);
      } else {
        int *val = g_new(int, 1);
        *val = 1;
        buf[c] = 1;
        g_ptr_array_add(px, val);
      }
      c++;
    }
  }

  gtk_widget_queue_draw(pop_up->app_obj->preview_draw_area);
}

void on_add_text(GtkButton *button, gpointer user_data) {
  PopUp *pop_up = (PopUp *)user_data;
  gtk_widget_set_visible(pop_up->mask, FALSE);
  gtk_widget_set_visible(pop_up->pop_up_box, FALSE);
  TextObject *new_obj = text_object_new("dammy", g_uuid_string_random(), 50.0, 150.0, 100.0, BLACK);
  pop_up->app_obj->obj_mode = TEXT;
  pop_up->app_obj->obj_text = new_obj;

  label_bind_double("x", pop_up->app_obj->text_labels->x, pop_up->app_obj->obj_text);
  label_bind_double("y", pop_up->app_obj->text_labels->y, pop_up->app_obj->obj_text);
  label_bind_double("font_size", pop_up->app_obj->text_labels->font_size, pop_up->app_obj->obj_text);

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