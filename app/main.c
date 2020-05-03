#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static void destroyWinCb(GtkWidget* widget, GtkWidget* window) {
  gtk_main_quit();
}

static gboolean closeWebCb(WebKitWebView* webView, GtkWidget* window) {
  gtk_widget_destroy(window);
  return TRUE;
}

int main(int argc, char* argv[])
{
  GtkWidget *win;

  WebKitWebView *web;
  gchar * url = "http://localhost:8080";
  GdkScreen *screen;
  GdkRGBA rgba = { .alpha = 0.0 };

  gtk_init(&argc, &argv);

  if (argc == 2) {
    url = argv[1];
  }

  int bar_height = 64;
  int screen_height = 0;
  int screen_width = 0;

  screen = gtk_widget_get_screen(win);
  screen_height = gdk_screen_get_height(screen);
  screen_width = gdk_screen_get_width(screen);

  /* gtk_widget_set_visual(win, gdk_screen_get_rgba_visual(screen)); */
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_decorated(win, false);
  gtk_window_stick(win);
  gtk_window_set_position(win, GTK_WIN_POS_NONE);
  gtk_window_set_gravity(win, GDK_GRAVITY_SOUTH_WEST);
  gtk_window_set_default_size(GTK_WINDOW(win), screen_width, bar_height);
  gtk_window_move(win, 0, screen_height);
  /* gtk_widget_set_app_paintable(win, TRUE); */

  web = WEBKIT_WEB_VIEW(webkit_web_view_new());
  /* webkit_web_view_set_background_color(web, &rgba); */

  gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(web));

  g_signal_connect(win, "destroy", G_CALLBACK(destroyWinCb), NULL);
  g_signal_connect(web, "close", G_CALLBACK(closeWebCb), win);

  webkit_web_context_set_cache_model(web, WEBKIT_CACHE_MODEL_DOCUMENT_VIEWER);
  webkit_web_view_load_uri(web, url);

  /* GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(win)); */
  /* gdk_window_hide(GDK_WINDOW(gdk_window)); */

  gtk_window_set_keep_above       (GTK_WINDOW(win), true);
  /* gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window), true); */
  /* gtk_window_set_accept_focus     (GTK_WINDOW(window), false); */
  /* gtk_window_set_decorated        (GTK_WINDOW(window), false); */
  /* gtk_window_set_resizable        (GTK_WINDOW(win), false); */
  gtk_window_set_type_hint        (GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_DOCK);

  /* gtk_widget_grab_focus(GTK_WIDGET(web)); */

  gtk_widget_show_all(win);

  gtk_main();

  return 0;
}
