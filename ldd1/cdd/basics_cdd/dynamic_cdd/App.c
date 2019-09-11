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

int main()
{	
	int fd ;
	char  ubuff[100]="hai hello world";
	
	fd = open ("/dev/CharDriver", O_WRONLY , 0777 ) ;
	if (fd <0 )
	{	
		perror ("open:%s") ;
		exit (-1 ) ;
	}
	write ( fd, ubuff, sizeof ( ubuff ) );
		//perror("write") ;
	close(fd);
	return 0 ;
}


