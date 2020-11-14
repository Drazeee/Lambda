#include "interface.h"

int columns = 1;
int contrast = 0;
int noise = 1;
int correction = 1;

GtkBuilder *builder;
SDL_Surface *img;
char *filename;

typedef struct {
    GtkWidget *errorImageLabel;
    GtkWidget *resultLabel;
} app_widgets;

app_widgets        *widgets;

void interface()
{
    widgets = g_slice_new(app_widgets);
    gtk_init(NULL, NULL);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/Interface/interface.glade", NULL);
    GtkWidget       *window= GTK_WIDGET(gtk_builder_get_object(builder, "main"));
    widgets->errorImageLabel  = GTK_WIDGET(gtk_builder_get_object(builder, "errorImage"));
    widgets->resultLabel  = GTK_WIDGET(gtk_builder_get_object(builder, "resultOutput"));
    
    gtk_builder_connect_signals(builder, widgets);

    gtk_widget_show(window);
    g_object_unref(builder);

    gtk_main();

    printf("%i|%i|%i|%i", columns, contrast, noise, correction);
}

// called when window is closed
void on_destroy()
{
    gtk_main_quit();
}

void file_set (GtkFileChooser *file_chooser, gpointer data)
{
    filename = gtk_file_chooser_get_preview_filename (file_chooser);
    img = SDL_LoadBMP(filename);
    if (!img) {
        gtk_label_set_text(GTK_LABEL(widgets->errorImageLabel), "We cant't load your image. Please make sur that this is a .bmp extension");
    }
    else {
        gtk_label_set_text(GTK_LABEL(widgets->errorImageLabel), "");
    }
}


void toggleColumns()
{
    columns = !columns;
}

void toggleContrast()
{
    contrast = !contrast;
}

void toggleNoise()
{
    noise = !noise;
}

void toggleCorrection()
{
    correction = !correction;
}


void launchRecognition()
{
    if (img) {
        char *result = characterSegmentation(filename, "results/test", 0);
        GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgets->resultLabel));
        gtk_text_buffer_set_text (buffer, result, -1);
    }
    else {
        GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgets->resultLabel));
        gtk_text_buffer_set_text (buffer, "Not good", -1);
    }
}