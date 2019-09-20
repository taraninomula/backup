#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gst/pbutils/pbutils.h>//for gstdiscover utility object ,Pbutils — General Application and Plugin Utility Library

#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//interface b//w gstreamer and window supported library
gint w=720,h=540;
gchar *filename1,*filename2;
static gint i=0;

typedef struct play{
	GstElement *pipeline, *decodebinn, *Vsink,*Are_sa,*Asink,*Vconv,*Aconv,*Vsink1;
	GstElement *audioqueue,*videoqueue;
	GstState state;
	GMainLoop *loop;
  	GstDiscoverer *discoverer;//
	GtkWidget *slider;            
  	gulong slider_update_signal_id; 
	gint64 duration,current,position; 
}Playdata;


static void on_pad_added (GstElement *element,  GstPad  *pad,Playdata *data);
static void error_cb (GstBus *bus, GstMessage *msg, Playdata *data); 
static void state_changed_cb (GstBus *bus, GstMessage *msg, Playdata *data);
static void eos_cb (GstBus *bus, GstMessage *msg, Playdata *data);

static void create_gui (Playdata *data);
void myCSS(void);
static void play_cb (GtkButton *button, Playdata *data) ;
static void pause_cb (GtkButton *button, Playdata *data) ;
static void stop_cb (GtkButton *button, Playdata *data) ;

static void forward_seek_cb (GtkRange *range, Playdata *data);
static void backward_seek_cb (GtkRange *range, Playdata *data);
static void slider_cb (GtkRange *range, Playdata *data) ;
static void folder_cb(GtkButton *button, Playdata *data); 
static void previous_cb(GtkButton *button, Playdata *data);
static gboolean Win_Mouse_cb(GtkWidget* widget,GdkEventButton *event,Playdata *data);

static void realize_cb (GtkWidget *widget, Playdata *data);
static gboolean draw_cb (GtkWidget *widget, cairo_t *cr, Playdata *data);
static gboolean refresh_ui (Playdata *data) ;
static void delete_event_cb (GtkWidget *widget, GdkEvent *event, Playdata *data);

static void on_discovered_cb (GstDiscoverer *discoverer, GstDiscovererInfo *info, GError *err, Playdata *data);
static void print_topology (GstDiscovererStreamInfo *info, gint depth) ;
static void print_stream_info (GstDiscovererStreamInfo *info, gint depth) ;
static void print_tag_foreach (const GstTagList *tags, const gchar *tag, gpointer user_data);

static gboolean cb_print_position () ;//

