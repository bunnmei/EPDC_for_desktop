#pragma once

#include <gtk/gtk.h>
#include "object_common.h"

void draw_function(GtkDrawingArea *drawing_area,
                   cairo_t *cr,
                   int width,
                   int height,
                   gpointer user_data);
