/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page	: www.facebook.com/kernelmasters                   *
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

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int fd, count;
        char buff="12345";
	fd = open("/dev/MyChar", O_RDWR);
	printf("fd:%d\n", fd);
       
        count = write(fd,buff,2);
	printf("count:%d\n", count);
        
	count = read(fd,buff,2);
	printf("count:%d\n", count);
         
}
