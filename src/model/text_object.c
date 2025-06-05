#include <glib.h>
#include <glib-object.h>

#include "text_object.h"

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

enum {
  PROP_0,
  PROP_UUID,
  PROP_TEXT,
  PROP_X,
  PROP_Y,
  PROP_FONT_SIZE,
  PROP_COLOR,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL };

G_DEFINE_FINAL_TYPE(TextObject, text_object, G_TYPE_OBJECT)

static void text_object_set_property(GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec) {
  TextObject *self = TEXT_OBJECT(object);
  switch (prop_id) {
    case PROP_UUID: g_free(self->uuid); self->uuid = g_value_dup_string(value); break;
    case PROP_TEXT: g_free(self->text); self->text = g_value_dup_string(value); break;
    case PROP_X: self->x = g_value_get_double(value); break;
    case PROP_Y: self->y = g_value_get_double(value); break;
    case PROP_FONT_SIZE: self->font_size = g_value_get_double(value); break;
    case PROP_COLOR:
      self->color = g_value_get_enum(value); break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
    }
}

static void text_object_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec) {
  TextObject *self = TEXT_OBJECT(object);
  switch (prop_id) {
    case PROP_UUID: g_value_set_string(value, self->uuid); break;
    case PROP_TEXT: g_value_set_string(value, self->text); break;
    case PROP_X: g_value_set_double(value, self->x); break;
    case PROP_Y: g_value_set_double(value, self->y); break;
    case PROP_FONT_SIZE: g_value_set_double(value, self->font_size); break;
    case PROP_COLOR: g_value_set_enum(value, self->color); break;
    default: G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec); break;
  }
}

static void text_object_finalize(GObject *object) {
  TextObject *self = TEXT_OBJECT(object);
  g_free(self->uuid);
  g_free(self->text);
  G_OBJECT_CLASS(text_object_parent_class)->finalize(object);
}

static void text_object_class_init(TextObjectClass *klass) {
  GObjectClass *object_class = G_OBJECT_CLASS(klass);
  object_class->set_property = text_object_set_property;
  object_class->get_property = text_object_get_property;
  object_class->finalize = text_object_finalize;

  obj_properties[PROP_UUID] = g_param_spec_string("uuid", "UUID", "Unique ID", NULL, G_PARAM_READWRITE);
  obj_properties[PROP_TEXT] = g_param_spec_string("text", "Text", "Display Text", NULL, G_PARAM_READWRITE);
  obj_properties[PROP_X] = g_param_spec_double("x", "X", "X Coordinate", -G_MAXDOUBLE, G_MAXDOUBLE, 0, G_PARAM_READWRITE);
  obj_properties[PROP_Y] = g_param_spec_double("y", "Y", "Y Coordinate", -G_MAXDOUBLE, G_MAXDOUBLE, 0, G_PARAM_READWRITE);
  obj_properties[PROP_FONT_SIZE] = g_param_spec_double("font-size", "Font Size", "Font Size", 1, 200, 12, G_PARAM_READWRITE);
  obj_properties[PROP_COLOR] = g_param_spec_enum("color", "Color", "Color Mode", color_mode_get_type(), RED,  G_PARAM_READWRITE
  );

  g_object_class_install_properties(object_class, N_PROPERTIES, obj_properties);
}

static void text_object_init(TextObject *self) {
  self->uuid = g_strdup("");
  self->text = g_strdup("");
}


TextObject *text_object_new(const gchar *text,
                            gchar *uuid,
                            gdouble x, gdouble y,
                            gdouble font_size,
                            ColorMode color) {
  return g_object_new(TEXT_TYPE_OBJECT,
                      "text", text,
                      "uuid", uuid,
                      "x", x, "y", y,
                      "font-size", font_size,
                      "color", color,
                      NULL);
}