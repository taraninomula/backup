#include"header.h"
//GUI
/*
#include<gst/gst.h>
#include <glib.h>
#include<gtk/gtk.h>
#include<string.h>
#include <gdk/gdkx.h>//linux platform supported library
#include <gst/video/videooverlay.h>//**/
 void create_gui (Playdata *data) 
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
 	//g_signal_connect (video_window, "draw", G_CALLBACK (draw_cb), data);

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
	gtk_window_set_default_size (GTK_WINDOW (main_window), 720, 540);
	gtk_container_set_border_width (GTK_CONTAINER (main_window), 8);
	gtk_window_set_resizable (GTK_WINDOW(main_window), TRUE);
	gtk_container_add (GTK_CONTAINER (main_window), main_box);


  	gtk_widget_show_all (main_window);
}


