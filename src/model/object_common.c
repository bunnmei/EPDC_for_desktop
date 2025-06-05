#include "object_common.h"

EPDC_App_Obj *app_obj_init() {
  EPDC_App_Obj *app_obj = g_new0(EPDC_App_Obj, 1);
  // app_obj->text_objs = g_ptr_array_new_with_free_func(g_free);
  app_obj->text_objs = g_ptr_array_new_full(
    0, // 初期サイズ
    (GDestroyNotify)g_object_unref // ここを g_object_unref に変更
);
  app_obj->ope_draw_area = NULL;
  app_obj->preview_draw_area = NULL;
  app_obj->stack = NULL;
  app_obj->obj_mode = NONE;
  app_obj->obj_text = NULL;
  app_obj->text_store = NULL;

  TextLabels *text_labels = g_new0(TextLabels, 1);
  text_labels->x = NULL;
  text_labels->y = NULL;
  text_labels->font_size = NULL;
  text_labels->entry = NULL;

  app_obj->text_labels = text_labels;
  return app_obj;
}