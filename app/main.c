#include <JavaScriptCore/JavaScript.h>
#include <cairo/cairo.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <libgen.h>
#include <stdio.h>
#include <webkit2/webkit2.h>
#include <webkitdom/webkitdom.h>

#include "docks.c"

GtkWidget* win;
GdkWindow* gdk_window;
GdkScreen* screen;
WebKitWebView* web;
WebKitUserContentManager* manager;
GdkDisplay* display;
GdkRectangle geo;

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

static int get_monitor_rects(GdkDisplay* display, GdkRectangle** rectangles) {
  int n = gdk_display_get_n_monitors(display);
  GdkRectangle* new_rectangles = (GdkRectangle*)malloc(n * sizeof(GdkRectangle));
  for (int i = 0; i < n; ++i) {
    GdkMonitor* monitor = gdk_display_get_monitor(display, i);
    gdk_monitor_get_geometry(monitor, &new_rectangles[i]);
  }
  *rectangles = new_rectangles;
  return n;
}

static void emit_rects() {
  GdkDisplay* display = gdk_display_get_default();
  GdkRectangle* rectangles = NULL;
  int nRectangles = get_monitor_rects(display, &rectangles);

  // CAIRO
  gchar* script;
  script = g_strdup_printf("window.faltbarMonitors = [];");
  webkit_web_view_run_javascript(web, script, NULL, NULL, NULL);

  for (int i = 0; i < nRectangles; ++i) {
    GdkRectangle rect = rectangles[i];
    GdkMonitor* monitor = gdk_display_get_monitor(display, i);
    const char* name = gdk_monitor_get_model(monitor);

    script = g_strdup_printf("window.faltbarMonitors.push({ name: '%s', x: %d, y: %d, w: %d, h: %d });", name, rect.x,
                             rect.y, rect.width, rect.height);
    webkit_web_view_run_javascript(web, script, NULL, NULL, NULL);
    g_free(script);
  }

  free(rectangles);
}

static void init_webkit(WebKitWebView* web) {
  gchar* url = "http://localhost:8080";
  WebKitSettings* config = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(web));
  webkit_settings_set_enable_webgl(config, true);
  webkit_settings_set_enable_developer_extras(config, true);
  webkit_settings_set_enable_write_console_messages_to_stdout(config, true);
  g_object_set(G_OBJECT(config), "enable-developer-extras", TRUE, NULL);

  webkit_web_context_set_cache_model(WEBKIT_WEB_CONTEXT(web), WEBKIT_CACHE_MODEL_DOCUMENT_VIEWER);
  webkit_web_view_load_uri(web, url);
  emit_rects();
  WebKitWebInspector* inspector = webkit_web_view_get_inspector(WEBKIT_WEB_VIEW(web));
  webkit_web_inspector_show(WEBKIT_WEB_INSPECTOR(inspector));
}

