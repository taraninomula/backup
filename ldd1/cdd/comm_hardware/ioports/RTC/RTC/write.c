/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page   : www.facebook.com/kernelmasters                   *
 *                                                                         *
 *  Conducting Workshops on - Embedded Linux & Device Drivers Training.    *
 *  -------------------------------------------------------------------    *
 *  Tel : 91-9949062828, Email : kernelmasters@gmail.com                   *
 *                                                                         *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation. No warranty is attached; we cannot take *
 *   responsibility for errors or fitness for use.                         *
 ***************************************************************************/
/* This program shows how to access clock using our driver
*/

# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
main(){
	int fd,i;
	unsigned char data;
	fd = open("/dev/clock",O_RDWR,0777);
	if(fd < 0){
		perror("clock:");
		exit(1);
	}
	data =0x04;
	for(i=0;i<6;i++){
		write(fd,&data,1);
		printf(" .... %x....\n",data);
	}
}			
