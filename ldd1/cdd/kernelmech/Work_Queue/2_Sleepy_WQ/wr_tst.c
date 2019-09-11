/*
 * wr_tst.c
 * Test the "sleepy" demo driver (slpy.c)
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define FLGS		O_RDWR
#define DMODE		0
#define SZ		1024

int main(int argc, char **argv)
{
	int fd;
	size_t n;
	char buf[SZ];

	if( argc==1 ) {
		fprintf(stderr,"Usage: %s device_file\n", argv[0]);
		exit(1);
	}

	if( (fd=open(argv[1],FLGS,DMODE)) == -1)
		perror("open"),exit(1);

	for(n=0;n<SZ;n++) buf[n] = '\0';
	// test writing..
	n=write(fd,buf,1024);
	if( n == -1 ) { perror("write failed");close(fd);exit(1);}

	printf("sleepy:: wrote %d bytes\n",n);
    close(fd);
	exit(0);       
}

// end wr_tst.c
