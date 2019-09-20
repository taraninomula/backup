/**
#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>**/
#include"header.h"
//Forward
 void forward_seek_cb (GtkRange *range, Playdata *data)
{ 
	gst_element_query_duration (data->pipeline, GST_FORMAT_TIME, &data->duration);
	gst_element_query_position (data->pipeline, GST_FORMAT_TIME, &data->current);	

    
    	data->position = data->current+(data->duration * 5.0 / 100.0);
 	
  		gst_element_seek_simple (data->pipeline, GST_FORMAT_TIME,GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH, data->position);
  	

	 
}

