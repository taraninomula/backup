#include"header.h"
//window acts as button(Play and Pause)
 gboolean Win_Mouse_cb(GtkWidget* widget,GdkEventButton *event, Playdata *data)
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
