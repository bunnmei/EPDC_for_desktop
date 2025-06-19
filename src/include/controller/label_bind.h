#pragma once 

#include <gtk/gtk.h>
#include "text_object.h"
#include "rect_object.h"

gchar *f2i(GObject *obj, gdouble d, const char *prefix);

void label_bind_double(const char *prop_name, gpointer value, gpointer obj); 
void label_bind_double_rect(const char *prop_name, gpointer value, gpointer obj); 