static void draw_rects() {
  GdkDisplay* display = gdk_display_get_default();
  GdkRectangle* rectangles = NULL;
  int nRectangles = get_monitor_rects(display, &rectangles);
  int nRegions = nRectangles * 2;

  cairo_rectangle_int_t regions[nRegions];

  // CAIRO
  cairo_region_t* region;

  for (int i = 0; i < nRectangles; ++i) {
    GdkRectangle rect = rectangles[i];

    regions[i].x = rect.x;
    regions[i].y = rect.y;
    regions[i].width = rect.width;
    regions[i].height = bar_height;

    regions[i + nRectangles].x = rect.x;
    regions[i + nRectangles].y = rect.height - bar_height;
    regions[i + nRectangles].width = rect.width;
    regions[i + nRectangles].height = bar_height;

    /* int actualWidth = rect.x + rect.width; */
    /* int actualHeight = rect.y + rect.height; */
    /* if (width < actualWidth) width = actualWidth; */
    /* if (height < actualHeight) height = actualHeight; */
  }

  region = cairo_region_create_rectangles(regions, nRegions);
  gdk_window_shape_combine_region(GDK_WINDOW(gdk_window), region, 0, 0);
  cairo_region_destroy(region);
  free(rectangles);
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

/**
 * Handler for the message sent by the web app.
 *
 * The format of the message is:
 * [
 *   [x, y, w, h],
 *   [x, y, w, h],
 *   [x, y, w, h]
 * ]
 *
 * It describes the rectangles of the currently visible bars.
 */
static void faltbar_bar_received_cb(WebKitUserContentManager* manager, WebKitJavascriptResult* js_result,
                                    gpointer user_data) {
  JSCValue* value = webkit_javascript_result_get_js_value(js_result);

  if (jsc_value_is_array(value)) {
    JSCValue* len = jsc_value_object_get_property(value, "length");
    const gint32 dlen = jsc_value_to_int32(len);

    cairo_rectangle_int_t regions[dlen];

    for (ptrdiff_t i = 0; i < dlen; ++i) {
      JSCValue* rect_array = jsc_value_object_get_property_at_index(value, i);

      gint32 x = jsc_value_to_int32(jsc_value_object_get_property_at_index(rect_array, 0));
      gint32 y = jsc_value_to_int32(jsc_value_object_get_property_at_index(rect_array, 1));
      gint32 w = jsc_value_to_int32(jsc_value_object_get_property_at_index(rect_array, 2));
      gint32 h = jsc_value_to_int32(jsc_value_object_get_property_at_index(rect_array, 3));

      regions[i].x = x;
      regions[i].y = y;
      regions[i].width = w;
      regions[i].height = h;

      /* faltbar_docks_reposition(i, x, y, w, h); */
    }
    cairo_region_t* region;

    gtk_widget_hide(win);
    region = cairo_region_create_rectangles(regions, dlen);
    gdk_window_shape_combine_region(GDK_WINDOW(gdk_window), region, 0, 0);
    cairo_region_destroy(region);
    gtk_widget_show_all(win);
  }

  /* g_free(message); */
  webkit_javascript_result_unref(js_result);
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

static void faltbar_get_monitors() {
  int i;
  int n = gdk_display_get_n_monitors(display);

  for (i = 0; i < n; i++) {
    GdkMonitor* moni = gdk_display_get_monitor(display, i);
    const char* model = gdk_monitor_get_model(moni);

    int sf = gdk_monitor_get_scale_factor(moni);
    gdk_monitor_get_geometry(moni, &geo);
    int w = geo.width;
    int h = geo.height;
    int x = geo.x;
    int y = geo.y;

    g_print("\n");
    g_print("Monitor: %s [%d]\n", model, i);
    g_print(" %d x %d [mm x mm]\n", w, h);
    g_print("x: %d - y: %d\n", x, y);
    g_print(" scale: %d\n", sf);
  }
}

static void size_to_screen(GtkWindow* window) {
  // Get total screen size.  This involves finding all physical monitors
  // connected, and examining their positions and sizes.  This is as complex
  // as it is because monitors can be configured to have relative
  // positioning, causing overlapping areas and a non-rectangular total
  // desktop area.
  //
  // We want our window to cover the minimum axis-aligned bounding box of
  // that total desktop area.  This means it's too large (even large bits of
  // it may be outside the accessible desktop) but it's easier to manage than
  // multiple windows.

  // TODO Find the min x and y too, just in case someone's weird setup
  // has something other than 0,0 as top-left.

  GdkDisplay* display = gdk_display_get_default();
  GdkRectangle* rectangles = NULL;
  int nRectangles = get_monitor_rects(display, &rectangles);

  int width = 0, height = 0;
  for (int i = 0; i < nRectangles; ++i) {
    GdkRectangle rect = rectangles[i];
    int actualWidth = rect.x + rect.width;
    int actualHeight = rect.y + rect.height;
    if (width < actualWidth) width = actualWidth;
    if (height < actualHeight) height = actualHeight;
  }
  free(rectangles);

  printf("width:  %d\n", width);
  printf("height: %d\n", height);

  /* gtk_window_set_default_size(window, width, height); */
  /* gtk_window_resize(window, width, height); */
  /* gtk_window_set_resizable(window, false); */
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
  webkit_user_content_manager_register_script_message_handler(manager, "faltbar_bar");
  g_signal_connect(manager, "script-message-received::faltbar", G_CALLBACK(faltbar_message_received_cb), NULL);
  g_signal_connect(manager, "script-message-received::faltbar_bar", G_CALLBACK(faltbar_bar_received_cb), NULL);

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

  /* printf("height: %d\n", screen_height); */
  /* printf("width:  %d\n", screen_width); */

  display = gdk_display_get_default();
  /* faltbar_get_monitors(); */

  /* size_to_screen(GTK_WINDOW(win)); */

  faltbar_docks_init(2);

  draw_window();
  // CAIRO
  draw_rects();

  g_signal_connect(win, "destroy", G_CALLBACK(destroyWinCb), NULL);
  g_signal_connect(web, "close", G_CALLBACK(closeWebCb), win);

  // Initialize Docks.
  GtkWidget* dock_bottom;
  dock_bottom = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  /* create_dock(dock_bottom, GDK_GRAVITY_SOUTH_WEST, screen_width, screen_height, bar_height); */

  GtkWidget* dock_top;
  dock_top = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  /* create_dock(dock_top, GDK_GRAVITY_NORTH_WEST, screen_width, screen_height, bar_height); */

  gtk_main();

  return 0;
}
