#pragma once

#include <libusb-1.0/libusb.h>
#include <gtk/gtk.h>
#include "object_common.h"

extern unsigned char gImage1_BW[4736]; 
extern unsigned char gImage1_RED[4736]; 

bool usb_emit(GPtrArray *array, PopUp *pop_up);