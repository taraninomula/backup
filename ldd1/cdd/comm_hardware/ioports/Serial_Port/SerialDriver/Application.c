/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page   : www.facebook.com/kernelmasters                   *
 *                                                                         *
 *  Conducting Workshops on - Embedded Linux & Device Drivers Training.    *
 *  -------------------------------------------------------------------    *
 *  Tel : 91-9949062828, Email : kernelmasters@gmail.com                   *
 *  Website: www.kernelmasters.org                                                                         *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation. No warranty is attached; we cannot take *
 *   responsibility for errors or fitness for use.                         *
 ***************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{
	int FileDesc,i;
	
        FileDesc=open("/dev/serial",O_RDWR,0777);
	char k[]={"this is the first program in serial port"};
        if(FileDesc <0)
	{
		perror("\nError Opening Device\n");	
		exit(1);
	}

	for(i=0;i<50;i++)
        write(FileDesc,&k[i],1);


//ead(FileDesc,Kbuff,sizeof(Ubuff));

	printf("\n\n\n chaacter k send to minicom via serail port\n\n\n");


        sleep(30);

	close(FileDesc);
}
