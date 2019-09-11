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
//#include <process.h>

struct sub {
	int a;
	int b;
};
struct sub subtest;

int main()
{	
	int fd, result;
	//char  ubuff[80]="hai hello world", kbuff[80];
	subtest.a = 35;
	subtest.b = 5;
	fd = open ("/dev/sub", O_RDWR , 0777 ) ;
	if (fd <0 )
	{	
		perror ("open:%s") ;
		exit (-1 ) ;
	}
	if(write ( fd, &subtest, sizeof ( struct sub ) ) < 0)
		perror("write") ;
	sleep (1);
	if(read ( fd, &result, 4 ) < 0)
		perror("read") ;
	printf ("\n Kernel Data: %d\n", result);
	close(fd);
	return 0 ;
}


