#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

extern char *fpSource,*fpTarget,*secretKey,*Mode;

void print_filename(GtkWidget *file)
{
    GtkWidget *dialog;
    gchar *filename;
    filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
    gtk_widget_destroy(file);
    dialog=gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,filename);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
void Source_select_file(GtkWidget *widget,gpointer data)
{
    GtkWidget *file;
    int file_return;
    file=gtk_file_chooser_dialog_new("SelectFile",NULL,GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,NULL);
    if(gtk_dialog_run(GTK_DIALOG(file))==GTK_RESPONSE_ACCEPT)
        {fpSource=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
            print_filename(file);}
    else
        gtk_widget_destroy(file);
}

void Target_select_file(GtkWidget *widget,gpointer data)
{
    GtkWidget *file;
    int file_return;
    file=gtk_file_chooser_dialog_new("SelectFile",NULL,GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,NULL);
    if(gtk_dialog_run(GTK_DIALOG(file))==GTK_RESPONSE_ACCEPT)
        fpTarget=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file)),print_filename(file);
    else
        gtk_widget_destroy(file);
}

void print_star_run(GtkWidget *start)
{
    GtkWidget *dialog_start;
    GtkWidget *dialog_end;
    //char start_tip[20]="处理中...";
    char start_end[20]="加密完成";
    gtk_widget_destroy(start);
    //dialog_start=gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,start_tip);
    dialog_end=gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,start_end);
    //gtk_dialog_run(GTK_DIALOG(dialog_start));
    option_in();
    if(select(fpSource,fpTarget,secretKey,Mode))
        printf("\ncongratulation"),
    gtk_dialog_run(GTK_DIALOG(dialog_end));
    //gtk_widget_destroy(dialog_start);
    gtk_widget_destroy(dialog_end);
}
