#pragma once

#include <gtk/gtk.h>
#include "text_object.h"

typedef struct 
{
  GPtrArray *text_objs;
  GtkWidget *ope_draw_area;
  GtkWidget *preview_draw_area;
  GtkWidget *stack;
  ObjMode obj_mode;
  TextObject *obj_text;
  TextLabels *text_labels;
  GListStore *text_store;
} EPDC_App_Obj;

EPDC_App_Obj *app_obj_init();