all:=player
player: main.o create_gui.o on_pad_added.o bus_message.o Mycss.o play_pause_stop_delete.o forward_seek.o \
	backward_seek.o refresh.o silder.o win_mouse.o file_select_folder.o back_button.o relize.o win_draw.o
	gcc main.o create_gui.o on_pad_added.o bus_message.o Mycss.o play_pause_stop_delete.o forward_seek.o		       		backward_seek.o	refresh.o silder.o win_mouse.o file_select_folder.o back_button.o relize.o win_draw.o -o player `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0`

main.o:main.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c main.c 

on_pad_added.o:on_pad_added.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c  on_pad_added.c 

bus_message.o:bus_message.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c bus_message.c 
create_gui.o:create_gui.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c create_gui.c 
Mycss.o : Mycss.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c Mycss.c 
play_pause_stop_delete.o:play_pause_stop_delete.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c  play_pause_stop_delete.c 
forward_seek.o:forward_seek.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c forward_seek.c 
backward_seek.o:backward_seek.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c backward_seek.c 
silder.o:silder.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c silder.c 
win_mouse.o:win_mouse.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c win_mouse.c 
file_select_folder.o:file_select_folder.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c file_select_folder.c 
back_button.o:back_button.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c back_button.c 
relize.o:relize.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c relize.c 
win_draw.o:win_draw.c
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c win_draw.c
refresh.o:refresh.c        
	gcc `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -c refresh.c 
clean:
	rm -rf *.o *.c~ *.h~ Makefile~ player mystyle.css~
