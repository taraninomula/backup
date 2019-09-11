
obj-m :=clock.o
KDIR= /lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	insmod clock.ko

clean:
	rm -rf *.o *.ko *.mod.* .c* .t* Module.symvers
	rmmod clock

