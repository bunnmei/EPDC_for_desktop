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

typedef struct 
{
  EPDC_App_Obj *app_obj;
  GtkWidget *mask;
  GtkWidget *pop_up_box;
  GPtrArray *pixels;
  GThread *usb_thread;
  GMutex *thread_mutex;
  bool keep_running;
} PopUp;

EPDC_App_Obj *app_obj_init();
PopUp *pop_up_init(EPDC_App_Obj *app_obj);