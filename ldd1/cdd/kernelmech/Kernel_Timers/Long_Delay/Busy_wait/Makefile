obj-m += busy_wait.o

all:
	make -C /lib/modules/`uname -r`/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/`uname -r`/build M=$(shell pwd) clean
