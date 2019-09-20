#include"header.h"
/**
#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//**/
//Play
 void play_cb (GtkButton *button, Playdata *data) 
{
	gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
}
//Pause
 void pause_cb (GtkButton *button, Playdata *data) 
{
  	gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
}
//Stop
 void stop_cb (GtkButton *button, Playdata *data)
{
 	gst_element_set_state (data->pipeline, GST_STATE_READY);
}
//delete
 void delete_event_cb (GtkWidget *widget, GdkEvent *event, Playdata *data) 
{
  stop_cb (NULL, data);
  gtk_main_quit ();
}
