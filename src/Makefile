CC=/usr/local/toolchain/gcc/bin/i686-pc-elf-gcc
CFLAGS= -Iinclude -c -W -Wno-long-long -nostdlib -nostdinc -fno-builtin -fno-stack-protector -fomit-frame-pointer
LD=/usr/local/toolchain/gcc/bin/i686-pc-elf-ld

DIR_BIN=../bin
DIR_INCLUDE=include
DIR_BOOT=boot
DIR_IRQ=irq

IMAGE = ~/myos/myos.img
BOOT_IMAGE = $(DIR_BIN)/boot/boot.o
LOADER_OBJ = $(DIR_BIN)/boot/load.o
KERNEL_IMAGE = $(DIR_BIN)/kernel.bin

SOURCES = $(wildcard *.s ) $(wildcard *.c )\
		  $(wildcard $(DIR_IRQ)/*.s) $(wildcard $(DIR_IRQ)/*.c)

OBJECTS = $(patsubst %.s, $(DIR_BIN)/%.o,$(filter %.s, $(SOURCES)))\
		  $(patsubst %.c, $(DIR_BIN)/%.o,$(filter %.c, $(SOURCES))) 

HEADERS = $(wildcard $(DIR_INCLUDE)/*.h)

$(IMAGE): $(BOOT_IMAGE) $(KERNEL_IMAGE)
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$(KERNEL_IMAGE) of=$@ oseek=1 bs=512 conv=notrunc
	dd if=$(BOOT_IMAGE) of=$@ bs=512 count=1 conv=notrunc

#依赖关系啊依赖关系 SHIIIIIIIIIIIIIIIIIIIIIIIIIT
#bin/kernel.bin:  bin/load.o bin/isr.o bin/isr_c.o  bin/kmain.o
$(KERNEL_IMAGE): $(LOADER_OBJ) $(OBJECTS)
	$(LD) -e load --oformat binary -Ttext 0x1000 -s -N -o $@ $^

$(DIR_BIN)/%.o: %.c	$(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

$(DIR_BIN)/%.o: %.s
	nasm -f elf -o $@ $^

$(BOOT_IMAGE): $(DIR_BOOT)/boot.s
	nasm -o $@ $^


.PHONY : clean
clean:
	-rm $(DIR_BIN)/*
	-rm $(DIR_BIN)/$(DIR_BOOT)/*
	-rm $(DIR_BIN)/$(DIR_IRQ)/*

