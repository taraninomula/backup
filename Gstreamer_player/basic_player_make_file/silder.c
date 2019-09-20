#include"header.h"
/**
#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//**/
//Slider
 void slider_cb (GtkRange *range, Playdata *data) 
{
  	gdouble value = gtk_range_get_value (GTK_RANGE (data->slider));
  	gst_element_seek_simple (data->pipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT,(gint64)(value * GST_SECOND));

}


