#include "object_common.h"

EPDC_App_Obj *app_obj_init() {
  EPDC_App_Obj *app_obj = g_new0(EPDC_App_Obj, 1);
  app_obj->text_objs = g_ptr_array_new_with_free_func(g_free);
  app_obj->ope_draw_area = NULL;
  app_obj->preview_draw_area = NULL;
  app_obj->stack = NULL;
  app_obj->obj_mode = NONE;
  app_obj->obj_text = NULL;
  return app_obj;
}