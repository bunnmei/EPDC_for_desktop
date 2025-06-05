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
  RECT,
  NONE,
} ObjMode;