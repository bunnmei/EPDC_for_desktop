#include "object_common.h"

EPDC_App_Obj *app_obj_init() {
  EPDC_App_Obj *app_obj = g_new0(EPDC_App_Obj, 1);
  // app_obj->text_objs = g_ptr_array_new_with_free_func(g_free);
  app_obj->text_objs = g_ptr_array_new_full(
    0, // 初期サイズ
    (GDestroyNotify)g_object_unref // ここを g_object_unref に変更
  );
  app_obj->rect_objs = g_ptr_array_new_full(
      0,
      (GDestroyNotify)g_object_unref);
  app_obj->ope_draw_area = NULL;
  app_obj->preview_draw_area = NULL;
  app_obj->stack = NULL;
  app_obj->obj_mode = NONE;

  app_obj->obj_text = NULL;
  app_obj->text_store = NULL;
  app_obj->text_selection = NULL;
  app_obj->select_color = NULL;

  app_obj->obj_rect = NULL;
  app_obj->rect_store = NULL;
  app_obj->rect_selection = NULL;
  app_obj->select_color_rect = NULL;

  TextLabels *text_labels = g_new0(TextLabels, 1);
  text_labels->x = NULL;
  text_labels->y = NULL;
  text_labels->font_size = NULL;
  text_labels->entry = NULL;

  RectLabels *rect_labels = g_new0(RectLabels, 1);
  rect_labels->x = NULL;
  rect_labels->y = NULL;
  rect_labels->w = NULL;
  rect_labels->h = NULL;
  rect_labels->degree = NULL;

  app_obj->text_labels = text_labels;
  app_obj->rect_labels = rect_labels;
  return app_obj;
}

PopUp *pop_up_init(EPDC_App_Obj *app_obj) {
  PopUp *pop_up = g_new0(PopUp, 1);
  pop_up->mask = NULL;
  pop_up->pop_up_box = NULL;
  pop_up->app_obj = app_obj;
  pop_up->pixels = g_ptr_array_new_with_free_func(g_free);
  pop_up->pixels_red = g_ptr_array_new_with_free_func(g_free);
  pop_up->usb_thread = NULL;
  pop_up->keep_running = false;
  pop_up->thread_mutex = NULL;
  return pop_up;
}