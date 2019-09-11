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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct mul {
	int a;
	int b;
};
struct mul multest;

int main()
{	
	int fd, result;
	//char  ubuff[80]="hai hello world", kbuff[80];
	multest.a = 35;
	multest.b = 5;
	fd = open ("/dev/MyCharDevice2", O_RDWR , 0777 ) ;
	if (fd <0 )
	{	
		perror ("open:%s") ;
		exit (-1 ) ;
	}
	if(write ( fd, &multest, sizeof ( struct mul ) ) < 0)
		perror("write") ;
	sleep (3);
	if(read ( fd, &result, 4 ) < 0)
		perror("read") ;
	printf ("\n Kernel Data: %d", result);
	close(fd);
	return 0 ;
}


