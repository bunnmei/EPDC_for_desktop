
#include "draw_canvas.h"
#include "canvas.h"

void
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

void
draw_preview_function(GtkDrawingArea *drawing_area,
              cairo_t *cr,
              int width,
              int height,
              gpointer user_data)
{
  PopUp *pop_up  = (PopUp *)user_data;
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
  cairo_paint(cr);

  for (guint i = 0; i < pop_up->pixels->len; i++) {
    int *pixel = (int *)g_ptr_array_index(pop_up->pixels, i);
    int x = i % (CANVAS_WIDTH/ 2); // 2倍の幅で計算
    int y = i / (CANVAS_WIDTH / 2); // 2倍の幅で計算
    if (*pixel == 1) {
      cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); 
    } else {
      cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); 
    }
    cairo_rectangle(cr,  x * 2,  y * 2, 2, 2); // 各ピクセルを2x2の正方形として描画
    cairo_fill(cr);
  }
}