int main(int argc, char *argv[])
{

	GMainLoop *loop;
  	GstBus *bus;
	GstStateChangeReturn ret;
	Playdata data;
	GError *err = NULL;//
	gchar *uri;
  	gst_init(&argc,&argv);//initize the gstreamer library
	gtk_init(&argc,&argv);//initize the gstreamer library

	if(argc==3)
		w=atoi(argv[2]);//char to integer convertion
	if(argc==4)
		h=atoi(argv[3]);

	loop = g_main_loop_new (NULL, FALSE);
	memset (&data, 0, sizeof (data));
	data.duration = GST_CLOCK_TIME_NONE;

	/* Create gstreamer elements */
  	data.pipeline = gst_pipeline_new ("Video-Audio-VT-Player");
  	
  
 	data.decodebinn  = gst_element_factory_make ("uridecodebin","decoderr");
  	data.audioqueue = gst_element_factory_make("queue","audioqueue");
  	data.videoqueue = gst_element_factory_make("queue","videoqueue");
  	data.Vconv     = gst_element_factory_make ("videoconvert",  "Vconverter");
  	data.Vsink     = gst_element_factory_make ("xvimagesink", "Video-output");


  	data.Aconv     = gst_element_factory_make ("audioconvert",  "data.Aconverter");
  	data.Are_sa    = gst_element_factory_make ("audioresample", "data.Are_sample");
  	data.Asink     = gst_element_factory_make ("autoaudiosink", "Audio-output");

	
			 

  	create_gui (&data);
	
 	bus = gst_element_get_bus (data.pipeline);
  	gst_bus_add_signal_watch (bus);
  	g_signal_connect (G_OBJECT (bus), "message::error", (GCallback)error_cb, &data);
   	g_signal_connect (G_OBJECT (bus), "message::eos", (GCallback)eos_cb, &data);
  	g_signal_connect (G_OBJECT (bus), "message::state-changed", (GCallback)state_changed_cb, &data);

  	 gst_object_unref (bus);
	
 	 gst_bin_add_many (GST_BIN (data.pipeline),data.decodebinn,data.videoqueue, data.Vconv,data.Vsink,data.audioqueue, 		 			data.Aconv , data.Asink, data.Are_sa, NULL);//add ele in bin


  	 gst_element_link_many (data.videoqueue,data.Vconv, data.Vsink, NULL);
  	 gst_element_link_many (data.audioqueue, data.Aconv,data.Are_sa, data.Asink, NULL);

   	 g_signal_connect (data.decodebinn, "pad-added", G_CALLBACK(on_pad_added),&data);//link pads
	
	if(argc>=2){
		if (gst_uri_is_valid (argv[1])) {
                	uri = g_strdup (argv[1]);
		} 
		else {
                	uri = gst_filename_to_uri (argv[1], NULL);
		}
	}
	else
		uri="file:///home/kakanhar/Pictures/sample.png";//uri="file:///home/valajkal/Pictures/sample.";//	
	g_object_set (G_OBJECT(data.decodebinn), "uri", uri, NULL);

	 data.discoverer = gst_discoverer_new (25* GST_SECOND, &err);//initilize discoverer	//
	 g_signal_connect (data.discoverer, "discovered", G_CALLBACK (on_discovered_cb), &data);//signal //
	 gst_discoverer_start (data.discoverer);//start discovering //
	 gst_discoverer_discover_uri_async (data.discoverer,uri);

	 g_print ("Now playing: %s\n", argv[1]);
  	 ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);

  	 if (ret == GST_STATE_CHANGE_FAILURE) {
   		g_printerr ("Unable to set the pipeline to the playing state.\n");
    		gst_object_unref (data.pipeline);
    		return -1;
  	 }


	 g_timeout_add_seconds (1, (GSourceFunc)refresh_ui, &data);
	 g_main_loop_run (loop);
	

  	// Free resources 
  	gst_element_set_state (data.pipeline, GST_STATE_NULL);
  	gst_object_unref (data.pipeline);
	gst_discoverer_stop (data.discoverer);
	g_main_loop_unref (loop);
  	return 0;
}
//
static void on_pad_added (GstElement *element,  GstPad  *pad, Playdata *data)
{
 
 	 GstPad *sinkpad;
  	 GstCaps *caps; 
  	 GstStructure *str; 
  	 const gchar *new_pad_type = NULL;
  	 caps =  gst_pad_get_current_caps (pad); //get current capbalities of demuxer pads
 
  	 str = gst_caps_get_structure (caps, 0); 
  
  	 new_pad_type = gst_structure_get_name (str);
  	
	 if (g_strrstr (gst_structure_get_name (str), "audio"))
	 { 
		
		sinkpad = gst_element_get_static_pad(data->audioqueue, "sink"); 
		gst_pad_link (pad, sinkpad);
		gst_object_unref (sinkpad);
		
		
	 }
	 else if(g_strrstr(gst_structure_get_name (str),"video"))
	 {
		sinkpad = gst_element_get_static_pad(data->videoqueue,"sink");
		gst_pad_link(pad,sinkpad);
		gst_object_unref (sinkpad);
	 }	
	
 	 gst_caps_unref (caps);
}
//Error
static void error_cb (GstBus *bus, GstMessage *msg,Playdata *data) 
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
static void state_changed_cb (GstBus *bus, GstMessage *msg,Playdata *data)
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
					refresh_ui (data);
}
//EOS
static void eos_cb (GstBus *bus, GstMessage *msg, Playdata *data) 
{
	  g_print ("End-Of-Stream reached.\n");
	  gst_element_set_state (data->pipeline, GST_STATE_READY);
}
//GUI
static void create_gui (Playdata *data) 
{
	GtkWidget *main_window;
	GtkWidget *play_button,*pause_button,*stop_button,*forward_seek_button ,*backward_seek_button,*folder_button,*zoom_in_button,
	*zoom_out_button,*previous_button;
	GtkWidget *video_window; 
	GtkWidget *main_box;     
  	GtkWidget *main_hbox,*folder;
  	GtkWidget *controls_UP,*controls_DW;    
	
  	main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(main_window), "button-press-event",G_CALLBACK(Win_Mouse_cb), data);

	g_signal_connect (G_OBJECT (main_window), "delete-event", G_CALLBACK (delete_event_cb), data);
	gtk_window_set_title(GTK_WINDOW(main_window), "Votary_Player");
  	video_window = gtk_drawing_area_new ();
	
	gtk_widget_set_double_buffered (video_window, FALSE);
  	g_signal_connect (video_window, "realize", G_CALLBACK (realize_cb), data);
 	

	myCSS();//casecade style sheet function it is scripting language

	folder_button = gtk_button_new_from_icon_name ("folder", GTK_ICON_SIZE_SMALL_TOOLBAR);
	g_signal_connect (G_OBJECT (folder_button), "clicked", G_CALLBACK (folder_cb), data);
	
	previous_button =gtk_button_new_from_icon_name ("edit-undo", GTK_ICON_SIZE_SMALL_TOOLBAR);//go-previous
	g_signal_connect (G_OBJECT (previous_button), "clicked", G_CALLBACK (previous_cb), data);

	play_button =gtk_button_new_from_icon_name ("media-playback-start", GTK_ICON_SIZE_SMALL_TOOLBAR);//go-previous
	g_signal_connect (G_OBJECT (play_button), "clicked", G_CALLBACK (play_cb), data);
	
    	stop_button = gtk_button_new_from_icon_name ("media-playback-stop", GTK_ICON_SIZE_SMALL_TOOLBAR);
  	g_signal_connect (G_OBJECT (stop_button), "clicked", G_CALLBACK (stop_cb), data);

  	pause_button = gtk_button_new_from_icon_name ("media-playback-pause", GTK_ICON_SIZE_SMALL_TOOLBAR);//input-mouse media-playback-pause
  	g_signal_connect (G_OBJECT (pause_button), "clicked", G_CALLBACK (pause_cb), data);
 	
	forward_seek_button = gtk_button_new_from_icon_name ("media-seek-forward", GTK_ICON_SIZE_SMALL_TOOLBAR);
  	g_signal_connect (G_OBJECT (forward_seek_button), "clicked", G_CALLBACK (forward_seek_cb), data);

	backward_seek_button= gtk_button_new_from_icon_name ("media-seek-backward", GTK_ICON_SIZE_SMALL_TOOLBAR);
  	g_signal_connect (G_OBJECT (backward_seek_button), "clicked", G_CALLBACK (backward_seek_cb), data);

	data->slider = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 100,1);//slider start , end and step
	gtk_scale_set_draw_value (GTK_SCALE (data->slider), 0);
	data->slider_update_signal_id = g_signal_connect (G_OBJECT (data->slider), "value-changed", G_CALLBACK (slider_cb), data);

	gtk_widget_set_name(folder_button, "myButton_IndianRed");
   	gtk_widget_set_name(play_button, "myButton_green");//CSS stands for Cascading Style Sheets
   	gtk_widget_set_name(pause_button, "myButton_blue");
	gtk_widget_set_name(stop_button, "myButton_DarkMagenta");
   	gtk_widget_set_name(forward_seek_button, "myButton_red");
	gtk_widget_set_name(backward_seek_button, "myButton_red");
	gtk_widget_set_name(pause_button, "myButton_yellow");
	gtk_widget_set_name(data->slider, "myButton_CornflowerBlue");//myButton_DarkMagenta
	
	controls_DW = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);//HORIZONTAL ,VERTICAL reflects buttons container
  	gtk_box_pack_start (GTK_BOX (controls_DW), play_button, FALSE, FALSE, 2);
  	gtk_box_pack_start (GTK_BOX (controls_DW), pause_button, FALSE, FALSE,2);//2,4,5..-space b//w buttons
  	gtk_box_pack_start (GTK_BOX (controls_DW), stop_button, FALSE, FALSE, 2);//icons display on terminal proper order what we want
	gtk_box_pack_start (GTK_BOX (controls_DW), backward_seek_button, FALSE, TRUE, 2);
	gtk_box_pack_start (GTK_BOX (controls_DW), forward_seek_button, FALSE, FALSE, 2);//if both True button size is increased horizontally
  	gtk_box_pack_start (GTK_BOX (controls_DW), data->slider, TRUE, TRUE, 2);
	
	controls_UP = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  	gtk_box_pack_start (GTK_BOX (controls_UP), folder_button, FALSE, FALSE, 2);
	gtk_box_pack_start (GTK_BOX (controls_UP), previous_button, FALSE, FALSE,2);
  	
  	main_hbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  	gtk_box_pack_start (GTK_BOX (main_hbox), video_window, TRUE, TRUE, 0);//PACKING GSTREAMER AND GUI WINDOW
  	
  	main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (main_box), controls_UP, FALSE, FALSE, 0);//
  	gtk_box_pack_start (GTK_BOX (main_box), main_hbox, TRUE, TRUE, 0);
  	gtk_box_pack_start (GTK_BOX (main_box), controls_DW, FALSE, FALSE, 0);//PACKING USER HANDLE OPTIONS IN THE WINDOW

  	//adding gstreamer sink window and gui window
	gtk_window_set_default_size (GTK_WINDOW (main_window), w, h);
	gtk_container_set_border_width (GTK_CONTAINER (main_window), 8);
	gtk_window_set_resizable (GTK_WINDOW(main_window), TRUE);
	gtk_container_add (GTK_CONTAINER (main_window), main_box);


  	gtk_widget_show_all (main_window);
}


