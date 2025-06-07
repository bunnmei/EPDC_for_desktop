#pragma once

#include <gtk/gtk.h>
#include "object_common.h"

#define CANVAS_WIDTH 888
#define CANVAS_HEIGHT 384

GtkWidget *create_canvas(GtkWidget *box, PopUp *pop_up);
GtkWidget *create_canvas_layer(PopUp *pop_up);
GtkWidget *create_operate_btns_layer(PopUp *pop_up);
GtkWidget *create_mask_layer(PopUp *pop_up);
GtkWidget *create_pop_up_layer(PopUp *pop_up);