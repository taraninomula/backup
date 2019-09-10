#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<linux/input.h>
#include<fcntl.h>
#include <string.h>
int fd;
int main()
{
	fd_set read_fileset,testfd;
        int fd1,fd2, retfd;
        int buf;
        int val,ret,value;
        char buff[4099];
        fd1=open("/dev/input/event5",O_RDONLY);
        if(fd1<0)
                printf("error while open the file event1\n");
        fd2=open("/dev/input/event2",O_RDONLY);
        if(fd2<0)
                printf("error while open the file event2\n");
        while(1) {
        /* initially makes as zero files */
        FD_ZERO(&read_fileset);

        /* add our file discriptors */
        FD_SET(fd1,&read_fileset);
        FD_SET(fd2,&read_fileset);

        testfd=read_fileset;
        retfd=select(FD_SETSIZE,&testfd,NULL,NULL,0);
        printf ("retfd:%d\n",retfd);
        if(retfd<0){
                printf("select is failed\n");
                return -1;
                }
        /* Keyboard data event0  */
        if(FD_ISSET(fd1,&testfd))
                {
                printf("keyboard working fine\n");
                input_read(fd1);
		printf("keyboard exit\n");
                }
        if(FD_ISSET(fd2,&testfd))
                {
                printf("usb mouse working fine\n");
		input_read(fd2);
		printf("usb keypad exit\n");
                }
	}
}

int input_read(int fd)
{
printf("keyboard read fun");
       
int rd, i, j, k;
struct input_event ev[64];

char *events[EV_MAX + 1] = {
[EV_MSC] = "Misc",[EV_KEY] = "Key",
};
char *keys[KEY_MAX + 1] = {
[KEY_A] = "A",
        [KEY_F1] = "F1",
        [KEY_F2] = "F2",                        [KEY_F3] = "F3",
        [KEY_F4] = "F4",                        [KEY_F5] = "F5",
        [KEY_F6] = "F6",           
        [KEY_F7] = "F7",
        [KEY_F8] = "F8",                        [KEY_F9] = "F9",
        [KEY_F10] = "F10",
};
char *relatives[REL_MAX + 1] = {
        [REL_MISC] = "Misc",
};
char *misc[MSC_MAX + 1] = {
        [MSC_RAW] = "RawData",
        [MSC_SCAN] = "ScanCode",
};

char **names[EV_MAX + 1] = {
[EV_KEY] = keys,
        [EV_SYN] = events,
        [EV_MSC] = misc,
};
		printf("fd --> %d \n",fd);

            rd = read(fd, ev, sizeof(struct input_event) * 64);

                if (rd < (int) sizeof(struct input_event)) {
                        printf("yyy\n");
                        perror("\nevtest: error reading");
                        return 1;
                }

                for (i = 0; i < rd / sizeof(struct input_event); i++)

                        if (ev[i].type == EV_SYN) {
                                printf("Event: time %ld.%06ld, -------------- %s ------------\n",
                                        ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].code ? "Config Sync" : "Report Sync" );
                        } else if (ev[i].type == EV_MSC && (ev[i].code == MSC_RAW || ev[i].code == MSC_SCAN)) {
                                printf("Event: time %ld.%06ld, type %d (%s), code %d (%s), value %02x\n",
                                        ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,
                                        events[ev[i].type] ? events[ev[i].type] : "?",
                                        ev[i].code,
                                        names[ev[i].type] ? (names[ev[i].type][ev[i].code] ? names[ev[i].type][ev[i].code] : "?") : "?",
                                        ev[i].value);
                        } else {
                                printf("Event: time %ld.%06ld, type %d (%s), code %d (%s), value %d\n",
                                        ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,
                                        events[ev[i].type] ? events[ev[i].type] : "?",
                                        ev[i].code,
                                        names[ev[i].type] ? (names[ev[i].type][ev[i].code] ? names[ev[i].type][ev[i].code] : "?") : "?",
                                        ev[i].value);
                        }


}


