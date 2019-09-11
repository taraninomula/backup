# Makefile for 2.6 kernel cz driver
# This Makefile idiom from the Rubini & Corbet (LDD3) book.

ifneq ($(KERNELRELEASE),)
obj-m       := slpy_wq.o
EXTRA_CFLAGS += -DDEBUG

else
KDIR        := /lib/modules/$(shell uname -r)/build
PWD         := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
endif

clean:
	rm -f *.o *.ko Modules.symver* *~ *.mod.c
