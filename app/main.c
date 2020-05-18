#include <JavaScriptCore/JavaScript.h>
#include <cairo/cairo.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <libgen.h>
#include <stdio.h>
#include <webkit2/webkit2.h>
#include <webkitdom/webkitdom.h>

GtkWidget* win;
GdkWindow* gdk_window;
GdkScreen* screen;
WebKitWebView* web;
WebKitUserContentManager* manager;

int bar_height = 32;
int margin = 10;
int screen_height = 0;
int screen_width = 0;

/**
 * Returns the script result as string.
 * Returned string must be freed by g_free.
 */
char* util_js_result_as_string(WebKitJavascriptResult* result) {
  JSValueRef value;
  JSStringRef string;
  size_t len;
  char* retval = NULL;

  value = webkit_javascript_result_get_value(result);
  string = JSValueToStringCopy(webkit_javascript_result_get_global_context(result), value, NULL);

  len = JSStringGetMaximumUTF8CStringSize(string);
  if (len) {
    retval = g_malloc(len);
    JSStringGetUTF8CString(string, retval, len);
  }
  JSStringRelease(string);

  return retval;
}

static void initialize_web_extensions_cb(WebKitWebContext* context, gpointer user_data) {
  /* Web Extensions get a different ID for each Web Process */
  static guint32 unique_id = 0;

  webkit_web_context_set_web_extensions_directory(context, WEB_EXTENSIONS_DIRECTORY);
  webkit_web_context_set_web_extensions_initialization_user_data(context, g_variant_new_uint32(unique_id++));

  printf("\n\n\n%s\n\n\n", WEB_EXTENSIONS_DIRECTORY);
}

static void destroyWinCb(GtkWidget* widget, GtkWidget* window) { gtk_main_quit(); }

static gboolean closeWebCb(WebKitWebView* webView, GtkWidget* window) {
  gtk_widget_destroy(window);
  return TRUE;
}

static void onLoad(WebKitWebView* webView, GtkWidget* window) { printf("ON LOAD \n"); }

static void create_dock(GtkWidget* dock, GdkGravity gravity, int screen_width, int screen_height, int height) {
  int y;

  if (gravity == GDK_GRAVITY_NORTH_WEST) {
    y = 0;
  } else {
    y = screen_height - height;
  }

  gtk_window_set_type_hint(GTK_WINDOW(dock), GDK_WINDOW_TYPE_HINT_DOCK);
  gtk_window_set_position(GTK_WINDOW(dock), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(dock), screen_width, height);
  gtk_window_set_gravity(GTK_WINDOW(dock), gravity);
  gtk_window_move(GTK_WINDOW(dock), 0, y);
  gtk_window_resize(GTK_WINDOW(dock), screen_width, height);

  gtk_widget_show(dock);
  gtk_widget_show_all(dock);
  gtk_window_move(GTK_WINDOW(dock), 0, y);
}

static void init_webkit(WebKitWebView* web) {
  gchar* url = "http://localhost:8080";

  WebKitSettings* config = webkit_settings_new();
  webkit_settings_set_enable_webgl(config, true);
  webkit_settings_set_enable_developer_extras(config, true);
  webkit_settings_set_enable_write_console_messages_to_stdout(config, true);

  webkit_web_context_set_cache_model(WEBKIT_WEB_CONTEXT(web), WEBKIT_CACHE_MODEL_DOCUMENT_VIEWER);
  webkit_web_view_load_uri(web, url);
}

static void draw_rects() {
  // CAIRO
  int offset_y = screen_height - bar_height;
  cairo_region_t* region;
  cairo_rectangle_int_t region_top = {0, 0, screen_width, bar_height};
  cairo_rectangle_int_t region_bottom = {0, offset_y, screen_width, bar_height};

  cairo_rectangle_int_t regions[2];

  regions[0] = region_top;
  regions[1] = region_bottom;

  region = cairo_region_create_rectangles(regions, 2);

  gdk_window_shape_combine_region(GDK_WINDOW(gdk_window), region, 0, 0);
  cairo_region_destroy(region);
}

static void clear_rects() {
  cairo_region_t* region;
  cairo_rectangle_int_t rect = {0, 0, screen_width, screen_height};

  region = cairo_region_create_rectangle(&rect);

  gdk_window_shape_combine_region(GDK_WINDOW(gdk_window), region, 0, 0);
  cairo_region_destroy(region);
}

static void draw_window() {
  gtk_window_resize(GTK_WINDOW(win), screen_width, screen_height);
  gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_TOOLTIP);
  gdk_window_set_override_redirect(GDK_WINDOW(gdk_window), true);
  gtk_window_set_default_size(GTK_WINDOW(win), screen_width, screen_height);

  gtk_widget_show(win);
  gtk_window_present(GTK_WINDOW(win));
  gtk_widget_show_all(win);
  gtk_window_resize(GTK_WINDOW(win), screen_width, screen_height);
  gtk_window_move(GTK_WINDOW(win), 0, 0);
  gtk_widget_show_all(win);
}