//CSS////////////////////
void myCSS(void)
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}
//Play
static void play_cb (GtkButton *button, Playdata *data) 
{
	gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
}
//Pause
static void pause_cb (GtkButton *button, Playdata *data) 
{
  	gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
}
//Stop
static void stop_cb (GtkButton *button, Playdata *data)
{
 	gst_element_set_state (data->pipeline, GST_STATE_READY);

}
//delete
static void delete_event_cb (GtkWidget *widget, GdkEvent *event, Playdata *data) 
{
  stop_cb (NULL, data);
  gtk_main_quit ();
}

//Forward
static void forward_seek_cb (GtkRange *range, Playdata *data)
{ 
	gst_element_query_duration (data->pipeline, GST_FORMAT_TIME, &data->duration);
	gst_element_query_position (data->pipeline, GST_FORMAT_TIME, &data->current);	

    
    	data->position = data->current+(data->duration * 5.0 / 100.0);
 	
  	gst_element_seek_simple (data->pipeline, GST_FORMAT_TIME,GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH, data->position);
  	

	 
}
//Backward
static void backward_seek_cb (GtkRange *range, Playdata *data)
{ 
	gst_element_query_duration (data->pipeline, GST_FORMAT_TIME, &data->duration);
	gst_element_query_position (data->pipeline, GST_FORMAT_TIME, &data->current);	
  	
    
    	data->position = data->current-(data->duration * 5 / 100);//error:::'seek_pos >= 0' failed

 	if(data->position>=0)
  		gst_element_seek_simple (data->pipeline, GST_FORMAT_TIME,GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH, data->position);
  	

	 
}
//Slider
static void slider_cb (GtkRange *range, Playdata *data) 
{
  	gdouble value = gtk_range_get_value (GTK_RANGE (data->slider));
  	gst_element_seek_simple (data->pipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT,(gint64)(value * GST_SECOND));
	 
   
}
//window acts as button(Play and Pause)
static gboolean Win_Mouse_cb(GtkWidget* widget,GdkEventButton *event, Playdata *data)
{

    if (event->type == GDK_BUTTON_PRESS) 
    {
      		if( (event->button == 1) &&(data->state==GST_STATE_PLAYING))
	  			gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
		else
				gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
    }
  
    return TRUE;
}
//folder
static void folder_cb(GtkButton *button, Playdata *data) 
{
	GtkWidget *dialog; 
	static char *filename=NULL,*uri=NULL;
	gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
	dialog = gtk_file_chooser_dialog_new("Open File",NULL, GTK_FILE_CHOOSER_ACTION_OPEN,"_Cancel", GTK_RESPONSE_CANCEL,"_Open", 				GTK_RESPONSE_ACCEPT,NULL);

	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) 
	{
		if(i!=2)
			filename1=filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		g_message("File selected: %s", filename);
		data->duration = GST_CLOCK_TIME_NONE;
		gst_element_set_state (data->pipeline, GST_STATE_READY);//
		filename = gst_filename_to_uri (filename, NULL);
	 	gst_discoverer_discover_uri_async (data->discoverer,filename);//metadata info

		g_object_set (G_OBJECT (data->decodebinn), "uri",filename, NULL);//set source property
		gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
		filename2=filename;

	}

	gtk_widget_destroy (dialog);

}
//Previous
static void previous_cb(GtkButton *button, Playdata *data) 
{

	static char *filename,*uri=NULL;
	if((filename1!=NULL)&&(filename2!=NULL))
	{	
		if(i==0){
			filename=filename1;
			i=2;
		}
		else
		{
			filename=filename2;
			i=0;
		}
		g_message("File selected: %s", filename);
		data->duration = GST_CLOCK_TIME_NONE;
		gst_element_set_state (data->pipeline, GST_STATE_READY);//
		gst_discoverer_discover_uri_async (data->discoverer,filename);//metadata info

		g_object_set (G_OBJECT (data->decodebinn), "uri",filename, NULL);//set source property
		gst_element_set_state (data->pipeline, GST_STATE_PLAYING);//

	}
}


