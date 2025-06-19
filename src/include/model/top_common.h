#pragma once

#include <gtk/gtk.h>
#include <glib-object.h>

typedef enum 
{
  BLACK = 0,
  RED = 1,
} ColorMode;

typedef enum
{
  TEXT,
  RECT_OBJMode,
  NONE,
} ObjMode;

GType color_mode_get_type(void);
#define COLOR_MODE_TYPE (color_mode_get_type())