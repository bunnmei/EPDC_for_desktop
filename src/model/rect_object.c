#include <glib.h>
#include <glib-object.h>

#include "rect_object.h"

enum {
  PROP_0,
  PROP_UUID,
  PROP_X,
  PROP_Y,
  PROP_W,
  PROP_H,
  PROP_DEGREE,
  PROP_COLOR,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL };

G_DEFINE_FINAL_TYPE(RectObject, rect_object, G_TYPE_OBJECT)

static void rect_object_set_property(GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec) {
  RectObject *self = RECT_OBJMode_OBJECT(object);
  switch (prop_id) {
    case PROP_UUID: g_free(self->uuid); self->uuid = g_value_dup_string(value); break;
    case PROP_X: self->x = g_value_get_double(value); break;
    case PROP_Y: self->y = g_value_get_double(value); break;
    case PROP_W: self->w = g_value_get_double(value); break;
    case PROP_H: self->h = g_value_get_double(value); break;
    case PROP_DEGREE: self->degree = g_value_get_double(value); break;

    case PROP_COLOR:
      self->color = g_value_get_enum(value); break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
    }
}

static void rect_object_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec) {
  RectObject *self = RECT_OBJMode_OBJECT(object);
  switch (prop_id) {
    case PROP_UUID: g_value_set_string(value, self->uuid); break;
    case PROP_X: g_value_set_double(value, self->x); break;
    case PROP_Y: g_value_set_double(value, self->y); break;
    case PROP_W: g_value_set_double(value, self->w); break;
    case PROP_H: g_value_set_double(value, self->h); break;
    case PROP_DEGREE: g_value_set_double(value, self->degree); break;
    case PROP_COLOR: g_value_set_enum(value, self->color); break;
    default: G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec); break;
  }
}

static void rect_object_finalize(GObject *object) {
  RectObject *self = RECT_OBJMode_OBJECT(object);
  g_free(self->uuid);
  G_OBJECT_CLASS(rect_object_parent_class)->finalize(object);
}

static void rect_object_class_init(RectObjectClass *klass) {
  GObjectClass *object_class = G_OBJECT_CLASS(klass);
  object_class->set_property = rect_object_set_property;
  object_class->get_property = rect_object_get_property;
  object_class->finalize = rect_object_finalize;

  obj_properties[PROP_UUID] = g_param_spec_string("uuid", "UUID", "Unique ID", NULL, G_PARAM_READWRITE);
  obj_properties[PROP_X] = g_param_spec_double("x", "X", "X Coordinate", -G_MAXDOUBLE, G_MAXDOUBLE, 0, G_PARAM_READWRITE);
  obj_properties[PROP_Y] = g_param_spec_double("y", "Y", "Y Coordinate", -G_MAXDOUBLE, G_MAXDOUBLE, 0, G_PARAM_READWRITE);
  obj_properties[PROP_W] = g_param_spec_double("w", "W", "W Coordinate", -G_MAXDOUBLE, G_MAXDOUBLE, 0, G_PARAM_READWRITE);
  obj_properties[PROP_H] = g_param_spec_double("h", "H", "H Coordinate", -G_MAXDOUBLE, G_MAXDOUBLE, 0, G_PARAM_READWRITE);
  obj_properties[PROP_DEGREE] = g_param_spec_double("degree", "DEGREE", "DEGREE Coordinate", -G_MAXDOUBLE, G_MAXDOUBLE, 0, G_PARAM_READWRITE);
  obj_properties[PROP_COLOR] = g_param_spec_enum("color", "Color", "Color Mode", color_mode_get_type(), RED,  G_PARAM_READWRITE
  );

  g_object_class_install_properties(object_class, N_PROPERTIES, obj_properties);
}

static void rect_object_init(RectObject *self) {
  self->uuid = g_strdup("");
}


RectObject *rect_object_new(gchar *uuid,
                            gdouble x,
                            gdouble y,
                            gdouble w,
                            gdouble h,
                            gdouble degree,
                            ColorMode color) {
  return g_object_new(RECT_TYPE_OBJECT,
                      "uuid", uuid,
                      "x", x, 
                      "y", y,
                      "w", w,
                      "h", h,
                      "degree", degree,
                      "color", color,
                      NULL);
}