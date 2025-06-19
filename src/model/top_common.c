#include "top_common.h"

GType color_mode_get_type(void) {
  static GType type = 0;
  static const GEnumValue values[] = {
      { BLACK, "BLACK", "black" },
      { RED, "RED", "red" },
      { 0, NULL, NULL }
  };

  if (type == 0) {
      type = g_enum_register_static("ColorMode", values);
  }
  return type;
}