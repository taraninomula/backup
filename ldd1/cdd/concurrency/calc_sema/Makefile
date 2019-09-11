obj-m :=CalculatorDriver.o

KERNELDIR=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm Add Sub Mul Div
Application:
	$(MAKE) Add
	$(MAKE) Sub
	$(MAKE) Mul
	$(MAKE) Div
