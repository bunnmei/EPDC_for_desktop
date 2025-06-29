#pragma once

#include <gtk/gtk.h>
#include "text_object.h"
#include "rect_object.h"

typedef struct 
{
  GPtrArray *text_objs;
  GPtrArray *rect_objs;
  GtkWidget *ope_draw_area;
  GtkWidget *preview_draw_area;
  GtkWidget *stack;

  ObjMode obj_mode;

  TextObject *obj_text;
  TextLabels *text_labels;
  GListStore *text_store;
  GtkWidget *select_color;

  RectObject *obj_rect;
  RectLabels *rect_labels;
  GListStore *rect_store;
  GtkWidget *select_color_rect;

  GtkSingleSelection *text_selection;
  GtkSingleSelection *rect_selection;
} EPDC_App_Obj;

typedef struct 
{
  EPDC_App_Obj *app_obj;
  GtkWidget *mask;
  GtkWidget *pop_up_box;
  GPtrArray *pixels;
  GPtrArray *pixels_red;
  GThread *usb_thread;
  GMutex *thread_mutex;
  bool keep_running;
} PopUp;

EPDC_App_Obj *app_obj_init();
PopUp *pop_up_init(EPDC_App_Obj *app_obj);