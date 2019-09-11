obj-m := panic.o

all:
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` modules
clean:
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` clean
install:
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` modules_install
