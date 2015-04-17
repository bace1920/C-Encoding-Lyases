#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *fpSource,*fpTarget,fs[100],ft[100];

int encryptFile(char *sourcefile,char *targetFile)
{FILE *fpSource, *fpTarget;  // 要打开的文件的指针
    char buffer[21];  // 缓冲区，用于存放从文件读取的数据
     char *secretKey;
     char key[8]="12345678";
     secretKey=key;
    int readCount,  // 每次从文件中读取的字节数
        keyLen = strlen(secretKey),  // 密钥的长度
        i;  // 循环次数

    // 以二进制方式读取/写入文件
      fpSource = fopen(sourcefile, "rb");
    if(fpSource==NULL){
        printf("[%s] open failed\n", sourcefile);
        return 0;
    }
    fpTarget = fopen(targetFile, "wb");
    if(fpTarget==NULL){
        printf("文件[%s] write filed\n", fpTarget);
        return 0;
    }
    // 不断地从文件中读取 keyLen 长度的数据，保存到buffer，直到文件结束
    while( (readCount=fread(buffer, 1, keyLen, fpSource)) > 0 ){
        // 对buffer中的数据逐字节进行异或运算
        for(i=0; i<readCount; i++){
            buffer[i] ^= secretKey[i];
        }
        // 将buffer中的数据写入文件
        fwrite(buffer, 1, readCount, fpTarget);
    }

    fclose(fpSource);
    fclose(fpTarget);
    return 1;
}


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
        {   fpSource=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
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
    if(encryptFile(fpSource,fpTarget))
        printf("congratulation"),
    gtk_dialog_run(GTK_DIALOG(dialog_end));
    //gtk_widget_destroy(dialog_start);
    gtk_widget_destroy(dialog_end);
}

int main(int argc, char** argv) {
//GtkWidget *label;
GtkWidget *window;
GtkWidget *frame;
GtkWidget *Target;
GtkWidget *start;
//GtkWidget *minus;
GtkWidget *Source;
gtk_init(&argc, &argv);
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(window), 320, 80);
gtk_window_set_title(GTK_WINDOW(window), "Lyases");
frame = gtk_fixed_new();
gtk_container_add(GTK_CONTAINER(window), frame);

Source=gtk_button_new_with_label("SourceFile");
gtk_widget_set_size_request(Source, 80, 35);
gtk_fixed_put(GTK_FIXED(frame), Source, 20, 20);
gtk_container_add(GTK_CONTAINER(window),Source);
g_signal_connect(G_OBJECT(Source),"clicked",G_CALLBACK(Source_select_file),NULL);

Target = gtk_button_new_with_label("TargetFile");
gtk_widget_set_size_request(Target, 80, 35);
gtk_fixed_put(GTK_FIXED(frame), Target, 120, 20);
gtk_container_add(GTK_CONTAINER(window),Target);
g_signal_connect(G_OBJECT(Target),"clicked",G_CALLBACK(Target_select_file),NULL);

start=gtk_button_new_with_label("Start");
gtk_widget_set_size_request(start, 80, 35);
gtk_fixed_put(GTK_FIXED(frame), start, 220, 20);
gtk_container_add(GTK_CONTAINER(window),start);
g_signal_connect(G_OBJECT(start),"clicked",G_CALLBACK(print_star_run),NULL);

//minus = gtk_button_new_with_label("-");
//gtk_widget_set_size_request(minus, 80, 35);
//gtk_fixed_put(GTK_FIXED(frame), minus, 50, 80);
//label = gtk_label_new("0");
//gtk_fixed_put(GTK_FIXED(frame), label, 190, 58);

//g_signal_connect(Target, "clicked", G_CALLBACK(increase), label);
//g_signal_connect(minus, "clicked", G_CALLBACK(decrease), label);

gtk_widget_show_all(window);
g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit),NULL);
gtk_widget_show_all(window);
gtk_main();
return 0;
}
