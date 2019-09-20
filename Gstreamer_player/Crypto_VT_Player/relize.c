
//Realize
//Now that we have our window and playbin(pipeline) ready, we need to integrate the two. To integrate, we’ll inform GStreamer to render the video output from playbin into one of our window widgets. By doing this, the video will be embedded into the window. Note that if we didn’t inform GStreamer, it would create its own window since we are using the playbin element.

#include"header.h"
/**
#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//**/
 void realize_cb (GtkWidget *widget, Playdata *data)
{
  	GdkWindow *window = gtk_widget_get_window (widget);
  	guintptr window_handle;

  	if (!gdk_window_ensure_native (window))
  		  g_error ("Couldn't create native window needed for GstXOverlay!");
	
	window_handle = GDK_WINDOW_XID (window);
  
  	gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (data->Vsink), window_handle);
}
