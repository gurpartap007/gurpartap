INSTALLDIR= $(shell pwd)/modules
ifneq ($(KERNELRELEASE),)
obj-m := gill.o
gill-objs := initial.o cleanup.o scull_open.o scull_write.o scull_read.o scull_release.o

else
	KERNDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules
	@rm -rf $(INSTALLDIR)
	@mkdir $(INSTALLDIR)
	@mv *.ko *.mod.c *.o .*.cmd $(INSTALLDIR)

clean:
	rm -rf $(INSTALLDIR)

endif

