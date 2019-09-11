obj-m := parlelport.o


KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)


default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

install:
	arm-linux-gcc -C $(KERNELDIR) M=$(PWD) modules_intall



