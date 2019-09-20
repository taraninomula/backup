#ifndef HEADER_H
#define HEADER_H

#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//interface b//w gstreamer and window supported library*/

	//gint w=720,h=540;
char *filename1,*filename2;
	static int i=0;	
typedef struct play{

	GstElement *pipeline, *source, *decodebinn,*cryptoo,*crypto_queue, *Vsink,*Are_sa,*Asink,*Vconv,*Aconv,*playbin,*Vsink1;
	GstElement *audioqueue,*videoqueue;
	GstState state;
	GMainLoop *loop;
	GtkWidget *slider;            
  	gulong slider_update_signal_id; 
	gint64 duration,current,position; 
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

//static gboolean cb_print_position (Playdata *) ;//
#endif

