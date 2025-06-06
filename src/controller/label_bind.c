#include "label_bind.h"

gchar *f2i(GObject *obj, gdouble d, const char *prefix){
    return g_strdup_printf("%s: %d", prefix, (int)d);
}

void label_bind_double(const char *prop_name, gpointer value, gpointer obj) {
  GtkExpression *params[2]; //切り出し
  params[0] = gtk_property_expression_new(TEXT_TYPE_OBJECT, NULL, prop_name);
  params[1] = gtk_constant_expression_new(G_TYPE_STRING, prop_name);
  GtkExpression *format_ex = gtk_cclosure_expression_new(G_TYPE_STRING, NULL, 2, params, G_CALLBACK(f2i), NULL, NULL);
  gtk_expression_bind(format_ex, value, "label", obj);
}