#pragma once

#include <libusb-1.0/libusb.h>
#include <gtk/gtk.h>
#include "object_common.h"

bool usb_emit(GPtrArray *array, PopUp *pop_up);