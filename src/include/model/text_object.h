#pragma once

#include <glib-object.h>
#include <gtk/gtk.h>
#include "top_common.h"

#define TEXT_TYPE_OBJECT (text_object_get_type())
G_DECLARE_FINAL_TYPE(TextObject, text_object, TEXT, OBJECT, GObject);

GType color_mode_get_type(void);
#define COLOR_MODE_TYPE (color_mode_get_type())

struct _TextObject {
    GObject parent_instance;

    gchar *uuid;
    gchar *text;
    gdouble x, y;
    gdouble font_size;
    ColorMode color;
  };

TextObject *text_object_new(
    const gchar *text,
    gchar *uuid,
    gdouble x,
    gdouble y,
    gdouble font_size,
    ColorMode color);

    
typedef struct {
  GtkWidget *x;
  GtkWidget *y;
  GtkWidget *font_size;
  GtkWidget *entry;
} TextLabels;