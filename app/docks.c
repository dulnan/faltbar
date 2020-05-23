#include <gmodule.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GPtrArray* docks;

/**
 * Initialize with the specified mount of docks.
 */
void faltbar_docks_init(int count) {
  docks = g_ptr_array_new();

  for (int i = 0; i < count; i++) {
    GtkWidget* dock = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_ptr_array_add(docks, dock);
  }
}

/**
 * Reposition the dock windows, add one if needed.
 */
static void faltbar_docks_reposition(int index, int x, int y, int w, int h) {
  if (index >= docks->len) {
    GtkWidget* dock = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_ptr_array_add(docks, dock);
  }

  const GtkWidget* dock = g_ptr_array_index(docks, index);

  gtk_widget_hide(GTK_WINDOW(dock));
  gtk_window_set_type_hint(GTK_WINDOW(dock), GDK_WINDOW_TYPE_HINT_DOCK);
  gtk_window_set_position(GTK_WINDOW(dock), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(dock), w, h);
  gtk_window_move(GTK_WINDOW(dock), x, y);
  gtk_window_resize(GTK_WINDOW(dock), w, h);

  gtk_widget_show(GTK_WINDOW(dock));
  gtk_widget_show_all(GTK_WINDOW(dock));
  gtk_window_move(GTK_WINDOW(dock), x, y);
}
