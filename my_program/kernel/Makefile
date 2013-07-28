TARGET=hello

obj-m := hello.o 
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd) 

modules: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules 

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

install: modules_install

clean:
	find . -name "*.o" -o -name "*.ko" -o -name ".*.o.cmd" -o \
                -name "*.mod.*" -o -name "*.symvers" -o -name "*.order" | xargs rm -f

