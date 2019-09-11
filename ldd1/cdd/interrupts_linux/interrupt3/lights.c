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
#include <unistd.h></p>
int main() {
  unsigned char byte,dummy;
  FILE * PARLELPORT;
  /* Opening the device parlelport */
  PARLELPORT=fopen("/dev/parlelport","w");
  /* We remove the buffer from the file i/o */
  setvbuf(PARLELPORT,&dummy,_IONBF,1);
  /* Initializing the variable to one */
  byte=1;
  /* We make an infinite loop */
  while (1) {
    /* Writing to the parallel port */
    /* to turn on a LED */
    printf("Byte value is %d\n",byte);
    fwrite(&byte,1,1,PARLELPORT);
    sleep(1);
    /* Updating the byte value */
    byte<<=1;
    if (byte == 0) byte = 1;
  }
  fclose(PARLELPORT);
}



