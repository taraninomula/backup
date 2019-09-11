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
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <asm/ioctl.h>
#include "ioctl.h"
int main()
{
	int FileDesc, Result, BAUD_RATE = 9600, STP_BITS = 8;
	char Ubuff[]="THis is the User Buffer......Sending Data to the Kernel....";
	char Kbuff[100];	
	FileDesc=open("/dev/ioctl",O_RDWR,0777);
	if(FileDesc <0)
	{
		printf("\nError Opening Device\n");	
		exit(1);
	}
	Result = ioctl (FileDesc, SET_BAUD_RATE, BAUD_RATE);
	if (Result < 0) {
		printf ("\n IOCTL Error");
		return (-1);
	}
	ioctl (FileDesc, SET_NO_STOP_BITS, STP_BITS);
	ioctl (FileDesc, SET_DIRECTION_WRITE, NULL);
	
	write(FileDesc,Ubuff,sizeof(Ubuff));
	read(FileDesc,Kbuff,sizeof(Ubuff));
	printf("\n The Data read from the Kernel is\n>>>> %s <<<<\n",Kbuff);
	close(FileDesc);
}
