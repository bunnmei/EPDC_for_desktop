#include <gtk/gtk.h>

#include "setup_style.h"
#include "header.h"
#include "main_content.h"
#include "canvas.h"
#include "tab_ui.h"
#include "text_object.h"
#include "object_common.h"

static void app_activate(GApplication *app){
  EPDC_App_Obj *app_obj = app_obj_init();
  PopUp *pop_up = pop_up_init(app_obj);
  setup_css(); // cssの読み込み.

  GtkWidget *win = gtk_application_window_new(GTK_APPLICATION (app));
  gtk_window_set_default_size (GTK_WINDOW (win), 1440, 810);
  create_header(win); //カスタムヘッダーを作成.

  // 左右分割画面の作成.
  GtkWidget *main_box = create_main_content_box(win);
  GtkWidget *left_box = create_content_left_box(main_box);
  GtkWidget *right_box = create_content_right_box(main_box);

  create_canvas(left_box, pop_up);
  create_tab_ui(right_box, pop_up);

  gtk_window_present(GTK_WINDOW(win));
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int stat;

  app = gtk_application_new ("space.webkombinat.epdc", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
  stat =g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return stat;
}