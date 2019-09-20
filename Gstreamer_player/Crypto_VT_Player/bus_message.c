#include"header.h"
/******************************************
Error
******************************************/
#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//**/
 void error_cb (GstBus *bus, GstMessage *msg,Playdata *data) 
{
  	GError *err;
  	gchar *debug_info;
  	gst_message_parse_error (msg, &err, &debug_info);
  	g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
  	g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
  	g_clear_error (&err);
  	g_free (debug_info);
  	gst_element_set_state (data->pipeline, GST_STATE_READY);
}
//State change
 void state_changed_cb (GstBus *bus, GstMessage *msg,Playdata *data)
{
  	GstState old_state, new_state, pending_state;
  	gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
  	if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data->pipeline)) 
	{
	    data->state = new_state;
	    g_print ("State set to %s\n", gst_element_state_get_name (new_state));
   

	    if (old_state == GST_STATE_READY && new_state == GST_STATE_PAUSED) 
				refresh_ui (data);
   	}

}
//EOS
 void eos_cb (GstBus *bus, GstMessage *msg, Playdata *data) 
{
	  g_print ("End-Of-Stream reached.\n");
	  gst_element_set_state (data->pipeline, GST_STATE_READY);
}
