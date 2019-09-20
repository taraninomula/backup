#include"header.h"
int main(int argc, char *argv[])
{
	GMainLoop *loop;
  	GstBus *bus;
	GstStateChangeReturn ret;
	Playdata data;
	GError *err = NULL;
	gchar *uri;
  	gst_init(&argc,&argv);//initize the gstreamer library
	gtk_init(&argc,&argv);//initize the gstreamer library

	/*if(argc==3)
		w=atoi(argv[2]);//char to integer convertion
	if(argc==4)
		h=atoi(argv[3]);*/

	loop = g_main_loop_new (NULL, FALSE);
	memset (&data, 0, sizeof (data));
	data.duration = GST_CLOCK_TIME_NONE;

	/* Create gstreamer elements */
  	data.pipeline = gst_pipeline_new ("Video-Audio-VT-Player");
  	data.source   = gst_element_factory_make ("filesrc","file-source");
  
 	data.decodebinn  = gst_element_factory_make ("decodebin","decoderr");
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

 	 gst_bin_add_many (GST_BIN (data.pipeline),data.source,data.decodebinn,data.videoqueue, data.Vconv,data.Vsink,data.audioqueue, 		 			data.Aconv , data.Asink, data.Are_sa, NULL);//add ele in bin

	 gst_element_link (data.source, data.decodebinn);
  	 gst_element_link_many (data.videoqueue,data.Vconv, data.Vsink, NULL);
  	 gst_element_link_many (data.audioqueue, data.Aconv,data.Are_sa, data.Asink, NULL);

   	 g_signal_connect (data.decodebinn, "pad-added", G_CALLBACK(on_pad_added),&data);//link pads

	 if(argc>=2){
		uri=gst_filename_to_uri (argv[1],NULL);
  		g_object_set (G_OBJECT (data.source), "location", argv[1], NULL);//set source property
	 }
	 else{
		uri="file:///home/kakanhar/Pictures/sample.png";//
		g_object_set (G_OBJECT (data.source), "location","/home/kakanhar/Pictures/sample.png", NULL);
	 }

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