//Realize
//Now that we have our window and playbin(pipeline) ready, we need to integrate the two. To integrate, we’ll inform GStreamer to render the video output from playbin into one of our window widgets. By doing this, the video will be embedded into the window. Note that if we didn’t inform GStreamer, it would create its own window since we are using the playbin element.
static void realize_cb (GtkWidget *widget, Playdata *data)
{
  	GdkWindow *window = gtk_widget_get_window (widget);
  	guintptr window_handle;

  	if (!gdk_window_ensure_native (window))
  		  g_error ("Couldn't create native window needed for GstXOverlay!");
	
	window_handle = GDK_WINDOW_XID (window);
  
  	gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (data->Vsink), window_handle);
}

//re-draw
static gboolean draw_cb (GtkWidget *widget, cairo_t *cr, Playdata *data) 
{
 	 if (data->state < GST_STATE_PAUSED) 
  	 {
    		GtkAllocation allocation;

    /* Cairo is a 2D graphics library which we use here to clean the video window.
      It is used by GStreamer for other reasons, so it will always be available to us. */
   		gtk_widget_get_allocation (widget, &allocation);
    		cairo_set_source_rgb (cr, 0, 0, 1);
    		cairo_rectangle (cr, 0, 0, allocation.width, allocation.height);
    		cairo_fill (cr);
  	 }

  	 return FALSE;
}

