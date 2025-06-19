#pragma once

#include <glib-object.h>
#include <gtk/gtk.h>
#include "top_common.h"

#define RECT_TYPE_OBJECT (rect_object_get_type())
G_DECLARE_FINAL_TYPE(RectObject, rect_object, RECT_OBJMode, OBJECT, GObject);

struct _RectObject {
    GObject parent_instance;

    gchar *uuid;
    gdouble x, y;
    gdouble w, h;
    gdouble degree;
    ColorMode color;
  };

RectObject *rect_object_new(
    gchar *uuid,
    gdouble x,
    gdouble y,
    gdouble w,
    gdouble h,
    gdouble degree,
    ColorMode color
);

    
typedef struct {
  GtkWidget *x;
  GtkWidget *y;
  GtkWidget *w;
  GtkWidget *h;
  GtkWidget *degree;
} RectLabels;