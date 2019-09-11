/*************************************************************************\
*                  Copyright (C) Arun Kumar Sahu, 2018.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Program for Printing child values synchronously using semaphores */

#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/fcntl.h>
#include<sys/stat.h>
int main()
{
	sem_t *sem1,*sem2,*sem3;
	pid_t pid1,pid2,pid3,pid0;
	int i=0;
	/* Three semaphores for #3 Children */

	sem1=sem_open("pSem1",O_CREAT|O_EXCL,0666,1);
	sem2=sem_open("pSem2",O_CREAT|O_EXCL,0666,0);
	sem3=sem_open("pSem3",O_CREAT|O_EXCL,0666,0);

	/* Unlink prevents semaphores to exist forever */
	sem_unlink("pSem1");
	sem_unlink("pSem2");
	sem_unlink("pSem3");

	/* Parent creates 3 child process to execute 1,2,3 */
	pid1=fork();
	if(pid1!=0){
		pid2=fork();
		if(pid1!=0 && pid2 !=0)
			pid3=fork();
	}

	/* Print the value of childs in 10 iterations */
	while(i++<10){
		if(pid1==0){
			sem_wait(sem1);
			printf("1");
			usleep(1);
			sem_post(sem2);
		}
		if(pid2==0){
			sem_wait(sem2);
			printf("2");
			usleep(1);
			sem_post(sem3);
		}
		if(pid3==0){
			sem_wait(sem3);
			printf("3\n");
			usleep(1);
			sem_post(sem1);
		}
	}

}
