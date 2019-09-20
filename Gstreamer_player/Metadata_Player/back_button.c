
//Previous

#include"header.h"

void previous_cb(GtkButton *button, Playdata *data) 
{
	g_print("i======================%d\n",i);
	static char *filename,*uri=NULL;
	if((filename1!=NULL)&&(filename2!=NULL))
	{	
		if(i==0){
			filename=filename1;i=1;
			}
		else{
			filename=filename2;i=0;}
		
		 uri=gst_filename_to_uri (filename,NULL);
       		 g_printf("\n\n\n\n\n\n\n");
		 g_message("File selected: %s", filename);
        	 g_message("File selected:1 %s", filename1);
        	 g_message("File selected:2 %s", filename2);
		 data->duration = GST_CLOCK_TIME_NONE;
		 gst_element_set_state (data->pipeline, GST_STATE_READY);//
		 gst_discoverer_discover_uri_async (data->discoverer,uri);//metadata info
  		 g_object_set (G_OBJECT (data->source), "location",filename, NULL);//set source property
		 gst_element_set_state (data->pipeline, GST_STATE_PLAYING);//
		
	}
}
