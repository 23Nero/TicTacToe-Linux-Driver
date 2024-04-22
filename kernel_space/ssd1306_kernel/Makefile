# Định đường dẫn đến thư mục chứa kernel và toolchain
BBB_KERNEL := /home/kequing/BBB/kernelbuildscripts/KERNEL
TOOLCHAIN := /home/kequing/BBB/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

# CFLAGS bổ sung
EXTRA_CFLAGS=-Wall
obj-m := ssd1306_driver_kernel.o
ssd1306_driver_kernel-objs = ssd1306_lib.o ssd1306_kernel.o

all:
	make ARCH=arm CROSS_COMPILE=$(TOOLCHAIN) -C $(BBB_KERNEL) M=$(shell pwd) modules
	
clean:
	make -C $(BBB_KERNEL) M=$(shell pwd) clean