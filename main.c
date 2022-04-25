#include <gtk/gtk.h>
#include "lexico.h"

static GtkWidget *stack;

static void analisar(GtkWidget *widget, GtkTextBuffer *buffer) {
  //Pega o iterador inicial e final passados no buffer.
  GtkTextIter iter, end;
  gtk_text_buffer_get_start_iter(buffer, &iter);
  gtk_text_buffer_get_end_iter(buffer, &end);

  parse(gtk_text_buffer_get_text(buffer, &iter, &end, true));
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;

  GtkWidget *header;
  GtkWidget *sw;
  GtkWidget *view;
  GtkWidget *show_source;
  GtkTextBuffer *buffer;
  GtkTextIter iter;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "Análisador Léxico");
  gtk_window_set_default_size(GTK_WINDOW (window), 600, 200);

  stack = gtk_stack_new();
  gtk_widget_show(stack);
  gtk_window_set_child(GTK_WINDOW (window), stack);

  show_source = gtk_button_new_with_label("Analisar");
  gtk_widget_set_valign(show_source, GTK_ALIGN_CENTER);

  header = gtk_header_bar_new();
  gtk_header_bar_pack_start(GTK_HEADER_BAR (header), show_source);
  gtk_window_set_titlebar(GTK_WINDOW (window), header);

  view = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW (view), TRUE);
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW (view), GTK_WRAP_WORD_CHAR);
  gtk_text_view_set_left_margin(GTK_TEXT_VIEW (view), 10);
  gtk_text_view_set_right_margin(GTK_TEXT_VIEW (view), 10);

  sw = gtk_scrolled_window_new();
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (sw),
                                 GTK_POLICY_AUTOMATIC,
                                 GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW (sw), view);

  gtk_stack_add_named(GTK_STACK (stack), sw, "formatado");

  //Criação de instancia do buffer.
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (view));
  gtk_text_buffer_set_enable_undo(buffer, TRUE);
  gtk_text_buffer_begin_irreversible_action(buffer);
  gtk_text_buffer_get_start_iter(buffer, &iter);

  gtk_text_buffer_end_irreversible_action(buffer);

  g_signal_connect (show_source, "clicked", G_CALLBACK(analisar), buffer);

  gtk_widget_show(window);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.mattes.AnalisadorLexico", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;
}
