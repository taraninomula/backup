obj-m := ioctl.o


KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)


default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
#	$(MAKE) IOCTL_Application
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a

