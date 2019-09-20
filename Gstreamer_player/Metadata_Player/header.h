#ifndef HEADER_H
#define HEADER_H

#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//interface b//w gstreamer and window supported library*/
#include <gst/pbutils/pbutils.h>//for gstdiscover utility object ,Pbutils — General Application and Plugin Utility Library
	//gint w=720,h=540;
char *filename1,*filename2;
	static int i=0;	
typedef struct play{

	GstElement *pipeline, *source, *decodebinn, *Vsink,*Are_sa,*Asink,*Vconv,*Aconv,*playbin,*Vsink1;
	GstElement *audioqueue,*videoqueue;
	GstState state;
	GMainLoop *loop;
	GtkWidget *slider;            
  	gulong slider_update_signal_id; 
	gint64 duration,current,position; 
  	GstDiscoverer *discoverer;
}Playdata;
 void on_pad_added (GstElement *,  GstPad  *,Playdata *);
 void error_cb (GstBus *, GstMessage *, Playdata *); 
 void state_changed_cb (GstBus *, GstMessage *, Playdata *);
 void eos_cb (GstBus *, GstMessage *, Playdata *);

 void create_gui (Playdata *);
 void myCSS(void);
 void play_cb (GtkButton *, Playdata *) ;
 void pause_cb (GtkButton *, Playdata *) ;
 void stop_cb (GtkButton *, Playdata *) ;

 void forward_seek_cb (GtkRange *, Playdata *);
 void backward_seek_cb (GtkRange *, Playdata *);
 void slider_cb (GtkRange *, Playdata *) ;
 void folder_cb(GtkButton *, Playdata *); 
 void previous_cb(GtkButton *, Playdata *);
 gboolean Win_Mouse_cb(GtkWidget* ,GdkEventButton *,Playdata *);

 void realize_cb (GtkWidget *, Playdata *);
 gboolean draw_cb (GtkWidget *, cairo_t *, Playdata *);
 gboolean refresh_ui (Playdata *) ;
 void delete_event_cb (GtkWidget *, GdkEvent *, Playdata *);

 void on_discovered_cb (GstDiscoverer *discoverer, GstDiscovererInfo *info, GError *err, Playdata *data);
 void print_topology (GstDiscovererStreamInfo *info, gint depth) ;
 void print_stream_info (GstDiscovererStreamInfo *info, gint depth) ;
 void print_tag_foreach (const GstTagList *tags, const gchar *tag, gpointer user_data);

//static gboolean cb_print_position (Playdata *) ;//
#endif