//Refresh

static gboolean refresh_ui (Playdata *data)
{
  	data->current = -1;

	if (data->state < GST_STATE_PAUSED)
  		  return TRUE;


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
//////////////////////METADATA function definations/////////////////////////////
static void on_discovered_cb (GstDiscoverer *discoverer, GstDiscovererInfo *info, GError *err, Playdata *data) 
{
 	 GstDiscovererResult result;
	 const gchar *uri;
  	 const GstTagList *tags;
  	 GstDiscovererStreamInfo *sinfo;

  	 uri = gst_discoverer_info_get_uri (info);
  	 result = gst_discoverer_info_get_result (info);

   	 switch (result) 
	 {
   		 case GST_DISCOVERER_URI_INVALID:
   		   	g_print ("Invalid URI '%s'\n", uri);
   			break;
    		 case GST_DISCOVERER_ERROR:
      			g_print ("Discoverer error: %s\n", err->message);
      			break;
    		 case GST_DISCOVERER_TIMEOUT:
    			 g_print ("Timeout\n");
    			 break;
    		 case GST_DISCOVERER_BUSY:
    			  g_print ("Busy\n");
    			  break;
    		 case GST_DISCOVERER_MISSING_PLUGINS:
		 {
                         const GstStructure *s;
      			 gchar *str;

    			 s = gst_discoverer_info_get_misc (info);
     			 str = gst_structure_to_string (s);

     			 g_print ("Missing plugins: %s\n", str);
     			 g_free (str);
     			 break;
    		 }
    		 case GST_DISCOVERER_OK:
    			 g_print ("Discovered '%s'\n", uri);
      			 break;
  	  }

  	 if (result != GST_DISCOVERER_OK) {
    		g_printerr ("This URI cannot be played\n");
    		return;
  	  }

 	 sinfo = gst_discoverer_info_get_stream_info (info);
	 if (!sinfo)
	        return;
	 g_print ("\nTopology:\n");
  	 print_topology (sinfo, 1);
  	 g_print ("\n");

  /* If we got no error, show the retrieved information */
  	g_print ("\n\nProperties:");
  	g_print ("\n  Duration: %" GST_TIME_FORMAT "\n", GST_TIME_ARGS (gst_discoverer_info_get_duration (info)));
  	g_print ("  Seekable: %s\n", (gst_discoverer_info_get_seekable (info) ? "yes" : "no"));

  	tags = gst_discoverer_info_get_tags (info);
  	if (tags) {
    		g_print ("  Tags:\n");
    		gst_tag_list_foreach (tags, print_tag_foreach, GINT_TO_POINTER (1));
  	}

  	gst_discoverer_stream_info_unref (sinfo);

 	g_print ("\n");
}

/* Print a tag in a human-readable format (name: value) */
static void print_tag_foreach (const GstTagList *tags, const gchar *tag, gpointer user_data) 
{
 	GValue val = { 0, };
  	gchar *str;
  	gint depth = GPOINTER_TO_INT (user_data);

  	gst_tag_list_copy_value (&val, tags, tag);

  	if (G_VALUE_HOLDS_STRING (&val))
   	 	str = g_value_dup_string (&val);
  	else
    		str = gst_value_serialize (&val);

  	g_print ("\t%*s%s: %s\n", 2 * depth, " ", gst_tag_get_nick (tag), str);
  	g_free (str);

  	g_value_unset (&val);
}

/* Print information regarding a stream */
static void print_stream_info (GstDiscovererStreamInfo *info, gint depth) 
{
  	gchar *desc = NULL;
 	GstCaps *caps;
 	const GstTagList *tags;

  	caps = gst_discoverer_stream_info_get_caps (info);

  	if (caps) {
    		if (gst_caps_is_fixed (caps))
      			desc = gst_pb_utils_get_codec_description (caps);
    		else
      			desc = gst_caps_to_string (caps);
    		gst_caps_unref (caps);
  	}

  	g_print ("%*s%s: %s\n", 2 * depth, " ", gst_discoverer_stream_info_get_stream_type_nick (info), (desc ? desc : ""));

  	if (desc) {
  		  g_free (desc);
    		  desc = NULL;
  	}
}

/* Print information regarding a stream and its substreams, if any */
static void print_topology (GstDiscovererStreamInfo *info, gint depth) 
{
 	GstDiscovererStreamInfo *next;

  	if (!info)
    		return;

  	print_stream_info (info, depth);//audio,video related info

  	next = gst_discoverer_stream_info_get_next (info);
  	if (next) {
    		print_topology (next, depth + 1);
    		gst_discoverer_stream_info_unref (next);
  	} 
	else if (GST_IS_DISCOVERER_CONTAINER_INFO (info)) {
		
		GList *tmp, *streams;
		streams = gst_discoverer_container_info_get_streams (GST_DISCOVERER_CONTAINER_INFO (info));
		for (tmp = streams; tmp; tmp = tmp->next) {
      			GstDiscovererStreamInfo *tmpinf = (GstDiscovererStreamInfo *) tmp->data;
      			print_topology (tmpinf, depth + 1);
    		}
    		gst_discoverer_stream_info_list_free (streams);
  	}
}
///////////////////print the current position and end position of playback function
static gboolean cb_print_position (Playdata *data) 
{
 // gint64 pos, len;
	g_print("hello\n");
    if (gst_element_query_position (data->pipeline, GST_FORMAT_TIME, &data->current) && gst_element_query_duration (data->pipeline, GST_FORMAT_TIME, &data->duration))
    {
     	 g_print ("Time: %" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r", GST_TIME_ARGS (data->current), GST_TIME_ARGS (data->duration));
    }
  return TRUE;
}


  
