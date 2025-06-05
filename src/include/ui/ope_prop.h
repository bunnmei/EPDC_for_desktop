#pragma once

#include <gtk/gtk.h>
#include "text_object.h"
#include "object_common.h"
#include "top_common.h"

GtkWidget *create_prop_stack(EPDC_App_Obj *app_obj);
GtkWidget *create_none_select_box();
GtkWidget *create_prop(char *id, EPDC_App_Obj *app_obj);
GtkWidget *create_text_prop_box(EPDC_App_Obj *app_obj);