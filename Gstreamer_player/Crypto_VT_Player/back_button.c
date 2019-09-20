
//Previous

#include"header.h"

 void previous_cb(GtkButton *button, Playdata *data) 
{

	static char *filename;
	if((filename1!=NULL)&&(filename2!=NULL))
	{	
		if(i==0){
			filename=filename1;i=1;
			}
		else{
			filename=filename2;i=0;}
			
		 g_message("File selected: %s", filename);
		 data->duration = GST_CLOCK_TIME_NONE;
		 gst_element_set_state (data->pipeline, GST_STATE_READY);//
	
  		 g_object_set (G_OBJECT (data->source), "location",filename, NULL);//set source property
		 gst_element_set_state (data->pipeline, GST_STATE_PLAYING);//
	
	}
}
