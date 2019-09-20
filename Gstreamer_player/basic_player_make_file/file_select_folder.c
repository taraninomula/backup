//folder
/**
#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//**/
#include"header.h"

 void folder_cb(GtkButton *button, Playdata *data) 
{
	GtkWidget *dialog; static char *filename=NULL;
	gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
        dialog = gtk_file_chooser_dialog_new("Open File",NULL, GTK_FILE_CHOOSER_ACTION_OPEN,"_Cancel", GTK_RESPONSE_CANCEL,"_Open", 				GTK_RESPONSE_ACCEPT,NULL);
	
    	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) 
    	{
		//if(i!=1)
			filename1=filename;
        	GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
        	g_message("File selected: %s", filename);
		data->duration = GST_CLOCK_TIME_NONE;
		gst_element_set_state (data->pipeline, GST_STATE_READY);
	
  		g_object_set (G_OBJECT (data->source), "location",filename, NULL);//set source property
		gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
		filename2=filename;
      		//g_free(filename);
    	}

    	gtk_widget_destroy (dialog);

}