static void faltbar_message_received_cb(WebKitUserContentManager* manager, WebKitJavascriptResult* js_result,
                                        gpointer user_data) {
  char* message = util_js_result_as_string(js_result);

  if (!strcmp(message, "full")) {
    gdk_window_set_override_redirect(GDK_WINDOW(gdk_window), false);
    gtk_widget_hide(win);
    clear_rects();
    /* gtk_window_present(GTK_WINDOW(win)); */
    gtk_window_set_keep_above(GTK_WINDOW(win), true);
    /*  */
    /* gtk_window_move(GTK_WINDOW(win), 0, 0); */
    /* gtk_window_resize(GTK_WINDOW(win), screen_width, screen_height); */
    gtk_window_fullscreen(GTK_WINDOW(win));
    gtk_widget_set_can_focus(win, true);
    gtk_widget_set_can_focus(GTK_WIDGET(web), true);
    gtk_window_set_accept_focus(GTK_WINDOW(win), true);
    gtk_window_activate_focus(GTK_WINDOW(win));
    gtk_widget_grab_focus(GTK_WIDGET(web));
    /* gtk_window_set_default_size(GTK_WINDOW(win), screen_width, screen_height); */
    /* gtk_window_move(GTK_WINDOW(win), 0, 0); */
    /* gtk_window_resize(GTK_WINDOW(win), screen_width, screen_height); */
    /*  */
    /* gtk_window_resize(GTK_WINDOW(win), screen_width, screen_height); */
    gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_DIALOG);
    /* gtk_window_set_default_size(GTK_WINDOW(win), screen_width, screen_height); */
    /* gtk_window_resize(GTK_WINDOW(win), screen_width, screen_height); */
    /* gtk_window_move(GTK_WINDOW(win), 0, 0); */
    gtk_widget_show_all(win);

    g_message("FULL\n\n\n\n");
  } else if (!strcmp(message, "small")) {
    gtk_widget_hide(win);
    g_message("SMALL\n\n\n\n");
    gtk_window_unfullscreen(GTK_WINDOW(win));
    /* gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_TOOLTIP); */
    /* gtk_widget_set_can_focus(win, false); */
    /* gtk_window_set_accept_focus(GTK_WINDOW(win), false); */
    /* gtk_widget_set_app_paintable(win, true); */
    /* #<{(| gtk_window_set_keep_above(GTK_WINDOW(win), true); |)}># */
    /* #<{(| gtk_window_set_keep_below(GTK_WINDOW(win), false); |)}># */
    /* gtk_window_set_resizable(GTK_WINDOW(win), false); */
    /* gtk_window_set_decorated(GTK_WINDOW(win), false); */
    /* gtk_window_set_skip_taskbar_hint(GTK_WINDOW(win), false); */
    gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_TOOLTIP);
    /* gtk_widget_set_focus_on_click(win, true); */

    draw_window();
    draw_rects();
    gtk_widget_show_all(win);
    /* gtk_window_move(GTK_WINDOW(win), 0, 0); */
  }

  g_free(message);
  webkit_javascript_result_unref(js_result);
}

int main(int argc, char* argv[]) {
  gtk_init(&argc, &argv);

  g_signal_connect(webkit_web_context_get_default(), "initialize-web-extensions",
                   G_CALLBACK(initialize_web_extensions_cb), NULL);

  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  manager = webkit_user_content_manager_new();
  web = WEBKIT_WEB_VIEW(webkit_web_view_new_with_user_content_manager(manager));
  init_webkit(web);
  gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(web));

  // Add C <-> JS handlers.
  webkit_user_content_manager_register_script_message_handler(manager, "faltbar");
  g_signal_connect(manager, "script-message-received::faltbar", G_CALLBACK(faltbar_message_received_cb), NULL);

  // Set window properties.
  gtk_widget_set_can_focus(win, false);
  gtk_window_set_accept_focus(GTK_WINDOW(win), false);
  gtk_widget_set_app_paintable(win, true);
  /* gtk_window_set_keep_above(GTK_WINDOW(win), true); */
  /* gtk_window_set_keep_below(GTK_WINDOW(win), false); */
  gtk_window_set_resizable(GTK_WINDOW(win), false);
  gtk_window_set_decorated(GTK_WINDOW(win), false);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(win), false);
  gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_TOOLTIP);
  /* gtk_widget_set_focus_on_click(win, true); */

  gtk_widget_show_all(win);
  gtk_window_move(GTK_WINDOW(win), 0, 0);

  gdk_window = gtk_widget_get_window(GTK_WIDGET(win));

  screen = gtk_widget_get_screen(win);
  screen_height = gdk_screen_get_height(screen);
  screen_width = gdk_screen_get_width(screen);

  draw_window();
  // CAIRO
  draw_rects();

  g_signal_connect(win, "destroy", G_CALLBACK(destroyWinCb), NULL);
  g_signal_connect(web, "close", G_CALLBACK(closeWebCb), win);

  // Initialize Docks.
  GtkWidget* dock_bottom;
  dock_bottom = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  create_dock(dock_bottom, GDK_GRAVITY_SOUTH_WEST, screen_width, screen_height, bar_height);

  GtkWidget* dock_top;
  dock_top = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  create_dock(dock_top, GDK_GRAVITY_NORTH_WEST, screen_width, screen_height, bar_height);

  gtk_main();

  return 0;
}
