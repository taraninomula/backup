//Refresh
#include"header.h"
/**
#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//**/
 gboolean refresh_ui (Playdata *data)
{
  	data->current = -1;

	if (data->state < GST_STATE_PAUSED)
  		  return TRUE;

	//g_printf("duration:::::::: %"G_GUINT64_FORMAT"\n",data->duration);
  	if (!GST_CLOCK_TIME_IS_VALID (data->duration)) {
  		  if (!gst_element_query_duration (data->pipeline, GST_FORMAT_TIME, &data->duration)) 
		  {
  			    g_printerr ("Could not query current duration.\n");
          	  } 
		  else 
		  {
			   gtk_range_set_range (GTK_RANGE (data->slider), 0, (gdouble)data->duration / GST_SECOND);
    		  }
  	}

 	if (gst_element_query_position (data->pipeline, GST_FORMAT_TIME, &data->current))
	{
   
 	 		g_signal_handler_block (data->slider, data->slider_update_signal_id);

 			gtk_range_set_value (GTK_RANGE (data->slider), (gdouble)data->current / GST_SECOND);
			gtk_range_set_restrict_to_fill_level (GTK_RANGE (data->slider),0);//
    			g_signal_handler_unblock (data->slider, data->slider_update_signal_id);
  	}
  return TRUE;
}
