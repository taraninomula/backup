/* File: fbs.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
//#include <asm/page.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
/* Device Name like /dev/fb */
char *fbname;
/* handle to fb device */
int FrameBufferFD;
/* fixed screen information */
struct fb_fix_screeninfo fix_info;
/* configurable screen info */
struct fb_var_screeninfo var_info;
/* The frame buffer memory pointer */
void *framebuffer;
/* function to plot pixel at position (x,y) */
void draw_pixel(int x,int y, u_int32_t pixel);
int main(int argc, char *argv[])
{
int size;
u_int8_t red, green, blue;
int x, y;
u_int32_t pixel;
fbname = "/dev/fb0";
/* Open the framebuffer device in read write */
FrameBufferFD = open(fbname, O_RDWR);
if (FrameBufferFD < 0) {
printf("Unable to open %s.\n", fbname);
return 1;
}
/* Do Ioctl. Retrieve fixed screen info. */
if (ioctl(FrameBufferFD, FBIOGET_FSCREENINFO, &fix_info) < 0) {
printf("get fixed screen info failed: %s\n",
strerror(errno));
close(FrameBufferFD);
return 1;
}
/* Do Ioctl. Get the variable screen info. */
if (ioctl(FrameBufferFD, FBIOGET_VSCREENINFO, &var_info) < 0) {
printf("Unable to retrieve variable screen info: %s\n",
strerror(errno));
close(FrameBufferFD);
return 1;
}
/* Print some screen info currently available */
printf("Screen resolution: (%dx%d)\n",
var_info.xres,var_info.yres);
printf("Line width in bytes %d\n", fix_info.line_length);
printf("bits per pixel : %d\n", var_info.bits_per_pixel);
printf("Red: length %d bits, offset %d\n",
var_info.red.length,var_info.red.offset);
printf("Green: length %d bits, offset %d\n",
var_info.red.length, var_info.green.offset);
printf("Blue: length %d bits, offset %d\n",
var_info.red.length,var_info.blue.offset);
/* Calculate the size to mmap */
size=fix_info.line_length * var_info.yres;
/* Now mmap the framebuffer. */
framebuffer = mmap(NULL, size, PROT_READ | PROT_WRITE,
MAP_SHARED, FrameBufferFD,0);
if (framebuffer == NULL) {
printf("mmap failed:\n");
close(FrameBufferFD);
return 1;
}
printf("framebuffer mmap address=%p\n", framebuffer);
printf("framebuffer size=%d bytes\n", size);
/* The program will work only on TRUECOLOR */
if (fix_info.visual == FB_VISUAL_TRUECOLOR) {
/* White pixel ? maximum red, green & blue values */
/* Max 8 bit value = 0xFF */
red = 0xFF;
green = 0xFF;
blue = 0xFF;
/*
* Now pack the pixel based on the rgb bit offset.
* We compute each color value based on bit length
* and shift it to its corresponding offset in the pixel.
*
* For example: Considering a RGB565, the formula will
* expand as:-
* Red len=5, off=11 : Green len=6, off=6 : Blue len=5, off=0
* pixel_value = ((0xFF >> (8 - 5) << 11)|
*
((0xFF >> (8 - 6) << 6) |
*
((0xFF >> (8 - 5) << 0) = 0xFFFF // White
*/
pixel =
((red >> (8-var_info.red.length)) <<
var_info.red.offset) |
((green >> (8-var_info.green.length)) <<
var_info.green.offset) |
((blue >>(8-var_info.blue.length)) <<
var_info.blue.offset);
}else {
printf("Unsupported Mode.\n");
return 1;

}

printf ("pixel: %x\n",pixel);
/* Obtain center of the screen */
x = var_info.xres/2  + var_info.xoffset;
y = var_info.yres/2  + var_info.yoffset;
pixel=0xFFFFFF;
printf ("x: %d y: %d \n",x,y );
/* Plot the pixel at x,y */
draw_pixel(x,y, pixel);
/* Release mmap. */
munmap(framebuffer,0);
close(FrameBufferFD);
return 0;
}
void draw_pixel(int x, int y, u_int32_t pixel)
{
/*
* Based on bits per pixel we assign the pixel_value to the
* framebuffer pointer. Recollect the matrix indexing method
* described for the linear framebuffer.
* pixel(x,y)=(line_width * y) + x.
*/
switch (var_info.bits_per_pixel) {
case 8:
*((u_int8_t *)framebuffer + fix_info.line_length * y +x) =
(u_int8_t)pixel;
break;
case 16:
*((u_int16_t *)framebuffer + fix_info.line_length/2 *y +x) =
(u_int16_t)pixel;
break;
case 32:
*((u_int32_t *)framebuffer + fix_info.line_length/4*y +x) =
(u_int32_t)pixel;
break;
default:
printf("Unknown depth.\n");
}
}

