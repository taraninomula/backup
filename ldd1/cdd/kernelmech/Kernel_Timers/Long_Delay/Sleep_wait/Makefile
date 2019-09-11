obj-m += sleep_wait.o

all:
	make -C /lib/modules/`uname -r`/build M=$(shell pwd) modules
	#make -C /usr/src/linux M=$(shell pwd) modules
clean:
	#make -C /usr/src/linux M=$(shell pwd) clean
	make -C /lib/modules/`uname -r`/build M=$(shell pwd) clean
