#include "setup_style.h"

void setup_css() {
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "src/css/header.css");

  GdkDisplay *display = gdk_display_get_default();

  gtk_style_context_add_provider_for_display(
    display,
    GTK_STYLE_PROVIDER(provider),
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
  );
}