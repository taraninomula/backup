
//re-draw
#include"header.h"
 gboolean draw_cb (GtkWidget *widget, cairo_t *cr, Playdata *data) 
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
